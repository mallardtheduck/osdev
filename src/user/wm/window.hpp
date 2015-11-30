#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <btos_api.h>
#include <terminal.h>
#include <string>
#include <gds/gds.h>
#include <memory>

#include "rect.hpp"
#include "client.hpp"

class Client;

enum class WindowArea{
	Content,
	Title,
	MenuButton,
	CloseButton,
	HideButton,
	ExpandButton,
	Border,
	None
};

class Window{
private:
	std::weak_ptr<Client> owner;
	Point pos;
	uint32_t z = 0;
	uint64_t gds_id;
	gds_SurfaceInfo gds_info;
	uint64_t gds_title_id = 0;
	gds_SurfaceInfo gds_titleinfo;
	std::string title;
	bool active = false;
	bool last_active = false;
	bool dragging = false;
	Point dragoffset;
	Point last_drag_pos = {0, 0};
	int64_t gds_drag_id;
	WindowArea pressed = WindowArea::None;
	uint32_t event_subs = 0;
	uint32_t options = wm_WindowOptions::Default;
	
	WindowArea GetWindowArea(Point p);
	void RefreshTitleBar(bool force = false);
	bool UpdateTitleBar(bool force = false);
public:
	uint64_t id = UINT64_MAX;
	
	Window(uint64_t surface_id);
	~Window();
	
	void Draw(bool active, bool content = true, uint64_t target = 0);
	void Draw(bool active, const Rect &r);
	void SetPosition(Point p);
	Point GetPosition();
	Point GetContentPosition();
	void SetTitle(std::string title);
	std::string GetTitle();
	uint64_t GetSurface();
	
	void SetZOrder(uint32_t zorder, bool update = true);
	uint32_t GetZOrder();
	
	Rect GetBoundingRect();
	
	void KeyInput(uint32_t key);
	void PointerInput(const bt_terminal_pointer_event &pevent);
	void PointerEnter();
	void PointerLeave();
	void OpenMenu();
	void Close();
	void Hide();
	void Expand();
	
	void SetVisible(bool v, bool update = true);
	bool GetVisible();
	void SetOwner(std::weak_ptr<Client> o);
	void Subscribe(uint32_t subs);
	uint32_t Subscribe();
	void SetOptions(uint32_t opts);
	uint32_t GetOptions();
};

#endif // WINDOW_HPP
