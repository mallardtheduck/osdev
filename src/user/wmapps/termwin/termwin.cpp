#include <btos.h>
#include <wm/libwm.h>
#include <gds/libgds.h>
#include <string>
#include <vector>
#include <utility>
#include <dev/terminal.h>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include "table.hpp"

USE_BT_TERMINAL_API;

using namespace std;

const string ProcInfoPath = "info:/procs";

const size_t terminal_width = 80;
const size_t terminal_height = 25;
const bt_vidmode terminal_mode = {1, terminal_width, terminal_height, 4, true, false, 0, 0, 0, 0, 0, 0, 0}; 
const uint32_t font_width = 6;
const uint32_t font_height = 13;
const gds_TEMPFonts::Enum font = gds_TEMPFonts::Small;
const size_t buffer_size = (terminal_width * terminal_height * 2);
uint8_t buffer[buffer_size];
uint8_t tempbuffer[buffer_size];
const size_t thread_stack_size = 16 * 1024;
char mainthread_stack[thread_stack_size];
char renderthread_stack[thread_stack_size];
bt_handle_t terminal_handle = 0;
volatile bool ready = false;
bt_handle_t render_counter;
bt_handle_t renderthread = 0;
volatile bool endrender = false;
bt_handle_t bufferlock = 0;
size_t curpos;

string get_env(const string &name){
	char value[128];
	string ret;
	size_t size=bt_getenv(name.c_str(), value, 128);
	ret=value;
	if(size>128){
		char *buf=new char[size];
		bt_getenv(name.c_str(), value, size);
		ret=buf;
	}
	if(size) return ret;
	else return "";
}

template<typename T> void send_reply(const bt_msg_header &msg, const T &content){
	bt_msg_header reply;
	reply.to = msg.from;
	reply.reply_id = msg.id;
	reply.flags = bt_msg_flags::Reply;
	reply.length = sizeof(content);
	reply.content = (void*)&content;
	bt_send(reply);
}

template<typename T> void send_reply(const bt_msg_header &msg, const T *content, size_t size){
	bt_msg_header reply;
	reply.to = msg.from;
	reply.reply_id = msg.id;
	reply.flags = bt_msg_flags::Reply;
	reply.length = size;
	reply.content = (void*)content;
	bt_send(reply);
}

template<typename T> T get_content(bt_msg_header &msg){
	if(msg.length == sizeof(T)){
		T ret;
		bt_msg_content(&msg, &ret, sizeof(ret));
		return ret;
	}else{
		stringstream ss;
		ss << "TW: Message length mismatch. Expected " << sizeof(T) << " got " << msg.length << "." << endl;
		ss << "TW: Message type: " << msg.type << " from: " << msg.from << " (source: " << msg.source << ")" << endl;
		bt_zero(ss.str().c_str());
		return T();
	}
}

void kill_children(){
	bool found = true;
	while(found){
		found = false;
		ifstream procinfostream(ProcInfoPath);
		table procs = parsecsv(procinfostream);
		for(auto row: procs.rows){
			if(strtoul(row["parent"].c_str(), NULL, 0) == bt_getpid()){
				bt_kill(strtoul(row["PID"].c_str(), NULL, 0));
				found = true;
			}
		}
	}
}

uint32_t getcolour(uint8_t id){
	static uint32_t colours[16] = {0};
	if(id < 16 && colours[id]) return colours[id];
	switch(id){
		case 0: return colours[0] = GDS_GetColour(0, 0, 0);
		case 1: return colours[1] = GDS_GetColour(0, 0, 0xaa);
		case 2: return colours[2] = GDS_GetColour(0, 0xaa, 0);
		case 3: return colours[3] = GDS_GetColour(0, 0xaa, 0xaa);
		case 4: return colours[4] = GDS_GetColour(0xaa, 0, 0);
		case 5: return colours[5] = GDS_GetColour(0xaa, 0, 0xaa);
		case 6: return colours[6] = GDS_GetColour(0xaa, 0x55, 0);
		case 7: return colours[7] = GDS_GetColour(0xaa, 0xaa, 0xaa);
		case 8: return colours[8] = GDS_GetColour(0x55, 0x55, 0x55);
		case 9: return colours[9] = GDS_GetColour(0x55, 0x55, 0xff);
		case 10: return colours[10] = GDS_GetColour(0x55, 0xff, 0x55);
		case 11: return colours[11] = GDS_GetColour(0x55, 0xff, 0xff);
		case 12: return colours[12] = GDS_GetColour(0xff, 0x55, 0x55);
		case 13: return colours[13] = GDS_GetColour(0xff, 0x55, 0xff);
		case 14: return colours[14] = GDS_GetColour(0xff, 0xff, 0x55);
		case 15: return colours[15] = GDS_GetColour(0xff, 0xff, 0xff);
		default: return colours[0] = GDS_GetColour(0, 0, 0);
	}
}

bool compare_chars(char a, char b){
	if(a < 32 && b < 32) return true;
	else return a == b;
}

void render_terminal_thread(){
	if(!terminal_handle) return;
	uint64_t render_counted = 0;
	while(true){
		render_counted = bt_wait_atom(render_counter, bt_atom_compare::NotEqual, render_counted);
		if(endrender) return;
		static char ltitle[WM_TITLE_MAX] = {0};
		char title[WM_TITLE_MAX];
		bt_terminal_get_title(terminal_handle, WM_TITLE_MAX, title);
		if(strncmp(ltitle, title, WM_TITLE_MAX)) {
			WM_SetTitle(title);
			strncpy(ltitle, title, WM_TITLE_MAX);
		}
		static size_t lpos = SIZE_MAX;
		for(size_t line = 0; line < terminal_mode.height; ++line){
			vector<pair<size_t, uint16_t>> line_changes;
			bt_lock(bufferlock);
			for(size_t col = 0; col < terminal_mode.width; ++col){
				size_t bufaddr = ((line * terminal_mode.width) + col) * 2;
				if(!compare_chars(tempbuffer[bufaddr], buffer[bufaddr]) || tempbuffer[bufaddr + 1] != buffer[bufaddr + 1] || bufaddr == curpos || bufaddr == lpos){
					buffer[bufaddr] = tempbuffer[bufaddr];
					if(bufaddr == curpos) buffer[bufaddr + 1] = ((tempbuffer[bufaddr + 1] & 0x0f) << 4) | ((tempbuffer[bufaddr + 1] & 0xf0) >> 4);
					else buffer[bufaddr + 1] = tempbuffer[bufaddr + 1];
					uint16_t change = (buffer[bufaddr] > 32 ? buffer[bufaddr] : ' ') | buffer[bufaddr + 1] << 8;
					line_changes.push_back(make_pair(col, change));
				}
			}
			bt_unlock(bufferlock);
			if(line_changes.size()){
				size_t firststart = UINT32_MAX;
				size_t overallend = 0;
				size_t start = UINT32_MAX;
				size_t end = 0;
				stringstream text;
				uint8_t col = 0, ncol = 0;
				for(auto change : line_changes){
					bool draw = false;
					if(start == UINT32_MAX) start = end = change.first;
					if(firststart == UINT32_MAX) firststart = change.first;
					overallend = change.first;
					if(change.first == end){
						++end;
						char c = change.second & 0xFF;
						uint8_t ccol = (change.second & 0xFF00) >> 8;
						if(ccol == col){
							text << c;
						}else{
							ncol = ccol;
							draw = true;
						}
					}else{
						draw = true;
					}
					if(draw){
						if(text.str().length()){
							uint8_t bgcol = col >> 4;
							uint8_t fgcol = col & 0x0F;
							uint32_t width = text.str().length() * font_width;
							GDS_Box(start * font_width, line * font_height, width , font_height, getcolour(bgcol), getcolour(bgcol), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
							GDS_Text(start * font_width, line * font_height, text.str().c_str(), font, 0, getcolour(fgcol));
							//WM_UpdateRect(start * font_width, line * font_height, width, font_height);
						}
						text.str("");
						text << (char)(change.second & 0xFF);
						start = change.first;
						end = change.first + 1;
						col = ncol;
					}
				}
				if(start != UINT32_MAX){
					uint8_t bgcol = col >> 4;
					uint8_t fgcol = col & 0x0F;
					uint32_t width = (end * font_width) - (start * font_width);
					GDS_Box(start * font_width, line * font_height, width , font_height, getcolour(bgcol), getcolour(bgcol), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
					GDS_Text(start * font_width, line * font_height, text.str().c_str(), font, 0, getcolour(fgcol));
				}
				WM_UpdateRect(firststart * font_width, line * font_height, (overallend - firststart + 1) * font_width, font_height);
			}
		}
		lpos = curpos;
	}
}

void renderthread_start(void *){
	render_terminal_thread();
}


void render_terminal(){
	if(!terminal_handle) return;
	if(!renderthread) renderthread = bt_new_thread(&renderthread_start, NULL, renderthread_stack + thread_stack_size);
	bt_lock(bufferlock);
	curpos = bt_terminal_get_pos(terminal_handle);
	bt_terminal_read_buffer(terminal_handle, buffer_size, tempbuffer);
	bt_modify_atom(render_counter, bt_atom_modify::Add, 1);
	bt_unlock(bufferlock);
}

void mainthread(void*){
	size_t cpos  = 0;
	size_t refcount = 0;
	uint8_t textcolours = 0x07; 
	uint64_t surf = GDS_NewSurface(gds_SurfaceType::Bitmap, terminal_mode.width * font_width, terminal_mode.height * font_height);
	/*uint64_t win =*/ WM_NewWindow(50, 50, wm_WindowOptions::Default, wm_EventType::Keyboard | wm_EventType::Close, surf, "Terminal Window");
	ready = true;
	bt_msg_filter filter;
	filter.flags = bt_msg_filter_flags::NonReply;
	bt_msg_header msg = bt_recv_filtered(filter);
	size_t maxlen = 0;
	bt_terminal_backend_operation *op = (bt_terminal_backend_operation*)new uint8_t[1];
	bool loop = true;
	while(loop){
		if(msg.from == 0 && msg.source == bt_terminal_ext_id && msg.type == bt_terminal_message_type::BackendOperation){
			if(msg.length > maxlen){
				delete op;
				maxlen = msg.length;
				op = (bt_terminal_backend_operation*)new uint8_t[maxlen];
			}
			bt_msg_content(&msg, op, msg.length);
			switch(op->type){
				case bt_terminal_backend_operation_type::CanCreate:{
					send_reply(msg, (bool)(refcount == 0));
					break;
				}
				case bt_terminal_backend_operation_type::GetCurrentScreenMode:{
					send_reply(msg, terminal_mode);
					break;
				}
				case bt_terminal_backend_operation_type::GetScreenScroll:{
					send_reply(msg, true);
					break;
				}
				case bt_terminal_backend_operation_type::DisplaySeek:{
					struct sp{
						size_t pos;
						uint32_t flags;
					};
					sp seek_params = *(sp*)op->data;
					if((seek_params.flags & FS_Backwards) && (seek_params.flags & FS_Relative)) cpos -= seek_params.pos;
					else if (seek_params.flags & FS_Relative) cpos += seek_params.pos;
					else cpos = seek_params.pos;
					send_reply(msg, cpos);
					break;
				}
				case bt_terminal_backend_operation_type::DisplayRead:{
					size_t readsize = *(size_t*)op->data;
					send_reply(msg, &buffer[cpos], readsize);
					cpos += readsize;
					break;
				}
				case bt_terminal_backend_operation_type::DisplayWrite:{
					cpos += msg.length;
					send_reply(msg, msg.length);
					break;
				}
				case bt_terminal_backend_operation_type::IsActive:{
					send_reply(msg, true);
					break;
				}
				case bt_terminal_backend_operation_type::SetTextColours:{
					textcolours = *(uint8_t*)op->data;
					break;
				}
				case bt_terminal_backend_operation_type::GetTextColours:{
					send_reply(msg, textcolours);
					break;
				}
				case bt_terminal_backend_operation_type::Refresh:{
					render_terminal();
					break;
				}
				case bt_terminal_backend_operation_type::Open:{
					++refcount;
					break;
				}
				case bt_terminal_backend_operation_type::Close:{
					--refcount;
					if(refcount == 0) loop = false;
					break;
				}case bt_terminal_backend_operation_type::GetPointerVisibility:{
					send_reply(msg, false);
					break;
				}
				case bt_terminal_backend_operation_type::GetPointerInfo:{
					send_reply(msg, bt_terminal_pointer_info());
					break;
				}
				case bt_terminal_backend_operation_type::GetScreenModeCount:{
					send_reply(msg, (size_t)1);
					break;
				}
				case bt_terminal_backend_operation_type::GetScreenMode:{
					send_reply(msg, terminal_mode);
					break;
				}
				case bt_terminal_backend_operation_type::GetPaletteEntry:{
					send_reply(msg, bt_video_palette_entry());
					break;
				}
				case bt_terminal_backend_operation_type::ClearScreen:{
					memset(buffer, 0, buffer_size);
					break;
				}
				default:{
					stringstream ss;
					ss << "TW: Unhandled backend operation: " << op->type << endl;
					bt_zero(ss.str().c_str());
				}
			}
		}else{
			wm_Event e = WM_ParseMessage(&msg);
			if(e.type == wm_EventType::Close) break;
			else if(e.type == wm_EventType::Keyboard){
				if(terminal_handle){
					bt_terminal_event te;
					te.type = bt_terminal_event_type::Key;
					te.key = e.Key.code;
					bt_terminal_queue_event(terminal_handle, &te);
				}
			}
		}
		bt_next_msg_filtered(&msg, filter);
	}
	delete op;
	endrender = true;
	bt_modify_atom(render_counter, bt_atom_modify::Add, 1);
	kill_children();
	bt_end_thread();
}

int main(){
	bt_terminial_init();
	bufferlock = bt_create_lock();
	render_counter = bt_create_atom(0);
	bt_handle_t backend_handle = bt_terminal_create_backend();
	bt_threadhandle thread = bt_new_thread(&mainthread, NULL, mainthread_stack + thread_stack_size);
	while(!ready) bt_yield();
	terminal_handle = bt_terminal_create_terminal(backend_handle);
	string shell = get_env("SHELL");
	bt_terminal_run(terminal_handle, shell.c_str());
	bt_wait_thread(thread);
	return 0;
}
