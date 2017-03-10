#include "ansi.h"
extern "C" {
#include "tmt.h"
}
#include <btos.h>
#include <dev/terminal.h>
#include <dev/video_dev.h>
#include <dev/keyboard.h>
#include <dev/rtc.h>
#include <crt_support.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <deque>
#include <sstream>
#include <map>

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

using namespace std;

static const size_t thread_stack_size = (4 * 1024);
static char keythread_stack[thread_stack_size];
static uint16_t terminal_ext_id = 0;

static volatile bt_handle_t keybufferlock = 0;
static volatile bool key_thread_ready = false;

static bt_threadhandle key_thread_id = 0;
static bt_threadhandle wait_thread_id = 0;
static bool ansi_on = false;
static bool exit_registered = false;

static deque<char> keybuffer;
static virtual_handle *real_stdout;
static virtual_handle *real_stdin;

static void ansi_stdin_thread(void*);
static map<size_t, map<size_t,char>> screen_cache;

static bool getinfoline(){
	bool ret;
	bt_fioctl(real_stdout->handle, bt_terminal_ioctl::GetInfoLine, sizeof(ret), (char*)&ret);
	return ret;
}

static bt_vidmode getvidmode(){
	bt_vidmode mode;
	bt_fioctl(real_stdout->handle, bt_terminal_ioctl::QueryScreenMode, sizeof(mode), (char*)&mode);
	return mode;
}

static void start_event_mode(){
	bt_fioctl(real_stdin->handle, bt_terminal_ioctl::StartEventMode, 0, NULL);
	bt_terminal_event_mode::Enum mode = bt_terminal_event_mode::Keyboard;
	bt_fioctl(real_stdin->handle, bt_terminal_ioctl::SetEventMode, sizeof(mode), (char*)&mode);
}

static void end_event_mode(){
	bt_fioctl(real_stdin->handle, bt_terminal_ioctl::EndEventMode, 0, NULL);
}

static void set_scrolling(int onoff){
	bool bonoff = !!onoff;
	bt_fioctl(real_stdout->handle, bt_terminal_ioctl::SetScrolling, sizeof(bonoff), (char*)&bonoff);
}

static void ansi_add_input(const char *s, size_t len = 0){
	if(!len) len = strlen(s);
	bt_lock(keybufferlock);
	for(size_t i = 0; i < len; ++i){
		keybuffer.push_back(s[i]);
	}
	if(wait_thread_id) bt_unblock_thread(wait_thread_id);
	wait_thread_id = 0;
	bt_unlock(keybufferlock);
}

static char ansi_getchar(){
	fflush(stdout);
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
	return ret;
}

static void gotoxy(int c, int r){
	bt_vidmode mode = getvidmode();
	if(!mode.textmode) return;
	if(getinfoline()) ++r;
	
	size_t pos = (mode.width * r) + c;
	bt_fseek(real_stdout->handle, pos, FS_Set);
}

static void clearscreen(){
	bt_fioctl(real_stdout->handle, bt_terminal_ioctl::ClearScreen, 0, NULL);
}

static bool cache_match(size_t row, size_t col, char ch){
	return (screen_cache.find(row) != screen_cache.end()) && (screen_cache.at(row).find(col) != screen_cache.at(row).end()) && (screen_cache.at(row).at(col) == ch);
}

static void cache_set(size_t row, size_t col, char ch){
	if(screen_cache.find(row) == screen_cache.end()){
		screen_cache[row] = map<size_t, char>();
	}
	screen_cache[row][col] = ch;
}

static int ansi_virt_write(void *t, char *buf, int size){
	tmt_write((TMT*)t, buf, size);
	return size;
}

static int ansi_virt_read(void *t, char *buf, int size){
	for(int i = 0; i < size; ++i){
		buf[i]=ansi_getchar();
	}
	return size;
}

static off_t ansi_virt_lseek(void *t, off_t o, int mode){
	return 0;
}

static int ansi_virt_fsync(void *t){
	return 0;
}

static int ansi_virt_isatty(void *t){
	return 1;
}

static int ansi_virt_close(void *t){
	tmt_close((TMT*)t);
	end_ansi();
	return 0;
}

static void callback(tmt_msg_t m, TMT *vt, const void *a, void *p){
	const TMTSCREEN *s = tmt_screen(vt);
	const TMTPOINT *c = tmt_cursor(vt);
	
	switch(m){
		case TMT_MSG_BELL:{
			char curtitle[128];
			bt_fioctl(real_stdout->handle, bt_terminal_ioctl::GetTitle, 128, curtitle);
			string belltitle (strlen(curtitle), '*');
			bt_fioctl(real_stdout->handle, bt_terminal_ioctl::SetTitle, belltitle.length() + 1, (char*)belltitle.c_str());
			bt_rtc_sleep(200);
			bt_fioctl(real_stdout->handle, bt_terminal_ioctl::SetTitle, 128, curtitle);
		}
		break;
		
		case TMT_MSG_UPDATE:{
			bt_filesize_t pos = bt_fseek(real_stdout->handle, 0, FS_Relative);
			for(size_t r = 0; r < s->nline; ++r){
				int changestart = -1;
				string changestring;
				if (s->lines[r]->dirty){
					for (size_t c = 0; c < s->ncol; ++c){
						char ch = (char)s->lines[r]->chars[c].c;
						if(ch == 10 || ch == 13) ch = ' ';
						if(!cache_match(r, c, ch)){
							if(changestart == -1) changestart = c;
							changestring += ch;
							cache_set(r, c, ch);
						}else if(changestart != -1){
							gotoxy(changestart, r);
							bt_fwrite(real_stdout->handle, changestring.length(), changestring.c_str());
							changestart = -1;
							changestring = "";
						}
					}
					if(changestart != -1){
						gotoxy(changestart, r);
						bt_fwrite(real_stdout->handle, changestring.length(), changestring.c_str());
					}
					s->lines[r]->dirty = 0;
				}
			}
			bt_fseek(real_stdout->handle, pos, FS_Set);
		}
		break;
		
		case TMT_MSG_ANSWER:{
			ansi_add_input((const char*)a);
		}
		break;
		
		case TMT_MSG_MOVED:{
			gotoxy(c->c, c->r);
		}
		break;
		
		case TMT_MSG_CURSOR:
		break;
	}
}

static void ansi_stdin_thread(void*){
	keybufferlock = bt_create_lock();
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
			uint16_t code = KB_code(key);
			if((code & KeyFlags::Control) && KB_char(key)){
				char c = KB_char(key);
				if(c >= 'a' && c <= 'z') c -= ('a' - 1);
				if(c >= 'A' && c <= 'Z') c -= ('A' - 1);
				ansi_add_input(&c, 1);
			}else if(code == (KeyFlags::NonASCII | KeyCodes::UpArrow)){
				ansi_add_input(TMT_KEY_UP);
			}else if(code == (KeyFlags::NonASCII | KeyCodes::DownArrow)){
				ansi_add_input(TMT_KEY_DOWN);
			}else if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow)){
				ansi_add_input(TMT_KEY_LEFT);
			}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow)){
				ansi_add_input(TMT_KEY_RIGHT);
			}else if(code == (KeyFlags::NonASCII | KeyCodes::Delete)){
				char c = 4;
				ansi_add_input(&c, 1);
			}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp)){
				ansi_add_input(TMT_KEY_PAGE_UP);
			}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown)){
				ansi_add_input(TMT_KEY_PAGE_DOWN);
			}else if(code == (KeyFlags::NonASCII | KeyCodes::Home)){
				ansi_add_input(TMT_KEY_HOME);
			}else if(code == (KeyFlags::NonASCII | KeyCodes::End)){
				ansi_add_input(TMT_KEY_END);
			}else if(!(code & KeyFlags::NonASCII)){
				char c = KB_char(key);
				if(c == 10) ansi_add_input("\r");
				else if(c) ansi_add_input(&c, 1);
			}
		}
		bt_next_msg_filtered(&msg, filter);
	}
}

extern "C" void init_ansi(){
	if(ansi_on) return;
	terminal_ext_id = bt_query_extension("TERMINAL");
	if(!isatty(fileno(stdout))) return;
	real_stdout = btos_get_handle_virt(fileno(stdout));
	real_stdin = btos_get_handle_virt(fileno(stdin));
	bt_vidmode mode = getvidmode();
	if(!mode.textmode) return;
	if(getinfoline()) --mode.height;
	TMT *tmt = tmt_open(mode.height, mode.width, &callback, NULL, NULL);
	virtual_handle ansi_terminal;
	ansi_terminal.type = HANDLE_VIRT;
	ansi_terminal.virt.data = (void*)tmt;
	ansi_terminal.virt.write = &ansi_virt_write;
	ansi_terminal.virt.read = &ansi_virt_read;
	ansi_terminal.virt.lseek = &ansi_virt_lseek;
	ansi_terminal.virt.fsync = &ansi_virt_fsync;
	ansi_terminal.virt.isatty = &ansi_virt_isatty;
	ansi_terminal.virt.close = &ansi_virt_close;
	btos_set_specific_filenum_virt(fileno(stdout), ansi_terminal);
	btos_set_specific_filenum_virt(fileno(stdin), ansi_terminal);
	start_event_mode();
	if(!key_thread_id){
		key_thread_id = bt_new_thread(&ansi_stdin_thread, NULL, keythread_stack + thread_stack_size);
		while(!key_thread_ready) bt_yield();
	}
	set_scrolling(false);
	ansi_on = true;
	if(!exit_registered){
		atexit(&end_ansi);
		exit_registered = true;
	}
}

extern "C" void end_ansi(){
	if(ansi_on){
		clearscreen();
		set_scrolling(true);
		end_event_mode();
		btos_set_specific_filenum_virt(fileno(stdout), *real_stdout);
		btos_set_specific_filenum_virt(fileno(stdin), *real_stdin);
		free(real_stdout);
		free(real_stdout);
		ansi_on = false;
	}
}
