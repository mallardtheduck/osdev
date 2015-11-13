#include <sstream>
#include <gds/libgds.h>
#include <btos_stubs.h>
#include "window.hpp"
#include "metrics.hpp"
#include "drawing.hpp"
#include "windows.hpp"

using namespace std;

Window::Window(uint64_t surface_id) : gds_id(surface_id)
{
}

Window::~Window()
{
}

void Window::Draw(bool active, bool content){
	this->active = active;
	GDS_SelectSurface(gds_id);
	gds_SurfaceInfo info = GDS_SurfaceInfo();
	GDS_SelectScreen();
	if(content) GDS_Blit(gds_id, 0, 0, info.w, info.h, pos.x + GetMetric(BorderWidth), pos.y + GetMetric(TitleBarSize), info.w, info.h);
	DrawTitleBar(pos.x, pos.y, info.w + (2 * GetMetric(BorderWidth)), title, active, pressed);
	DrawBorder(pos.x, pos.y, info.w + (2 * GetMetric(BorderWidth)), info.h + GetMetric(TitleBarSize) + GetMetric(BorderWidth));
}

void Window::SetPosition(Point p){
	Rect oldrect = GetBoundingRect();
	pos = p;
	Rect newrect = GetBoundingRect();
	if(visible){
		DrawAndRefreshWindows(TileRects(newrect, oldrect));
	}
}

void Window::SetTitle(string ntitle){
	title=ntitle;
}

std::string Window::GetTitle(){
	return title;
}

void Window::SetZOrder(uint32_t zorder, bool update){
	z = zorder;
	if(update && visible){
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
	GDS_SelectSurface(gds_id);
	gds_SurfaceInfo info = GDS_SurfaceInfo();
	ret.w = info.w + (2 * GetMetric(BorderWidth));
	ret.h = info.h + GetMetric(BorderWidth) + GetMetric(TitleBarSize);
	return ret;
}

void Window::KeyInput(uint32_t key){
	stringstream ss;
	ss << "WM: Window '" << title << "' key input:" << key << endl;
	bt_zero(ss.str().c_str());
}

void Window::PointerInput(const bt_terminal_pointer_event &pevent){
	if(dragging){
		if(pevent.type == bt_terminal_pointer_event_type::ButtonUp){
			UnGrab();
			dragging = false;
		}else{
			Point curpos = Point(pevent.x, pevent.y);
			Point newpos = {curpos.x - dragoffset.x, curpos.y - dragoffset.y};
			if(newpos.x == pos.x && newpos.y == pos.y) return;
			SetPosition(newpos);
		}
	}
	stringstream ss;
	Point epoint = Reoriginate(Point(pevent.x, pevent.y), pos);
	WindowArea over = GetWindowArea(epoint);
	ss << "WM: Window '" << title << "' pointer input at (" << epoint.x << "," << epoint.y << ") - " << pevent.type << "."<< endl;
	ss << "Area: " << (int)over << endl;
	bt_zero(ss.str().c_str());
	if(pevent.type == bt_terminal_pointer_event_type::ButtonDown){
		pressed = over;
		if(pressed != WindowArea::Content){
			RefreshTitleBar();
			if(pressed == WindowArea::Title){
				WindowGrab(id);
				dragoffset = epoint;
				dragging = true;
			}
		}
	}
	if(pevent.type == bt_terminal_pointer_event_type::ButtonUp && pressed != WindowArea::None){
		pressed = WindowArea::None;
		RefreshTitleBar();
	}
}

void Window::PointerEnter(){
	stringstream ss;
	ss << "WM: Window '" << title << "' pointer enter."<< endl;
	bt_zero(ss.str().c_str());
}

void Window::PointerLeave(){
	stringstream ss;
	ss << "WM: Window '" << title << "' pointer leave."<< endl;
	bt_zero(ss.str().c_str());
	if(pressed != WindowArea::None){
		pressed = WindowArea::None;
		RefreshTitleBar();
	}
}

void Window::SetVisible(bool v){
	bool oldvisible = visible;
	visible = v;
	if(oldvisible){
		DrawWindows();
		RefreshScreen(GetBoundingRect());
	}
}

bool Window::GetVisible(){
	return visible;
}

WindowArea Window::GetWindowArea(Point p){
	GDS_SelectSurface(gds_id);
	gds_SurfaceInfo info = GDS_SurfaceInfo();
	if(p.x >= GetMetric(BorderWidth) && p.x < GetMetric(BorderWidth) + info.w){
		if(p.y >= GetMetric(BorderWidth)){
			if(p.y >= GetMetric(TitleBarSize)){
				if(p.y < GetMetric(TitleBarSize) + info.h) return WindowArea::Content;
				else return WindowArea::Border;
			}else{
				if(p.x < GetMetric(MenuButtonWidth) + GetMetric(BorderWidth)) return WindowArea::MenuButton;
				if(p.x >= info.w - GetMetric(ButtonSize) - GetMetric(BorderWidth)) return WindowArea::MaxButton;
				if(p.x >= info.w - (GetMetric(ButtonSize) * 2) - GetMetric(BorderWidth)) return WindowArea::MinButton;
				if(p.x >= info.w - (GetMetric(ButtonSize) * 3) - GetMetric(BorderWidth)) return WindowArea::CloseButton;
				return WindowArea::Title;
			}
		}else return WindowArea::Border;
	}else{
		return WindowArea::Border;
	}
}

void Window::RefreshTitleBar(){
	Draw(active, false);
	Rect r = GetBoundingRect();
	r.h = GetMetric(TitleBarSize);
	RefreshScreen(r);
}