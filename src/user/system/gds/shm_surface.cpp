#include "shm_surface.hpp"
#include "graphics.hpp"
#include <gd.h>
#include <dev/rtc.h>
#include <malloc.h>

using namespace std;

static inline uint32_t getPixelTrueColour(char *ptr, uint32_t w, uint32_t x, uint32_t y){
	size_t pos = (w * y) + x;
	return ((uint32_t*)ptr)[pos];
}

static inline uint32_t getPixelIndexed(char *ptr, uint32_t w, uint32_t x, uint32_t y){
	size_t pos = (w * y) + x;
	return ((uint8_t*)ptr)[pos];
}


SHMSurface::SHMSurface(size_t w, size_t h, uint32_t cT, uint32_t /*scale*/, uint64_t shmRegion, size_t shmOffset) : width(w), height(h), colourType(cT) {
	size_t size = width * height * (GetDepth() / 8);
	size_t pages = size / 4096;
	if(pages * 4096 < size) ++pages;
	ptr = (char*)memalign(4096, pages * 4096);
	shm_handle = bt_shm_map(shmRegion, ptr, shmOffset, pages, bt_shm_flags::ReadOnly);
}

SHMSurface::~SHMSurface(){
	bt_closehandle(shm_handle);
	free(ptr);
}

size_t SHMSurface::AddOperation(gds_DrawingOp /*op*/){
	return 0;
}

void SHMSurface::RemoveOperation(size_t /*id*/){
}

gds_DrawingOp SHMSurface::GetOperation(size_t /*id*/){
	gds_DrawingOp ret;
	ret.type = gds_DrawingOpType::None;
	return ret;
}

size_t SHMSurface::GetWidth(){
	return width;
}

size_t SHMSurface::GetHeight(){
	return height;
}

size_t SHMSurface::GetDepth(){
	return (colourType & gds_ColourType::True) ? 32 : 8;
}

uint32_t SHMSurface::GetScale(){
	return 100;
}

void SHMSurface::SetScale(uint32_t /*scale*/){
}

gds_SurfaceType::Enum SHMSurface::GetType(){
	return gds_SurfaceType::Memory;
}

uint32_t SHMSurface::GetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
	a >>= 1;
	uint32_t colour = (a << 24) | (r << 16) | (g << 8) | b;
	if((colourType & gds_ColourType::True)){
		return colour;
	}else{
		if(colour == 0) return 0;
		uint32_t dist = UINT32_MAX;
		size_t best = 0;
		for(size_t i = 1; i < palette.size(); ++i){
			if(!palette[i]){
				palette[i] = colour;
				return i;
			}
			if(max(colour, palette[i]) - min(colour, palette[i]) < dist){
				dist = max(colour, palette[i]) - min(colour, palette[i]);
				best = i;
			}
		}
		return best;
	}
}

void SHMSurface::SetOpParameters(std::shared_ptr<gds_OpParameters> /*p*/){
}

std::shared_ptr<gds_OpParameters> SHMSurface::GetOpParameters(uint32_t /*op*/){
	auto ret = make_shared<gds_OpParameters>();
	ret->op_id = 0;
	ret->size = 0;
	return ret;
}
	
void SHMSurface::Resize(size_t w, size_t h, bool i){
	width = w;
	height = h;
	if(i){
		colourType &= ~gds_ColourType::True;
	}else{
		colourType |= gds_ColourType::True;
	}
}

std::shared_ptr<GD::Image> SHMSurface::Render(uint32_t /*scale*/){
	shared_ptr<GD::Image> rendering = make_shared<GD::Image>(width, height, !(colourType & gds_ColourType::True));
	uint64_t start = bt_rtc_millis();
	RenderTo(rendering, 0, 0, 0, 0, width, height);
	uint64_t end = bt_rtc_millis();
	DBG("GDS: SHM surface rendered in " << end - start << "ms.");
	return rendering;
}

void SHMSurface::RenderTo(std::shared_ptr<GD::Image> dst, int32_t srcX, int32_t srcY, int32_t dstX, int32_t dstY, uint32_t w, uint32_t h){
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
	if(srcX > (int32_t)width) return;
	if(srcY > (int32_t)height) return;
	if(dstX > dst->Width()) return;
	if(dstY > dst->Height()) return;
	if(srcX + w > width) w = width - srcX;
	if(srcY + h > height) h = height - srcY;
	if(dstX + w > (uint32_t)dst->Width()) w = dst->Width() - dstX;
	if(dstY + h > (uint32_t)dst->Height()) h = dst->Height() - dstY;
	gdImagePtr dstPtr = dst->GetPtr();
	if((colourType & gds_ColourType::True)){
		if(dst->IsTrueColor()){
			for(size_t y = 0; y < h; ++y){
				for(size_t x = 0; x < w; ++x){
					uint32_t srcPxl = getPixelTrueColour(ptr, width, srcX + x, srcY + y);
					if(!(colourType & ~gds_ColourType::AlphaDisable) && gdTrueColorGetAlpha(srcPxl) != gdAlphaOpaque){
						uint32_t dstPxl = gdImageTrueColorPixel(dstPtr, dstX + x, dstY + y);
						srcPxl = gdAlphaBlend(dstPxl, srcPxl);
					}else{
						srcPxl = gdTrueColorAlpha(gdTrueColorGetRed(srcPxl), gdTrueColorGetGreen(srcPxl), gdTrueColorGetBlue(srcPxl), gdAlphaOpaque);
					}
					gdImageTrueColorPixel(dstPtr, dstX + x, dstY + y) = srcPxl;
				}
			}
		}else{
			uint32_t srcCol;
			uint8_t dstCol;
			for(size_t y = 0; y < h; ++y){
				for(size_t x = 0; x < w; ++x){
					uint32_t srcPxl = getPixelTrueColour(ptr, width, srcX + x, srcY + y);
					if((!y && !x) || srcCol != srcPxl){
						dstCol = gdImageColorResolveAlpha(dstPtr, gdTrueColorGetRed(srcPxl), gdTrueColorGetGreen(srcPxl), gdTrueColorGetBlue(srcPxl), gdAlphaOpaque);// gdTrueColorGetAlpha(srcPxl));
						srcCol = srcPxl;
					}
					gdImagePalettePixel(dstPtr, dstX + x, dstY + y) = dstCol;
				}
			}
		}
	}else{
		if(dst->IsTrueColor()){
			uint8_t srcCol;
			uint32_t dstCol;
			for(size_t y = 0; y < h; ++y){
				for(size_t x = 0; x < w; ++x){
					uint8_t srcPxl = getPixelIndexed(ptr, width, srcX + x, srcY + y);
					if((!y && !x) || srcCol != srcPxl){
						dstCol = palette[srcPxl];
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
					uint8_t srcPxl = getPixelIndexed(ptr, width, srcX + x, srcY + y);
					if ((!y && !x) || srcPxl != srcCol){
						dstCol = palette[srcPxl];
						srcCol = srcPxl;
					}
					gdImagePalettePixel(dstPtr, dstX + x, dstY + y) = dstCol;
				}
			}
		}
	}
}

void SHMSurface::ReorderOp(uint32_t /*op*/, uint32_t /*ref*/, gds_ReorderMode::Enum /*mode*/){
	
}

void SHMSurface::Clear(){}

std::unique_ptr<gds_TextMeasurements> SHMSurface::MeasureText(const gds_TextParameters &p, std::string text){
	return ::MeasureText(p, text);
}

