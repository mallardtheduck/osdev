#include <btos.h>
#include <wm/libwm.h>
#include <crt_support.h>
#include "libwm_internal.hpp"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <cstring>
#include <sm/sm.h>

using namespace std;

static bt_pid_t wm_pid = 0;

static bool Init(){
	if(!wm_pid){
		wm_pid = sm::SM_GetService("wm");
		if(!wm_pid){
			cout << "ERROR: Could not communicate with WM." << endl;
			return false;
		}
		return true;
	}
	return true;
}

template<typename T> static T GetContent(const bt_msg_header &msg){
	T ret;
	bt_msg_content((bt_msg_header*)&msg, (void*)&ret, sizeof(ret));
	bt_msg_ack((bt_msg_header*)&msg);
	return ret;
}

static bt_msg_header SendMessage(wm_RequestType::Enum type, size_t size, void* content, bool waitreply){
	if(!wm_pid  && !Init()) return bt_msg_header();
	bt_msg_header msg;
	msg.flags = 0;
	msg.to = wm_pid;
	msg.type = type;
	msg.length = size;
	msg.content = content;
	msg.id = bt_send(msg);
	if(waitreply) {
		bt_msg_header ret;
		bt_msg_filter filter;
		filter.flags = bt_msg_filter_flags::Reply;
		filter.reply_to = msg.id;
		ret = bt_recv_filtered(filter, true);
		while(ret.reply_id != msg.id){
			stringstream ss;
			ss << "LIBWM: Spurious message!" << endl;
			ss << "Message id: " << ret.id << endl;
			ss << "From : " << ret.from << endl;
			ss << "Flags : " << ret.flags << endl;
			ss << "Reply ID: " << ret.reply_id << " (Waiting for: " << msg.id << ")" << endl;
			bt_zero(ss.str().c_str());
			bt_next_msg_filtered(&ret, filter);
		}
		return ret;
	}
	else return bt_msg_header();
}

template<typename T> static bt_msg_header SendMessage(wm_RequestType::Enum type, const T& content, bool waitreply){
	return SendMessage(type, sizeof(T), (void*)&content, waitreply);
}

extern "C" uint64_t WM_SelectWindow(uint64_t id){
	bt_msg_header reply = SendMessage(wm_RequestType::SelectWindow, id, true);
	return GetContent<uint64_t>(reply);
}

extern "C" uint64_t WM_CreateWindow(wm_WindowInfo info){
	bt_msg_header reply = SendMessage(wm_RequestType::CreateWindow, info, true);
	return GetContent<uint64_t>(reply);
}

extern "C" uint64_t WM_NewWindow(int32_t x, int32_t y, uint32_t options, uint32_t subscriptions, uint64_t gds_id, const char *title){
	wm_WindowInfo info;
	info.x = x;
	info.y = y;
	info.options = options;
	info.subscriptions = subscriptions;
	info.gds_id = gds_id;
	strncpy(info.title, title, WM_TITLE_MAX);
	return WM_CreateWindow(info);
}

extern "C" void WM_DestroyWindow(){
	SendMessage(wm_RequestType::DestroyWindow, 0, NULL, false);
}

extern "C" wm_WindowInfo WM_WindowInfo(){
	bt_msg_header reply = SendMessage(wm_RequestType::CreateWindow, 0, NULL, true);
	return GetContent<wm_WindowInfo>(reply);
}

extern "C" void WM_Subscribe(uint32_t events){
	wm_WindowInfo info;
	info.subscriptions = events;
	SendMessage(wm_RequestType::MoveWindow, info, false);
}

extern "C" void WM_Update(){
	SendMessage(wm_RequestType::Update, 0, NULL, false);
}

extern "C" void WM_UpdateRect(int32_t x, int32_t y, uint32_t w, uint32_t h){
	wm_Rect r;
	r.x = x; r.y = y; r.w = w; r.h = h;
	SendMessage(wm_RequestType::UpdateRect, r, false);
}

void WM_UpdateRect(wm_Rect r){
	SendMessage(wm_RequestType::UpdateRect, r, false);
}

extern "C" void WM_ReplaceSurface(uint64_t gds_id){
	SendMessage(wm_RequestType::ReplaceSurface, gds_id, false);
}

extern "C" void WM_MoveWindow(int32_t x, int32_t y){
	wm_WindowInfo info;
	info.x = x; info.y = y;
	SendMessage(wm_RequestType::MoveWindow, info, false);
}

extern "C" void WM_ChangeOptions(uint32_t opts){
	wm_WindowInfo info;
	info.options = opts;
	SendMessage(wm_RequestType::ChangeOptions, info, false);
}

extern "C" void WM_SetTitle(const char *title){
	wm_WindowInfo info;
	strncpy(info.title, title, WM_TITLE_MAX);
	SendMessage(wm_RequestType::SetTitle, info, false);
}

void WM_SetTitle(const std::string title){
	WM_SetTitle(title.c_str());
}

extern "C" bt_msg_filter WM_GetEventFilter(){
	bt_msg_filter filter;
	filter.flags = (bt_msg_filter_flags::Enum)(bt_msg_filter_flags::From | bt_msg_filter_flags::Type);
	filter.pid = wm_pid;
	filter.type = wm_MessageType::Event;
	return filter;
}

extern "C" wm_Event WM_ParseMessage(bt_msg_header *msg){
	wm_Event ret;
	if(msg && msg->from == wm_pid && msg->type == wm_MessageType::Event && msg->length == sizeof(wm_Event)){
		ret = GetContent<wm_Event>(*msg);
	}else{
		ret.type = wm_EventType::None;
	}
	return ret;
}

extern "C" wm_Event WM_GetEvent(){
	bt_msg_filter filter = WM_GetEventFilter();
	bt_msg_header msg = bt_recv_filtered(filter, true);
	wm_Event ret;
	ret = WM_ParseMessage(&msg);
	bt_msg_ack(&msg);
	return ret;
}

extern "C" void WM_Sync(){
	bt_msg_header reply = SendMessage(wm_RequestType::Sync, 0, NULL, true);
	GetContent<bool>(reply);
}

extern "C" uint64_t WM_SelectMenu(uint64_t id){
	bt_msg_header reply = SendMessage(wm_RequestType::SelectMenu, id, true);
	return GetContent<uint64_t>(reply);
}

extern "C" uint64_t WM_CreateMenu(){
	bt_msg_header reply = SendMessage(wm_RequestType::CreateMenu, 0, NULL, true);
	return GetContent<uint64_t>(reply);
}

extern "C" void WM_DestroyMenu(uint64_t id){
	SendMessage(wm_RequestType::DestroyMenu, id, false);
}

extern "C" uint32_t WM_AddMenuItem(wm_MenuItem i){
	bt_msg_header reply = SendMessage(wm_RequestType::AddMenuItem, i, true);
	return GetContent<uint32_t>(reply);
}

extern "C" void WM_RemoveMenuItem(uint32_t id){
	SendMessage(wm_RequestType::RemoveMenuItem, id, false);
}

extern "C" void WM_ShowMenu(wm_Rect pos){
	SendMessage(wm_RequestType::ShowMenu, pos, false);
}

extern "C" void WM_SelectWindowMenu(){
	SendMessage(wm_RequestType::SelectWindowMenu, 0, NULL, false);
}

extern "C" void WM_SetWindowMenu(){
	SendMessage(wm_RequestType::SetWindowMenu, 0, NULL, false);
}

extern "C" void WM_UnSetWindowMenu(){
	SendMessage(wm_RequestType::UnSetWindowMenu, 0, NULL, false);
}
