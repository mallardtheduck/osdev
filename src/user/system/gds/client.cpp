#include "gds.hpp"
#include "bitmap_surface.hpp"
#include "screen.hpp"
#include <algorithm>
#include <sstream>
#include "fonts.hpp"

using namespace std;

map<uint64_t, weak_ptr<Surface>> allSurfaces;
static uint64_t surfaceCounter = 0;

static map<bt_pid_t, shared_ptr<Client>> allClients;

template<typename T> static void SendReply(const bt_msg_header &msg, const T &content) {
	bt_msg_header reply;
	reply.to = msg.from;
	reply.reply_id = msg.id;
	reply.flags = bt_msg_flags::Reply;
	reply.length = sizeof(content);
	reply.content = (void*)&content;
	bt_send(reply);
}

Client::Client() {
}

Client::~Client() {
}

void Client::ProcessMessage(bt_msg_header msg) {
	/*stringstream d;
	d << "GDS: Message type: " << msg.type << " from: " << msg.from << endl;
	bt_zero(d.str().c_str());*/
	switch(msg.type) {
		case gds_MsgType::Info:
			gds_Info info;
			info.clientCount = 0;
			info.surfaceCount = 0;
			info.version = 0;
			SendReply(msg, info);
			break;
		case gds_MsgType::NewSurface:
			gds_SurfaceInfo s_info;
			bt_msg_content(&msg, (void*)&s_info, sizeof(s_info));
			Surface *newsurf;
			newsurf = NULL;
			switch(s_info.type) {
				case gds_SurfaceType::Bitmap:
					newsurf = new BitmapSurface(s_info.w, s_info.h, (s_info.colourType == gds_ColourType::Indexed), s_info.scale);
					break;
				default:
					break;
			}
			if(newsurf) {
				s_info.id = ++surfaceCounter;
				newsurf->id = s_info.id;
				shared_ptr<Surface> ptr(newsurf);
				surfaces.insert(ptr);
				allSurfaces.insert(pair<uint64_t, weak_ptr<Surface>>(s_info.id, ptr));
				currentSurface = ptr;
			}
			SendReply(msg, s_info);
			break;
		case gds_MsgType::DeleteSurface:
			if(currentSurface) {
				surfaces.erase(currentSurface);
				currentSurface.reset();
			}
			break;
		case gds_MsgType::SelectSurface:
			uint64_t select_id;
			bt_msg_content(&msg, (void*)&select_id, sizeof(select_id));
			try {
				currentSurface = allSurfaces.at(select_id).lock();
				if(!currentSurface) allSurfaces.erase(select_id);
				surfaces.insert(currentSurface);
			} catch(out_of_range &) {
				currentSurface.reset();
			}
			if(currentSurface) {
				select_id = currentSurface->id;
			} else {
				select_id = 0;
			}
			SendReply(msg, select_id);
			break;
		case gds_MsgType::AddDrawingOp:
			if(currentSurface) {
				gds_DrawingOp op;
				bt_msg_content(&msg, (void*)&op, sizeof(op));
				size_t op_id = currentSurface->AddOperation(op);
				SendReply(msg, op_id);
			} else {
				SendReply(msg, (size_t)0);
			}
			break;
		case gds_MsgType::RemoveDrawingOp:
			if(currentSurface) {
				size_t op_id = 0;
				bt_msg_content(&msg, (void*)op_id, sizeof(op_id));
				currentSurface->RemoveOperation(op_id);
			}
			break;
		case gds_MsgType::GetDrawingOp:
			gds_DrawingOp ret_op;
			ret_op.type = gds_DrawingOpType::None;
			if(currentSurface) {
				size_t op_id = 0;
				bt_msg_content(&msg, (void*)op_id, sizeof(op_id));
				ret_op = currentSurface->GetOperation(op_id);
			}
			SendReply(msg, ret_op);
			break;
		case gds_MsgType::SurfaceInfo:
			gds_SurfaceInfo ret_s_info;
			ret_s_info.type = gds_SurfaceType::None;
			if(currentSurface) {
				ret_s_info.type = currentSurface->GetType();
				ret_s_info.id = currentSurface->id;
				ret_s_info.w = currentSurface->GetWidth();
				ret_s_info.h = currentSurface->GetHeight();
				ret_s_info.colourType = (currentSurface->GetDepth() > 8) ? gds_ColourType::True : gds_ColourType::Indexed;
				ret_s_info.scale = currentSurface->GetScale();
			}
			SendReply(msg, ret_s_info);
			break;
		case gds_MsgType::SetScale:
			if(currentSurface) {
				uint32_t newscale;
				bt_msg_content(&msg, (void*)&newscale, sizeof(newscale));
				currentSurface->SetScale(newscale);
			}
			break;
		case gds_MsgType::GetColour:
			if(currentSurface) {
				gds_TrueColour truecol;
				bt_msg_content(&msg, (void*)&truecol, sizeof(truecol));
				uint32_t col = currentSurface->GetColour(truecol.r, truecol.g, truecol.b, truecol.a);
				SendReply(msg, col);
			} else {
				SendReply(msg, (uint32_t)0);
			}
			break;
		case gds_MsgType::SetOpParameters:
			if(currentSurface){
				shared_ptr<gds_OpParameters> params((gds_OpParameters*)new char[msg.length+1]());
				((char*)(params.get()))[msg.length] = '\0';
				bt_msg_content(&msg, (void*)params.get(), msg.length);
				currentSurface->SetOpParameters(params);
			}
			break;
		case gds_MsgType::SelectScreen:
			currentSurface = GetScreen();
			break;
		case gds_MsgType::UpdateScreen:
			gds_ScreenUpdateRect screen_rect;
			bt_msg_content(&msg, (void*)&screen_rect, sizeof(screen_rect));
			GetScreen()->UpdateScreen(screen_rect.x, screen_rect.y, screen_rect.w, screen_rect.h);
			break;
		case gds_MsgType::SetScreenMode:
			bt_vidmode mode;
			bt_msg_content(&msg, (void*)&mode, sizeof(mode));
			GetScreen()->SetMode(mode.width, mode.height, mode.bpp);
			break;
		case gds_MsgType::SetCursor: {
				gds_CursorInfo cinfo;
				bt_msg_content(&msg, (void*)&cinfo, sizeof(cinfo));
				shared_ptr<Surface> cur_surface = allSurfaces[cinfo.surfaceId].lock();
				if(cur_surface) {
					GetScreen()->SetCursorImage(*cur_surface->Render(GetScreen()->GetScale()), cinfo.hotx, cinfo.hoty);
				}
			}
			break;
		case gds_MsgType::CursorVisibility:
			bool cur_visible;
			bt_msg_content(&msg, (void*)&cur_visible, sizeof(cur_visible));
			if(cur_visible) GetScreen()->ShowCursor();
			else GetScreen()->HideCursor();
			break;
		case gds_MsgType::GetFontID:{
				gds_FontRequest req;
				bt_msg_content(&msg, (void*)&req, sizeof(req));
				shared_ptr<gds_FontInfo> f = GetFontManager()->GetFont(req.name, (gds_FontStyle::Enum)req.fontStyle);
				if(f){
					SendReply(msg, f->fontID);
				}else{
					SendReply(msg, (uint32_t)0);
				}
			}
			break;
		case gds_MsgType::GetFontInfo:{
				uint32_t fontID;
				bt_msg_content(&msg, (void*)&fontID, sizeof(fontID));
				shared_ptr<gds_FontInfo> f = GetFontManager()->GetFont(fontID);
				if(f){
					SendReply(msg, *f);
				}else{
					SendReply(msg, gds_FontInfo());
				}
			}
			break;
		case gds_MsgType::GetGlyphInfo:{
				gds_GlyphInfo_Request req;
				bt_msg_content(&msg, (void*)&req, sizeof(req));
				gds_GlyphInfo info = GetFontManager()->GetGlyphInfo(req.fontID, req.size, req.ch);
				SendReply(msg, info);
			}
			break;
	}
}


void Service(bt_pid_t root_pid) {
	bt_subscribe(bt_kernel_messages::ProcessEnd);
	bt_msg_header msg = bt_recv(true);
	while(true) {
		if(msg.from == 0 && msg.source == 0 && msg.type == bt_kernel_messages::ProcessEnd) {
			bt_pid_t pid = 0;
			bt_msg_content(&msg, (void*)&pid, sizeof(pid));
			stringstream ss;
			ss << "GDS: PID: " << pid << " terminated." << endl;
			bt_zero(ss.str().c_str());
			allClients.erase(pid);
			if(pid == root_pid) return;
		} else {
			if(allClients.find(msg.from) == allClients.end()) {
				Client *newclient = new Client();
				if(newclient) {
					shared_ptr<Client> ptr(newclient);
					allClients.insert(pair<bt_pid_t, shared_ptr<Client>>(msg.from, ptr));
				}
			}
			try {
				allClients.at(msg.from)->ProcessMessage(msg);
			} catch(out_of_range&) {}
		}
		bt_next_msg(&msg);
	}
}
