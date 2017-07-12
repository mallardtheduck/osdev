#ifndef _MENU_HPP
#define _MENU_HPP

#include <wm/wm.h>
#include <gds/surface.hpp>
#include <string>

namespace btos_api{
namespace wm{

/*
	uint32_t actionID;
	char text[WM_MENUTEXT_MAX+1];
	uint32_t flags;
	uint64_t image;
	uint64_t childMenu;*/

	class Menu;

	class MenuItem : public wm_MenuItem{
	private:
	public:
		MenuItem(uint32_t actionID, const std::string &text, const gds::Surface *image = nullptr, const Menu *childMenu = nullptr);
	};

	class Menu{
	private:
		uint64_t id;
		bool owned;

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
	};

}
}
#endif
