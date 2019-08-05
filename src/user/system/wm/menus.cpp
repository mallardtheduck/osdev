#include "menus.hpp"
#include "drawing.hpp"
#include "metrics.hpp"
#include "windows.hpp"
#include <gds/libgds.h>
#include <sstream>
#include <gds/screen.hpp>

#define DBG(x) do{std::stringstream dbgss; dbgss << x << std::endl; bt_zero(dbgss.str().c_str());}while(0)

using namespace std;
using namespace gds;

static vector<shared_ptr<Menu>> currentMenus;
static map<uint64_t, weak_ptr<Menu>> allMenus;

MenuItem::MenuItem(const wm_MenuItem &i) :
	MenuItem(i.text, i.flags, GetMenu(i.childMenu), i.image ? make_shared<Surface>(Surface::Wrap(i.image, true)) : nullptr, ((i.flags & wm_MenuItemFlags::ChildMenu) ? MenuActionType::ChildMenu : ((i.flags & wm_MenuItemFlags::Separator) ? MenuActionType::None : MenuActionType::Custom)), i.actionID) {}

MenuItem::MenuItem(const std::string t, uint32_t f, std::shared_ptr<Menu> cM, shared_ptr<Surface> i, MenuActionType a, uint32_t cID) :
	text(t), flags(f), childMenu(cM), image(i), actionType(a), customID(cID) {}
	
MenuItem::~MenuItem(){
	DropCache();
}
void MenuItem::DropCache(){
	cacheNormal.reset();
	cacheSelected.reset();
	cacheWidth = 0;
}

shared_ptr<Surface> MenuItem::Draw(uint32_t width, bool selected, uint32_t dflags){
	if(dflags == 0) dflags = flags;
	if(width != cacheWidth || dflags != cacheFlags) DropCache();
	cacheWidth = width;
	cacheFlags = dflags;
	if(selected){
		if(!cacheSelected) cacheSelected = make_shared<Surface>(DrawMenuItem(text, dflags, image.get(), width, true));
		return cacheSelected;
	}else{
		if(!cacheNormal) cacheNormal = make_shared<Surface>(DrawMenuItem(text, dflags, image.get(), width, false));
		return cacheNormal;
	}
}

uint32_t MenuItem::GetHeight(){
	if((flags & wm_MenuItemFlags::Separator)) return (GetMetric(MenuItemMargin) * 2) + 1;
	else return GetMetric(MenuItemHeight);
}

uint32_t MenuItem::GetMinWidth(){
	uint32_t ret = minWidth;
	if(!ret){
		if((flags & wm_MenuItemFlags::Separator)){
			ret = (2 * GetMetric(MenuItemMargin)) + 1;
		}else{
			ret = (2 * GetMetric(MenuItemMargin));
			if(image){
				gds_SurfaceInfo image_info = image->Info();
				ret += image_info.w;
				ret += GetMetric(MenuItemMargin);
			}
			if(!(flags & wm_MenuItemFlags::ImageOnly)){
				Font font = Font::Get(GetSetting(MenuFontName), gds_FontStyle::Normal);
				for(const char c : text){
					gds_GlyphInfo ginfo = font.GetGlyphInfo(GetMetric(MenuFontSize), c);
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

uint32_t MenuItem::GetFlags(){
	return flags;
}

uint32_t Menu::EffectiveFlags(uint32_t menuFlags, MenuActionType action){
	auto win = window.lock();
	if(!win || action == MenuActionType::Custom || action == MenuActionType::ChildMenu || action == MenuActionType::None) return menuFlags;
	uint32_t windowOptions = win->GetOptions();
	if(action == MenuActionType::Close && (windowOptions & wm_WindowOptions::NoClose)) return menuFlags | wm_MenuItemFlags::Disabled;
	if(action == MenuActionType::Expand && (windowOptions & wm_WindowOptions::NoExpand)) return menuFlags | wm_MenuItemFlags::Disabled;
	if(action == MenuActionType::Hide && (windowOptions & wm_WindowOptions::NoHide)) return menuFlags | wm_MenuItemFlags::Disabled;
	return menuFlags;
}

bool Menu::Draw(Point p, const Point &cursor, bool force){
	if(!p){
		p = lp;
	}
	uint32_t nsel = lsel;
	if(cursor){
		nsel = GetSelected(cursor);
		if(!force && lsel == nsel) return false;
	}
	DBG("WM: Drawing menu at (" << p.x << ", " << p.y << ")");
	int32_t cy = p.y;
	uint32_t width = 0;
	for(auto &i : items){
		uint32_t w = i.second->GetMinWidth();
		if(w > width) width = w;
	}
	for(auto &i : items){
		bool selected = (i.first == nsel);
		uint32_t height = i.second->GetHeight();
		auto surf = i.second->Draw(width, selected, EffectiveFlags(i.second->GetFlags(), i.second->GetAction()));
		Screen.Blit(*surf, {0, 0, width, height}, {p.x, cy, width, height});
		cy += height;
	}
	DrawBorder(Screen, {p.x, p.y, width, (uint32_t)cy - p.y});
	lp = p;
	lsel = nsel;
	open = true;
	return true;
}

void Menu::Redraw(){
	Draw({0, 0}, {0, 0}, true);
}

uint32_t Menu::AddMenuItem(std::shared_ptr<MenuItem> i){
	uint32_t ret = ++idCounter;
	items[ret] = i;
	return ret;
}

void Menu::RemoveMenuItem(uint32_t itemId){
	if(items.find(itemId) != items.end()){
		items.erase(itemId);
	}
}

Rect Menu::GetBoundingRect(){
	uint32_t width = 0;
	uint32_t height = 0;
	for(auto &i : items){
		uint32_t w = i.second->GetMinWidth();
		if(w > width) width = w;
		height += i.second->GetHeight();
	}
	return {lp, width, height};
}

uint32_t Menu::GetSelected(const Point &cursor){
	Rect brect = GetBoundingRect();
	if(!InRect(cursor, brect)) return 0;
	int32_t cy = lp.y;
	for(auto &i : items){
		uint32_t height = i.second->GetHeight();
		if(!(EffectiveFlags(i.second->GetFlags(), i.second->GetAction()) & wm_MenuItemFlags::Disabled)){
			if(InRect(cursor, {lp.x, cy, brect.w, height})) return i.first;
		}
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
	lp = {0, 0};
	lsel = 0;
	open = false;
	childMenu.reset();
	window.reset();
}

bool Menu::IsOpen(){
	return open;
}

void Menu::PointerInput(const bt_terminal_pointer_event &pevent){
	Rect brect = GetBoundingRect();
	if(pevent.type == bt_terminal_pointer_event_type::Move){
		if(Draw({0, 0}, {(int32_t)pevent.x, (int32_t)pevent.y})) RefreshScreen(brect);
		DBG("WM: menuParent: " << menuParent << " lsel: " << lsel << " childMenu: " << childMenu << " IsOpen: " << (childMenu ? (int)childMenu->IsOpen() : -1));
		if(lsel != menuParent && childMenu && childMenu->IsOpen()){
			DBG("WM: Closing child menu.");
			CloseMenu(childMenu);
			childMenu.reset();
			menuParent = 0;
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
					menuParent = 0;
				}
				DBG("WM: Opening child menu.");
				OpenMenu(item->GetChildMenu(), window, {(int32_t)(brect.x + brect.w), GetTop(selId)});
				childMenu = item->GetChildMenu();
				menuParent = selId;
			}
		}
	}else if(pevent.type == bt_terminal_pointer_event_type::ButtonUp){
		uint32_t selId = GetSelected({(int32_t)pevent.x, (int32_t)pevent.y});
		if(selId){
			auto item = GetItem(selId);
			auto action = item->GetAction();
			auto win = window.lock();
			if(action != MenuActionType::ChildMenu){
				CloseMenu(NULL);
			}
			switch(action){
				case MenuActionType::Close:
					win->Close();
					break;
				case MenuActionType::Hide:
					win->Hide();
					break;
				case MenuActionType::Expand:
					win->Expand();
					break;
				case MenuActionType::Custom:
					win->MenuAction(id, item->GetCustomAction());
					break;
				default: break;
			}
		}else{
			CloseMenu(NULL);
		}
	}
}

int32_t Menu::GetTop(uint32_t item){
	int32_t cy = lp.y;
	for(auto &i : items){
		uint32_t height = i.second->GetHeight();
		if(i.first == item) return cy;
		cy += height;
	}
	return 0;
}

void Menu::SetWindow(weak_ptr<Window> win){
	window = win;
}

Point Menu::GetPosition(){
	return lp;
}

map<uint32_t, shared_ptr<MenuItem>> Menu::GetItems(){
	return items;
}

Menu::~Menu(){
	allMenus.erase(id);
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

void OpenMenu(std::shared_ptr<Menu> menu, std::weak_ptr<Window> win, const Point &p){
	if(menu){
		currentMenus.push_back(menu);
		menu->SetWindow(win);
		Screen.BeginQueue();
		menu->Draw(p, {0, 0}, true);
		Screen.CommitQueue();
		RefreshScreen(menu->GetBoundingRect());
	}
}

void CloseMenu(std::shared_ptr<Menu> menu){
	vector<Rect> refreshList;
	while(currentMenus.size()){
		auto cmenu = currentMenus.back();
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

shared_ptr<Menu> GetMenu(uint64_t id){
	auto it = allMenus.find(id);
	if(it != allMenus.end()){
		return it->second.lock();
	}else return nullptr;
}

shared_ptr<Menu> GetDefaultWindowMenu(){
	static shared_ptr<Menu> winMenu;
	if(!winMenu){
		winMenu = CreateMenu();
		winMenu->AddMenuItem(make_shared<MenuItem>("Expand", wm_MenuItemFlags::Default, nullptr, nullptr, MenuActionType::Expand, 0));
		winMenu->AddMenuItem(make_shared<MenuItem>("Hide", wm_MenuItemFlags::Default, nullptr, nullptr, MenuActionType::Hide, 0));
		winMenu->AddMenuItem(make_shared<MenuItem>("Close", wm_MenuItemFlags::Default, nullptr, nullptr, MenuActionType::Close, 0));
	}
	return winMenu;
}

shared_ptr<Menu> GetWindowMenuTemplate(){
	static shared_ptr<Menu> templateMenu;
	if(!templateMenu){
		templateMenu = CreateMenu();
		templateMenu->AddMenuItem(make_shared<MenuItem>("Window", wm_MenuItemFlags::ChildMenu, GetDefaultWindowMenu(), nullptr, MenuActionType::ChildMenu, 0));
		templateMenu->AddMenuItem(make_shared<MenuItem>("", wm_MenuItemFlags::Separator, nullptr, nullptr, MenuActionType::None, 0));
	}
	return templateMenu;
}

shared_ptr<Menu> CreateMenu(uint64_t id){
	static uint64_t id_counter = 0;
	if(id == UINT64_MAX) id = ++id_counter;
	auto ret = make_shared<Menu>(id);
	allMenus[id] = ret;
	return ret;
}

void RedrawMenus(const Rect &r){
	Screen.BeginQueue();
	for(auto m : currentMenus){
		if(Overlaps(m->GetBoundingRect(), r)){
			m->Redraw();
		}
	}
	Screen.CommitQueue();
}

shared_ptr<Menu> MergeMenus(shared_ptr<Menu> m1, shared_ptr<Menu> m2, uint64_t id){
	auto ret = CreateMenu(id);
	auto m1items = m1->GetItems();
	auto m2items = m2->GetItems();
	
	for(auto item : m1items){
		ret->AddMenuItem(item.second);
	}
	for(auto item : m2items){
		ret->AddMenuItem(item.second);
	}
	return ret;
}
