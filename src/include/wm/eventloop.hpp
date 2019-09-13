#ifndef _EVENT_HPP
#define _EVENT_HPP

#include <btos.h>
#include <wm/wm.h>
#include <functional>
#include <map>
#include <memory>
#include <vector>
#include <deque>

#include <btos/imessagehandler.hpp>
#include <btos/thread.hpp>
#include <btos/atom.hpp>

#include "window.hpp"
#include "menu.hpp"

namespace btos_api{
namespace wm{

	class EventLoop : public IMessageHandler{
	private:
		std::function<bool(const wm_Event&)> previewer;
		std::map<uint64_t, std::shared_ptr<Window>> windows;
		std::map<uint64_t, std::shared_ptr<Menu>> menus;
		
		std::vector<uint64_t> winRemoveList;
		std::vector<uint64_t> menuRemoveList;
		
		std::map<uint64_t, std::deque<wm_Event>> eventQueues;
		std::vector<Thread> threads;
		std::unique_ptr<Thread> eventThread;
		
		Atom eventSerial = 0;
		bt_handle_t lock = bt_create_lock();
		Atom quitAtom = 0;
		Atom winCountAtom = 0;
		
		friend void EventThread(void *);
		
		void SetupWindow(std::shared_ptr<Window> win, bool independent);
		void StartEventThread();
	public:
		EventLoop();
		EventLoop(const std::vector<std::shared_ptr<Window>> &windows, const std::vector<std::shared_ptr<Menu>> &menus = std::vector<std::shared_ptr<Menu>>());
		~EventLoop();

		void SetPreviewer(std::function<bool(const wm_Event&)> &fn);
		std::function<bool(const wm_Event&)> GetPreviewer();

		void AddWindow(std::shared_ptr<Window> win);
		void RemoveWindow(uint64_t id);
		void AddMenu(std::shared_ptr<Menu> m);
		void RemoveMenu(uint64_t id);

		void RunLoop();
		void RunModal(std::shared_ptr<Window> modal);
		void RunWindow(uint64_t id);
		bool HandleMessage(const Message &msg) override;
		bool HandleEvent(const wm_Event &e);
		
		static EventLoop *GetFor(const Window &win);
		static EventLoop *GetFor(const Menu &menu);
	};

}
}

#endif
