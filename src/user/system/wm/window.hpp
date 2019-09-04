#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <btos.h>
#include <dev/terminal.h>
#include <string>
#include <gds/gds.h>
#include <memory>

#include "rect.hpp"
#include "client.hpp"
#include "drawing.hpp"

class Client;
class TitleBar;
class Menu;

class Window : public std::enable_shared_from_this<Window>{
private:
	std::weak_ptr<Client> owner;
	gds::Point pos;
	uint32_t z = 0;
	std::shared_ptr<gds::Surface> content;
	gds_SurfaceInfo gds_info;
	TitleBar titlebar;
	std::shared_ptr<gds::Surface> titleImage;
	gds_SurfaceInfo gds_titleinfo;
	std::string title;
	bool active = false;
	bool last_active = false;
	
	enum class DragMode{
		None, Move, Resize
	};
	
	DragMode dragMode = DragMode::None;
	gds::Point dragoffset;
	gds::Point last_drag_pos = {0, 0};
	gds::Point resize_origin;
	gds::Point pre_move_pos;
	std::shared_ptr<gds::Surface> dragImage;
	WindowArea pressed = WindowArea::None;
	uint32_t event_subs = 0;
	uint32_t options = wm_WindowOptions::Default;
	std::shared_ptr<Menu> windowMenu;
	
	std::weak_ptr<Window> modal;
	
	WindowArea GetWindowArea(gds::Point p);
	void RefreshTitleBar(bool force = false);
	bool UpdateTitleBar(bool force = false);
public:
	uint64_t id = UINT64_MAX;
	
	Window(std::shared_ptr<gds::Surface> surf);
	~Window();
	
	void Draw(bool active, bool content = true, std::shared_ptr<gds::Surface> = nullptr);
	void Draw(bool active, const gds::Rect &r);
	void DrawGrabbed(const gds::Rect &r);
	void SetPosition(gds::Point p);
	gds::Point GetPosition();
	gds::Point GetContentPosition();
	void SetTitle(std::string title);
	std::string GetTitle();
	std::shared_ptr<gds::Surface> GetSurface();
	void SetSurface(std::shared_ptr<gds::Surface> surf);
	
	void SetZOrder(uint32_t zorder, bool update = true);
	uint32_t GetZOrder();
	
	gds::Rect GetBoundingRect();
	uint32_t GetWidth();
	uint32_t GetHeight();
	gds::Point GetContentOffset();
	
	bool HasTitleBar();
	bool HasBorder();
	
	void KeyInput(uint32_t key);
	void PointerInput(const bt_terminal_pointer_event &pevent);
	void PointerEnter();
	void PointerLeave();
	void OpenMenu();
	void Close();
	void Hide();
	void Expand();
	void MenuAction(uint64_t menu, uint32_t action);
	void Move(gds::Point newpos);
	void Resize(uint32_t w, uint32_t h);
	void GlobalEvent(wm_EventType::Enum e, std::shared_ptr<Window> win);
	
	void SetVisible(bool v, bool update = true);
	bool GetVisible();
	void SetOwner(std::weak_ptr<Client> o);
	void Subscribe(uint32_t subs);
	uint32_t Subscribe();
	void SetOptions(uint32_t opts);
	uint32_t GetOptions();
	void SetWindowMenu(std::shared_ptr<Menu> menu);
	std::shared_ptr<Menu> GetWindowMenu();
	
	void StartDrag();
	void StartResize();
	
	void SetModal(std::weak_ptr<Window> win);
	void ClearModal();
	
	std::shared_ptr<Client> GetOwner();
};

#endif // WINDOW_HPP
