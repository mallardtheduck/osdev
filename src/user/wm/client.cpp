#include <wm/wm.h>
#include "client.hpp"
#include "windows.hpp"

using namespace std;

template<typename T> static T GetContent(const bt_msg_header &msg){
	T ret;
	bt_msg_content((bt_msg_header*)&msg, (void*)&ret, sizeof(ret));
	return ret;
}

template<typename T> static void SendReply(const bt_msg_header &msg, const T &content) {
	bt_msg_header reply;
	reply.to = msg.from;
	reply.reply_id = msg.id;
	reply.flags = bt_msg_flags::Reply;
	reply.length = sizeof(content);
	reply.content = (void*)&content;
	bt_send(reply);
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

void Client::ProcessMessage(const bt_msg_header &msg){
	switch(msg.type){
		case wm_RequestType::SelectWindow:{
			uint64_t id = GetContent<uint64_t>(msg);
			if(windows.find(id) != windows.end()){
				currentWindow = windows[id];
				SendReply(msg, id);
			}
			break;
		}
		case wm_RequestType::CreateWindow:{
			wm_WindowInfo info = GetContent<wm_WindowInfo>(msg);
			shared_ptr<Window> win(new Window(info.gds_id));
			win->SetPosition({info.x, info.y});
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
			uint64_t id = GetContent<uint64_t>(msg);
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
				info.gds_id = currentWindow->GetSurface();
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
				wm_WindowInfo info = GetContent<wm_WindowInfo>(msg);
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
		case wm_RequestType::ReplaceSurface:{
			//TODO: Implement
			break;
		}
		case wm_RequestType::MoveWindow:{
			if(currentWindow){
				wm_WindowInfo info = GetContent<wm_WindowInfo>(msg);
				currentWindow->SetPosition({info.x, info.y});
			}
			break;
		}
		case wm_RequestType::ChangeOptions:{
			if(currentWindow){
				wm_WindowInfo info = GetContent<wm_WindowInfo>(msg);
				currentWindow->SetOptions(info.options);
			}
			break;
		}
		case wm_RequestType::SetTitle:{
			if(currentWindow){
				wm_WindowInfo info = GetContent<wm_WindowInfo>(msg);
				currentWindow->SetTitle(info.title);
			}
			break;
		}
	}
}

void Client::SendEvent(const wm_Event &e){
	eventQ.push(e);
	if(!msgPending) SendNextEvent();
}

void Client::SendNextEvent(){
	if(eventQ.size()){
		SendMessage(pid, wm_MessageType::Event, eventQ.front());
		eventQ.pop();
		msgPending = true;
	}else{
		msgPending = false;
	}
}