#include <wm/libwm.h>
#include <gds/libgds.h>
#include <string>
#include <vector>
#include <utility>
#include <btos_stubs.h>
#include <terminal.h>
#include <sstream>
#include <algorithm>

USE_BT_TERMINAL_API;

using namespace std;

const size_t terminal_width = 80;
const size_t terminal_height = 25;
const bt_vidmode terminal_mode = {1, terminal_width, terminal_height, 4, true, false}; 
const uint32_t font_width = 5;
const uint32_t font_height = 8;
const gds_TEMPFonts::Enum font = gds_TEMPFonts::Tiny;
const size_t buffer_size = (terminal_width * terminal_height * 2);
uint8_t buffer[buffer_size];
const size_t mainthread_stack_size = 16 * 1024;
char mainthread_stack[mainthread_stack_size];
bt_handle_t terminal_handle = 0;
volatile bool ready = false;

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
	T ret;
	bt_msg_content(&msg, &ret, sizeof(ret));
	return ret;
}

uint32_t getcolour(uint8_t id){
	switch(id){
		case 0: return GDS_GetColour(0, 0, 0);
		case 1: return GDS_GetColour(0, 0, 0xaa);
		case 2: return GDS_GetColour(0, 0xaa, 0);
		case 3: return GDS_GetColour(0, 0xaa, 0xaa);
		case 4: return GDS_GetColour(0xaa, 0, 0);
		case 5: return GDS_GetColour(0xaa, 0, 0xaa);
		case 6: return GDS_GetColour(0xaa, 0x55, 0);
		case 7: return GDS_GetColour(0xaa, 0xaa, 0xaa);
		case 8: return GDS_GetColour(0x55, 0x55, 0x55);
		case 9: return GDS_GetColour(0x55, 0x55, 0xff);
		case 10: return GDS_GetColour(0x55, 0xff, 0x55);
		case 11: return GDS_GetColour(0x55, 0xff, 0xff);
		case 12: return GDS_GetColour(0xff, 0x55, 0x55);
		case 13: return GDS_GetColour(0xff, 0x55, 0xff);
		case 14: return GDS_GetColour(0xff, 0xff, 0x55);
		case 15: return GDS_GetColour(0xff, 0xff, 0xff);
		default: return GDS_GetColour(0, 0, 0);
	}
}

void render_terminal(bt_handle_t terminal_handle, uint64_t surf, uint64_t /*win*/){
	if(!terminal_handle) return;
	GDS_SelectSurface(surf);
	uint8_t tempbuffer[buffer_size];
	bt_terminal_read_buffer(terminal_handle, buffer_size, tempbuffer);
	uint32_t minX = UINT32_MAX, minY = UINT32_MAX, maxX = 0, maxY = 0;
	for(size_t line = 0; line < terminal_mode.height; ++line){
		for(size_t col = 0; col < terminal_mode.width; ++col){
			char c[2] = {0};
			size_t buffaddr = ((line * terminal_mode.width) + col) * 2;
			if(tempbuffer[buffaddr] != buffer[buffaddr] || tempbuffer[buffaddr + 1] != buffer[buffaddr + 1]){
				minX = min(minX, (uint32_t)(col * font_width));
				minY = min(minY, (uint32_t)(line * font_height));
				maxX = max(maxX, (uint32_t)((col * font_width) + font_width));
				maxY = max(maxY, (uint32_t)((line * font_height) + font_height));
				buffer[buffaddr] = tempbuffer[buffaddr];
				buffer[buffaddr + 1] = tempbuffer[buffaddr + 1];
				c[0] = buffer[buffaddr];
				uint8_t bgcol = buffer[buffaddr + 1] >> 4;
				uint8_t fgcol = buffer[buffaddr + 1] & 0x0F;
				GDS_Box(col * font_width, line * font_height, font_width , font_height, getcolour(bgcol), getcolour(bgcol), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				if(c[0] > 32) GDS_Text(col * font_width, line * font_height, c, font, 0, getcolour(fgcol));
			}
		}
	}
	if(maxX){
		//WM_SelectWindow(win);
		WM_UpdateRect(minX, minY, maxX - minX, maxY - minY);
	}
}

void mainthread(void*){
	size_t cpos  = 0;
	uint8_t textcolours = 0x07;
	uint64_t surf = GDS_NewSurface(gds_SurfaceType::Bitmap, terminal_mode.width * font_width, terminal_mode.height * font_height);
	uint64_t win = WM_NewWindow(50, 50, wm_WindowOptions::Default, wm_EventType::Keyboard | wm_EventType::Close, surf, "Terminal Window");
	ready = true;
	bt_msg_header msg = bt_recv(true);
	while(true){
		if(msg.from == 0 && msg.source == bt_terminal_ext_id && msg.type == bt_terminal_message_type::BackendOperation){
			bt_terminal_backend_operation *op = (bt_terminal_backend_operation*)new uint8_t[msg.length];
			bt_msg_content(&msg, op, msg.length);
			stringstream ss;
			ss << "TW: Backend operation: " << op->type << endl;
			bt_zero(ss.str().c_str());
			switch(op->type){
				case bt_terminal_backend_operation_type::CanCreate:{
					send_reply(msg, true);
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
					sp seek_params = get_content<sp>(msg);
					if((seek_params.flags & FS_Backwards) && (seek_params.flags & FS_Relative)) cpos -= seek_params.pos;
					else if (seek_params.flags & FS_Relative) cpos += seek_params.pos;
					else cpos = seek_params.pos;
					send_reply(msg, cpos);
					break;
				}
				case bt_terminal_backend_operation_type::DisplayRead:{
					size_t readsize = get_content<size_t>(msg);
					send_reply(msg, &buffer[cpos], readsize);
					cpos += readsize;
					break;
				}
				case bt_terminal_backend_operation_type::DisplayWrite:{
					cpos += msg.length;
					send_reply(msg, msg.length);
					render_terminal(terminal_handle, surf, win);
					break;
				}
				case bt_terminal_backend_operation_type::IsActive:{
					send_reply(msg, true);
					break;
				}
				case bt_terminal_backend_operation_type::SetTextColours:{
					textcolours = get_content<uint8_t>(msg);
					break;
				}
				case bt_terminal_backend_operation_type::GetTextColours:{
					send_reply(msg, textcolours);
					break;
				}
				default:{
					bt_zero("TW: Unhandled backend operation.\n");
					render_terminal(terminal_handle, surf, win);
				}
			}
			delete op;
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
		bt_next_msg(&msg);
	}
}

int main(){
	bt_terminial_init();
	bt_handle_t backend_handle = bt_terminal_create_backend();
	bt_threadhandle thread = bt_new_thread(&mainthread, NULL, mainthread_stack + mainthread_stack_size);
	while(!ready) bt_yield();
	terminal_handle = bt_terminal_create_terminal(backend_handle);
	stringstream ss;
	ss << "TW: Backend: " <<  backend_handle << " Terminal: " << terminal_handle << endl;
	bt_zero(ss.str().c_str());
	string shell = get_env("SHELL");
	bt_terminal_run(terminal_handle, shell.c_str());
	bt_wait_thread(thread);
	return 0;
}