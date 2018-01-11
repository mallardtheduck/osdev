#ifndef _PADDLE_HPP
#define _PADDLE_HPP

#include "sprite.hpp"

class Paddle : public Sprite{
private:
	uint32_t x = 145;
	int32_t dx = 0;
	
public:
	static const uint32_t width = 50;
	static const uint32_t height = 20;
	static const uint32_t y = 200;
	static const uint32_t speed = 15;

	Paddle(std::shared_ptr<gds::Surface> s) : Sprite(s) {}	

	void Draw();
	void Left();
	void Right();
	bool Step();
	gds::Rect GetBoundingRect();
	uint32_t GetZOrder();
	
	void Input(const wm_Event &e);
};

#endif
