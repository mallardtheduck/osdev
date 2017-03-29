#ifndef _GRAPHICS_HPP
#define _GRPAHICS_HPP

#include "gds.hpp"

void FastBlit(const GD::Image &src, GD::Image &dst, int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY, uint32_t w, uint32_t h);
void FastBox(GD::Image &im, int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t col);

#endif
