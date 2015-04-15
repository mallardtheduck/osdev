#ifndef _BITMAP_SURFACE_HPP
#define _BITMAP_SURFACE_HPP

#include "gds.hpp"
#include "surface.hpp"
#include "drawingop.hpp"

class BitmapSurface : public Surface{
private:
	GD::Image *image;

public:
	BitmapSurface(size_t w, size_t h, bool indexed);

	virtual size_t AddOperation(DrawingOp op);
	virtual void RemoveOperation(size_t id);
	virtual size_t GetWidth();
	virtual size_t GetHeight();
	virtual size_t GetDepth();
	virtual void Resize(size_t w, size_t h, bool indexed);

	virtual ~BitmapSurface();

public:

};

#endif //_BITMAP_SURFACE_HPP
