#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

struct Rect{
	uint32_t x, y, w, h;
	Rect(): x(0), y(0), w(0), h(0) {};
	Rect(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h) : x(_x), y(_y), w(_w), h(_h) {} 
};

class Window{
private:
	uint32_t x, y, z;
	uint64_t gds_id;
	
	std::string title;
public:
	Window(uint64_t surface_id);
	~Window();
	
	void Draw(bool active);
	void SetPosition(uint32_t x, uint32_t y);
	void SetTitle(std::string title);
	
	void SetZOrder(uint32_t zorder);
	uint32_t GetZOrder();
	
	Rect GetBoundingRect();
};

#endif // WINDOW_HPP
