#include "menus.hpp"
#include "drawing.hpp"
#include "metrics.hpp"
#include "windows.hpp"
#include <gds/libgds.h>
#include <sstream>

#define DBG(x) do{std::stringstream dbgss; dbgss << x << std::endl; bt_zero(dbgss.str().c_str());}while(0)

using namespace std;

static vector<shared_ptr<Menu>> currentMenus;

MenuItem::MenuItem(const wm_MenuItem &i) :
	MenuItem(i.text, i.flags, GetMenu(i.childMenu), i.image, ((i.flags & wm_MenuItemFlags::ChildMenu) ? MenuActionType::ChildMenu : ((i.flags & wm_MenuItemFlags::Seperator) ? MenuActionType::None : MenuActionType::Custom)), i.actionID) {}

MenuItem::MenuItem(const std::string t, uint32_t f, std::shared_ptr<Menu> cM, uint64_t i, MenuActionType a, uint32_t cID) :
	text(t), flags(f), childMenu(cM), image(i), actionType(a), customID(cID) {}
	
MenuItem::~MenuItem(){
	DropCache();
}

void MenuItem::DropCache(){
	if(cacheNormal){
		GDS_SelectSurface(cacheNormal);
		GDS_DeleteSurface();
		cacheNormal = 0;
	}
	if(cacheSelected){
		GDS_SelectSurface(cacheSelected);
		GDS_DeleteSurface();
		cacheSelected = 0;
	}
	cacheWidth = 0;
}

uint64_t MenuItem::Draw(uint32_t width, bool selected){
	if(width != cacheWidth) DropCache();
	cacheWidth = width;
	if(selected){
		if(!cacheSelected) cacheSelected = DrawMenuItem(text, flags, image, width, true);
		return cacheSelected;
	}else{
		if(!cacheNormal) cacheNormal = DrawMenuItem(text, flags, image, width, false);
		return cacheNormal;
	}
}

uint32_t MenuItem::GetHeight(){
	if((flags & wm_MenuItemFlags::Seperator)) return (GetMetric(MenuItemMargin) * 2) + 1;
	else return GetMetric(MenuItemHeight);
}

uint32_t MenuItem::GetMinWidth(){
	uint32_t ret = minWidth;
	if(!ret){
		if((flags & wm_MenuItemFlags::Seperator)){
			ret = (2 * GetMetric(MenuItemMargin)) + 1;
		}else{
			ret = (2 * GetMetric(MenuItemMargin));
			if(image){
				GDS_SelectSurface(image);
				gds_SurfaceInfo image_info = GDS_SurfaceInfo();
				ret += image_info.w;
				ret += GetMetric(MenuItemMargin);
			}
			if(!(flags & wm_MenuItemFlags::ImageOnly)){
				uint32_t font = GDS_GetFontID(GetSetting(MenuFontName).c_str(), gds_FontStyle::Normal);
				for(const char c : text){
					gds_GlyphInfo ginfo = GDS_GetGlyphInfo(font, GetMetric(MenuFontSize), c);
					ret += ginfo.w;
				}
			}
			if((flags & wm_MenuItemFlags::ChildMenu)){
				ret += GetMetric(MenuItemHeight);
			}
		}
		minWidth = ret;
	}
	return ret;
}

MenuActionType MenuItem::GetAction(){
	return actionType;
}

uint32_t MenuItem::GetCustomAction(){
	return customID;
}

shared_ptr<Menu> MenuItem::GetChildMenu(){
	return childMenu;
}

bool Menu::Draw(int32_t x, int32_t y, const Point &cursor, bool force){
	if(!x && !y){
		x = lx;
		y = ly;
	}
	uint32_t nsel = lsel;
	if(cursor){
		nsel = GetSelected(cursor);
		if(!force && lsel == nsel) return false;
	}
	DBG("WM: Drawing menu at (" << x << ", " << y << ")");
	int32_t cy = y;
	uint32_t width = 0;
	for(auto &i : items){
		uint32_t w = i.second->GetMinWidth();
		if(w > width) width = w;
	}
	for(auto &i : items){
		bool selected = false;
		uint32_t height = i.second->GetHeight();
		if(i.first == nsel) selected = true;
		uint64_t surf = i.second->Draw(width, selected);
		GDS_SelectScreen();
		GDS_Blit(surf, 0, 0, width, height, x, cy, width, height);
		cy += height;
	}
	DrawBorder(x, y, width, cy - y);
	lx = x;
	ly = y;
	lsel = nsel;
	open = true;
	return true;
}

void Menu::Redraw(){
	Draw(0, 0, {0, 0}, true);
}

uint32_t Menu::AddMenuItem(std::shared_ptr<MenuItem> i){
	uint32_t ret = ++idCounter;
	items[ret] = i;
	return ret;
}

Rect Menu::GetBoundingRect(){
	uint32_t width = 0;
	uint32_t height = 0;
	for(auto &i : items){
		uint32_t w = i.second->GetMinWidth();
		if(w > width) width = w;
		height += i.second->GetHeight();
	}
	return {lx, ly, width, height};
}

uint32_t Menu::GetSelected(const Point &cursor){
	Rect brect = GetBoundingRect();
	if(!InRect(cursor, brect)) return 0;
	int32_t cy = ly;
	for(auto &i : items){
		uint32_t height = i.second->GetHeight();
		if(InRect(cursor, {lx, cy, brect.w, height})) return i.first;
		cy += height;
	}
	return 0;
}

shared_ptr<MenuItem> Menu::GetItem(uint32_t id){
	for(auto i : items){
		if(i.first == id) return i.second;
	}
	return NULL;
}

void Menu::Reset(){
	lx = 0;
	ly = 0;
	lsel = 0;
	open = false;
	childMenu.reset();
}

bool Menu::IsOpen(){
	return open;
}

void Menu::PointerInput(const bt_terminal_pointer_event &pevent){
	if(pevent.type == bt_terminal_pointer_event_type::Move){
		uint32_t selId = GetSelected({(int32_t)pevent.x, (int32_t)pevent.y});
		if(Draw(0, 0, {(int32_t)pevent.x, (int32_t)pevent.y})) RefreshScreen(GetBoundingRect());
		if(selId){
			if(selId != lsel && childMenu && childMenu->IsOpen()){
				DBG("WM: Closing child menu.");
				CloseMenu(childMenu);
				childMenu.reset();
			}
		}
	}else if(pevent.type == bt_terminal_pointer_event_type::ButtonDown){
		uint32_t selId = GetSelected({(int32_t)pevent.x, (int32_t)pevent.y});
		if(selId){
			auto item = GetItem(selId);
			if(item->GetAction() == MenuActionType::ChildMenu){
				if(childMenu && childMenu->IsOpen()){
					DBG("WM: Closing child menu.");
					CloseMenu(childMenu);
					childMenu.reset();
				}
				DBG("WM: Opening child menu.");
				OpenMenu(item->GetChildMenu(), pevent.x, pevent.y);
				childMenu = item->GetChildMenu();
			}
		}
	}else if(pevent.type == bt_terminal_pointer_event_type::ButtonUp){
		uint32_t selId = GetSelected({(int32_t)pevent.x, (int32_t)pevent.y});
		if(selId){
			auto item = GetItem(selId);
			if(item->GetAction() != MenuActionType::ChildMenu){
				CloseMenu(NULL);
			}
		}else{
			CloseMenu(NULL);
		}
	}
}

bool MenuPointerInput(const bt_terminal_pointer_event &pevent){
	bool handled = false;
	vector<shared_ptr<Menu>> toBeClosed;
	for(auto i = currentMenus.rbegin(); i != currentMenus.rend(); ++i){
		auto &menu = *i;
		if(InRect(pevent.x, pevent.y, menu->GetBoundingRect())){
			menu->PointerInput(pevent);
			handled = true;
			break;
		}else if(pevent.type == bt_terminal_pointer_event_type::ButtonDown){
			toBeClosed.push_back(menu);
		}
	}
	for(auto t : toBeClosed){
		CloseMenu(t);
	}
	return handled;
}

void OpenMenu(std::shared_ptr<Menu> menu, uint32_t x, uint32_t y){
	currentMenus.push_back(menu);
	menu->Draw(x, y, {0, 0}, true);
	RefreshScreen(menu->GetBoundingRect());
}

void CloseMenu(std::shared_ptr<Menu> menu){
	vector<Rect> refreshList;
	while(currentMenus.size()){
		auto &cmenu = currentMenus.back();
		currentMenus.pop_back();
		DrawWindows(cmenu->GetBoundingRect());
		refreshList.push_back(cmenu->GetBoundingRect());
		cmenu->Reset();
		if(menu && cmenu == menu) break;
	}
	for(auto &menu : currentMenus){
		menu->Redraw();
	}
	RefreshScreen(refreshList);	
}

shared_ptr<Menu> GetMenu(uint64_t /*id*/){
	return NULL;
}

shared_ptr<Menu> GetTestMenu(){
	static shared_ptr<Menu> testMenu;
	if(!testMenu){
		testMenu = make_shared<Menu>();
		testMenu->AddMenuItem(make_shared<MenuItem>("One Apple", wm_MenuItemFlags::Default, shared_ptr<Menu>(), 0, MenuActionType::None, 0));
		testMenu->AddMenuItem(make_shared<MenuItem>("Two Potatoes", wm_MenuItemFlags::Default, shared_ptr<Menu>(), 0, MenuActionType::None, 0));
		testMenu->AddMenuItem(make_shared<MenuItem>("Three Chickens", wm_MenuItemFlags::Default, shared_ptr<Menu>(), 0, MenuActionType::None, 0));
		testMenu->AddMenuItem(make_shared<MenuItem>("", wm_MenuItemFlags::Seperator, shared_ptr<Menu>(), 0, MenuActionType::None, 0));
		testMenu->AddMenuItem(make_shared<MenuItem>("Four Lemon Cheesecakes", wm_MenuItemFlags::Default, shared_ptr<Menu>(), 0, MenuActionType::None, 0));
		auto testChildMenu = make_shared<Menu>();
		testChildMenu->AddMenuItem(make_shared<MenuItem>("Child Menu Item 1", wm_MenuItemFlags::Default, shared_ptr<Menu>(), 0, MenuActionType::None, 0));
		testChildMenu->AddMenuItem(make_shared<MenuItem>("Child Menu Item 2", wm_MenuItemFlags::Default, shared_ptr<Menu>(), 0, MenuActionType::None, 0));
		testMenu->AddMenuItem(make_shared<MenuItem>("Five Gold Rings", wm_MenuItemFlags::ChildMenu, testChildMenu, 0, MenuActionType::ChildMenu, 0));
	}
	return testMenu;
}
