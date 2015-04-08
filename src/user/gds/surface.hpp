#ifndef _SURFACE_HPP
#define _SURFACE_HPP

#include "drawingop.h"

class Surface{
public:
	size_t AddOperation(DrawingOp op)=0;
	void RemoveOperation(size_t id);

	size_t GetWidth();
	size_t GetHeight();
	size_t GetDepth();

	~Surface() = 0;
};

#endif