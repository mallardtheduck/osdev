#include <btos_module.h>
#include <dev/keyboard.h>
#include <util/holdlock.hpp>
#include "vterm.hpp"
#include "terminal.hpp"
#include "device.hpp"

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

//vterm *current_vterm=NULL;
vterm_list *terminals=NULL;

bool event_blockcheck(void *p);

size_t strlen(const char *str){
	size_t len;
    for (len = 0; str[len]; (len)++);
	return len;
}

vterm::vterm(uint64_t nid, i_backend *back)
{
	backend=back;
	id=nid;
	buffer=NULL;
	bufsize=0;
	bufpos=0;
	scrolling=true;
	infoline=true;
	textcolour=0x07;
	echo=true;
	init_lock(&term_lock);
	init_lock(&input_lock);
	keyboard_buffer.clear();
	pointer_buffer.clear();
	refcount=0;
	scrollcount=0;
	sprintf(title, "BT/OS Terminal %i", (int)id);
	pointer_enabled=false;
	pointer_autohide = true;
	pointer_bitmap=NULL;
	curpid = 0;
	events_pid = 0;
	event_mode = bt_terminal_event_mode::None;
	event_mode_enabled = false;
	last_move_message = 0;
	pointer_speed = back->get_pointer_speed();
	if(backend) backend->open(nid);
}

vterm::~vterm()
{
	if(backend) backend->close(id);
	if(buffer) free(buffer);
}

void vterm::putchar(char c)
{
	if(!vidmode.textmode) return;
	if(c == '\n') {
		bufpos=(((bufpos/(vidmode.width*2))+1) * (vidmode.width*2));
		if(backend && backend->is_active(id)) backend->display_write(1, &c);
	} else if(c == 0x08) {
		if(bufpos >= 2) {
			bufpos -= 2;
			buffer[bufpos++] = ' ';
			buffer[bufpos++] = textcolour;
			bufpos -= 2;
		}
		if(backend && backend->is_active(id)) {
			size_t cpos = backend->display_seek(0, true);
			cpos--;
			backend->display_seek(cpos, false);
			char s = ' ';
			backend->display_write(1, &s);
			backend->display_seek(cpos, false);
		}
	} else {
		buffer[bufpos++]=(uint8_t)c;
		buffer[bufpos++]=textcolour;
		if(backend && backend->is_active(id)) backend->display_write(1, &c);
	}
	if(bufpos>=bufsize) {
		scroll();
	}
}

void vterm::putstring(char *s)
{
	for(size_t i=0; i<strlen(s); ++i) {
		putchar(s[i]);
	}
}

void vterm::setcolours(uint8_t c)
{
	textcolour=c;
	if(backend && backend->is_active(id)) backend->set_text_colours(c);
}

uint8_t vterm::getcolours()
{
	return textcolour;
}

void vterm::scroll()
{
	int factor=1;
	if(vidmode.textmode) factor=2;
	if(scrolling){
		size_t start = infoline ? 1 : 0;
		for(size_t y = start + 1; y<vidmode.height; ++y) {
			for(size_t x=0; x<(vidmode.width*factor); ++x) {
				const size_t source = y * (vidmode.width*factor) + x;
				if(y > start) {
					const size_t dest = (y-1) * (vidmode.width*factor) + x;
					buffer[dest]=buffer[source];
				}
				buffer[source]=0;
				if(vidmode.textmode && source % 2) buffer[source]=textcolour;
			}
		}
	}
	bufpos=((vidmode.height-1)*vidmode.width)*factor;
	scrollcount++;
}

void vterm::do_infoline()
{
	vterm_options opts;
	if(backend && backend->is_active(id) && infoline && vidmode.textmode) {
		size_t pos=seek(opts, 0, true);
		char *infoline_text = (char*)malloc(vidmode.width + 1);
		memset(infoline_text, 0, vidmode.width + 1);
		sprintf(infoline_text, "[%i] %s", (int)id, title);
		for(size_t i = 0; i < vidmode.width; ++i){
			if(infoline_text[i] == 0) infoline_text[i] = ' ';
		}
		seek(opts, 0, false);
		uint16_t linecol=0x1F;
		uint8_t colour=backend->get_text_colours();
		setcolours(linecol);
		putstring(infoline_text);
		setcolours(colour);
		seek(opts, pos, false);
		if(pos < vidmode.width) putchar('\n');
		free(infoline_text);
		//backend->refresh();
	}
}

uint64_t vterm::get_id()
{
	return id;
}

const char *vterm::get_title()
{
	//hold_lock hl(&term_lock);
	return title;
}

void vterm::activate()
{
	hold_lock hl(&term_lock, false);
	bool scroll=false;
	if(backend) {
		backend->set_screen_mode(vidmode);
		backend->set_active(id);
		backend->set_screen_scroll(scroll);
		if(vidmode.textmode) {
			backend->set_text_access_mode(bt_vid_text_access_mode::Raw);
			setcolours(getcolours());
		}
		backend->display_seek(0, false);
		backend->display_write(bufsize, (char*)buffer);
		if(vidmode.textmode) {
			backend->set_text_access_mode(bt_vid_text_access_mode::Simple);
			backend->display_seek(bufpos/2, false);
		} else {
			backend->display_seek(bufpos, false);
		}
		backend->set_screen_scroll(scrolling);
		do_infoline();
		if(infoline && bufpos==0) putchar('\n');
		if(pointer_enabled) {
			if(pointer_bitmap) backend->set_pointer_bitmap(pointer_bitmap);
			backend->show_pointer();
		} else {
			backend->hide_pointer();
		}
		backend->set_pointer_autohide(pointer_autohide);
		backend->set_pointer_speed(pointer_speed);
		backend->refresh();
	}
}

void vterm::deactivate()
{
	if(!backend) return;
	if(!backend->is_active(id)) return;
	backend->set_pointer_autohide(true);
	backend->hide_pointer();
	if(!vidmode.textmode) {
		size_t pos = backend->display_seek(0, true);
		backend->display_seek(0, false);
		backend->display_read(bufsize, (char *) buffer);
		backend->display_seek(pos, false);
	}
}

size_t vterm::write(vterm_options &/*opts*/, size_t size, char *buf)
{
	hold_lock hl(&term_lock);
	update_current_pid();
	bool iline_valid=infoline && vidmode.textmode;
	if(bufpos <= vidmode.width) iline_valid=false;
	if(bufpos+size > bufsize) size = bufsize - bufpos;
	if(vidmode.textmode) {
		uint64_t scount=scrollcount;
		for(size_t i=0; i<size; ++i) putchar(buf[i]);
		if(scount != scrollcount) iline_valid=false;
	} else {
		if(backend && backend->is_active(id)) {
			backend->display_write(size, buf);
		} else {
			memcpy(buffer + bufpos, buf, size);
		}
		bufpos += size;
	}
	if(!iline_valid) do_infoline();
	if(backend && backend->is_active(id)) backend->refresh();
	return size;
}

size_t vterm::read(vterm_options &opts, size_t size, char *buf)
{
	hold_lock hl(&term_lock);
	update_current_pid();
	if(opts.mode == bt_terminal_mode::Terminal) {
		int incr;
		for(size_t i=0; i<size; i+=incr) {
			incr=1;
			uint32_t input = 0;
			char c = 0;
			while(!input || !c) {
				release_lock(&term_lock);
				input=get_input();
				take_lock(&term_lock);
				if((input & KeyFlags::Control) && !(input & KeyFlags::KeyUp) && ((char) input == 'c' || (char) input == 'C')) {
					release_lock(&term_lock);
					kill(getpid());
				}
				c = KB_char(input);
			}
			buf[i] = c;
			if(opts.mode == bt_terminal_mode::Terminal) {
				bool put=true;
				if(c == 0x08) {
					if(i) {
						--i;
						buf[i] = '\0';
					} else put=false;
					incr=0;
				}
				if(c == '\n') {
					uint64_t scount=scrollcount;
					if(echo){
						putchar(c);
						if(backend && backend->is_active(id)) backend->refresh();
					}
					if(scount != scrollcount) do_infoline();
					return i + 1;
				}
				if(echo && put) {
					putchar(c);
					if(backend && backend->is_active(id)) backend->refresh();
				}
			}
		}
		return size;
	} else if(opts.mode == bt_terminal_mode::Video) {
		if(bufpos + size > bufsize) size = bufsize - bufpos;
		if(backend && backend->is_active(id)) {
			backend->display_read(size, buf);
		} else {
			memcpy(buf, buffer + bufpos, size);
		}
		bufpos += size;
		return size;
	}
	return 0;
}

size_t vterm::seek(vterm_options &/*opts*/, size_t pos, uint32_t flags)
{
	hold_lock hl(&term_lock, false);
	update_current_pid();
	int factor=1;
	if(vidmode.textmode) factor=2;
	if(flags & FS_Relative) bufpos+=pos*factor;
	else if(flags & FS_Backwards) {
		bufpos = bufsize - (pos*factor);
	} else if(flags == (FS_Relative | FS_Backwards)) bufpos -= (pos*factor);
	else bufpos=pos*factor;
	if(bufpos>bufsize) bufpos=bufsize;
	if(backend && backend->is_active(id)) {
		backend->display_seek(pos, flags);
	}
	return bufpos/factor;
}

int vterm::ioctl(vterm_options &opts, int fn, size_t size, char *buf)
{
	hold_lock hl(&term_lock);
	update_current_pid();
	switch(fn) {
		case bt_terminal_ioctl::SetTitle:{
			if(buf){
				memset(title, 0, titlemax);
				memcpy(title, buf, size);
				do_infoline();
				if(backend && backend->is_active(id)) backend->refresh();
			}
			break;
		}
		case bt_terminal_ioctl::GetTitle:{
			if(buf){
				strncpy(buf, title, MIN(size, titlemax));
			}
			return strlen(title) + 1;
			break;
		}
		case bt_terminal_ioctl::ClearScreen: {
			clear_buffer();
			seek(opts, 0, false);
			if(backend && backend->is_active(id)) {
				backend->clear_screen();
			}
			if(infoline) {
				putchar('\n');
				do_infoline();
				if(backend && backend->is_active(id)) backend->refresh();
			}
			break;
		}
		case bt_terminal_ioctl::SetEcho: {
			if(size && buf) echo=*(bool*)buf;
			break;
		}
		case bt_terminal_ioctl::GetEcho:{
			if(buf) *(bool*)buf = echo;
			break;
		}
		case bt_terminal_ioctl::SetTerminalMode: {
			if(buf)	opts.mode=*(bt_terminal_mode::Enum*)buf;
			break;
		}
		case bt_terminal_ioctl::GetTerminalMode: {
			if(buf) *(bt_terminal_mode::Enum*)buf = opts.mode;
			break;
		}
		case bt_terminal_ioctl::SetInfoLine:{
			if(buf) infoline = *(bool*)buf;
			break;
		}
		case bt_terminal_ioctl::GetInfoLine:{
			if(buf) *(bool*)buf = infoline;
			break;
		}
		case bt_terminal_ioctl::NewTerminal: {
			create_terminal(buf);
			break;
		}
		case bt_terminal_ioctl::SwitchTerminal: {
			uint64_t sw_id=*(uint64_t*)buf;
			if(backend) backend->switch_terminal(sw_id);
			break;
		}
		case bt_terminal_ioctl::GetScreenModeCount: {
			return backend ? backend->get_screen_mode_count() : 0;
			break;
		}
		case bt_terminal_ioctl::GetScreenMode: {
			if(buf) {
				*(bt_vidmode*)buf = backend ? backend->get_screen_mode(*(size_t*)buf) : bt_vidmode();
				return sizeof(bt_vidmode);
			}
			break;
		}
		case bt_terminal_ioctl::SetScreenMode: {
			if(buf && size==sizeof(bt_vidmode)) {
				if(backend && backend->is_active(id)) {
					backend->set_screen_mode(*(bt_vidmode*)buf);
				}
				vidmode=*(bt_vidmode*)buf;
				allocate_buffer();
				clear_buffer();
				if(vidmode.textmode && infoline) {
					putchar('\n');
					do_infoline();
					if(backend && backend->is_active(id)) backend->refresh();
				}
			}
			break;
		}
		case bt_terminal_ioctl::QueryScreenMode: {
			if(size == sizeof(bt_vidmode)) {
				bt_vidmode *mode = (bt_vidmode *) buf;
				*mode = vidmode;
				return size;
			}
			break;
		}
		case bt_terminal_ioctl::GetPaletteEntry: {
			if(buf){
				*(bt_video_palette_entry*)buf = backend ? backend->get_palette_entry(*(size_t*)buf) : bt_video_palette_entry();
				return sizeof(bt_video_palette_entry);
			}
			break;
		}
		case bt_terminal_ioctl::SetTextColours: {
			if(size==sizeof(uint8_t)) {
				setcolours(*(uint8_t*)buf);
			}
			break;
		}
		case bt_terminal_ioctl::GetTextColours: {
			return getcolours();
			break;
		}
		case bt_terminal_ioctl::GetScrolling: {
			return scrolling;
			break;
		}
		case bt_terminal_ioctl::SetScrolling: {
			if(size==sizeof(bool)) {
				scrolling=*(bool*)buf;
				if(backend && backend->is_active(id)) {
					backend->set_screen_scroll(scrolling);
				}
			}
			break;
		}
		case bt_terminal_ioctl::ShowPointer: {
			if(backend && backend->is_active(id)) backend->show_pointer();
			pointer_enabled=true;
			break;
		}
		case bt_terminal_ioctl::HidePointer: {
			if(backend && backend->is_active(id)) backend->hide_pointer();
			pointer_enabled=false;
			break;
		}
		case bt_terminal_ioctl::GetPointerVisibility:{
			if(buf) *(bool*)buf = pointer_enabled;
			break;
		}
		case bt_terminal_ioctl::GetPointerInfo: {
			if(size==sizeof(bt_terminal_pointer_info)) {
				*(bt_terminal_pointer_info*)buf = backend ? backend->get_pointer_info() : bt_terminal_pointer_info();
			}
			break;
		}
		case bt_terminal_ioctl::StartEventMode: {
			if(!event_mode_enabled) {
				events_pid = getpid();
				opts.event_mode_owner = true;
				event_mode_enabled = true;
			}
			break;
		}
		case bt_terminal_ioctl::EndEventMode: {
			if(event_mode_enabled && opts.event_mode_owner) {
				event_mode_enabled = false;
				opts.event_mode_owner = false;
				event_mode = bt_terminal_event_mode::None;
				events_pid = 0;
			}
			break;
		}
		case bt_terminal_ioctl::SetEventMode: {
			if(event_mode_enabled && opts.event_mode_owner) {
				if(size == sizeof(bt_terminal_event_mode::Enum)) {
					event_mode = *(bt_terminal_event_mode::Enum*)buf;
				}
			}
			break;
		}
		case bt_terminal_ioctl::SetPointerBitmap: {
			if(size > sizeof(bt_terminal_pointer_bitmap)) {
				bt_terminal_pointer_bitmap *bmp=(bt_terminal_pointer_bitmap*)buf;
				if(pointer_bitmap) free(pointer_bitmap);
				pointer_bitmap=NULL;
				size_t totalsize=sizeof(bt_terminal_pointer_bitmap) + bmp->datasize;
				pointer_bitmap=(bt_terminal_pointer_bitmap*) malloc(totalsize);
				memcpy(pointer_bitmap, bmp, totalsize);
				if(backend && backend->is_active(id)) backend->set_pointer_bitmap(pointer_bitmap);
			}
			break;
		}
		case bt_terminal_ioctl::PointerAutoHide: {
			if(size == sizeof(bool)) {
				pointer_autohide = *(bool*)buf;
				if(backend && backend->is_active(id)) backend->set_pointer_autohide(*(bool*)buf);
			}
			break;
		}
		case bt_terminal_ioctl::PointerFreeze: {
			if(backend && backend->is_active(id)) backend->freeze_pointer();
			break;
		}
		case bt_terminal_ioctl::PointerUnfreeze: {
			if(backend && backend->is_active(id)) backend->unfreeze_pointer();
			break;
		}
		case bt_terminal_ioctl::GetPointerSpeed: {
			if(size == sizeof(uint32_t)){
				*(uint32_t*)buf = pointer_speed;
			}
			break;
		}
		case bt_terminal_ioctl::SetPointerSpeed: {
			if(size == sizeof(uint32_t)){
				pointer_speed = *(uint32_t*)buf;
				if(backend && backend->is_active(id)) backend->set_pointer_speed(pointer_speed);
			}
			break;
		}
		case bt_terminal_ioctl::RegisterGlobalShortcut:{ 
			if(buf){
				uint16_t keycode = *(uint16_t*)buf;
				if(backend) backend->register_global_shortcut(keycode, id);
			}
		}
	}
	if(backend && backend->is_active(id)) backend->refresh();
	return 0;
}

struct cmdLine{
	char *cmd;
	size_t argc;
	char **argv;
};

cmdLine parse_cmd(const char *c){
	cmdLine cl = {nullptr, 0, nullptr};
	char* buf = (char*)malloc(BT_MAX_PATH);
	memset(buf, 0, BT_MAX_PATH);
	size_t i = 0;
	bool escape = false;
	bool quote = false;
	while(c && *c){
		if(escape) buf[i] = *c;
		else if(quote && *c != '"') buf[i] = *c;
		else if(*c == '\\') escape = true;
		else if(*c == '"') quote = !quote;
		else if((*c == ' ' && i) || i == BT_MAX_PATH - 1){
			if(!cl.cmd) cl.cmd = buf;
			else{
				char **nargv = (char**)malloc((cl.argc + 1) * sizeof(char*));
				for(size_t j = 0; j < cl.argc; ++j){
					nargv[j] = cl.argv[j];
				}
				nargv[cl.argc] = buf;
				if(cl.argv) free(cl.argv);
				cl.argv = nargv;
				++cl.argc;
			}
			buf = (char*)malloc(BT_MAX_PATH);
			memset(buf, 0, BT_MAX_PATH);
			i = -1;
			escape=quote=false;
		}else{
			buf[i] = *c;
		}
		++i; ++c;
	}
	if(i){
		char **nargv = (char**)malloc((cl.argc + 1) * sizeof(char*));
		for(size_t j = 0; j < cl.argc; ++j){
			nargv[j] = cl.argv[j];
		}
		nargv[cl.argc] = buf;
		if(cl.argv) free(cl.argv);
		cl.argv = nargv;
		++cl.argc;
	}else{
		free(buf);
	}
	dbgpf("CL: %i args: %s - ", (int)cl.argc, cl.cmd);
	for(size_t i = 0; i < cl.argc; ++i){
		dbgpf(" (%p) %s - ", cl.argv[i], cl.argv[i]);
	}
	dbgout("\n");
	return cl;
};

void free_cmd(cmdLine c){
	if(c.cmd) free(c.cmd);
	for(size_t i = 0; i < c.argc; ++i){
		free(c.argv[i]);
	}
	free(c.argv);
}

void vterm::create_terminal(char *command)
{
	uint64_t new_id=terminals->create_terminal(backend);
	if(new_id){
		dbgpf("TERM: Created new terminal %i.\n", (int) new_id);
		terminals->get(new_id)->sync(false);
		if(backend && backend->is_active(id)) backend->switch_terminal(new_id);
		if(command) {
			char old_terminal_id[128]="0";
			strncpy(old_terminal_id, getenv(terminal_var, getpid()), 128);
			char new_terminal_id[128]= {0};
			i64toa(new_id, new_terminal_id, 10);
			setenv(terminal_var, new_terminal_id, 0, getpid());
			cmdLine cmd = parse_cmd(command);
			pid_t pid=spawn(cmd.cmd, cmd.argc, cmd.argv);
			free_cmd(cmd);
			setenv(terminal_var, old_terminal_id, 0, getpid());
			vterm_options opts;
			if(!pid) terminals->get(new_id)->close(opts);
		}
	}
}

uint64_t vterm::send_event(const bt_terminal_event &e)
{
	btos_api::bt_msg_header msg;
	memset((void*)&msg, 0, sizeof(msg));
	bt_terminal_event *content = new bt_terminal_event();
	*content = e;
	msg.to = events_pid;
	msg.source = terminal_extension_id;
	msg.type = bt_terminal_message_type::InputEvent;
	msg.content = content;
	msg.length = sizeof(*content);
	return msg_send(&msg);
}

void vterm::open()
{
	hold_lock hl(&term_lock);
	refcount++;
}

void vterm::close(vterm_options &opts)
{
	take_lock(&term_lock);
	if(event_mode_enabled && opts.event_mode_owner) {
		event_mode_enabled = false;
		events_pid = 0;
		event_mode = bt_terminal_event_mode::None;
	}
	if(refcount) refcount--;
	if(!refcount) {
		if(terminals->get_count() > 1) {
			release_lock(&term_lock);
			terminals->delete_terminal(id);
			return;
		}
	}
	release_lock(&term_lock);
}

void vterm::sync(bool content)
{
	hold_lock hl(&term_lock);
	if(!backend) return;
	vidmode = backend->get_current_screen_mode();
	allocate_buffer();
	if(content) {
		size_t vpos = this->backend->display_seek(0, true);
		this->backend->display_seek(0, false);
		if(this->vidmode.textmode) {
			backend->set_text_access_mode(bt_vid_text_access_mode::Raw);
			backend->set_text_colours(textcolour);
		}
		this->backend->display_read(this->bufsize, (char *) this->buffer);
		if(this->vidmode.textmode) 	backend->set_text_access_mode(bt_vid_text_access_mode::Simple);
		this->backend->display_seek(vpos, false);
		this->bufpos = this->backend->display_seek(0, true);
		if(this->vidmode.textmode) {
			this->bufpos *= 2;
		}
	} else {
		clear_buffer();
	}
	this->scrolling = backend->get_screen_scroll();
}

void vterm::clear_buffer()
{
	memset(buffer, 0, bufsize);
	if(vidmode.textmode) {
		for(size_t i = 1; i < bufsize; i += 2) {
			buffer[i] = textcolour;
		}
	}
	bufpos = 0;
}

void vterm::allocate_buffer()
{
	size_t newbufsize=0;
	if(vidmode.textmode) {
		newbufsize =(vidmode.width * vidmode.height) * (((vidmode.bpp * 2) / 8) + 1);
	} else {
		if(vidmode.bpp > 8) {
			newbufsize = (vidmode.width * vidmode.height) * (vidmode.bpp / 8);
		} else {
			size_t depth=8/vidmode.bpp;
			newbufsize = (vidmode.width * vidmode.height) / depth;
		}
	}
	if(buffer) {
		free(buffer);
		buffer =NULL;
	}
	buffer=(uint8_t*)malloc(newbufsize);
	bufsize=newbufsize;
}

void vterm::queue_input(uint32_t code)
{
	take_lock(&input_lock);
	if((code & KeyFlags::Control) && !(code & KeyFlags::KeyUp) && ((char) code == 'c' || (char) code == 'C')) {
		release_lock(&input_lock);
		kill(curpid);
		return;
	}
	if(event_mode_enabled && (event_mode & bt_terminal_event_mode::Keyboard)) {
		bt_terminal_event event;
		event.type = bt_terminal_event_type::Key;
		event.key = code;
		send_event(event);
	} else {
		keyboard_buffer.add_item(code);
	}
	release_lock(&input_lock);
}

void vterm::queue_pointer(bt_terminal_pointer_event event)
{
	take_lock(&input_lock);
	if(event_mode_enabled && (event_mode & bt_terminal_event_mode::Pointer)) {
		if(event.type != bt_terminal_pointer_event_type::Move || !last_move_message || msg_query_recieved(last_move_message)) {
			bt_terminal_event e;
			e.type = bt_terminal_event_type::Pointer;
			e.pointer = event;
			last_move_message = send_event(e);
		}
	}
	pointer_buffer.add_item(event);
	release_lock(&input_lock);
}

bool input_blockcheck(void *p)
{
	vterm *v=(vterm*)p;
	return (bool)v->keyboard_buffer.count();
}

uint32_t vterm::get_input()
{
	hold_lock hl(&input_lock);
	while(!keyboard_buffer.count()) {
		release_lock(&input_lock);
		thread_setblock(&input_blockcheck, (void *) this);
		take_lock(&input_lock);
	}
	uint32_t ret=keyboard_buffer.read_item();
	return ret;
}

bool pointer_blockcheck(void *p)
{
	vterm *v=(vterm*)p;
	return (bool)v->pointer_buffer.count();
}

bool event_blockcheck(void *p)
{
	return input_blockcheck(p) || pointer_blockcheck(p);
}

bt_terminal_pointer_event vterm::get_pointer()
{
	hold_lock hl(&input_lock);
	while(!pointer_buffer.count()) {
		release_lock(&input_lock);
		thread_setblock(&pointer_blockcheck, (void *) this);
		take_lock(&input_lock);
	}
	bt_terminal_pointer_event ret=pointer_buffer.read_item();
	return ret;
}

char vterm::get_char()
{
	return KB_char(get_input());
}

void vterm::update_current_pid()
{
	curpid = getpid();
	/*pid_t pid = getpid();
	if(pid) {
		uint64_t termid=0;
		if(getenv(terminal_var, pid)) {
			termid=atoi64(getenv(terminal_var, pid));
		}
		if(termid == id) {
			//dbgpf("TERM: %i updating curpid from %i to %i\n", (int)id, (int)curpid, (int)id);
			curpid = pid;
		}
	}*/
}

i_backend *vterm::get_backend(){
	return backend;
}

void vterm::read_buffer(size_t size, uint8_t *buf){
	//hold_lock hl(&term_lock);
	if(size > bufsize) size = bufsize;
	memcpy(buf, buffer, size);
}

void vterm::set_backend(i_backend *back){
	hold_lock hl(&term_lock);
	backend = back;
}

size_t vterm::getpos(){
	return bufpos;
}

vterm_list::vterm_list()
{
	id = 0;
	init_lock(&vtl_lock);
}

uint64_t vterm_list::create_terminal(i_backend *back)
{
	hold_lock hl(&vtl_lock);
	if(!back->can_create()) return 0;
	uint64_t new_id=++id;
	vterm *newterm=new vterm(new_id, back);
	terminals.push_back(newterm);
	return new_id;
}

void vterm_list::delete_terminal(uint64_t id)
{
	hold_lock hl(&vtl_lock);
	for(size_t i=0; i<terminals.size(); ++i) {
		if(terminals[i]->get_id() == id) {
			vterm *term=terminals[i];
			terminals.erase(i);
			term->deactivate();
			delete term;
			break;
		}
	}
}

void vterm_list::delete_backend(i_backend *back){
	hold_lock hl(&vtl_lock);
	for(size_t i=0; i<terminals.size(); ++i) {
		if(terminals[i]->get_backend() == back){
			terminals[i]->set_backend(NULL);
		}
	}
}

vterm *vterm_list::get(uint64_t id)
{
	hold_lock hl(&vtl_lock, false);
	for(size_t i=0; i<terminals.size(); ++i) {
		if(!id || terminals[i]->get_id() == id) {
			return terminals[i];
		}
	}
	return NULL;
}

size_t vterm_list::get_count()
{
	return terminals.size();
}

char *terms_infofs()
{
	char *buffer=(char*)malloc(4096);
	vterm_list *t=terminals;
	memset(buffer, 0, 4096);
	sprintf(buffer, "# ID, title, backend\n");
	for(size_t i=0; i<t->terminals.size(); ++i) {
		sprintf(&buffer[strlen(buffer)], "%i, \"%s\", %p\n", (int)t->terminals[i]->get_id(), t->terminals[i]->get_title(), t->terminals[i]->get_backend());
	}
	return buffer;
}
