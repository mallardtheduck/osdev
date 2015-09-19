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

};

#endif // WINDOW_HPP
