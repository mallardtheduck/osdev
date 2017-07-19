#include <wm/wm.h>
#include <btos/message.hpp>
#include "client.hpp"
#include "windows.hpp"

#include <sstream>
#include <algorithm>

#define DBG(x) do{std::stringstream dbgss; dbgss << x << std::endl; bt_zero(dbgss.str().c_str());}while(0)

using namespace std;
using namespace gds;

template<typename T> static void SendReply(const Message &msg, const T &content) {
	msg.SendReply(content);
}

template<typename T> static void SendMessage(bt_pid_t to, wm_MessageType::Enum type, const T &content) {
	bt_msg_header msg;
	msg.type = type;
	msg.to = to;
	msg.flags = 0;
	msg.length = sizeof(content);
	msg.content = (void*)&content;
	bt_send(msg);
}

Client::Client(bt_pid_t p): pid(p) 
{}

Client::~Client(){
	for(auto win: windows){
		RemoveWindow(win.first);
	}
}

bool Client::HandleMessage(const Message &msg){
	if(msg.From() != pid) return true;
	switch(msg.Type()){
		case wm_RequestType::SelectWindow:{
			uint64_t id = msg.Content<uint64_t>();
			if(windows.find(id) != windows.end()){
				currentWindow = windows[id];
				SendReply(msg, id);
			}
			break;
		}
		case wm_RequestType::CreateWindow:{
			wm_WindowInfo info = msg.Content<wm_WindowInfo>();
			shared_ptr<Window> win = make_shared<Window>(make_shared<Surface>(Surface::Wrap(info.gds_id, true)));
			win->SetPosition({info.x, info.y});
			win->SetOptions(info.options);
			win->SetTitle(info.title);
			win->Subscribe(info.subscriptions);
			win->SetOwner(shared_from_this());
			uint64_t id = AddWindow(win);
			windows.insert({id, win});
			BringToFront(win);
			DrawAndRefreshWindows(win->GetBoundingRect());
			currentWindow =	win;
			SendReply(msg, id);
			break;
		}
		case wm_RequestType::DestroyWindow:{
			uint64_t id = msg.Content<uint64_t>();
			if(windows.find(id) != windows.end()){
				RemoveWindow(id);
				if(windows[id] == currentWindow) currentWindow.reset();
				windows.erase(id);
			}
		}
		case wm_RequestType::WindowInfo:{
			wm_WindowInfo info;
			if(currentWindow){
				Point p = currentWindow->GetPosition();
				info.x = p.x;
				info.y = p.y;
				info.options = wm_WindowOptions::Visible;
				info.subscriptions = currentWindow->Subscribe();
				info.gds_id = currentWindow->GetSurface()->GetID();
			}else{
				info.x = 0;
				info.y = 0;
				info.options = 0;
				info.subscriptions = 0;
				info.gds_id = 0;
			}
			SendReply(msg, info);
			break;
		}
		case wm_RequestType::Subscribe:{
			if(currentWindow){
				wm_WindowInfo info = msg.Content<wm_WindowInfo>();
				currentWindow->Subscribe(info.subscriptions);
			}
			break;
		}
		case wm_RequestType::Update:{
			if(currentWindow){
				DrawAndRefreshWindows(currentWindow->GetBoundingRect());
			}
			break;
		}
		case wm_RequestType::UpdateRect:{
			if(currentWindow){
				wm_Rect r = msg.Content<wm_Rect>();
				Rect rect = {r.x, r.y, r.w, r.h};
				Point p = currentWindow->GetContentPosition();
				rect = Reoriginate(rect, {-p.x, -p.y});
				DrawAndRefreshWindows(rect, currentWindow->id);
			}
			break;
		}
		case wm_RequestType::ReplaceSurface:{
			//TODO: Implement
			break;
		}
		case wm_RequestType::MoveWindow:{
			if(currentWindow){
				wm_WindowInfo info = msg.Content<wm_WindowInfo>();
				currentWindow->SetPosition({info.x, info.y});
			}
			break;
		}
		case wm_RequestType::ChangeOptions:{
			if(currentWindow){
				wm_WindowInfo info = msg.Content<wm_WindowInfo>();
				currentWindow->SetOptions(info.options);
			}
			break;
		}
		case wm_RequestType::SetTitle:{
			if(currentWindow){
				wm_WindowInfo info = msg.Content<wm_WindowInfo>();
				currentWindow->SetTitle(info.title);
			}
			break;
		}
		case wm_RequestType::Sync:{
			SendReply(msg, true);
		}
		break;
		case wm_RequestType::SelectMenu:{
			uint64_t id = msg.Content<uint64_t>();
			if(menus.find(id) != menus.end()){
				currentMenu = menus[id];
				SendReply(msg, id);
			}
			break;	
		}
		case wm_RequestType::CreateMenu:{
			auto menu = CreateMenu();
			menus[menu->id] = menu;
			currentMenu = menu;
			SendReply(msg, menu->id);
			break;
		}
		case wm_RequestType::DestroyMenu:{
			uint64_t id = msg.Content<uint64_t>();
			if(menus.find(id) != menus.end()){
				if(menus[id] == currentMenu) currentMenu.reset();
				menus.erase(id);
			}
			break;
		}
		case wm_RequestType::AddMenuItem:{
			if(currentMenu){
				wm_MenuItem item = msg.Content<wm_MenuItem>();
				uint32_t itemId = currentMenu->AddMenuItem(make_shared<MenuItem>(item));
				SendReply(msg, itemId);
			}
			break;
		}
		case wm_RequestType::RemoveMenuItem:{
			if(currentMenu){
				uint32_t itemId = msg.Content<uint32_t>();
				currentMenu->RemoveMenuItem(itemId);
			}
			break;
		}
		case wm_RequestType::ReOrderMenu:{
			//TODO: Implement
			break;
		}
		case wm_RequestType::MenuInfo:{
			//TODO: Implement
			break;
		}
		case wm_RequestType::ShowMenu:{
			if(currentWindow && currentMenu){
				wm_Rect menuPoint = msg.Content<wm_Rect>();
				Point winPoint = currentWindow->GetContentPosition();
				OpenMenu(currentMenu, currentWindow, {winPoint.x + menuPoint.x, winPoint.y + menuPoint.y});
			}
			break;
		}
		case wm_RequestType::SelectWindowMenu:{
			if(currentWindow) currentMenu = currentWindow->GetWindowMenu();
			break;
		}
		case wm_RequestType::SetWindowMenu:{
			if(currentWindow && currentMenu) currentWindow->SetWindowMenu(currentMenu);
			break;
		}
		case wm_RequestType::UnSetWindowMenu:{
			if(currentWindow) currentWindow->SetWindowMenu(nullptr);
			break;
		}
	}
	return true;
}

void Client::SendEvent(const wm_Event &e){
	if(msgPending && e.type == wm_EventType::PointerMove){
		auto i = find_if(eventQ.begin(), eventQ.end(), [](const wm_Event &e){return e.type == wm_EventType::PointerMove;});
		if(i != eventQ.end()) eventQ.erase(i);
	}
	eventQ.push_back(e);
	if(!msgPending) SendNextEvent();
}

void Client::SendNextEvent(){
	if(eventQ.size()){
		SendMessage(pid, wm_MessageType::Event, eventQ.front());
		eventQ.pop_front();
		msgPending = true;
	}else{
		msgPending = false;
	}
}
