#include "btos-conio.h"
#include <btos.h>
#include <dev/terminal.h>
#include <dev/video_dev.h>
#include <dev/keyboard.h>
#include <crt_support.h>
#include <cstdio>
#include <deque>
#include <cstring>

using namespace std;

static const size_t thread_stack_size = (4 * 1024);
static char keythread_stack[thread_stack_size];
static uint16_t terminal_ext_id = 0;

static volatile bt_handle_t keybufferlock = 0;
static volatile bool key_thread_ready = false;

static bt_threadhandle key_thread_id = 0;
static bt_threadhandle wait_thread_id = 0;

static deque<char> keybuffer;

void start_event_mode(){
	terminal_ext_id = bt_query_extension("TERMINAL");
	bt_handle_t th = btos_get_handle(fileno(stdin));
	bt_fioctl(th, bt_terminal_ioctl::StartEventMode, 0, NULL);
	bt_terminal_event_mode::Enum mode = bt_terminal_event_mode::Keyboard;
	bt_fioctl(th, bt_terminal_ioctl::SetEventMode, sizeof(mode), (char*)&mode);
}

static void conio_terminal_thread(void*){
	keybufferlock = bt_create_lock();
	start_event_mode();
	bt_msg_filter filter;
	filter.flags = bt_msg_filter_flags::From | bt_msg_filter_flags::Source;
	filter.pid = 0;
	filter.source = terminal_ext_id;
	key_thread_ready = true;
	bt_msg_header msg = bt_recv_filtered(filter);
	while(true){
		bt_terminal_event event;
		bt_msg_content(&msg, &event, sizeof(event));
		if(event.type == bt_terminal_event_type::Key){
			uint32_t &key = event.key;
			char c = 0;
			uint16_t code = KB_code(key);
			if((code & KeyFlags::Control) && KB_char(key)){
				c = KB_char(key);
				if(c >= 'a' && c <= 'z') c -= ('a' - 1);
				if(c >= 'A' && c <= 'Z') c -= ('A' - 1);
			}else if(code == (KeyFlags::NonASCII | KeyCodes::UpArrow)){
				c = 30;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::DownArrow)){
				c = 31;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow)){
				c = 28;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow)){
				c = 29;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::Delete)){
				c = 4;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp)){
				c = 2;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown)){
				c = 6;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::Home)){
				c = 20;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::End)){
				c = 5;
			}else if(!(code & KeyFlags::NonASCII)){
				c = KB_char(key);
			}
			
			if(c){
				bt_lock(keybufferlock);
				keybuffer.push_back(c);
				if(c == '\n') keybuffer.push_back(12);
				if(wait_thread_id) bt_unblock_thread(wait_thread_id);
				wait_thread_id = 0;
				bt_unlock(keybufferlock);
			}
		}
		bt_next_msg_filtered(&msg, filter);
	}
}

static bt_vidmode getvidmode(){
	bt_handle_t h = btos_get_handle(fileno(stdout));
	bt_vidmode mode;
	bt_fioctl(h, bt_terminal_ioctl::QueryScreenMode, sizeof(mode), (char*)&mode);
	return mode;
}

static bool getinfoline(){
	bt_handle_t h = btos_get_handle(fileno(stdout));
	bool ret;
	bt_fioctl(h, bt_terminal_ioctl::GetInfoLine, sizeof(ret), (char*)&ret);
	return ret;
}

extern "C" void putch(char c){
	bt_fwrite(btos_get_handle(fileno(stdout)), 1, &c);
}

extern "C" char getch(){
	fflush(stdout);
	if(!key_thread_id){
		key_thread_id = bt_new_thread(&conio_terminal_thread, NULL, keythread_stack + thread_stack_size);
		while(!key_thread_ready) bt_yield();
	}
	char ret;
	bt_lock(keybufferlock);
	while(!keybuffer.size()){
		wait_thread_id = bt_get_thread();
		bt_unlock(keybufferlock);
		bt_block_thread();
		bt_lock(keybufferlock);
	}
	ret = keybuffer.front();
	keybuffer.pop_front();
	bt_unlock(keybufferlock);
	if(ret > 0x1F) putch(ret);
	return ret;
}

extern "C" void gotoxy(int c, int r){
	bt_vidmode mode = getvidmode();
	if(!mode.textmode) return;
	if(!getinfoline()) r--;
	c--;
	
	size_t pos = (mode.width * r) + c;
	bt_handle_t h = btos_get_handle(fileno(stdout));
	bt_fseek(h, pos, FS_Set);
}

extern "C" void clearline(){
	bt_vidmode mode = getvidmode();
	if(!mode.textmode) return;
	
	char *blstr = new char[mode.width]();
	memset(blstr, ' ', mode.width);
	bt_fwrite(btos_get_handle(fileno(stdout)), mode.width, blstr);
	delete blstr;
}

extern "C" void clearscreen(){
	bt_handle_t h = btos_get_handle(fileno(stdout));
	bt_fioctl(h, bt_terminal_ioctl::ClearScreen, 0, NULL);
}

extern "C" void set_scrolling(int onoff){
	bool bonoff = !!onoff;
	bt_handle_t h = btos_get_handle(fileno(stdout));
	bt_fioctl(h, bt_terminal_ioctl::SetScrolling, sizeof(bonoff), (char*)&bonoff);
}
