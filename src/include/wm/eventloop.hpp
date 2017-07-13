#ifndef _EVENT_HPP
#define _EVENT_HPP

#include <btos.h>
#include <wm/wm.h>
#include <functional>
#include <map>
#include <memory>

#include "window.hpp"
#include "menu.hpp"

namespace btos_api{
namespace wm{

	class EventLoop{
	private:
		std::function<bool(const wm_Event&)> previewer;
		std::function<bool(const bt_msg_header &)> otherHandler;
		std::map<uint64_t, std::shared_ptr<Window>> windows;
		std::map<uint64_t, std::shared_ptr<Menu>> menus;

	public:
		void SetPreviewer(std::function<bool(const wm_Event&)> &fn);
		std::function<bool(const wm_Event&)> GetPreviewer();
		
		void SetOtherHandler(std::function<bool(const bt_msg_header &)> fn);
		std::function<bool(const bt_msg_header &)> GetOtherHandler();

		void AddWindow(std::shared_ptr<Window> win);
		void RemoveWindow(uint64_t id);
		void AddMenu(std::shared_ptr<Menu> m);
		void RemoveMenu(uint64_t id);

		void RunLoop();
		bool HandleMessage(const bt_msg_header &msg);
		bool HandleEvent(const wm_Event &e);
	};

}
}

#endif
