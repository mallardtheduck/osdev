#include "mouse.h"
#include "keyboard.h"
#include "console_backend.hpp"
#include "vterm.hpp"
#include "module_stubs.h"
#include "holdlock.hpp"
#include "device.hpp"

console_backend *cons_backend;
const char* video_device_name="DISPLAY_DEVICE";
const char* input_device_name="INPUT_DEVICE";
const char* pointer_device_name="POINTER_DEVICE";

const uint32_t pointer_speed=300000;

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

static uint64_t create_terminal(char *command) {
    uint64_t new_id=terminals->create_terminal(cons_backend);
    terminals->get(new_id)->sync(false);
    if(command){
        char old_terminal_id[128]="0";
        strncpy(old_terminal_id, getenv(terminal_var, getpid()), 128);
        char new_terminal_id[128]={0};
        i64toa(new_id, new_terminal_id, 10);
        setenv(terminal_var, new_terminal_id, 0, getpid());
        pid_t pid=spawn(command, 0, NULL);
        setenv(terminal_var, old_terminal_id, 0, getpid());
        if(!pid) terminals->get(new_id)->close();
    }
    return new_id;
}

static uint64_t switcher_term=0;

void console_backend_input_thread(void *p){
    console_backend *backend=(console_backend*)p;
    thread_priority(2);
    while(true){
        uint32_t key=0;
        size_t read=fread(backend->input, sizeof(key), (char*)&key);
        if(read){
            hold_lock hl(&backend->backend_lock);
            if(backend->active) {
                vterm *term=terminals->get(backend->active);
                if ((key & KeyFlags::NonASCII) && (key & KeyFlags::Control) && (key & KeyCodes::Escape)==KeyCodes::Escape && !(key & KeyFlags::KeyUp)) {
                    release_lock(&backend->backend_lock);
                    terminals->switch_terminal(switcher_term);
                    take_lock(&backend->backend_lock);
                }else if (term) {
                    release_lock(&backend->backend_lock);
                    term->queue_input(key);
                    take_lock(&backend->backend_lock);
                }
            }
        }
    }
}
void console_backend_pointer_thread(void *p){
    console_backend *backend=(console_backend*)p;
    thread_priority(2);
    while(true){
        bt_mouse_packet packet;
        size_t read=fread(backend->pointer, sizeof(packet), (char*)&packet);
        if(read){
            hold_lock hl(&backend->backend_lock);
            packet.y_motion=-packet.y_motion;
            packet.x_motion*= msb32(abs32(packet.x_motion));
            packet.y_motion*= msb32(abs32(packet.y_motion));
            uint32_t oldx=backend->pointer_info.x;
            backend->pointer_info.x+=(packet.x_motion * pointer_speed);
            if(packet.x_motion > 0 && backend->pointer_info.x < oldx) backend->pointer_info.x=0xFFFFFFFF;
            if(packet.x_motion < 0 && backend->pointer_info.x > oldx) backend->pointer_info.x=0;
            uint32_t oldy=backend->pointer_info.y;
            backend->pointer_info.y+=(packet.y_motion * pointer_speed);
            if(packet.y_motion > 0 && backend->pointer_info.y < oldy) backend->pointer_info.y=0xFFFFFFFF;
            if(packet.y_motion < 0 && backend->pointer_info.y > oldy) backend->pointer_info.y=0;
            uint16_t oldflags=backend->pointer_info.flags;
            backend->pointer_info.flags=packet.flags;
            backend->update_pointer();
            vterm *term=terminals->get(backend->active);
            bt_vidmode mode;
            fioctl(backend->display, bt_vid_ioctl::QueryMode, sizeof(mode), (char*)&mode);
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

bool pointer_draw_blockcheck(void *p){
	uint32_t **params = (uint32_t**)p;
	return *params[0] != *params[1];
}

void console_backend_pointer_draw_thread(void *p){
	console_backend *backend=(console_backend*)p;
	uint32_t &serial = backend->pointer_cur_serial;
	while(true){
		uint32_t *bc_params[2] = {&serial, &backend->pointer_draw_serial};
		thread_setblock(&pointer_draw_blockcheck, (void*)bc_params);
		serial = backend->pointer_draw_serial;
		{
			hold_lock hl(&backend->backend_lock, true);
			if(backend->pointer_info.x != backend->old_pointer_info.x || backend->pointer_info.y != backend->old_pointer_info.y || backend->pointer_visible != backend->old_pointer_visible){
				bt_vidmode mode;
				fioctl(backend->display, bt_vid_ioctl::QueryMode, sizeof(mode), (char*)&mode);
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
    hold_lock hl(&backend_lock, false);
    bt_vidmode mode;
    fioctl(display, bt_vid_ioctl::QueryMode, sizeof(mode), (char*)&mode);
    if(mode.textmode){
        size_t pos=(((y * mode.width) + x) * 2) + 1;
        size_t cpos=fseek(display, 0, true);
        bt_vid_text_access_mode::Enum omode=(bt_vid_text_access_mode::Enum) fioctl(display, bt_vid_ioctl::GetTextAccessMode, 0, NULL);
        bt_vid_text_access_mode::Enum nmode=bt_vid_text_access_mode::Raw;
        fioctl(display, bt_vid_ioctl::SetTextAccessMode, sizeof(nmode), (char*)&nmode);
        fseek(display, pos, false);
        if(erase) {
            if(mouseback) {
                fwrite(display, 1, (char*)mouseback);
                free(mouseback);
                mouseback=NULL;
            }
        } else {
            if(mouseback) delete mouseback;
            mouseback=new uint8_t();
            fread(display, 1, (char*)mouseback);
            fseek(display, pos, false);
            uint8_t cursor=*mouseback ^ 0xFF;
            fwrite(display, 1, (char*)&cursor);
        }
        fioctl(display, bt_vid_ioctl::SetTextAccessMode, sizeof(omode), (char*)&omode);
        fseek(display, cpos, false);
    }else{
        if(erase){
            if(mouseback) {
                draw_graphics_pointer(display, x, y, pointer_bitmap, mouseback);
                free(mouseback);
                mouseback = NULL;
            }
        }else {
            if(mouseback) free(mouseback);
            mouseback= get_graphics_pointer_background(display, x, y, pointer_bitmap);
            draw_graphics_pointer(display, x, y, pointer_bitmap);
        }
    }
}

console_backend::console_backend() {
    init_lock(&backend_lock);
    pointer_visible=false;
    pointer_bitmap=NULL;
    pointer_info.x=0; pointer_info.y=0; pointer_info.flags=0;
    mouseback=NULL;
	pointer_draw_serial=0;
	pointer_cur_serial=0;

    char video_device_path[BT_MAX_PATH]="DEV:/";
    char input_device_path[BT_MAX_PATH]="DEV:/";
    char pointer_device_path[BT_MAX_PATH]="DEV:/";

    strncpy(video_device_path+5, (char*)getenv((char*)video_device_name, 0), BT_MAX_PATH-5);
    strncpy(input_device_path+5, (char*)getenv((char*)input_device_name, 0), BT_MAX_PATH-5);
    strncpy(pointer_device_path+5, (char*)getenv((char*)pointer_device_name, 0), BT_MAX_PATH-5);

    display=fopen(video_device_path, (fs_mode_flags)(FS_Read | FS_Write));
    if(!display->valid) panic("(TERMINAL) Could not open display device!");
    input=fopen(input_device_path, (fs_mode_flags)(FS_Read));
    if(!input->valid) panic("(TERMINAL) Could not open input device!");
    pointer=fopen(pointer_device_path, (fs_mode_flags)(FS_Read));
    if(!pointer->valid) panic("(TERMINAL) Could not open pointing device!");

    input_thread_id=new_thread(&console_backend_input_thread, (void*)this);
    pointer_thread_id=new_thread(&console_backend_pointer_thread, (void*)this);
	pointer_draw_thread_id=new_thread(&console_backend_pointer_draw_thread, (void*)this);
}

void console_backend::start_switcher(){
    switcher_term=create_terminal("HDD:/BTOS/SWITCHER.ELX");
}

size_t console_backend::display_read(size_t bytes, char *buf) {
    hold_lock hl(&backend_lock);
    bool pointer=pointer_visible;
    hide_pointer();
    size_t ret=fread(display, bytes, buf);
    if(pointer)show_pointer();
    return ret;
}

size_t console_backend::display_write(size_t bytes, char *buf) {
    hold_lock hl(&backend_lock);
    bool pointer=pointer_visible;
    hide_pointer();
    size_t ret=fwrite(display, bytes, buf);
    if(pointer)show_pointer();
    return ret;
}

size_t console_backend::display_seek(size_t pos, uint32_t flags) {
    return fseek(display, pos, flags);
}

int console_backend::display_ioctl(int fn, size_t bytes, char *buf) {
    hold_lock hl(&backend_lock);
    bool pointer=pointer_visible;
    hide_pointer();
    int ret=fioctl(display, fn, bytes, buf);
    if(pointer)show_pointer();
    return ret;
}

size_t console_backend::input_read(size_t bytes, char *buf) {
    return fread(input, bytes, buf);
}

size_t console_backend::input_write(size_t bytes, char *buf) {
    return fwrite(input, bytes, buf);
}

size_t console_backend::input_seek(size_t pos, uint32_t flags) {
    return fseek(input, pos, flags);
}

int console_backend::input_ioctl(int fn, size_t bytes, char *buf) {
    return fioctl(input, fn, bytes, buf);
}

bt_terminal_pointer_info console_backend::pointer_read(){
    bt_terminal_pointer_info ret;
    return ret;
}

void console_backend::show_pointer() {
    fioctl(pointer, bt_mouse_ioctl::ClearBuffer, 0, NULL);
    pointer_visible=true;
    update_pointer();
}

void console_backend::hide_pointer() {
	hold_lock hl(&backend_lock, false);
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
    hold_lock hl(&backend_lock);
    bool pointer=pointer_visible;
    hide_pointer();
    if(pointer_bitmap) free(pointer_bitmap);
    pointer_bitmap=NULL;
    if(!bmp) return;
    size_t totalsize=sizeof(bt_terminal_pointer_bitmap) + bmp->datasize;
    pointer_bitmap = (bt_terminal_pointer_bitmap*)malloc(totalsize);
    memcpy(pointer_bitmap, bmp, totalsize);
    if(pointer) show_pointer();
}

bt_terminal_pointer_info console_backend::get_pointer_info(){
    bt_vidmode mode;
    fioctl(display, bt_vid_ioctl::QueryMode, sizeof(mode), (char*)&mode);
    uint32_t xscale=(0xFFFFFFFF/(mode.width-1));
    uint32_t yscale=(0xFFFFFFFF/(mode.height-1));
    uint32_t x=(pointer_info.x/xscale);
    uint32_t y=(pointer_info.y/yscale);
    bt_terminal_pointer_info ret=pointer_info;
    ret.x=x; ret.y=y;
    return ret;
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
}
