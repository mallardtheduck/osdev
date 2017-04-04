#include <btos.h>
#include <sstream>
#include <gds/libgds.h>
#include <wm/wm.h>
#include <dev/rtc.h>
#include "window.hpp"
#include "metrics.hpp"
#include "drawing.hpp"
#include "windows.hpp"
#include "menus.hpp"

using namespace std;

#define DBG(x) do{std::stringstream dbgss; dbgss << x << std::endl; bt_zero(dbgss.str().c_str());}while(0)

Window::Window(uint64_t surface_id) : gds_id(surface_id){
	GDS_SelectSurface(gds_id);
	gds_info = GDS_SurfaceInfo();
}

Window::~Window(){
}

void Window::Draw(bool active, bool content, uint64_t target){
	Point pos = this->pos;
	if(target){
		pos.x = 0; pos.y = 0;
	}
	this->active = active;
	if(!target) GDS_SelectScreen();
	else GDS_SelectSurface(target);
	if(content) GDS_Blit(gds_id, 0, 0, gds_info.w, gds_info.h, pos.x + GetMetric(BorderWidth), pos.y + GetMetric(TitleBarSize), gds_info.w, gds_info.h);
	RefreshTitleBar();
	if(!target) GDS_SelectScreen();
	else GDS_SelectSurface(target);
	GDS_Blit(gds_title_id, 0, 0, gds_titleinfo.w, gds_titleinfo.h, pos.x, pos.y, gds_titleinfo.w, gds_titleinfo.h);
	DrawBorder(pos.x, pos.y, gds_info.w + (2 * GetMetric(BorderWidth)), gds_info.h + GetMetric(TitleBarSize) + GetMetric(BorderWidth));
	last_active = active;
}

void Window::Draw(bool active, const Rect &r){
	uint64_t draw_start = bt_rtc_millis();
	this->active = active;
	GDS_SelectScreen();
	Point cpos = GetContentPosition();
	bool drew = false;
	if(Overlaps(r, {cpos.x, cpos.y, gds_info.w, gds_info.h})){
		Rect contentDst = {max(r.x, cpos.x), max(r.y, cpos.y), min((cpos.x + gds_info.w), (r.x + r.w)) - max(r.x, cpos.x), min((cpos.y + gds_info.h), (r.y + r.h)) - max(r.y, cpos.y)};
		Rect contentSrc = Reoriginate(contentDst, {cpos.x, cpos.y});
		GDS_Blit(gds_id, contentSrc.x, contentSrc.y, contentSrc.w, contentSrc.h, contentDst.x, contentDst.y, contentDst.w, contentDst.h);
		drew = true;
	}
	uint64_t draw_s1 = bt_rtc_millis();
	RefreshTitleBar();
	uint64_t draw_s2 = bt_rtc_millis();
	if(Overlaps(r, {pos.x, pos.y, gds_titleinfo.w, gds_titleinfo.h})){
		Rect titleDst = {max(r.x, pos.x), max(r.y, pos.y), min((pos.x + gds_titleinfo.w), (r.x + r.w)) - max(r.x, pos.x), min((pos.y + gds_titleinfo.h), (r.y + r.h)) - max(r.y, pos.y)};
		Rect titleSrc = Reoriginate(titleDst, {pos.x, pos. y});
		GDS_Blit(gds_title_id, titleSrc.x, titleSrc.y, titleSrc.w, titleSrc.h, titleDst.x, titleDst.y, titleDst.w, titleDst.h);
		drew = true;
	}
	DrawBorder(pos.x, pos.y, gds_info.w + (2 * GetMetric(BorderWidth)), gds_info.h + GetMetric(TitleBarSize) + GetMetric(BorderWidth), r);
	last_active = active;
	uint64_t draw_end = bt_rtc_millis();
	DBG("WM Window " << id << " draw s1: " << draw_s1 - draw_start << "ms s2: " << draw_s2 - draw_s1 << "ms s3: " << draw_end - draw_s2 << "ms");
	if(!drew){
		stringstream ss;
		ss << "WM: Draw with no overlap!" << endl;
		ss << "WM: Draw rect: (" << r.x << ", " << r.y << ") " << r.w << " x " << r.h << "." << endl;
		Rect bounding = GetBoundingRect();
		ss << "WM: Bounding rect: (" << bounding.x << ", " << bounding.y << ") " << bounding.w << " x " << bounding.h << "." << endl;
		ss << "WM: Content rect: (" << cpos.x << ", " << cpos.y << ") " << gds_info.w << " x " << gds_info.h << "." << endl;
		ss << "WM: Content rect: (" << pos.x << ", " << pos.y << ") " << gds_titleinfo.w << " x " << gds_titleinfo.h << "." << endl;
		bt_zero(ss.str().c_str());
	}
}

void Window::SetPosition(Point p){
	Rect oldrect = GetBoundingRect();
	pos = p;
	Rect newrect = GetBoundingRect();
	if(GetVisible()){
		DrawAndRefreshWindows(oldrect);
		DrawAndRefreshWindows(newrect, id);
	}
	stringstream ss;
	ss << "WM: Window '" << title << "' moved to (" << p.x << ", " << p.y << ")."<< endl;
	bt_zero(ss.str().c_str());
}

Point Window::GetPosition(){
	return pos;
}

Point Window::GetContentPosition(){
	return {pos.x + GetMetric(BorderWidth), pos.y + GetMetric(TitleBarSize)};
}

void Window::SetTitle(string ntitle){
	title=ntitle;
	RefreshTitleBar(true);
	Rect r = GetBoundingRect();
	r.h = GetMetric(TitleBarSize);
	DrawAndRefreshWindows(r);
}

std::string Window::GetTitle(){
	return title;
}

uint64_t Window::GetSurface(){
	return gds_id;
}

void Window::SetZOrder(uint32_t zorder, bool update){
	z = zorder;
	if(update && GetVisible()){
		DrawWindows();
		RefreshScreen(GetBoundingRect());
	}
}

uint32_t Window::GetZOrder(){
	return z;
}

Rect Window::GetBoundingRect(){
	Rect ret;
	ret.x = pos.x;
	ret.y = pos.y;
	ret.w = gds_info.w + (2 * GetMetric(BorderWidth));
	ret.h = gds_info.h + GetMetric(BorderWidth) + GetMetric(TitleBarSize);
	return ret;
}

void Window::KeyInput(uint32_t key){
	stringstream ss;
	//ss << "WM: Window '" << title << "' key input:" << key << endl;
	bt_zero(ss.str().c_str());
	shared_ptr<Client> client = owner.lock();
	if(client && (event_subs & wm_EventType::Keyboard)){
		wm_Event e;
		e.window_id = id;
		e.type = wm_EventType::Keyboard;
		e.Key.code = key;
		client->SendEvent(e);
	}
}

void DrawAndRefreshRectEdges(int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t lineWidth){
	if(x >= 0) DrawAndRefreshWindows({x, y, lineWidth, h});
	if(y >= 0) DrawAndRefreshWindows({x, y, w, lineWidth});
	DrawAndRefreshWindows({x + (int32_t)w - 1, y, lineWidth, h});
	DrawAndRefreshWindows({x, y + (int32_t)h - 1, w, lineWidth});
}

void RefreshRectEdges(int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t lineWidth){
	if(x >= 0) RefreshScreen({x, y, lineWidth, h});
	if(y >= 0) RefreshScreen({x, y, w, lineWidth});
	RefreshScreen({x + (int32_t)w - 1, y, lineWidth, h});
	RefreshScreen({x, y + (int32_t)h - 1, w, lineWidth});
}

void Window::PointerInput(const bt_terminal_pointer_event &pevent){
	if(dragging){
		Point curpos = Point(pevent.x, pevent.y);
		Point newpos = {curpos.x - dragoffset.x, curpos.y - dragoffset.y};
		if(pevent.type == bt_terminal_pointer_event_type::ButtonUp){
			UnGrab();
			dragging = false;
			SetPosition(newpos);
			if(GetMetric(FullWindowDrag)){
				if(gds_drag_id){
					GDS_SelectSurface(gds_drag_id);
					GDS_DeleteSurface();
				}
				gds_drag_id = 0;
				SetVisible(true, true);
			}else{
				Rect winRect = {last_drag_pos.x, last_drag_pos.y, gds_info.w + (2 * GetMetric(BorderWidth)) + 10, gds_info.h + GetMetric(TitleBarSize)};
				DrawWindows(winRect);
				GDS_SelectScreen();
				RefreshRectEdges(last_drag_pos.x, last_drag_pos.y, gds_info.w + (2 * GetMetric(BorderWidth)), gds_info.h + GetMetric(TitleBarSize), GetMetric(BorderWidth));
			}
		}else{
			if(GetMetric(FullWindowDrag)){
				bool firstFrame = false;
				if(!gds_drag_id){
					gds_drag_id = GDS_NewSurface(gds_SurfaceType::Bitmap, GetBoundingRect().w, GetBoundingRect().h, 100, gds_info.colourType);
					Draw(active, true, gds_drag_id);
					SetVisible(false, false);
					firstFrame = true;
				}
				if(!firstFrame && newpos.x == pos.x && newpos.y == pos.y) return;
				GDS_SelectScreen();
				Rect oldrect = GetBoundingRect();
				DrawWindows(oldrect);
				GDS_Blit(gds_drag_id, 0, 0, oldrect.w, oldrect.h + GetMetric(TitleBarSize), newpos.x, newpos.y, oldrect.w, oldrect.h + GetMetric(TitleBarSize));
				pos = newpos;
				Rect newrect = GetBoundingRect();
				RefreshScreen(TileRects(oldrect, newrect));
			}else{
				if(newpos.x == pos.x && newpos.y == pos.y) return;
				GDS_SelectScreen();
				DrawAndRefreshRectEdges(last_drag_pos.x, last_drag_pos.y, gds_info.w + (2 * GetMetric(BorderWidth)), gds_info.h + GetMetric(TitleBarSize), GetMetric(BorderWidth));
				DrawBorder(newpos.x, newpos.y, gds_info.w + (2 * GetMetric(BorderWidth)), gds_info.h + GetMetric(TitleBarSize));
				last_drag_pos = newpos;
				RefreshRectEdges(last_drag_pos.x, last_drag_pos.y, gds_info.w + (2 * GetMetric(BorderWidth)), gds_info.h + GetMetric(TitleBarSize), GetMetric(BorderWidth));
			}
		}
	}
	Point epoint = Reoriginate(Point(pevent.x, pevent.y), pos);
	WindowArea over = GetWindowArea(epoint);
	if(pevent.type == bt_terminal_pointer_event_type::ButtonDown && pevent.button == 1){
		pressed = over;
		if(pressed != WindowArea::Content){
			if(pressed == WindowArea::Title){
				WindowGrab(id);
				dragoffset = epoint;
				dragging = true;
			}else{
				RefreshTitleBar(true);
				Rect r = GetBoundingRect();
				r.h = GetMetric(TitleBarSize);
				DrawAndRefreshWindows(r, id);
			}
		}
	}
	if(pevent.type == bt_terminal_pointer_event_type::ButtonUp && pevent.button == 1 && pressed != WindowArea::None){
		if(pressed == over){
			if(pressed == WindowArea::MenuButton) OpenMenu();
			if(pressed == WindowArea::CloseButton) Close();
			if(pressed == WindowArea::HideButton) Hide();
			if(pressed == WindowArea::ExpandButton) Expand();
		}
		pressed = WindowArea::None;
		RefreshTitleBar(true);
		Rect r = GetBoundingRect();
		r.h = GetMetric(TitleBarSize);
		DrawAndRefreshWindows(r, id);
	}
	if(over == WindowArea::Content){
		wm_Event e;
		if(pevent.type == bt_terminal_pointer_event_type::ButtonDown) e.type = wm_EventType::PointerButtonDown;
		else if(pevent.type == bt_terminal_pointer_event_type::ButtonUp) e.type = wm_EventType::PointerButtonUp;
		else if(pevent.type == bt_terminal_pointer_event_type::Move) e.type = wm_EventType::PointerMove;
		else return;
		shared_ptr<Client> client = owner.lock();
		if(client && (e.type & event_subs) == e.type){
			Point cpoint = Reoriginate(epoint, {GetMetric(BorderWidth), GetMetric(TitleBarSize)});
			e.window_id = id;
			e.Pointer.x = cpoint.x;
			e.Pointer.y = cpoint.y;
			e.Pointer.button = pevent.button;
			client->SendEvent(e);
		}
	}
}

void Window::PointerEnter(){
	stringstream ss;
	ss << "WM: Window '" << title << "' pointer enter."<< endl;
	bt_zero(ss.str().c_str());
	shared_ptr<Client> client = owner.lock();
	if(client && (event_subs & wm_EventType::PointerEnter)){
		wm_Event e;
		e.window_id = id;
		e.type = wm_EventType::PointerEnter;
		client->SendEvent(e);
	}
}

void Window::PointerLeave(){
	stringstream ss;
	ss << "WM: Window '" << title << "' pointer leave."<< endl;
	bt_zero(ss.str().c_str());
	if(pressed != WindowArea::None){
		pressed = WindowArea::None;
		RefreshTitleBar();
	}
	shared_ptr<Client> client = owner.lock();
	if(client && (event_subs & wm_EventType::PointerLeave)){
		wm_Event e;
		e.window_id = id;
		e.type = wm_EventType::PointerLeave;
		client->SendEvent(e);
	}
}

void Window::SetVisible(bool v, bool update){
	bool oldvisible = GetVisible();
	if(v) options |= wm_WindowOptions::Visible;
	else options &= ~wm_WindowOptions::Visible;
	if(oldvisible != GetVisible() && update){
		if(v) DrawWindows(GetBoundingRect(), id);
		else DrawWindows(GetBoundingRect());
		RefreshScreen(GetBoundingRect());
	}
}

bool Window::GetVisible(){
	return (options & wm_WindowOptions::Visible);
}

WindowArea Window::GetWindowArea(Point p){
	GDS_SelectSurface(gds_id);
	gds_SurfaceInfo info = GDS_SurfaceInfo();
	if(p.x >= GetMetric(BorderWidth) && p.x < GetMetric(BorderWidth) + (int32_t)info.w){
		if(p.y >= GetMetric(BorderWidth)){
			if(p.y >= GetMetric(TitleBarSize)){
				if(p.y < GetMetric(TitleBarSize) + (int32_t)info.h) return WindowArea::Content;
				else return WindowArea::Border;
			}else{
				if(p.x < GetMetric(MenuButtonWidth) + GetMetric(BorderWidth)) return WindowArea::MenuButton;
				if(p.x > (int32_t)info.w - GetMetric(ButtonSize)) return WindowArea::ExpandButton;
				if(p.x > (int32_t)info.w - (GetMetric(ButtonSize) * 2)) return WindowArea::HideButton;
				if(p.x > (int32_t)info.w - (GetMetric(ButtonSize) * 3)) return WindowArea::CloseButton;
				return WindowArea::Title;
			}
		}else return WindowArea::Border;
	}else{
		return WindowArea::Border;
	}
}

void Window::RefreshTitleBar(bool force){
	if(UpdateTitleBar(force)){
		GDS_SelectScreen();
		Rect r = GetBoundingRect();
		r.h = GetMetric(TitleBarSize);
		DrawBorder(pos.x, pos.y, gds_info.w + (2 * GetMetric(BorderWidth)), gds_info.h + GetMetric(TitleBarSize), r);
	}
}

bool Window::UpdateTitleBar(bool force){
	if(force || active != last_active){
		gds_title_id = titlebar.Draw(gds_info.w + (2 * GetMetric(BorderWidth)), title, active, pressed);
		GDS_SelectSurface(gds_title_id);
		gds_titleinfo = GDS_SurfaceInfo();
		return true;
	}
	return false;
}

void Window::OpenMenu(){
	stringstream ss;
	ss << "WM: Window '" << title << "' open menu."<< endl;
	bt_zero(ss.str().c_str());
	auto m = make_shared<Menu>();
	m->AddMenuItem(make_shared<MenuItem>("One Apple", wm_MenuItemFlags::Default, shared_ptr<Menu>(), 0, MenuActionType::None, 0));
	m->AddMenuItem(make_shared<MenuItem>("Two Potatoes", wm_MenuItemFlags::Default, shared_ptr<Menu>(), 0, MenuActionType::None, 0));
	m->AddMenuItem(make_shared<MenuItem>("Three Chickens", wm_MenuItemFlags::Default, shared_ptr<Menu>(), 0, MenuActionType::None, 0));
	m->AddMenuItem(make_shared<MenuItem>("", wm_MenuItemFlags::Seperator, shared_ptr<Menu>(), 0, MenuActionType::None, 0));
	m->AddMenuItem(make_shared<MenuItem>("Four Lemon Cheesecakes", wm_MenuItemFlags::Default, shared_ptr<Menu>(), 0, MenuActionType::None, 0));
	m->AddMenuItem(make_shared<MenuItem>("Five Gold Rings", wm_MenuItemFlags::Default, shared_ptr<Menu>(), 0, MenuActionType::None, 0));
	::OpenMenu(m, pos.x, pos.y + GetMetric(TitleBarSize));
	GDS_UpdateScreen();
}

void Window::Close(){
	stringstream ss;
	ss << "WM: Window '" << title << "' close."<< endl;
	shared_ptr<Client> client = owner.lock();
	if(client && (event_subs & wm_EventType::Close)){
		wm_Event e;
		e.window_id = id;
		e.type = wm_EventType::Close;
		client->SendEvent(e);
	}
}

void Window::Hide(){
	stringstream ss;
	ss << "WM: Window '" << title << "' hide."<< endl;
	bt_zero(ss.str().c_str());
	shared_ptr<Client> client = owner.lock();
	if(client && (event_subs & wm_EventType::Hide)){
		wm_Event e;
		e.window_id = id;
		e.type = wm_EventType::Hide;
		client->SendEvent(e);
	}
}

void Window::Expand(){
	stringstream ss;
	ss << "WM: Window '" << title << "' expand."<< endl;
	bt_zero(ss.str().c_str());
	shared_ptr<Client> client = owner.lock();
	if(client && (event_subs & wm_EventType::Expand)){
		wm_Event e;
		e.window_id = id;
		e.type = wm_EventType::Expand;
		client->SendEvent(e);
	}
}

void Window::SetOwner(std::weak_ptr<Client> o){
	owner = o;
}

void Window::Subscribe(uint32_t subs){
	event_subs = subs;
}

uint32_t Window::Subscribe(){
	return event_subs;
}

void Window::SetOptions(uint32_t opts){
	options = opts;
}

uint32_t Window::GetOptions(){
	return options;
}
