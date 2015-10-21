#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <btos_api.h>
#include <terminal.h>
#include <string>

struct Rect{
	uint32_t x, y, w, h;
	Rect(): x(0), y(0), w(0), h(0) {};
	Rect(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h) : x(_x), y(_y), w(_w), h(_h) {} 
};

struct Point{
	uint32_t x, y;
	Point(): x(0), y(0) {}
	Point(uint32_t _x, uint32_t _y): x(_x), y(_y) {}
};

bool InRect(uint32_t x, uint32_t y, const Rect &r);

class Window{
private:
	Point pos;
	uint32_t z = 0;
	uint64_t gds_id;
	std::string title;
	bool visible = false;
	
public:
	Window(uint64_t surface_id);
	~Window();
	
	void Draw(bool active);
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
