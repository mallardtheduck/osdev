#ifndef _EVENT_HPP
#define _EVENT_HPP

#include <btos.h>
#include <wm/wm.h>
#include <functional>
#include <map>
#include <memory>

#include <btos/imessagehandler.hpp>

#include "window.hpp"
#include "menu.hpp"

namespace btos_api{
namespace wm{

	class EventLoop : public IMessageHandler{
	private:
		std::function<bool(const wm_Event&)> previewer;
		std::map<uint64_t, std::shared_ptr<Window>> windows;
		std::map<uint64_t, std::shared_ptr<Menu>> menus;

	public:
		void SetPreviewer(std::function<bool(const wm_Event&)> &fn);
		std::function<bool(const wm_Event&)> GetPreviewer();

		void AddWindow(std::shared_ptr<Window> win);
		void RemoveWindow(uint64_t id);
		void AddMenu(std::shared_ptr<Menu> m);
		void RemoveMenu(uint64_t id);

		void RunLoop();
		bool HandleMessage(const Message &msg) override;
		bool HandleEvent(const wm_Event &e);
	};

}
}

#endif
