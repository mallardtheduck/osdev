#include <gds/libgds.h>
#include <btos_stubs.h>
#include <crt_support.h>
#include "libgds_internal.hpp"
#include <cstdlib>
#include <sstream>
#include <iostream>

using namespace std;

static bt_pid_t gds_pid = 0;

static bool Init(){
	if(!gds_pid){
		string pid_str = get_env("GDS_PID");
		gds_pid = strtoull(pid_str.c_str(), NULL, 10);
		if(!gds_pid){
			cout << "ERROR: Could not communicate with GDS." << endl;
			return false;
		}
		return true;
	}
	return true;
}

template<typename T> static T GetContent(bt_msg_header *msg){
	T ret;
	bt_msg_content(msg, (void*)&ret, sizeof(ret));
	bt_msg_ack(msg);
	return ret;
}

static bt_msg_header SendMessage(gds_MsgType::Enum type, size_t size, void* content, bool waitreply){
	if(!gds_pid  && !Init()) return bt_msg_header();
	bt_msg_header msg;
	msg.flags = 0;
	msg.to = gds_pid;
	msg.type = type;
	msg.length = size;
	msg.content = content;
	msg.id = bt_send(msg);
	if(waitreply) {
		bt_msg_header ret;
		bt_msg_filter filter;
		filter.flags = bt_msg_filter_flags::Reply;
		filter.reply_to = msg.id;
		ret = bt_recv_filtered(filter);
		while(ret.reply_id != msg.id){
			stringstream ss;
			ss << "LIBGDS: Spurious message!" << endl;
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

extern "C" gds_Info GDS_Info(){
	bt_msg_header reply = SendMessage(gds_MsgType::Info, 0, NULL, true);
	return GetContent<gds_Info>(&reply);
}

extern "C" uint64_t GDS_NewSurface(gds_SurfaceType::Enum type, uint32_t w, uint32_t h, uint32_t scale, gds_ColourType::Enum colourType){
	gds_SurfaceInfo info;
	info.type = type;
	info.w = w; info.h = h;
	info.scale = scale;
	info.colourType = colourType;
	bt_msg_header reply = SendMessage(gds_MsgType::NewSurface, sizeof(info), (void*)&info, true);
	return GetContent<uint64_t>(&reply);
}

extern "C" void GDS_DeleteSurface(){
	SendMessage(gds_MsgType::DeleteSurface, 0, NULL, false);
}

extern "C" uint64_t GDS_SelectSurface(uint64_t id){
	bt_msg_header reply = SendMessage(gds_MsgType::SelectSurface, sizeof(id), (void*)&id, true);
	return GetContent<uint64_t>(&reply);
}

extern "C" size_t GDS_AddDrawingOp(gds_DrawingOp op){
	bt_msg_header reply = SendMessage(gds_MsgType::AddDrawingOp, sizeof(op), (void*)&op, true);
	return GetContent<size_t>(&reply);
}

extern "C" void GDS_RemoveDrawingOp(size_t index){
	SendMessage(gds_MsgType::RemoveDrawingOp, sizeof(index), (void*)&index, false);
}

extern "C" gds_DrawingOp GDS_GetDrawingOp(size_t index){
	bt_msg_header reply = SendMessage(gds_MsgType::GetDrawingOp, sizeof(index), (void*)&index, true);
	return GetContent<gds_DrawingOp>(&reply);
}

extern "C" gds_SurfaceInfo GDS_SurfaceInfo(){
	bt_msg_header reply = SendMessage(gds_MsgType::SurfaceInfo, 0, NULL, true);
	return GetContent<gds_SurfaceInfo>(&reply);
}

extern "C" void GDS_SetScale(uint32_t scale){
	SendMessage(gds_MsgType::SetScale, sizeof(scale), (void*)scale, false);
}

extern "C" uint32_t GDS_GetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
	gds_TrueColour truecol;
	truecol.r = r; truecol.g = g; truecol.b = b; truecol.a = a;
	bt_msg_header reply = SendMessage(gds_MsgType::GetColour, sizeof(truecol), (void*)&truecol, true);
	return GetContent<uint32_t>(&reply);
}

extern "C" void GDS_SetOpParameters(const gds_OpParameters *params){
	SendMessage(gds_MsgType::SetOpParameters, sizeof(gds_OpParameters) + params->size, (void*)params, false);
}

extern "C" void GDS_SelectScreen(){
	SendMessage(gds_MsgType::SelectScreen, 0, NULL, false);
}

extern "C" void GDS_UpdateScreen(uint32_t x, uint32_t y, uint32_t w, uint32_t h){
	gds_ScreenUpdateRect rect;
	rect.x = x; rect.y = y; rect.w = w; rect.h = h;
	SendMessage(gds_MsgType::UpdateScreen, sizeof(rect), (void*)&rect, false);
}

extern "C" void GDS_SetScreenMode(bt_vidmode mode){
	SendMessage(gds_MsgType::SetScreenMode, sizeof(mode), (void*)&mode, false);
}

extern "C" void GDS_SetCursor(uint64_t surfaceID, uint32_t hotx, uint32_t hoty){
	gds_CursorInfo info;
	info.hotx = hotx;
	info.hoty = hoty;
	info.surfaceId = surfaceID;
	SendMessage(gds_MsgType::SetCursor, sizeof(info), (void*)&info, false);
}

extern "C" void GDS_CursorVisibility(bool visible){
	SendMessage(gds_MsgType::CursorVisibility, sizeof(visible), (void*)&visible, false);
}