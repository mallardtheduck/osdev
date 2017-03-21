#include "screen.hpp"
#include <cstring>
#include <cstdlib>
#include <dev/rtc.h>

void FastBlit(const GD::Image &src, GD::Image &dst, int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY, uint32_t w, uint32_t h){
	if(srcX < 0){
		if(w < (uint32_t)-srcX) return;
		w += srcX;
		dstX -= srcX;
		srcX = 0;
	}
	if(srcY < 0){
		if(h < (uint32_t)-srcY) return;
		h += srcY;
		dstY -= srcY;
		srcY = 0;
	}
	if(dstX < 0){
		if(w < (uint32_t)-dstX) return;
		w += dstX;
		srcX -= dstX;
		dstX = 0;
	}
	if(dstY < 0){
		if(h < (uint32_t)-dstY) return;
		h += dstY;
		srcY -= dstY;
		dstY = 0;
	}
	if(srcX > src.Width()) return;
	if(srcY > src.Height()) return;
	if(dstX > dst.Width()) return;
	if(dstY > dst.Height()) return;
	if(srcX + w > (uint32_t)src.Width()) w = src.Width() - srcX;
	if(srcY + h > (uint32_t)src.Height()) h = src.Height() - srcY;
	if(dstX + w > (uint32_t)dst.Width()) w = dst.Width() - dstX;
	if(dstY + h > (uint32_t)dst.Height()) h = dst.Height() - dstY;
	gdImagePtr srcPtr = src.GetPtr();
	gdImagePtr dstPtr = dst.GetPtr();
	if(src.IsTrueColor()){
		uint32_t srcTransparent = gdImageGetTransparent(srcPtr);
		if(dst.IsTrueColor()){
			for(size_t y = 0; y < h; ++y){
				for(size_t x = 0; x < w; ++x){
					uint32_t srcPxl = gdImageTrueColorPixel(srcPtr, srcX + x, srcY + y);
					if(srcPxl == srcTransparent) continue;
					if(gdTrueColorGetAlpha(srcPxl) != gdAlphaOpaque){
						uint32_t dstPxl = gdImageTrueColorPixel(dstPtr, dstX + x, dstY + y);
						srcPxl = gdAlphaBlend(dstPxl, srcPxl);
					}
					gdImageTrueColorPixel(dstPtr, dstX + x, dstY + y) = srcPxl;
				}
			}
		}else{
			uint32_t srcCol;
			uint8_t dstCol;
			for(size_t y = 0; y < h; ++y){
				for(size_t x = 0; x < w; ++x){
					uint32_t srcPxl = gdImageTrueColorPixel(srcPtr, srcX + x, srcY + y);
					if(srcPxl == srcTransparent) continue;
					if((!y && !x) || srcCol != srcPxl){
						dstCol = gdImageColorResolveAlpha(dstPtr, gdTrueColorGetRed(srcPxl), gdTrueColorGetGreen(srcPxl), gdTrueColorGetBlue(srcPxl), gdTrueColorGetAlpha(srcPxl));
						srcCol = srcPxl;
					}
					gdImagePalettePixel(dstPtr, dstX + x, dstY + y) = dstCol;
				}
			}
		}
	}else{
		uint8_t srcTransparent = (uint8_t)gdImageGetTransparent(srcPtr);
		if(dst.IsTrueColor()){
			uint8_t srcCol;
			uint32_t dstCol;
			for(size_t y = 0; y < h; ++y){
				for(size_t x = 0; x < w; ++x){
					uint8_t srcPxl = gdImagePalettePixel(srcPtr, srcX + x, srcY + y);
					if(srcPxl == srcTransparent) continue;
					if((!y && !x) || srcCol != srcPxl){
						dstCol = gdTrueColorAlpha(srcPtr->red[srcPxl], srcPtr->green[srcPxl], srcPtr->blue[srcPxl], srcPtr->alpha[srcPxl]);
						srcCol = srcPxl;
					}
					gdImageTrueColorPixel(dstPtr, dstX + x, dstY + y) = dstCol;
				}
			}
		}else{
			uint8_t srcCol;
			uint8_t dstCol;
			for(size_t y = 0; y < h; ++y){
				for(size_t x = 0; x < w; ++x){
					uint8_t srcPxl = gdImagePalettePixel(srcPtr, srcX + x, srcY + y);
					if(srcPxl == srcTransparent) continue;
					if(srcPtr == dstPtr) dstCol = srcPxl;
					else if ((!y && !x) || srcPxl != srcCol){
						dstCol = gdImageColorResolveAlpha(dstPtr, srcPtr->red[srcPxl], srcPtr->green[srcPxl], srcPtr->blue[srcPxl], srcPtr->alpha[srcPxl]);
						srcCol = srcPxl;
					}
					gdImagePalettePixel(dstPtr, dstX + x, dstY + y) = dstCol;
				}
			}
		}
	}
}

void FastBox(GD::Image &im, int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t col){
	if(x < 0){
		if(w < (uint32_t)-x) return;
		w += x;
		x = 0;
	}
	if(y < 0){
		if(h < (uint32_t)-y) return;
		h += y;
		y = 0;
	}
	if(x > im.Width()) return;
	if(y > im.Height()) return;
	if(x + w > (uint32_t)im.Width()) w = im.Width() - x;
	if(y + h > (uint32_t)im.Height()) h = im.Height() - y;
	gdImagePtr imPtr = im.GetPtr();
	if(im.IsTrueColor()){
		for(size_t ypos = 0; ypos < h; ++ypos){
			for(size_t xpos = 0; xpos < w; ++xpos){
				gdImageTrueColorPixel(imPtr, x + xpos, y + ypos) = col;
			}
		}
	}else{
		for(size_t ypos = 0; ypos < h; ++ypos){
			for(size_t xpos = 0; xpos < w; ++xpos){
				gdImagePalettePixel(imPtr, x + xpos, y + ypos) = (uint8_t)col;
			}
		}
	}
}
