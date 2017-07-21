#ifndef _MENU_HPP
#define _MENU_HPP

#include <wm/wm.h>
#include <gds/surface.hpp>
#include <string>
#include <functional>

namespace btos_api{
namespace wm{

	class Menu;

	class MenuItem : public wm_MenuItem{
	private:
	public:
		MenuItem(uint32_t actionID, const std::string &text, uint32_t flags = wm_MenuItemFlags::Default, const gds::Surface *image = nullptr, const Menu *childMenu = nullptr);
	};

	class Menu{
	private:
		uint64_t id;
		bool owned;
		std::function<bool(int)> handler;

		Menu(const Menu&) = delete;
		Menu operator=(const Menu&) = delete;
		Menu(int) {}
	public:
		Menu();
		Menu(Menu &&m);

		~Menu();
		
		static Menu Wrap(uint64_t id, bool own);

		void Select() const;
		uint64_t GetID() const;

		uint32_t AddItem(const MenuItem &i);
		void RemoveItem(uint32_t idx);

		void SetEventHandler(std::function<bool(int)> fn);
		std::function<bool(int)> GetEventHandler() const;
		virtual bool Event(int action);
	};

}
}
#endif
