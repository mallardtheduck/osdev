#include <btos_module.h>
#include <dev/mouse.h>
#include <dev/keyboard.h>
#include "console_backend.hpp"
#include "vterm.hpp"
#include "device.hpp"

console_backend *cons_backend;
const char* video_device_name="DISPLAY_DEVICE";
const char* input_device_name="INPUT_DEVICE";
const char* pointer_device_name="POINTER_DEVICE";

uint32_t abs32(int32_t i){
	if(i>0) return i;
	else return -i;
}

uint32_t msb32(uint32_t x)
{
	static const unsigned int bval[] = {0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4};

	unsigned int r = 0;
	if (x & 0xFFFF0000) { r += 16/1; x >>= 16/1; }
	if (x & 0x0000FF00) { r += 16/2; x >>= 16/2; }
	if (x & 0x000000F0) { r += 16/4; x >>= 16/4; }
	return r + bval[x];
}

void console_backend_input_thread(void *p){
	console_backend *backend=(console_backend*)p;
	API->CurrentThread().SetPriority(2);
	while(true){
		uint32_t key=0;
		size_t read = backend->input->Read(sizeof(key), (char*)&key);
		if(read){
			auto hl = backend->backend_lock->LockExclusive();
			if(backend->active) {
				vterm *term = terminals->get(backend->active);
				uint16_t keycode = (uint16_t)key;
				if(backend->global_shortcuts.has_key(keycode)){
					uint64_t termid = backend->global_shortcuts[keycode];
					backend->backend_lock->Release();
					backend->switch_terminal(termid);
					backend->backend_lock->TakeExclusive();
				}else if (term) {
					backend->backend_lock->Release();
					term->queue_input(key);
					backend->backend_lock->TakeExclusive();
				}
			}
		}
	}
}
void console_backend_pointer_thread(void *p){
	console_backend *backend=(console_backend*)p;
	API->CurrentThread().SetPriority(2);
	while(true){
		bt_mouse_packet packet;
		size_t read = backend->pointer->Read(sizeof(packet), (char*)&packet);
		if(read){
			auto hl = backend->backend_lock->LockExclusive();
			packet.y_motion=-packet.y_motion;
			packet.x_motion*= msb32(abs32(packet.x_motion));
			packet.y_motion*= msb32(abs32(packet.y_motion));
			uint32_t oldx=backend->pointer_info.x;
			backend->pointer_info.x += (packet.x_motion * backend->pointer_speed);
			if(packet.x_motion > 0 && backend->pointer_info.x < oldx) backend->pointer_info.x=0xFFFFFFFF;
			if(packet.x_motion < 0 && backend->pointer_info.x > oldx) backend->pointer_info.x=0;
			uint32_t oldy=backend->pointer_info.y;
			backend->pointer_info.y += (packet.y_motion * backend->pointer_speed);
			if(packet.y_motion > 0 && backend->pointer_info.y < oldy) backend->pointer_info.y=0xFFFFFFFF;
			if(packet.y_motion < 0 && backend->pointer_info.y > oldy) backend->pointer_info.y=0;
			uint16_t oldflags=backend->pointer_info.flags;
			backend->pointer_info.flags=packet.flags;
			backend->update_pointer();
			vterm *term=terminals->get(backend->active);
			bt_vidmode mode;
			backend->display->IOCtl(bt_vid_ioctl::QueryMode, sizeof(mode), (char*)&mode);
			uint32_t xscale=(0xFFFFFFFF/(mode.width-1));
			uint32_t yscale=(0xFFFFFFFF/(mode.height-1));
			uint32_t x=(backend->pointer_info.x/xscale);
			uint32_t y=(backend->pointer_info.y/yscale);
			if(packet.x_motion || packet.y_motion){
				bt_terminal_pointer_event event;
				event.type=bt_terminal_pointer_event_type::Move;
				event.x=x;
				event.y=y;
				event.button=0;
				event.button=0;
				if(term) term->queue_pointer(event);
			}
			if(packet.flags != oldflags){
				bt_terminal_pointer_event event;
				event.x=x;
				event.y=y;
				event.button=0;
				uint16_t diff=0;
				if(packet.flags > oldflags){
					event.type=bt_terminal_pointer_event_type::ButtonDown;
					diff=packet.flags - oldflags;
				}else{
					event.type=bt_terminal_pointer_event_type::ButtonUp;
					diff=oldflags - packet.flags;
				}
				if(diff == MouseFlags::Button1) event.button=1;
				if(diff == MouseFlags::Button2) event.button=2;
				if(diff == MouseFlags::Button3) event.button=3;
				if(term && event.button) term->queue_pointer(event);
			}
		}
	}
}
void console_backend_pointer_draw_thread(void *p){
	API->CurrentThread().SetPriority(1000);
	console_backend *backend=(console_backend*)p;
	while(true){
		if(backend->pointer_cur_serial == backend->pointer_draw_serial){
			API->CurrentThread().SetBlock([&]{
				return (!backend->frozen && backend->pointer_cur_serial != backend->pointer_draw_serial);
			});
		}
		backend->pointer_cur_serial = backend->pointer_draw_serial;
		{
			auto hl = backend->backend_lock->LockExclusive();
			if(backend->pointer_info.x != backend->old_pointer_info.x || backend->pointer_info.y != backend->old_pointer_info.y || backend->pointer_visible != backend->old_pointer_visible){
				bt_vidmode mode;
				backend->display->IOCtl(bt_vid_ioctl::QueryMode, sizeof(mode), (char*)&mode);
				uint32_t xscale=(0xFFFFFFFF/(mode.width-1));
				uint32_t yscale=(0xFFFFFFFF/(mode.height-1));
				uint32_t oldx=backend->old_pointer_info.x/xscale;
				uint32_t oldy=backend->old_pointer_info.y/yscale;
				uint32_t newx=backend->pointer_info.x/xscale;
				uint32_t newy=backend->pointer_info.y/yscale;
				if(oldx != newx || oldy != newy || backend->pointer_visible != backend->old_pointer_visible) {
					backend->draw_pointer(oldx, oldy, true);
					if(backend->pointer_visible) backend->draw_pointer(newx, newy, false);
				}
				backend->cur_pointer_x=newx;
				backend->cur_pointer_y=newy;
			}
			backend->old_pointer_info=backend->pointer_info;
			backend->old_pointer_visible=backend->pointer_visible;
		}
	}
}

void console_backend::update_pointer(){
	++pointer_draw_serial;
}

void console_backend::draw_pointer(uint32_t x, uint32_t y, bool erase) {
	auto hl = backend_lock->LockRecursive();
	bt_vidmode mode;
	display->IOCtl(bt_vid_ioctl::QueryMode, sizeof(mode), (char*)&mode);
	if(mode.textmode){
		size_t pos=(((y * mode.width) + x) * 2) + 1;
		size_t cpos = display->Seek(0, fs_seek_flags::FS_Relative);
		display->Seek(pos, fs_seek_flags::FS_Set);
		if(erase) {
			if(mouseback) {
				display->Write(1, (char*)mouseback);
				free(mouseback);
				mouseback=nullptr;
			}
		} else {
			if(mouseback) delete mouseback;
			mouseback=new uint8_t();
			display->Read(1, (char*)mouseback);
			display->Seek(pos, fs_seek_flags::FS_Set);
			uint8_t cursor=*mouseback ^ 0xFF;
			display->Write(1, (char*)&cursor);
		}
		display->Seek(cpos, fs_seek_flags::FS_Set);
	}else{
		if(erase){
			if(mouseback) {
				draw_graphics_pointer(display, x, y, pointer_bitmap, mouseback);
				free(mouseback);
				mouseback = nullptr;
			}
		}else {
			if(mouseback) free(mouseback);
			mouseback= get_graphics_pointer_background(display, x, y, pointer_bitmap);
			draw_graphics_pointer(display, x, y, pointer_bitmap);
		}
	}
}

console_backend::console_backend() {
	backend_lock = API->NewLock();
	pointer_visible=false;
	pointer_bitmap=nullptr;
	pointer_info.x=0; pointer_info.y=0; pointer_info.flags=0;
	mouseback=nullptr;
	pointer_draw_serial=0;
	pointer_cur_serial=0;
	autohide = true;
	frozen = false;

	char video_device_path[BT_MAX_PATH]="DEV:/";
	char input_device_path[BT_MAX_PATH]="DEV:/";
	char pointer_device_path[BT_MAX_PATH]="DEV:/";

	strncpy(video_device_path+5, (char*)CurrentProcess().GetEnvironmentVariable((char*)video_device_name, 0), BT_MAX_PATH-5);
	strncpy(input_device_path+5, (char*)CurrentProcess().GetEnvironmentVariable((char*)input_device_name, 0), BT_MAX_PATH-5);
	strncpy(pointer_device_path+5, (char*)CurrentProcess().GetEnvironmentVariable((char*)pointer_device_name, 0), BT_MAX_PATH-5);

	auto displayNode = API->GetVirtualFilesystem().GetNode(video_device_path);
	if(displayNode) display = displayNode->OpenFile(FS_Read | FS_Write);
	if(!displayNode || !display) panic("(TERMINAL) Could not open display device!");
	auto inputNode = API->GetVirtualFilesystem().GetNode(input_device_path);
	if(inputNode) input = inputNode->OpenFile(FS_Read);
	if(!inputNode || !input) panic("(TERMINAL) Could not open input device!");
	auto pointerNode = API->GetVirtualFilesystem().GetNode(pointer_device_path);
	if(pointerNode) pointer = pointerNode->OpenFile(FS_Read);
	if(!pointerNode || !pointer) panic("(TERMINAL) Could not open pointing device!");

	input_thread_id = API->GetScheduler().NewThread(&console_backend_input_thread, (void*)this);
	pointer_thread_id = API->GetScheduler().NewThread(&console_backend_pointer_thread, (void*)this);
	pointer_draw_thread_id = API->GetScheduler().NewThread(&console_backend_pointer_draw_thread, (void*)this);
}

size_t console_backend::display_read(size_t bytes, char *buf) {
	auto hl = backend_lock->LockExclusive();
	bool pointer=pointer_visible;
	if(autohide) hide_pointer();
	size_t ret = display->Read(bytes, buf);
	if(pointer) show_pointer();
	return ret;
}

size_t console_backend::display_write(size_t bytes, const char *buf) {
	auto hl = backend_lock->LockExclusive();
	bool pointer=pointer_visible;
	if(autohide) hide_pointer();
	size_t ret = display->Write(bytes, buf);
	if(pointer) show_pointer();
	return ret;
}

size_t console_backend::display_seek(size_t pos, uint32_t flags) {
	auto hl = backend_lock->LockExclusive();
	return display->Seek(pos, flags);
}

size_t console_backend::input_read(size_t bytes, char *buf) {
	return input->Read(bytes, buf);
}

size_t console_backend::input_write(size_t bytes, const char *buf) {
	return input->Write(bytes, buf);
}

size_t console_backend::input_seek(size_t pos, uint32_t flags) {
	return input->Seek(pos, flags);
}

void console_backend::show_pointer() {
	pointer->IOCtl(bt_mouse_ioctl::ClearBuffer, 0, nullptr);
	pointer_visible=true;
	update_pointer();
}

void console_backend::hide_pointer() {
	auto hl = backend_lock->LockRecursive();
	if(old_pointer_visible){
		draw_pointer(cur_pointer_x, cur_pointer_y, true);
		old_pointer_visible = false;
	}
	pointer_visible=false;
	update_pointer();
}

bool console_backend::get_pointer_visibility() {
	return pointer_visible;
}

void console_backend::set_pointer_bitmap(bt_terminal_pointer_bitmap *bmp) {
	auto hl = backend_lock->LockExclusive();
	bool pointer=pointer_visible;
	hide_pointer();
	if(pointer_bitmap) free(pointer_bitmap);
	pointer_bitmap = nullptr;
	if(!bmp) return;
	size_t totalsize=sizeof(bt_terminal_pointer_bitmap) + bmp->datasize;
	pointer_bitmap = (bt_terminal_pointer_bitmap*)malloc(totalsize);
	memcpy(pointer_bitmap, bmp, totalsize);
	if(pointer) show_pointer();
}

bt_terminal_pointer_info console_backend::get_pointer_info(){
	bt_vidmode mode;
	display->IOCtl(bt_vid_ioctl::QueryMode, sizeof(mode), (char*)&mode);
	uint32_t xscale=(0xFFFFFFFF/(mode.width-1));
	uint32_t yscale=(0xFFFFFFFF/(mode.height-1));
	uint32_t x=(pointer_info.x/xscale);
	uint32_t y=(pointer_info.y/yscale);
	bt_terminal_pointer_info ret=pointer_info;
	ret.x=x; ret.y=y;
	return ret;
}

void console_backend::set_pointer_autohide(bool val){
	autohide = val;
}

void console_backend::freeze_pointer(){
	frozen = true;
}

void console_backend::unfreeze_pointer(){
	frozen = false;
	if(pointer_draw_serial != pointer_cur_serial) API->CurrentThread().Yield();
}

bool console_backend::is_active(uint64_t id) {
	return active==id;
}

void console_backend::set_active(uint64_t id) {
	active=id;
}

void console_backend::open(uint64_t /*id*/){
}

void console_backend::close(uint64_t id){
	if(is_active(id)){
		dbgpf("TERM: Active terminal closed, activating new terminal..\n");
		//TODO: Make this work with multiple backends!
		vterm *term=terminals->get(0);
		if(!term){
			uint64_t new_id=terminals->create_terminal(this);
			term=terminals->get(new_id);
		}
		dbgpf("TERM: Activating terminal %i\n", (int)term->get_id());
		term->activate();
	}
	bool found = false;
	do{
		for(auto i = global_shortcuts.begin(); i!=global_shortcuts.end(); ++i){
			if(i->second == id){
				global_shortcuts.erase(i);
				found = true;
				break;
			}
		}
	}while(found);
}

size_t console_backend::get_screen_mode_count(){
	return display->IOCtl(bt_vid_ioctl::GetModeCount, 0, nullptr);
}

bt_vidmode console_backend::get_screen_mode(size_t index){
	bt_vidmode ret;
	*(size_t*)&ret = index;
	display->IOCtl(bt_vid_ioctl::GetMode, sizeof(ret), (char*)&ret);
	return ret;
}

void console_backend::set_screen_mode(const bt_vidmode &mode){
	display->IOCtl(bt_vid_ioctl::SetMode, sizeof(mode), (char*)&mode);
}

bt_vidmode console_backend::get_current_screen_mode(){
	bt_vidmode ret;
	display->IOCtl(bt_vid_ioctl::QueryMode, sizeof(ret), (char*)&ret);
	return ret;
}

bt_video_palette_entry console_backend::get_palette_entry(uint8_t entry){
	bt_video_palette_entry ret;
	*(uint8_t*)&ret = entry;
	display->IOCtl(bt_vid_ioctl::GetPaletteEntry, sizeof(ret), (char*)&ret);
	return ret;
}

void console_backend::clear_screen(){
	display->IOCtl(bt_vid_ioctl::ClearScreen, 0, nullptr);
}

void console_backend::set_cursor_position(size_t pos){
	display->IOCtl(bt_vid_ioctl::SetCursorPosition, sizeof(pos), (char*)&pos);
}

void console_backend::register_global_shortcut(uint16_t keycode, uint64_t termid){
	global_shortcuts[keycode] = termid;
}

void console_backend::switch_terminal(uint64_t id){
	vterm *target = terminals->get(id);
	vterm *current = terminals->get(active);
	if(target && target->get_backend() == this){
		if(current) current->deactivate();
		target->activate();
	}
}

bool console_backend::can_create(){
	return true;
}

void console_backend::refresh(){
}

uint32_t console_backend::get_pointer_speed(){
	return pointer_speed;
}

void console_backend::set_pointer_speed(uint32_t speed){
	pointer_speed = speed;
}

const char *console_backend::desc(){
	return "console";
}