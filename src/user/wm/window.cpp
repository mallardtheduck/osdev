#include <sstream>
#include <gds/libgds.h>
#include <btos_stubs.h>
#include "window.hpp"
#include "metrics.hpp"
#include "drawing.hpp"

using namespace std;

bool InRect(uint32_t x, uint32_t y, const Rect &r){
	if(x >= r.x && x <= (r.x + r.w) && y >= r.y && y <= (r.y + r.h)) return true;
	else return false;
}

Window::Window(uint64_t surface_id) : x(0), y(0), gds_id(surface_id)
{
}

Window::~Window()
{
}

void Window::Draw(bool active){
	GDS_SelectSurface(gds_id);
	gds_SurfaceInfo info = GDS_SurfaceInfo();
	GDS_SelectScreen();
	GDS_Blit(gds_id, 0, 0, info.w, info.h, x, y + GetMetric(TitleBarSize), info.w, info.h);
	DrawTitleBar(x, y, info.w, title, active);
	DrawBorder(x, y, info.w, info.h + GetMetric(TitleBarSize));
}

void Window::SetPosition(uint32_t nx, uint32_t ny){
	x=nx;
	y=ny;
}

void Window::SetTitle(string ntitle){
	title=ntitle;
}

std::string Window::GetTitle(){
	return title;
}

void Window::SetZOrder(uint32_t zorder){
	z = zorder;
}

uint32_t Window::GetZOrder(){
	return z;
}

Rect Window::GetBoundingRect(){
	Rect ret;
	ret.x = x ;//- GetMetric(BorderWidth);
	ret.y = y ;//- GetMetric(BorderWidth);
	GDS_SelectSurface(gds_id);
	gds_SurfaceInfo info = GDS_SurfaceInfo();
	ret.w = info.w ; //+ (2 * GetMetric(BorderWidth));
	ret.h = info.h /*+ (2 * GetMetric(BorderWidth))*/ + GetMetric(TitleBarSize);
	return ret;
}

void Window::KeyInput(uint32_t key){
	stringstream ss;
	ss << "WM: Window '" << title << "' key input:" << key << endl;
	bt_zero(ss.str().c_str());
}

void Window::PointerInput(const bt_terminal_pointer_event &/*pevent*/){
	stringstream ss;
	ss << "WM: Window '" << title << "' pointer input."<< endl;
	//bt_zero(ss.str().c_str());
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
}