#include <wm/window.hpp>
#include <wm/libwm.h>
#include <gds/geom.hpp>

using namespace std;

namespace btos_api{
namespace wm{

	Window::Window(const gds::Point &p, uint32_t options, uint32_t subscriptions, const gds::Surface &surf, const string &title) :
		id(WM_NewWindow(p.x, p.y, options, subscriptions, surf.GetID(), title.c_str())), owned(true)
	{}
	Window::Window(const wm_WindowInfo &info) :
		id(WM_CreateWindow(info)), owned(true)
	{}
	Window::Window(Window &&w) : id(w.id), owned(w.owned){
		w.id = 0;
		w.owned = false;
	}

	Window::~Window(){
		if(id && owned){
			Select();
			WM_DestroyWindow();
		}
	}

	Window Window::Wrap(uint64_t id, bool own){
		Window ret;
		ret.id = id;
		ret.owned = own;
		return ret;
	}

	void Window::Select() const{
		WM_SelectWindow(id);
	}
	uint64_t Window::GetID() const{
		return id;
	}
	
	wm_WindowInfo Window::Info() const{
		Select();
		return WM_WindowInfo();
	}
	void Window::SetSubscribed(uint32_t events){
		Select();
		WM_Subscribe(events);
	}
	void Window::Update(){
		Select();
		WM_Update();
	}
	void Window::Update(const gds::Rect &r){
		Select();
		WM_UpdateRect(r.x, r.y, r.w, r.h);
	}
	void Window::SetSurface(const gds::Surface &surf){
		Select();
		WM_ReplaceSurface(surf.GetID());
	}
	gds::Surface Window::GetSurface() const{
		return gds::Surface::Wrap(Info().gds_id, false);
	}
	void Window::SetPosition(const gds::Point &p){
		Select();
		WM_MoveWindow(p.x, p.y);
	}
	gds::Point Window::GetPosition() const{
		auto info = Info();
		return {info.x, info.y};
	}
	void Window::SetOptions(uint32_t options){
		Select();
		WM_ChangeOptions(options);
	}
	uint32_t Window::GetOptions() const{
		return Info().options;
	}
	void Window::SetTitle(const std::string &title){
		Select();
		WM_SetTitle(title.c_str());
	}
	std::string Window::GetTitle() const{
		return Info().title;
	}

	void Window::SetMenu(const Menu &m){
		Select();
		m.Select();
		WM_SetWindowMenu();
	}
	void Window::ResetMenu(){
		Select();
		WM_UnSetWindowMenu();
	}

	void Window::ShowMenu(const Menu &m, const gds::Point &p){
		Select();
		m.Select();
		WM_ShowMenu({p.x, p.y, 0, 0});
	}

	void Window::SetEventHandler(std::function<bool(const wm_Event&)> fn){
		handler = fn;
	}
	std::function<bool(const wm_Event&)> Window::GetEventHandler() const{
		return handler;
	}
	bool Window::Event(const wm_Event& evt){
		if(handler) return handler(evt);
		else return true;
	}

	void Window::Hide(){
		auto opts = GetOptions();
		opts &= ~wm_WindowOptions::Visible;
		SetOptions(opts);
	}
	void Window::Show(){
		auto opts = GetOptions();
		opts |= wm_WindowOptions::Visible;
		SetOptions(opts);
	}
	
	void Window::Close(){
		auto opts = GetOptions();
		opts &= ~wm_WindowOptions::Visible;
		opts |= wm_WindowOptions::Unlisted;
		SetOptions(opts);
	}
	void Window::Open(){
		auto opts = GetOptions();
		opts |= wm_WindowOptions::Visible;
		opts &= ~wm_WindowOptions::Unlisted;
		SetOptions(opts);
	}

}
}
