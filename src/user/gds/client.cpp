#include "gds.hpp"
#include "bitmap_surface.hpp"
#include "screen.hpp"
#include <map>
#include <algorithm>

using namespace std;

static map<uint64_t, weak_ptr<Surface>> allSurfaces;
static uint64_t surfaceCounter = 0;

static map<bt_pid_t, shared_ptr<Client>> allClients;

static void SendReply(bt_msg_header msg, size_t len, void *content) {
	bt_msg_header reply;
	reply.to = msg.from;
	reply.reply_id = msg.id;
	reply.flags = bt_msg_flags::Reply;
	reply.length = len;
	reply.content = content;
	bt_send(reply);
}

Client::Client() {
}

Client::~Client() {
}

void Client::ProcessMessage(bt_msg_header msg) {
	switch(msg.type) {
		case gds_MsgType::Info:
			gds_Info info;
			info.clientCount = 0;
			info.surfaceCount = 0;
			info.version = 0;
			SendReply(msg, sizeof(info), (void*)&info);
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
			SendReply(msg, sizeof(s_info), (void*)&s_info);
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
			SendReply(msg, sizeof(select_id), (void*)&select_id);
			break;
		case gds_MsgType::AddDrawingOp:
			if(currentSurface) {
				DrawingOp op;
				bt_msg_content(&msg, (void*)&op, sizeof(op));
				size_t op_id = currentSurface->AddOperation(op);
				SendReply(msg, sizeof(op_id), (void*)&op_id);
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
			DrawingOp ret_op;
			ret_op.type = gds_DrawingOpType::None;
			if(currentSurface) {
				size_t op_id = 0;
				bt_msg_content(&msg, (void*)op_id, sizeof(op_id));
				ret_op = currentSurface->GetOperation(op_id);
				SendReply(msg, sizeof(ret_op), (void*)&ret_op);
			}
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
			SendReply(msg, sizeof(ret_s_info), (void*)&ret_s_info);
			break;
		case gds_MsgType::SetScale:
			if(currentSurface) {
				uint32_t newscale;
				bt_msg_content(&msg, (void*)&newscale, sizeof(newscale));
				currentSurface->SetScale(newscale);
			}
			break;
		case gds_MsgType::SelectScreen:
			currentSurface.reset(GetScreen());
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
	}
}


void Service() {
	bt_subscribe(bt_kernel_messages::ProcessEnd);
	bt_msg_header msg = bt_recv(true);
	while(true) {
		if(msg.from == 0 && msg.source == 0 && msg.type == bt_kernel_messages::ProcessEnd) {
			bt_pid_t pid;
			bt_msg_content(&msg, (void*)pid, sizeof(pid));
			allClients.erase(pid);
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
