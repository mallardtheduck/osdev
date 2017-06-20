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
#include <memory>
#include <btos/table.hpp>
#include "dev/rtc.h"
#include "lrucache.hpp"

using namespace std;

#ifdef DEBUG
#define DBG(x) do{std::stringstream dbgss; dbgss << x << std::endl; bt_zero(dbgss.str().c_str());}while(0)
#else
#define DBG(x)
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

static const string ProcInfoPath = "info:/procs";
static const string fontName = "unscii";
static const size_t fontSize = 12;

const size_t terminal_width = 80;
const size_t terminal_height = 25;
const bt_vidmode terminal_mode = {1, terminal_width, terminal_height, 4, true, false, 0, 0, 0, 0, 0, 0, 0}; 
static uint32_t font_width = 0;
static uint32_t font_height = 0;
static uint32_t font;
const size_t buffer_size = (terminal_width * terminal_height * 2);
static uint8_t buffer[buffer_size];
static uint8_t tempbuffer[buffer_size];
static const size_t thread_stack_size = 16 * 1024;
static char mainthread_stack[thread_stack_size];
static char renderthread_stack[thread_stack_size];
static bt_handle_t terminal_handle = 0;
static volatile bool ready = false;
static bt_handle_t render_counter;
static bt_handle_t renderthread = 0;
static volatile bool endrender = false;
static size_t curpos;
static uint64_t surf;
static size_t lpos = SIZE_MAX;

struct glyph_holder{
	uint64_t gds_id;
	glyph_holder(uint64_t id): gds_id(id) {}
	~glyph_holder(){
		GDS_SelectSurface(gds_id);
		GDS_DeleteSurface();
		GDS_SelectSurface(surf);
	}
};
static cache::lru_cache<uint16_t, shared_ptr<glyph_holder>> glyphcache(1024);

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
		DBG("TW: Message length mismatch. Expected " << sizeof(T) << " got " << msg.length << ".");
		DBG("TW: Message type: " << msg.type << " from: " << msg.from << " (source: " << msg.source << ")");
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

uint32_t getcolour(uint8_t id, bool cache = true){
	static uint32_t colours[16] = {0};
	if(cache && id < 16 && colours[id]) return colours[id] - 1;
	uint32_t ret;
	switch(id){
		case 0: ret = GDS_GetColour(0, 0, 0); break;
		case 1: ret = GDS_GetColour(0, 0, 0xaa); break;
		case 2: ret = GDS_GetColour(0, 0xaa, 0); break;
		case 3: ret = GDS_GetColour(0, 0xaa, 0xaa); break;
		case 4: ret = GDS_GetColour(0xaa, 0, 0); break;
		case 5: ret = GDS_GetColour(0xaa, 0, 0xaa); break;
		case 6: ret = GDS_GetColour(0xaa, 0x55, 0); break;
		case 7: ret = GDS_GetColour(0xaa, 0xaa, 0xaa); break;
		case 8: ret = GDS_GetColour(0x55, 0x55, 0x55); break;
		case 9: ret = GDS_GetColour(0x55, 0x55, 0xff); break;
		case 10: ret = GDS_GetColour(0x55, 0xff, 0x55); break;
		case 11: ret = GDS_GetColour(0x55, 0xff, 0xff); break;
		case 12: ret = GDS_GetColour(0xff, 0x55, 0x55); break;
		case 13: ret = GDS_GetColour(0xff, 0x55, 0xff); break;
		case 14: ret = GDS_GetColour(0xff, 0xff, 0x55); break;
		case 15: ret = GDS_GetColour(0xff, 0xff, 0xff); break;
		default: ret = GDS_GetColour(0, 0, 0); break;
	}
	if(cache && id < 16) colours[id] = ret + 1;
	return ret;
}

uint64_t get_glyph(uint8_t attr, uint8_t ch){
	if(ch < 32) ch = ' ';
	uint16_t key = (attr << 8) | ch;
	if(glyphcache.exists(key)) return glyphcache.get(key)->gds_id;
	uint64_t id = GDS_NewSurface(gds_SurfaceType::Bitmap, font_width, font_height);
	uint8_t bgcol = attr >> 4;
	uint8_t fgcol = attr & 0x0F;
	uint32_t bg = getcolour(bgcol, false);
	uint32_t fg = getcolour(fgcol, false);
	GDS_Box(0, 0, font_width, font_height, bg, bg, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_TextChar(0, font_height - (font_height / 5), ch, font, fontSize, fg);
	glyphcache.put(key, make_shared<glyph_holder>(id));
	GDS_SelectSurface(surf);
	return id;
}

bool compare_chars(char a, char b){
	if(a <= 32 && b <= 32) return true;
	else return a == b;
}

static bool has_line_changed(size_t line){
	size_t laddr = (line * terminal_mode.width) * 2;
	if(memcmp(&tempbuffer[laddr], &buffer[laddr], terminal_mode.width * 2)) return true;
	if(lpos != curpos){
		if(lpos >= laddr && lpos < laddr + (terminal_mode.width * 2)) return true;
		if(curpos > laddr && curpos < laddr + (terminal_mode.width * 2)) return true;
	}
	return false;
}

static size_t detect_line_scroll(size_t line){
	for(size_t sline = 0; sline < terminal_mode.height; ++sline){
		size_t l0addr = (line * terminal_mode.width) * 2;
		size_t l1addr = (sline * terminal_mode.width) * 2;
		if(memcmp(&tempbuffer[l0addr], &buffer[l1addr], terminal_mode.width * 2) == 0) return sline;
	}
	return 0;
}

static void addRect(wm_Rect &a, const wm_Rect &b){
	if(a.x == 0 && a.y == 0 && a.w == 0 && a.h == 0){
		a = b;
		return;
	}
	int32_t ax1 = a.x;
	int32_t ay1 = a.y;
	int32_t ax2 = a.x + a.w;
	int32_t ay2 = a.y + a.h;
	int32_t bx1 = b.x;
	int32_t by1 = b.y;
	int32_t bx2 = b.x + b.w;
	int32_t by2 = b.y + b.h;
	if(bx1 < ax1) ax1 = bx1;
	if(by1 < ay1) ay1 = by1;
	if(bx2 > ax2) ax2 = bx2;
	if(by2 > ay2) ay2 = by2;
	a.x = ax1;
	a.y = ay1;
	a.w = (ax2 - ax1);
	a.h = (ay2 - ay1);	
}

void render_terminal_thread(){
	if(!terminal_handle) return;
	uint64_t render_counted = 0;
	while(true){
		render_counted = bt_wait_atom(render_counter, bt_atom_compare::NotEqual, render_counted);
		if(endrender) return;
		bt_terminal_read_buffer(terminal_handle, buffer_size, tempbuffer);
		static char ltitle[WM_TITLE_MAX] = {0};
		char title[WM_TITLE_MAX];
		bt_terminal_get_title(terminal_handle, WM_TITLE_MAX, title);
		if(strncmp(ltitle, title, WM_TITLE_MAX)) {
			WM_SetTitle(title);
			strncpy(ltitle, title, WM_TITLE_MAX);
		}
		wm_Rect updateRect = {0, 0, 0, 0};
		uint64_t prepStart = bt_rtc_millis();
		vector<gds_DrawingOp> drawingOps;
		for(size_t line = 0; line < terminal_mode.height; ++line){
			if(!has_line_changed(line)) continue;
			if(size_t sline = detect_line_scroll(line)){
				uint64_t start = bt_rtc_millis();
				drawingOps.push_back(GDS_Blit_Op(surf, 0, sline * font_height, terminal_mode.width * font_width, font_height, 0, line * font_height, terminal_mode.width * font_width, font_height));
				addRect(updateRect, {0, (int32_t)(line * font_height), (terminal_mode.width * font_width), font_height});
				size_t l0addr = (line * terminal_mode.width) * 2;
				size_t l1addr = (sline * terminal_mode.width) * 2;
				DBG("TW: l0addr: " << l0addr << " l1addr " << l1addr);
				memcpy(&buffer[l0addr], &buffer[l1addr], terminal_mode.width * 2);
				uint64_t end = bt_rtc_millis();
				DBG("TW: Scroll: " << end - start << "ms");
			}else{
				uint64_t start = bt_rtc_millis();
				size_t ch = 0;
				for(size_t col = 0; col < terminal_mode.width; ++col){
					size_t bufaddr = ((line * terminal_mode.width) + col) * 2;
					if(!compare_chars(tempbuffer[bufaddr], buffer[bufaddr]) || tempbuffer[bufaddr + 1] != buffer[bufaddr + 1] || bufaddr == curpos || bufaddr == lpos){
						buffer[bufaddr] = tempbuffer[bufaddr];
						if(bufaddr == curpos){
							buffer[bufaddr + 1] = ((tempbuffer[bufaddr + 1] & 0x0f) << 4) | ((tempbuffer[bufaddr + 1] & 0xf0) >> 4);
							lpos = curpos;
						}
						else buffer[bufaddr + 1] = tempbuffer[bufaddr + 1];
						uint64_t glyph = get_glyph(buffer[bufaddr + 1], buffer[bufaddr]);
						drawingOps.push_back(GDS_Blit_Op(glyph, 0, 0, font_width, font_height, col * font_width, line * font_height, font_width, font_height));
						addRect(updateRect, {(int32_t)(col * font_width), (int32_t)(line * font_height), font_width, font_height});
						++ch;
					}
				}
				uint64_t end = bt_rtc_millis();
				DBG("TW: line drawn in " << end - start << "ms (" << ch << " changes)");
			}
		}
		uint64_t updateStart = bt_rtc_millis();
		if(drawingOps.size()) GDS_MultiDrawingOps(drawingOps.size(), &drawingOps[0], NULL);
		WM_UpdateRect(updateRect);
		uint64_t updateEnd = bt_rtc_millis();
		DBG("TW: Prep: " << updateStart - prepStart << "ms Update: " << updateEnd - updateStart << "ms");
		updateRect = {0, 0, 0, 0};
		bt_rtc_sleep(50);
	}
}

void renderthread_start(void *){
	render_terminal_thread();
}


void render_terminal(){
	if(!terminal_handle) return;
	if(!renderthread) renderthread = bt_new_thread(&renderthread_start, NULL, renderthread_stack + thread_stack_size);
	curpos = bt_terminal_get_pos(terminal_handle);
	DBG("TW: rt!");
	bt_modify_atom(render_counter, bt_atom_modify::Add, 1);
}

void mainthread(void*){
	size_t cpos  = 0;
	size_t refcount = 0;
	uint8_t textcolours = 0x07; 
	surf = GDS_NewSurface(gds_SurfaceType::Bitmap, terminal_mode.width * font_width, terminal_mode.height * font_height);
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
					DBG("TW: Unhandled backend operation: " << op->type);
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
	if(renderthread){
		endrender = true;
		bt_modify_atom(render_counter, bt_atom_modify::Add, 1);
		bt_wait_thread(renderthread);
	}
	kill_children();
	bt_end_thread();
}

int main(){
	font = GDS_GetFontID(fontName.c_str(), gds_FontStyle::Normal);
	gds_FontInfo info = GDS_GetFontInfo(font);
	font_width = (info.maxW * fontSize) / info.scale;
	font_height = (info.maxH * fontSize) / info.scale;
	DBG("TW: Scale: " << info.scale << " width: " << info.maxW << " size: " << fontSize);
	bt_terminial_init();
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
