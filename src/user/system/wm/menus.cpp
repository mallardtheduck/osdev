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
			uint32_t font = GDS_GetFontID(GetSetting(MenuFontName).c_str(), gds_FontStyle::Normal);
			for(const char c : text){
				gds_GlyphInfo ginfo = GDS_GetGlyphInfo(font, GetMetric(MenuFontSize), c);
				ret += ginfo.w;
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

void Menu::Draw(int32_t x, int32_t y, const Point &cursor, bool force){
	if(!x && !y){
		x = lx;
		y = ly;
	}
	uint32_t nsel = GetSelected(cursor);
	if(!force && lsel == nsel) return;
	DBG("WM: Drawing menu at (" << x << ", " << y << ")");
	int32_t cy = y;
	uint32_t width = 0;
	for(auto &i : items){
		uint32_t w = i.second->GetMinWidth();
		if(w > width) width = w;
	}
	DBG("WM: Menu width: " << width);
	for(auto &i : items){
		bool selected = false;
		uint32_t height = i.second->GetHeight();
		if(i.first == nsel) selected = true;
		DBG("WM: Drawing menu item " << i.first << " at (" << x << ", " << cy << ")");
		uint64_t surf = i.second->Draw(width, selected);
		GDS_SelectScreen();
		DBG("WM: Menu item GDS id: " << surf);
		GDS_Blit(surf, 0, 0, width, height, x, cy, width, height);
		cy += height;
	}
	DrawBorder(x, y, width, cy - y);
	lx = x;
	ly = y;
	lsel = nsel;
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

pair<Rect, bool> MenuPointerInput(const bt_terminal_pointer_event &pevent){
	vector<Rect> updates;
	bool handled = false;
	if(pevent.type == bt_terminal_pointer_event_type::Move){
		for(auto &menu : currentMenus){
			if(InRect(pevent.x, pevent.y, menu->GetBoundingRect())){
				menu->Draw(0, 0, {(int32_t)pevent.x, (int32_t)pevent.y});
				return { menu->GetBoundingRect(), true };
			}
		}
	}else if(pevent.type == bt_terminal_pointer_event_type::ButtonDown){
		while(currentMenus.size()){
			if(InRect(pevent.x, pevent.y, currentMenus.back()->GetBoundingRect())){
				//Do something
				handled = true;
				break;
			}else{
				DrawWindows(currentMenus.back()->GetBoundingRect());
				updates.push_back(currentMenus.back()->GetBoundingRect());
				currentMenus.pop_back();
			}
		}
	}else if(pevent.type == bt_terminal_pointer_event_type::ButtonUp){
		while(currentMenus.size()){
			if(InRect(pevent.x, pevent.y, currentMenus.back()->GetBoundingRect())){
				//Do something
				handled = true;
			}
			DrawWindows(currentMenus.back()->GetBoundingRect());
			updates.push_back(currentMenus.back()->GetBoundingRect());
			currentMenus.pop_back();
		}
	}
	RefreshScreen(updates);
	return {{0, 0, 0, 0}, handled};
}

void OpenMenu(std::shared_ptr<Menu> menu, uint32_t x, uint32_t y){
	currentMenus.push_back(menu);
	menu->Draw(x, y, {0, 0}, true);
}

shared_ptr<Menu> GetMenu(uint64_t /*id*/){
	return NULL;
}

