#ifndef _MENUS_HPP
#define _MENUS_HPP

#include <wm/wm.h>
#include <string>
#include <memory>
#include <map>
#include <dev/terminal.h>

#include "rect.hpp"

enum class MenuActionType{
	Close,
	Hide,
	Expand,
	ChildMenu,
	Custom,
	None,
};

class Menu;

class MenuItem{
private:
	std::string text;
	uint32_t flags;
	std::shared_ptr<Menu> childMenu;
	uint64_t cacheNormal = 0;
	uint64_t cacheSelected = 0;
	uint32_t cacheWidth = 0;
	uint64_t image;
	
	MenuActionType actionType;
	uint32_t customID;
	
	void DropCache();
public:
	MenuItem(const wm_MenuItem &i);
	MenuItem(const std::string text, uint32_t flags, std::shared_ptr<Menu> childMenu, uint64_t image, MenuActionType action, uint32_t customId);
	
	uint64_t Draw(uint32_t width, bool selected);
	uint32_t GetHeight();
	uint32_t GetMinWidth();
	
	MenuActionType GetAction();
	uint32_t GetCustomAction();
	
	~MenuItem();
};

class Menu{
private:
	std::map<uint32_t, std::shared_ptr<MenuItem>> items;
	uint32_t idCounter = 0;
	
public:
	void Draw(int32_t x, int32_t y);
	Rect GetBoundingRect();
	void KeyInput(uint32_t key);
	void PointerInput(const bt_terminal_pointer_event &pevent);
	
	uint32_t AddMenuItem(std::shared_ptr<MenuItem> i);
	void RemoveMenuItem(uint32_t item);
};

std::shared_ptr<Menu> GetMenu(uint64_t id);

#endif
