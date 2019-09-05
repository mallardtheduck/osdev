#include "gds.hpp"
#include "bitmap_surface.hpp"
#include "vector_surface.hpp"
#include "shm_surface.hpp"
#include "screen.hpp"
#include <algorithm>
#include <sstream>
#include <btos/message.hpp>
#include <btos/messageloop.hpp>
#include <sm/sm.h>
#include "fonts.hpp"

using namespace std;

const size_t MaxSurfaceSize = 32768;

map<uint64_t, weak_ptr<Surface>> allSurfaces;
static uint64_t surfaceCounter = 0;

static map<bt_pid_t, shared_ptr<Client>> allClients;

static int32_t surfaceDeleteCounter = 0;
static const int32_t surfaceDeleteThreshold = 16;

static void PruneSurfaces(){
	for(auto i = allSurfaces.begin(), last = allSurfaces.end(); i != last; ){
		if(i->second.expired()) i = allSurfaces.erase(i);
		else ++i;
	}
	surfaceDeleteCounter = 0;
}

template<typename T> static void SendReply(const Message &msg, const T &content) {
	msg.SendReply(content, 0);
}

Client::Client(bt_pid_t p) : pid(p) {
}

Client::~Client() {
	surfaces.clear();
	PruneSurfaces();
}

bool Client::HandleMessage(const Message &msg) {
	if(msg.From() != pid) return true;
	/*stringstream d;
	d << "GDS: Message type: " << msg.type << " from: " << msg.from << endl;
	bt_zero(d.str().c_str());*/
	switch(msg.Type()) {
		case gds_MsgType::Info:
			gds_Info info;
			info.clientCount = 0;
			info.surfaceCount = 0;
			info.version = 0;
			SendReply(msg, info);
			break;
		case gds_MsgType::NewSurface:{
			gds_SurfaceInfo s_info = msg.Content<gds_SurfaceInfo>();
			if(s_info.w != 0 && s_info.w < MaxSurfaceSize && s_info.h != 0 && s_info.h < MaxSurfaceSize){
				Surface *newsurf;
				newsurf = NULL;
				switch(s_info.type) {
					case gds_SurfaceType::Bitmap:
						newsurf = new BitmapSurface(s_info.w, s_info.h, s_info.colourType, s_info.scale);
						break;
					case gds_SurfaceType::Vector:
						newsurf = new VectorSurface(s_info.w, s_info.h, s_info.colourType, s_info.scale);
						break;
					case gds_SurfaceType::Memory:
						newsurf = new SHMSurface(s_info.w, s_info.h, s_info.colourType, s_info.scale, s_info.shmRegion, s_info.shmOffset);
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
			}
			SendReply(msg, s_info);
			break;
		}
		case gds_MsgType::DeleteSurface:{
			if(currentSurface) {
				surfaces.erase(currentSurface);
				currentSurface.reset();
				++surfaceDeleteCounter;
				if(surfaceDeleteCounter > surfaceDeleteThreshold) PruneSurfaces();
			}
			break;
		}
		case gds_MsgType::SelectSurface:{
			uint64_t select_id = msg.Content<uint64_t>();
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
		}
		case gds_MsgType::AddDrawingOp:{
			if(currentSurface) {
				gds_DrawingOp op = msg.Content<gds_DrawingOp>();
				size_t op_id = currentSurface->AddOperation(op);
				SendReply(msg, op_id);
			} else {
				SendReply(msg, (size_t)0);
			}
			break;
		}
		case gds_MsgType::RemoveDrawingOp:
			if(currentSurface) {
				size_t op_id = msg.Content<size_t>();
				currentSurface->RemoveOperation(op_id);
			}
			break;
		case gds_MsgType::GetDrawingOp:{
			gds_DrawingOp ret_op;
			ret_op.type = gds_DrawingOpType::None;
			if(currentSurface) {
				size_t op_id = msg.Content<size_t>();
				ret_op = currentSurface->GetOperation(op_id);
			}
			SendReply(msg, ret_op);
			break;
		}
		case gds_MsgType::SurfaceInfo:{
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
		}
		case gds_MsgType::SetScale:{
			if(currentSurface) {
				uint32_t newscale = msg.Content<uint32_t>();
				currentSurface->SetScale(newscale);
			}
			break;
		}
		case gds_MsgType::GetColour:{
			if(currentSurface) {
				gds_TrueColour truecol = msg.Content<gds_TrueColour>();
				uint32_t col = currentSurface->GetColour(truecol.r, truecol.g, truecol.b, truecol.a);
				SendReply(msg, col);
			} else {
				SendReply(msg, (uint32_t)0);
			}
			break;
		}
		case gds_MsgType::SetOpParameters:{
			if(currentSurface){
				shared_ptr<gds_OpParameters> params((gds_OpParameters*)new char[msg.Length()+1]());
				((char*)(params.get()))[msg.Length()] = '\0';
				bt_msg_header head = msg.Header();
				bt_msg_content(&head, (void*)params.get(), msg.Length());
				currentSurface->SetOpParameters(params);
			}
			break;
		}
		case gds_MsgType::SelectScreen:{
			currentSurface = GetScreen();
			break;
		}
		case gds_MsgType::UpdateScreen:{
			gds_ScreenUpdateRect screen_rect = msg.Content<gds_ScreenUpdateRect>();
			GetScreen()->UpdateScreen(screen_rect.x, screen_rect.y, screen_rect.w, screen_rect.h);
			break;
		}
		case gds_MsgType::SetScreenMode:{
			bt_vidmode mode = msg.Content<bt_vidmode>();
			GetScreen()->SetMode(mode.width, mode.height, mode.bpp);
			break;
		}
		case gds_MsgType::SetCursor:{
				gds_CursorInfo cinfo = msg.Content<gds_CursorInfo>();
				shared_ptr<Surface> cur_surface = allSurfaces[cinfo.surfaceId].lock();
				if(cur_surface) {
					GetScreen()->SetCursorImage(*cur_surface->Render(GetScreen()->GetScale()), cinfo.hotx, cinfo.hoty);
				}
			}
			break;
		case gds_MsgType::CursorVisibility:{
			bool cur_visible = msg.Content<bool>();
			if(cur_visible) GetScreen()->ShowCursor();
			else GetScreen()->HideCursor();
			break;
		}
		case gds_MsgType::GetFontID:{
				gds_FontRequest req = msg.Content<gds_FontRequest>();
				shared_ptr<gds_FontInfo> f = GetFontManager()->GetFont(req.name, (gds_FontStyle::Enum)req.fontStyle);
				if(f){
					SendReply(msg, f->fontID);
				}else{
					SendReply(msg, (uint32_t)0);
				}
			}
			break;
		case gds_MsgType::GetFontInfo:{
				uint32_t fontID = msg.Content<uint32_t>();
				shared_ptr<gds_FontInfo> f = GetFontManager()->GetFont(fontID);
				if(f){
					SendReply(msg, *f);
				}else{
					SendReply(msg, gds_FontInfo());
				}
			}
			break;
		case gds_MsgType::GetGlyphInfo:{
				gds_GlyphInfo_Request req = msg.Content<gds_GlyphInfo_Request>();
				gds_GlyphInfo info = GetFontManager()->GetGlyphInfo(req.fontID, req.size, req.ch);
				SendReply(msg, info);
			}
			break;
		case gds_MsgType::GetMaxFontID:{
				uint32_t maxFontId = GetFontManager()->GetMaxFontID();
				SendReply(msg, maxFontId);
			}
			break;
		case gds_MsgType::MultiDrawingOps:{
			if(currentSurface){
				gds_MultiOps *mops = (gds_MultiOps *)malloc(msg.Length());
				bt_msg_header head = msg.Header();
				bt_msg_content(&head, (void*)mops, msg.Length());
				if(mops->count <= (BT_MSG_MAX - sizeof(gds_MultiOps)) / sizeof(gds_DrawingOp)){
					uint32_t *ids = new uint32_t[mops->count];
					for(size_t i = 0; i < mops->count; ++i){
						ids[i] = currentSurface->AddOperation(mops->ops[i]);
					}
					bt_msg_header reply;
					reply.to = msg.From();
					reply.reply_id = msg.ID();
					reply.flags = bt_msg_flags::Reply;
					reply.length = mops->count * sizeof(uint32_t);
					reply.content = (void*)ids;
					bt_send(reply);
					delete[] ids;
				}
				free(mops);
			}else{
				SendReply(msg, (uint32_t)0);
			}
			break;
		case gds_MsgType::ReorderOp:{
				if(currentSurface){
					gds_ReorderOp rop = msg.Content<gds_ReorderOp>();
					currentSurface->ReorderOp(rop.op, rop.ref, rop.mode);
				}			
			}
			break;
		}
		case gds_MsgType::ClearSurface:{
			if(currentSurface){
				currentSurface->Clear();
			}
		}
		case gds_MsgType::SetTextParameters:{
			txtParams = msg.Content<gds_TextParameters>();
			SendReply(msg, 0);
			break;
		}
		case gds_MsgType::MeasureText:{
			if(currentSurface){
				std::unique_ptr<char[]> text {new char[msg.Length()]};
				bt_msg_header head = msg.Header();
				bt_msg_content(&head, (void*)text.get(), msg.Length());
				auto ret = currentSurface->MeasureText(txtParams, text.get());
				bt_msg_header reply;
				reply.to = msg.From();
				reply.reply_id = msg.ID();
				reply.flags = bt_msg_flags::Reply;
				reply.length = sizeof(*ret) + (ret->charXCount * sizeof(double));
				reply.content = ret.get();
				bt_send(reply);
			}
			break;
		}
		case gds_MsgType::Compress:{
			if(currentSurface) currentSurface->Compress();
			break;
		}
		default:{
			DBG("GDS: Unknown request " << msg.Type() << " from PID: " << msg.From());
			break;
		}
	}
	return true;
}


void Service(bt_pid_t root_pid) {
	bt_subscribe(bt_kernel_messages::ProcessEnd);
	MessageLoop msgLoop;
	msgLoop.SetPreviewer([&](const Message &msg) -> bool{
		if(msg.From() == 0 && msg.Source() == 0 && msg.Type() == bt_kernel_messages::ProcessEnd) {
			bt_pid_t pid = msg.Content<bt_pid_t>();
			stringstream ss;
			ss << "GDS: PID: " << pid << " terminated." << endl;
			bt_zero(ss.str().c_str());
			if(allClients.find(pid) != allClients.end()){
				allClients.erase(pid);
			}
			if(pid == root_pid) return false;
		} else if(msg.From() == sm::SM_GetServerPID()) {
			if(msg.Type() == sm::sm_ServiceRequest::StopService) return false;
		} else {
			auto from = msg.From();
			if(allClients.find(from) == allClients.end()) {
				auto newclient = make_shared<Client>(msg.From());
				if(newclient) {
					allClients.insert(make_pair(from, newclient));
				}
			}
		}
		return true;
	});
	auto gdsHandler = make_shared<CustomHandler>([&](const Message &msg) -> bool{
		auto from = msg.From();
		if(allClients.find(from) != allClients.end()){
			if(msg.Type() == gds_MsgType::SelectScreen && root_pid == 0) root_pid = msg.From();
			return allClients.at(from)->HandleMessage(msg);
		}else return true;
	});
	msgLoop.AddHandler(gdsHandler);
	msgLoop.RunLoop();
}
