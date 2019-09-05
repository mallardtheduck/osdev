#include <btos.h>
#include <gds/libgds.h>
#include <crt_support.h>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "libgds_internal.hpp"
#include <cstring>
#include <sm/sm.h>

using namespace std;

static bt_pid_t gds_pid = 0;
static uint64_t current_surface = 0;
static bool current_known = false;
static bool current_screen = false;

static bool Init(){
	if(!gds_pid){
		gds_pid = sm::SM_GetService("gds");
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
		ret = bt_recv_filtered(filter, true);
		while(ret.reply_id != msg.id){
			stringstream ss;
			ss << "LIBGDS: Spurious message!" << endl;
			ss << "Message id: " << ret.id << endl;
			ss << "From : " << ret.from << endl;
			ss << "Flags : " << ret.flags << endl;
			ss << "Critical : " << ret.critical << endl;
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

extern "C" uint64_t GDS_NewSurface(gds_SurfaceType::Enum type, uint32_t w, uint32_t h, uint32_t scale, uint32_t colourType, uint64_t shmRegion, size_t shmOffset){
	gds_SurfaceInfo info;
	info.type = type;
	info.w = w; info.h = h;
	info.scale = scale;
	info.colourType = colourType;
	info.shmRegion = shmRegion;
	info.shmOffset = shmOffset;
	bt_msg_header reply = SendMessage(gds_MsgType::NewSurface, sizeof(info), (void*)&info, true);
	uint64_t ret = GetContent<uint64_t>(&reply);
	current_known = true;
	current_screen = false;
	current_surface = ret;
	return ret;
}

extern "C" void GDS_DeleteSurface(){
	current_known = false;
	current_screen = false;
	SendMessage(gds_MsgType::DeleteSurface, 0, NULL, false);
}

extern "C" uint64_t GDS_SelectSurface(uint64_t id){
	if(current_known && id == current_surface) return current_surface;
	bt_msg_header reply = SendMessage(gds_MsgType::SelectSurface, sizeof(id), (void*)&id, true);
	uint64_t ret = GetContent<uint64_t>(&reply);
	current_known = true;
	current_screen = false;
	current_surface = ret;
	return ret;
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
	if(current_screen && !current_known) return;
	current_known = false;
	current_screen = true;
	SendMessage(gds_MsgType::SelectScreen, 0, NULL, false);
}

extern "C" void GDS_UpdateScreen(uint32_t x, uint32_t y, uint32_t w, uint32_t h){
	gds_ScreenUpdateRect rect;
	rect.x = x; rect.y = y; rect.w = w; rect.h = h;
	SendMessage(gds_MsgType::UpdateScreen, sizeof(rect), (void*)&rect, false);
}

extern "C" void GDS_SetScreenMode(bt_vidmode mode){
	current_known = false;
	current_screen = false;
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

extern "C" uint32_t GDS_GetFontID(const char *name, gds_FontStyle::Enum style){
	gds_FontRequest i;
	strncpy(i.name, name, FONT_NAME_MAX);
	i.fontStyle = style;
	bt_msg_header reply = SendMessage(gds_MsgType::GetFontID, sizeof(i), (void*)&i, true);
	return GetContent<uint32_t>(&reply);
}

extern "C" gds_FontInfo GDS_GetFontInfo(uint32_t fontID){
	bt_msg_header reply = SendMessage(gds_MsgType::GetFontInfo, sizeof(fontID), (void*)&fontID, true);
	return GetContent<gds_FontInfo>(&reply);
}

extern "C" gds_GlyphInfo GDS_GetGlyphInfo(uint32_t fontID, size_t size, char ch){
	gds_GlyphInfo_Request req = {fontID, size, ch};
	bt_msg_header reply = SendMessage(gds_MsgType::GetGlyphInfo, sizeof(req), (void*)&req, true);
	return GetContent<gds_GlyphInfo>(&reply);
}

extern "C" uint32_t GDS_GetMaxFontID(){
	bt_msg_header reply = SendMessage(gds_MsgType::GetMaxFontID, 0, NULL, true);
	return GetContent<uint32_t>(&reply);
}

extern "C" void GDS_MultiDrawingOps(size_t count, gds_DrawingOp *ops, uint32_t *ids){
	size_t ops_per_req = (BT_MSG_MAX - sizeof(gds_MultiOps)) / sizeof(gds_DrawingOp);
	gds_MultiOps *mops = (gds_MultiOps*)malloc(BT_MSG_MAX);
	for(size_t i = 0; i < count; i += ops_per_req){
		size_t op_count = min(ops_per_req, count - i);
		mops->count = op_count;
		memcpy(mops->ops, &ops[i], op_count * sizeof(gds_DrawingOp));
		bt_msg_header reply = SendMessage(gds_MsgType::MultiDrawingOps, BT_MSG_MAX, (void*)mops, true);
		if(ids) bt_msg_content(&reply, &ids[i], sizeof(uint32_t) * op_count);
		bt_msg_ack(&reply);
	}
	free(mops);
}

extern "C" void GDS_ReorderOp(uint32_t op, uint32_t ref, gds_ReorderMode::Enum mode){
	gds_ReorderOp rop = {op, ref, mode};
	SendMessage(gds_MsgType::ReorderOp, sizeof(rop), (void*)&rop, false);
}

extern "C" void GDS_ClearSurface(){
	SendMessage(gds_MsgType::ClearSurface, 0, NULL, false);
}

extern "C" gds_TextMeasurements *GDS_MeasureText(gds_TextParameters p, const char *text){
	auto paramReply = SendMessage(gds_MsgType::SetTextParameters, sizeof(p), (void*)&p, true);
	bt_msg_ack(&paramReply);
	auto measureReply = SendMessage(gds_MsgType::MeasureText, strlen(text) + 1, (void*)text, true);
	gds_TextMeasurements *ret = (gds_TextMeasurements*)malloc(measureReply.length);
	bt_msg_content(&measureReply, (void*)ret, measureReply.length);
	bt_msg_ack(&measureReply);
	return ret;
}

extern "C" void GDS_Compress(){
	SendMessage(gds_MsgType::Compress, 0, NULL, false);
}
