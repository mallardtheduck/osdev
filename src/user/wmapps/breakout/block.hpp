#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <vector>
#include "sprite.hpp"

class Block : public Sprite{
private:
	uint32_t x, y;
	uint32_t colour;
	
public:
	static const uint32_t width = 40;
	static const uint32_t height = 20;

	Block(uint32_t sx, uint32_t sy, uint32_t col): x(sx), y(sy), colour(col) {}
	
	void Draw();
	bool Step();
	wm_Rect GetBoundingRect();
};

#endif