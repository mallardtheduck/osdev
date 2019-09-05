#ifndef _GRAPHICS_HPP
#define _GRPAHICS_HPP

#include "gds.hpp"
#include "bitmap_surface.hpp"

void FastBlitFromCompressed(CompressedImageCursor &src, GD::Image &dst, int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY, uint32_t w, uint32_t h, uint32_t flags);
void FastBlit(const GD::Image &src, GD::Image &dst, int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY, uint32_t w, uint32_t h, uint32_t flags);
void FastBox(GD::Image &im, int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t col);
std::unique_ptr<gds_TextMeasurements> MeasureText(const gds_TextParameters &p, std::string text);

#endif
