#include "ansi.h"
extern "C" {
#include "tmt.h"
}
#include <btos.h>
#include <dev/terminal.h>
#include <dev/terminal_ioctl.h>
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
#include <vector>

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
static map<size_t, map<size_t, uint16_t>> screen_cache;

static void start_event_mode(){
	bt_term_StartEventMode();
	bt_term_SetEventMode(bt_terminal_event_mode::Keyboard);
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
	bt_vidmode mode = bt_term_QueryScreenMode();
	if(!mode.textmode) return;
	if(bt_term_GetInfoLine()) ++r;
	
	size_t pos = (mode.width * r) + c;
	bt_fseek(real_stdout->handle, pos, FS_Set);
}

static void clearscreen(){
	char cc = 0x07;
	bt_term_SetTextColours(0x07);
	bt_term_ClearScreen();
}

static bool cache_match(size_t row, size_t col, uint16_t ch){
	return (screen_cache.find(row) != screen_cache.end()) && (screen_cache.at(row).find(col) != screen_cache.at(row).end()) && (screen_cache.at(row).at(col) == ch);
}

static void cache_set(size_t row, size_t col, uint16_t ch){
	if(screen_cache.find(row) == screen_cache.end()){
		screen_cache[row] = map<size_t, uint16_t>();
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

static uint8_t getcolour(tmt_color_t c, bool fg){
	switch(c){
		case TMT_COLOR_BLACK: return 0;
		case TMT_COLOR_RED: return 1;
		case TMT_COLOR_GREEN: return 2;
		case TMT_COLOR_YELLOW: return 3;
		case TMT_COLOR_BLUE: return 4;
		case TMT_COLOR_MAGENTA: return 5;
		case TMT_COLOR_CYAN: return 6;
		case TMT_COLOR_WHITE: return 7;
		case TMT_COLOR_MAX: return 15;
		case TMT_COLOR_DEFAULT: 
		default:
			return fg ? 7 : 0;
	}
}

static uint8_t encode_attrs(const TMTATTRS &attrs){
	uint8_t fg = getcolour(attrs.fg, true);
	uint8_t bg = getcolour(attrs.bg, false);
	
	if(attrs.bold) fg |= (1 << 4);
	
	if(attrs.reverse){
		uint8_t tmp = fg;
		fg = bg;
		bg = tmp;
	}
	
	if(attrs.invisible) fg = bg;
	
	return (bg << 4) | fg;
}

static uint16_t encode_value(const TMTCHAR &t){
	return (encode_attrs(t.a) << 8) | t.c;
}

static void write_screen(size_t c, size_t r, const vector<uint16_t> &chars){
	if(chars.empty()) return;
	uint8_t cc = bt_term_GetTextColours();
	
	uint8_t a = chars[0] >> 8;
	size_t cstart = 0;
	for(size_t i = 0; i < chars.size(); ++i){
		uint8_t ca = chars[i] >> 8;
		if(ca != a || i == chars.size() - 1){
			string cs;
			for(size_t j = cstart; j <= i; ++j){
				char ch = (char)chars[j];
				if(ch == 10 || ch == 13) ch = ' ';
				cs += ch;
			}
			gotoxy(c + cstart, r);
			bt_term_SetTextColours(a);
			bt_fwrite(real_stdout->handle, cs.length(), cs.c_str());
			a = ca;
			cstart = i;
		}
	}
	
	bt_term_SetTextColours(cc);
}

static void callback(tmt_msg_t m, TMT *vt, const void *a, void *p){
	const TMTSCREEN *s = tmt_screen(vt);
	const TMTPOINT *c = tmt_cursor(vt);
	
	switch(m){
		case TMT_MSG_BELL:{
			char curtitle[128];
			bt_term_GetTitle(curtitle, 128);
			string belltitle (strlen(curtitle), '*');
			bt_term_SetTitle(belltitle.c_str());
			bt_rtc_sleep(200);
			bt_term_SetTitle(curtitle);

		}
		break;
		
		case TMT_MSG_UPDATE:{
			bt_filesize_t pos = bt_fseek(real_stdout->handle, 0, FS_Relative);
			for(size_t r = 0; r < s->nline; ++r){
				int changestart = -1;
				vector<uint16_t> changestring;
				uint8_t a = 0;
				if (s->lines[r]->dirty){
					for (size_t c = 0; c < s->ncol; ++c){
						uint16_t v = encode_value(s->lines[r]->chars[c]);
						bool draw = false;
						if(!cache_match(r, c, v)){
							if(changestart == -1) changestart = c;
							changestring.push_back(v);
							cache_set(r, c, v);
						}else if(changestart != -1){
							write_screen(changestart, r, changestring);
							changestart = -1;
							changestring.clear();
						}
					}
					if(changestart != -1){
						write_screen(changestart, r, changestring);
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
	bt_term_stdout();
	bt_vidmode mode = bt_term_QueryScreenMode();
	if(!mode.textmode) return;
	if(bt_term_GetInfoLine()) --mode.height;
	TMT *tmt = tmt_open(mode.height + 1, mode.width + 1, &callback, NULL, NULL);
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
	bt_term_SetScrolling(false);
	ansi_on = true;
	if(!exit_registered){
		atexit(&end_ansi);
		exit_registered = true;
	}
}

extern "C" void end_ansi(){
	if(ansi_on){
		clearscreen();
		bt_term_SetScrolling(true);
		bt_term_EndEventMode();
		btos_set_specific_filenum_virt(fileno(stdout), *real_stdout);
		btos_set_specific_filenum_virt(fileno(stdin), *real_stdin);
		free(real_stdout);
		free(real_stdout);
		ansi_on = false;
	}
}
