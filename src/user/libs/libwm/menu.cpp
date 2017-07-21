#include <wm/menu.hpp>
#include <cstring>
#include <algorithm>
#include <wm/libwm.h>

using namespace std;

namespace btos_api{
namespace wm{

	MenuItem::MenuItem(uint32_t aID, const string &t, uint32_t f, const gds::Surface *i, const Menu *c)
	{
		actionID = aID;
		memcpy(text, t.c_str(), min(t.length() + 1, WM_MENUTEXT_MAX));
		flags = f;
		image = i ? i->GetID() : 0;
		childMenu = c ? c->GetID() : 0;
	}


	Menu::Menu() : 
		id(WM_CreateMenu()), owned(true)
	{}
	Menu::Menu(Menu &&m) : id(m.id), owned(m.owned){
		m.id = 0;
		m.owned = false;
	}

	Menu::~Menu(){
		if(owned && id){
			Select();
			WM_DestroyMenu(id);
		}
	}

	Menu Menu::Wrap(uint64_t id, bool own){
		Menu ret(0);
		ret.id = id;
		ret.owned = own;
		return ret;
	}

	void Menu::Select() const{
		WM_SelectMenu(id);
	}
	uint64_t Menu::GetID() const{
		return id;
	}

	uint32_t Menu::AddItem(const MenuItem &i){
		Select();
		return WM_AddMenuItem(i);
	}
	void Menu::RemoveItem(uint32_t idx){
		Select();
		WM_RemoveMenuItem(idx);
	}

	void Menu::SetEventHandler(std::function<bool(int)> fn){
		handler = fn;
	}
	std::function<bool(int)> Menu::GetEventHandler() const{
		return handler;
	}
	bool Menu::Event(int action){
		if(handler) return handler(action);
		else return true;
	}
}
}
