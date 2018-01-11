#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <vector>
#include <memory>
#include <gds/surface.hpp>
#include "sprite.hpp"

class Block : public Sprite{
private:
	uint32_t x, y;
	gds::Colour colour;
	
public:
	static const uint32_t width = 40;
	static const uint32_t height = 20;

	Block(std::shared_ptr<gds::Surface> s, gds::Point p, gds::Colour col): Sprite(s), x(p.x), y(p.y), colour(col) {}
	
	void Draw();
	bool Step();
	gds::Rect GetBoundingRect();
};

#endif
