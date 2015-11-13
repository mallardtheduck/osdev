#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <btos_api.h>
#include <terminal.h>
#include <string>

#include "rect.hpp"

enum class WindowArea{
	Content,
	Title,
	MenuButton,
	CloseButton,
	MinButton,
	MaxButton,
	Border,
	None
};

class Window{
private:
	Point pos;
	uint32_t z = 0;
	uint64_t gds_id;
	std::string title;
	bool visible = false;
	bool active = false;
	bool dragging = false;
	Point dragoffset;
	WindowArea pressed = WindowArea::None;
	
	WindowArea GetWindowArea(Point p);
	void RefreshTitleBar();
public:
	uint64_t id = UINT64_MAX;
	
	Window(uint64_t surface_id);
	~Window();
	
	void Draw(bool active, bool content = true);
	void SetPosition(Point p);
	void SetTitle(std::string title);
	std::string GetTitle();
	
	void SetZOrder(uint32_t zorder, bool update = true);
	uint32_t GetZOrder();
	
	Rect GetBoundingRect();
	
	void KeyInput(uint32_t key);
	void PointerInput(const bt_terminal_pointer_event &pevent);
	void PointerEnter();
	void PointerLeave();
	
	void SetVisible(bool v);
	bool GetVisible();
};

#endif // WINDOW_HPP
