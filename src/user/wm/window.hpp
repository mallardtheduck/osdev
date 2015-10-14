#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

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
};

#endif // WINDOW_HPP
