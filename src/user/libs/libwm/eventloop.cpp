#include <wm/eventloop.hpp>
#include <wm/libwm.h>

#include <btos/multiwait.hpp>

#include <util/tinyformat.hpp>

using namespace std;

namespace btos_api{
namespace wm{
	
	static std::vector<EventLoop*> activeLoops;
	static bt_handle_t activeLoopsLock = bt_create_lock();
	
	static void AddLoop(EventLoop *loop){
		bt_lock(activeLoopsLock);
		activeLoops.push_back(loop);
		bt_unlock(activeLoopsLock);
	}
	
	static void RemoveLoop(EventLoop *loop){
		bt_lock(activeLoopsLock);
		activeLoops.erase(std::remove(activeLoops.begin(), activeLoops.end(), loop), activeLoops.end());
		bt_unlock(activeLoopsLock);
	}
	
	void EventThread(void *ptr){
		EventLoop *evt = (EventLoop*)ptr;
		
		auto filt = WM_GetEventFilter();
		auto msgwait = MessageWait(filt);
		auto quitwait = evt->quitAtom.GetWaitFor(AtomValue != 0);
		auto anywait = MultiWait({&msgwait, &quitwait}, MultiWait::WaitMode::Any);
		
		evt->winCountAtom.WaitFor(AtomValue > 0);
		while(true){
			anywait.Wait();
			Handle *h = anywait.GetTriggerHandle();
			if(h == &msgwait){
				auto hdr = msgwait.GetMessage();
				if(!evt->HandleMessage(hdr)) break;
				bt_lock(evt->lock);
				bool found;
				do{
					found = false;
					for(auto i = evt->threads.begin(); i != evt->threads.end(); ++i){
						if(!i->Query()){
							evt->threads.erase(i);
							found = true;
							break;
						}
					}
				}while(found);
				bt_unlock(evt->lock);
				hdr.Acknowledge();
			}else break;
		}
		evt->quitAtom.Modify(AtomValue = 1);
	}
	
	struct ThreadArgs{
		EventLoop *evt;
		uint64_t winId;
		Atom running = 0;
	};
	
	void WinEventThread(void *ptr){
		ThreadArgs *a = (ThreadArgs*)ptr;
		EventLoop *evt = a->evt;
		uint64_t winId = a->winId;
		//tfm::printf("WinEventThread: ID: %s\n", winId);
		a->running.Modify(AtomValue = 1);
		evt->RunWindow(winId);
	}
	
	void EventLoop::SetupWindow(std::shared_ptr<Window> win, bool independent){
		bt_lock(lock);
		auto id = win->GetID();
		//tfm::printf("EventLoop::SetupWindow %s %s\n", id, independent);
		windows.insert(make_pair(id, win));
		winCountAtom.Modify(AtomValue = windows.size());
		eventQueues[id] = {};
		if(independent){
			ThreadArgs targs;
			targs.evt = this;
			targs.winId = id;
			threads.emplace_back(Thread {&WinEventThread, (void*)&targs});
			targs.running.WaitFor(AtomValue != 0);
		}
		bt_unlock(lock);
	}

	EventLoop::EventLoop() : eventThread(&EventThread, (void*) this) {
		AddLoop(this);
	}
	
	EventLoop::EventLoop(const vector<shared_ptr<Window>> &wins, const vector<shared_ptr<Menu>> &ms) :
	eventThread(&EventThread, (void*) this)
	{
		AddLoop(this);
		for(auto w : wins){
			AddWindow(w);
		}
		for(auto m : ms){
			AddMenu(m);
		}
	}
	
	EventLoop::~EventLoop(){
		quitAtom.Modify(AtomValue = 2);
		eventThread.Wait();
		RemoveLoop(this);
	}

	void EventLoop::SetPreviewer(std::function<bool(const wm_Event&)> &fn){
		previewer = fn;
	}
	std::function<bool(const wm_Event&)> EventLoop::GetPreviewer(){
		return previewer;
	}

	void EventLoop::AddWindow(shared_ptr<Window> win){
		SetupWindow(win, true);
	}
	void EventLoop::RemoveWindow(uint64_t id){
		bt_lock(lock);
		winRemoveList.push_back(id);
		eventQueues.erase(id);
		bt_unlock(lock);
	}
	void EventLoop::AddMenu(shared_ptr<Menu> m){
		bt_lock(lock);
		menus.insert(make_pair(m->GetID(), m));
		bt_unlock(lock);
	}
	void EventLoop::RemoveMenu(uint64_t id){
		bt_lock(lock);
		menuRemoveList.push_back(id);
		bt_unlock(lock);
	}

	void EventLoop::RunLoop(){
		quitAtom.WaitFor(AtomValue != 0);
	}
	
	void EventLoop::RunModal(std::shared_ptr<Window> modal){
		SetupWindow(modal, false);
		RunWindow(modal->GetID());
	}
	
	void EventLoop::RunWindow(uint64_t id){
		auto serial = eventSerial.Read();
		bool quit = false;
		while(!quit){
			bt_lock(lock);
			while(eventQueues.find(id) != eventQueues.end() && windows.find(id) != windows.end() && !eventQueues[id].empty()){
				auto win = windows[id];
				auto event = eventQueues[id].front();
				eventQueues[id].pop_front();
				bt_unlock(lock);
				auto res = win->Event(event);
				if(res && event.type == wm_EventType::MenuSelection){
					bt_lock(lock);
					if(menus.find(event.Menu.menu_id) != menus.end()){
						auto menu = menus[event.Menu.menu_id];
						bt_unlock(lock);
						res = menu->Event(event.Menu.action);
					}else bt_unlock(lock);
				}
				if(!res) quitAtom.Modify(AtomValue = 1);
				bt_lock(lock);
				for(auto w : winRemoveList) windows.erase(w);
				for(auto m : menuRemoveList) menus.erase(m);
				winRemoveList.clear();
				menuRemoveList.clear();
				winCountAtom.Modify(AtomValue = windows.size());
				if(windows.size() == 0) quitAtom.Modify(AtomValue = 1);
			}
			if(windows.find(id) == windows.end()){
				//tfm::printf("EventLoop::RunWindow: window %s not in collection. Quitting.\n", id);
				quit = true;
			}
			bt_unlock(lock);
			if(quitAtom.Read()){
				//tfm::printf("EventLoop::RunWindow: quitAtom activated. Quitting.\n");
				quit = true;
			}
			if(!quit) serial = eventSerial.WaitFor(AtomValue != serial);
		}
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
		bt_lock(lock);
		if(ret && windows.find(e.window_id) != windows.end()){
			auto &eventQ = eventQueues[e.window_id];
			if(e.type == wm_EventType::PointerMove){
				auto i = find_if(eventQ.begin(), eventQ.end(), [](const wm_Event &e){return e.type == wm_EventType::PointerMove;});
				if(i != eventQ.end()) eventQ.erase(i);
			}
			eventQ.push_back(e);
			eventSerial.Modify(++AtomValue);
		}
		bt_unlock(lock);
		return ret;
	}
	
	EventLoop *EventLoop::GetFor(const Window &win){
		typedef decltype(EventLoop::windows)::value_type wins_element;
		
		EventLoop *ret = nullptr;
		bt_lock(activeLoopsLock);
		for(auto loop : activeLoops){
			auto &wins = loop->windows;
			if(std::any_of(wins.begin(), wins.end(), [&](wins_element &w){
				return w.second->GetID() == win.GetID();
			})){
				ret = loop;
				break;
			}
		}
		bt_unlock(activeLoopsLock);
		return ret;
	}
	
	EventLoop *EventLoop::GetFor(const Menu &menu){
		typedef decltype(EventLoop::menus)::value_type menus_element;
		
		EventLoop *ret = nullptr;
		bt_lock(activeLoopsLock);
		for(auto loop : activeLoops){
			auto &menus = loop->menus;
			if(std::any_of(menus.begin(), menus.end(), [&](menus_element &w){
				return w.second->GetID() == menu.GetID();
			})){
				ret = loop;
				break;
			}
		}
		bt_unlock(activeLoopsLock);
		return ret;
	}
}
}
