#include <wm/eventloop.hpp>
#include <wm/libwm.h>

using namespace std;

namespace btos_api{
namespace wm{

	void EventLoop::SetPreviewer(std::function<bool(const wm_Event&)> &fn){
		previewer = fn;
	}
	std::function<bool(const wm_Event&)> EventLoop::GetPreviewer(){
		return previewer;
	}

	void EventLoop::AddWindow(shared_ptr<Window> win){
		windows[win->GetID()] = win;
	}
	void EventLoop::RemoveWindow(uint64_t id){
		windows.erase(id);
	}
	void EventLoop::AddMenu(shared_ptr<Menu> m){
		menus[m->GetID()] = m;
	}
	void EventLoop::RemoveMenu(uint64_t id){
		menus.erase(id);
	}

	void EventLoop::RunLoop(){
		while(true){
			wm_Event e = WM_GetEvent();
			if(!HandleEvent(e)) return;
		}
	}
	bool EventLoop::HandleMessage(const Message &msg){
		auto header = msg.Header();
		wm_Event e = WM_ParseMessage(&header);
		if(e.window_id){
			return HandleEvent(e);
		}
		return true;
	}
	bool EventLoop::HandleEvent(const wm_Event &e){
		if(previewer){
			if(!previewer(e)) return false;
		}
		if(windows.find(e.window_id) != windows.end()){
			if(!windows[e.window_id]->Event(e)) return false;
		}
		if(e.type == wm_EventType::MenuSelection){
			if(menus.find(e.Menu.menu_id) != menus.end()){
				if(!menus[e.Menu.menu_id]->Event(e.Menu.action)) return false;
			}
		}
		return true;
	}
}
}
