#ifndef _MENUS_HPP
#define _MENUS_HPP

#include <wm/wm.h>
#include <string>
#include <memory>
#include <map>
#include <dev/terminal.h>

#include "rect.hpp"
#include "windows.hpp"

enum class MenuActionType{
	Close,
	Hide,
	Expand,
	ChildMenu,
	Custom,
	None,
};

class Window;
class Menu;

class MenuItem{
private:
	std::string text;
	uint32_t flags;
	uint32_t cacheFlags = 0;
	std::shared_ptr<Menu> childMenu;
	uint64_t cacheNormal = 0;
	uint64_t cacheSelected = 0;
	uint32_t cacheWidth = 0;
	uint64_t image;
	uint32_t minWidth = 0;
	
	MenuActionType actionType;
	uint32_t customID;
	
	void DropCache();
public:
	MenuItem(const wm_MenuItem &i);
	MenuItem(const std::string text, uint32_t flags, std::shared_ptr<Menu> childMenu, uint64_t image, MenuActionType action, uint32_t customId);
	
	uint64_t Draw(uint32_t width, bool selected, uint32_t dflags = 0);
	uint32_t GetHeight();
	uint32_t GetMinWidth();
	
	MenuActionType GetAction();
	uint32_t GetCustomAction();
	std::shared_ptr<Menu> GetChildMenu();
	uint32_t GetFlags();
	
	~MenuItem();
};

class Menu{
private:
	std::map<uint32_t, std::shared_ptr<MenuItem>> items;
	uint32_t idCounter = 0;
	int32_t lx = 0;
	int32_t ly = 0;
	uint32_t lsel = 0;
	std::shared_ptr<Menu> childMenu;
	std::weak_ptr<Window> window;
	bool open = false;
	uint32_t menuParent = 0;
	
	uint32_t EffectiveFlags(uint32_t menuFlags, MenuActionType action);
	
public:
	uint64_t id = UINT64_MAX;
	
	Menu(uint64_t i) : id(i) {}
	bool Draw(int32_t x, int32_t y, const Point &cursor = {0, 0}, bool force = false);
	void Redraw();
	Rect GetBoundingRect();
	void PointerInput(const bt_terminal_pointer_event &pevent);
	
	uint32_t AddMenuItem(std::shared_ptr<MenuItem> i);
	void RemoveMenuItem(uint32_t item);
	uint32_t GetSelected(const Point &cursor);
	int32_t GetTop(uint32_t item);
	std::shared_ptr<MenuItem> GetItem(uint32_t id);
	void Reset();
	bool IsOpen();
	void SetWindow(std::weak_ptr<Window> win);
	Point GetPosition();
	
	std::map<uint32_t, std::shared_ptr<MenuItem>> GetItems();
};

std::shared_ptr<Menu> GetMenu(uint64_t id);
bool MenuPointerInput(const bt_terminal_pointer_event &pevent);
void OpenMenu(std::shared_ptr<Menu> menu, std::weak_ptr<Window> win, uint32_t x, uint32_t y);
void CloseMenu(std::shared_ptr<Menu> menu);
void RedrawMenus(const Rect &r);

std::shared_ptr<Menu> GetDefaultWindowMenu();
std::shared_ptr<Menu> GetWindowMenuTemplate();

std::shared_ptr<Menu> CreateMenu();
std::shared_ptr<Menu> MergeMenus(std::shared_ptr<Menu> m1, std::shared_ptr<Menu> m2);

#endif
