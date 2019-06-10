#include <wm/eventloop.hpp>
#include <wm/libwm.h>

using namespace std;

namespace btos_api{
namespace wm{
	
	EventLoop *EventLoop::current = nullptr;

	EventLoop::EventLoop(const vector<shared_ptr<Window>> &wins, const vector<shared_ptr<Menu>> &ms){
		for(auto w : wins){
			AddWindow(w);
		}
		for(auto m : ms){
			AddMenu(m);
		}
	}

	void EventLoop::SetPreviewer(std::function<bool(const wm_Event&)> &fn){
		previewer = fn;
	}
	std::function<bool(const wm_Event&)> EventLoop::GetPreviewer(){
		return previewer;
	}

	void EventLoop::AddWindow(shared_ptr<Window> win){
		windows.insert(make_pair(win->GetID(), win));
	}
	void EventLoop::RemoveWindow(uint64_t id){
		winRemoveList.push_back(id);
	}
	void EventLoop::AddMenu(shared_ptr<Menu> m){
		menus.insert(make_pair(m->GetID(), m));
	}
	void EventLoop::RemoveMenu(uint64_t id){
		menuRemoveList.push_back(id);
	}

	void EventLoop::RunLoop(){
		current = this;
		while(true){
			wm_Event e = WM_GetEvent();
			if(!HandleEvent(e)) break;
		}
		current = nullptr;
	}
	bool EventLoop::HandleMessage(const Message &msg){
		auto header = msg.Header();
		wm_Event e = WM_ParseMessage(&header);
		if(e.type != wm_EventType::None && e.window_id){
			return HandleEvent(e);
		}
		return true;
	}
	bool EventLoop::HandleEvent(const wm_Event &e){
		bool ret = true;
		if(previewer){
			if(!previewer(e)) ret =  false;
		}
		if(ret && windows.find(e.window_id) != windows.end()){
			ret = windows[e.window_id]->Event(e);
		}
		if(ret && e.type == wm_EventType::MenuSelection){
			if(menus.find(e.Menu.menu_id) != menus.end()){
				ret = menus[e.Menu.menu_id]->Event(e.Menu.action);
			}
		}
		for(auto w : winRemoveList) windows.erase(w);
		for(auto m : menuRemoveList) menus.erase(m);
		winRemoveList.clear();
		menuRemoveList.clear();
		if(windows.empty()) ret = false;
		return ret;
	}
	
	EventLoop *EventLoop::GetCurrent(){
		return current;
	}
}
}
