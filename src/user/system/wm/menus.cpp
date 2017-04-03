#include "menus.hpp"
#include "drawing.hpp"
#include "metrics.hpp"
#include <gds/libgds.h>
#include <sstream>

#define DBG(x) do{std::stringstream dbgss; dbgss << x << std::endl; bt_zero(dbgss.str().c_str());}while(0)

using namespace std;

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
		if(!cacheNormal) cacheSelected = DrawMenuItem(text, flags, image, width, false);
		return cacheNormal;
	}
}

uint32_t MenuItem::GetHeight(){
	return GetMetric(MenuItemHeight);
}

uint32_t MenuItem::GetMinWidth(){
	if(flags & wm_MenuItemFlags::Seperator){
		return (2 * GetMetric(MenuItemMargin)) + 1;
	}else{
		uint32_t ret = (2 * GetMetric(MenuItemMargin));
		if(image){
			GDS_SelectSurface(image);
			gds_SurfaceInfo image_info = GDS_SurfaceInfo();
			ret += image_info.w;
			ret += GetMetric(MenuItemMargin);
		}
		uint32_t font = GDS_GetFontID(GetSetting(MenuFontName).c_str(), gds_FontStyle::Normal);
		gds_FontInfo finfo = GDS_GetFontInfo(font);
		uint32_t font_width = (finfo.maxW * GetMetric(MenuFontSize)) / finfo.scale;
		ret += font_width * text.length();
		return ret;
	}
}

MenuActionType MenuItem::GetAction(){
	return actionType;
}

uint32_t MenuItem::GetCustomAction(){
	return customID;
}

shared_ptr<Menu> GetMenu(uint64_t /*id*/){
	return NULL;
}

void Menu::Draw(int32_t x, int32_t y){
	DBG("WM: Drawing menu.");
	int32_t cy = y;
	uint32_t width = 0;
	for(auto &i : items){
		uint32_t w = i.second->GetMinWidth();
		if(w > width) width = w;
	}
	DBG("WM: Menu width: " << width);
	for(auto &i : items){
		DBG("WM: Drawing menu item " << i.first);
		uint64_t surf = i.second->Draw(width, false);
		GDS_SelectScreen();
		uint32_t height = i.second->GetHeight();
		GDS_Blit(surf, 0, 0, width, height, x, cy, width, height);
		cy += height;
	}
}

uint32_t Menu::AddMenuItem(std::shared_ptr<MenuItem> i){
	uint32_t ret = ++idCounter;
	items[ret] = i;
	return ret;
}
