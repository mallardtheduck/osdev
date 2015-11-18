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
	GDS_SelectSurface(gds_id);
	gds_info = GDS_SurfaceInfo();
}

Window::~Window()
{
}

void Window::Draw(bool active, bool content, uint64_t target){
	Point pos = this->pos;
	if(target){
		pos.x = 0; pos.y = 0;
	}
	this->active = active;
	GDS_SelectSurface(gds_id);
	if(!target) GDS_SelectScreen();
	else GDS_SelectSurface(target);
	if(content) GDS_Blit(gds_id, 0, 0, gds_info.w, gds_info.h, pos.x + GetMetric(BorderWidth), pos.y + GetMetric(TitleBarSize), gds_info.w, gds_info.h);
	UpdateTitleBar();
	if(!target) GDS_SelectScreen();
	else GDS_SelectSurface(target);
	GDS_Blit(gds_title_id, 0, 0, gds_titleinfo.w, gds_titleinfo.h, pos.x, pos.y, gds_titleinfo.w, gds_titleinfo.h);
	DrawBorder(pos.x, pos.y, gds_info.w + (2 * GetMetric(BorderWidth)), gds_info.h + GetMetric(TitleBarSize) + GetMetric(BorderWidth));
	last_active = active;
}

void Window::SetPosition(Point p){
	Rect oldrect = GetBoundingRect();
	pos = p;
	Rect newrect = GetBoundingRect();
	if(visible){
		DrawAndRefreshWindows(TileRects(newrect, oldrect));
	}
	stringstream ss;
	ss << "WM: Window '" << title << "' moved to (" << p.x << ", " << p.y << ")."<< endl;
	bt_zero(ss.str().c_str());
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
			GDS_SelectSurface(gds_drag_id);
			GDS_DeleteSurface();
			gds_drag_id = 0;
			SetPosition(newpos);
			if(!GetMetric(FullWindowDrag)){
				Rect winRect = {last_drag_pos.x, last_drag_pos.y, gds_info.w, gds_info.h + GetMetric(TitleBarSize)};
				DrawWindows(winRect);
				GDS_SelectScreen();
				RefreshRectEdges(last_drag_pos.x, last_drag_pos.y, gds_info.w, gds_info.h + GetMetric(TitleBarSize), GetMetric(BorderWidth));
			}
		}else{
			if(GetMetric(FullWindowDrag)){;
				if(!gds_drag_id){
					gds_drag_id = GDS_NewSurface(gds_SurfaceType::Bitmap, gds_info.w, gds_info.h + GetMetric(TitleBarSize));
					Draw(active, true, gds_drag_id);
				}
				if(newpos.x == pos.x && newpos.y == pos.y) return;
				GDS_SelectScreen();
				GDS_Blit(gds_drag_id, 0, 0, gds_info.w, gds_info.h + GetMetric(TitleBarSize), newpos.x, newpos.y, gds_info.w, gds_info.h + GetMetric(TitleBarSize));
				Rect oldrect = GetBoundingRect();
				pos = newpos;
				Rect newrect = GetBoundingRect();
				DrawAndRefreshWindows(TileRects(newrect, oldrect));
			}else{
				if(newpos.x == pos.x && newpos.y == pos.y) return;
				Rect winRect = {last_drag_pos.x, last_drag_pos.y, gds_info.w, gds_info.h + GetMetric(TitleBarSize)};
				DrawWindows(winRect);
				GDS_SelectScreen();
				DrawBorder(newpos.x, newpos.y, gds_info.w, gds_info.h + GetMetric(TitleBarSize));
				RefreshRectEdges(last_drag_pos.x, last_drag_pos.y, gds_info.w, gds_info.h + GetMetric(TitleBarSize), GetMetric(BorderWidth));
				last_drag_pos = newpos;
				RefreshRectEdges(last_drag_pos.x, last_drag_pos.y, gds_info.w, gds_info.h + GetMetric(TitleBarSize), GetMetric(BorderWidth));
			}
		}
	}
	//stringstream ss;
	Point epoint = Reoriginate(Point(pevent.x, pevent.y), pos);
	WindowArea over = GetWindowArea(epoint);
	//ss << "WM: Window '" << title << "' pointer input at (" << epoint.x << "," << epoint.y << ") - " << pevent.type << "."<< endl;
	//ss << "Area: " << (int)over << endl;
	//bt_zero(ss.str().c_str());
	if(pevent.type == bt_terminal_pointer_event_type::ButtonDown && pevent.button == 1){
		pressed = over;
		if(pressed != WindowArea::Content){
			if(pressed == WindowArea::Title){
				WindowGrab(id);
				dragoffset = epoint;
				dragging = true;
			}else{
				RefreshTitleBar(true);
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
		GDS_Blit(gds_title_id, 0, 0, gds_titleinfo.w, gds_titleinfo.h, pos.x, pos.y, gds_titleinfo.w, gds_titleinfo.h);
		DrawBorder(pos.x, pos.y, gds_info.w, gds_info.h + GetMetric(TitleBarSize));
		Rect r = GetBoundingRect();
		r.h = GetMetric(TitleBarSize);
		RefreshScreen(r);
	}
}

bool Window::UpdateTitleBar(bool force){
	if(!gds_title_id || active != last_active || force){
		if(gds_title_id){
			GDS_SelectSurface(gds_title_id);
			GDS_DeleteSurface();
			gds_title_id = 0;
		}
		gds_title_id = DrawTitleBar(gds_info.w + (2 * GetMetric(BorderWidth)), title, active, pressed);
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
}

void Window::Close(){
	stringstream ss;
	ss << "WM: Window '" << title << "' close."<< endl;
	bt_zero(ss.str().c_str());
}

void Window::Hide(){
	stringstream ss;
	ss << "WM: Window '" << title << "' hide."<< endl;
	bt_zero(ss.str().c_str());
}

void Window::Expand(){
	stringstream ss;
	ss << "WM: Window '" << title << "' expand."<< endl;
	bt_zero(ss.str().c_str());
}