#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

class Window{
private:
	uint32_t x, y;
	uint64_t gds_id;
	
	std::string title;
public:
	Window(uint64_t surface_id);
	~Window();
	
	void Draw();
	void SetPosition(uint32_t x, uint32_t y);
};

#endif // WINDOW_HPP
