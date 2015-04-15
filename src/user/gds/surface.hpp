#ifndef _SURFACE_HPP
#define _SURFACE_HPP

#include "gds.hpp"
#include "drawingop.hpp"

class Surface {
public:
	virtual size_t AddOperation(DrawingOp op) = 0;

	virtual void RemoveOperation(size_t id) = 0;

	virtual size_t GetWidth() = 0;

	virtual size_t GetHeight() = 0;

	virtual size_t GetDepth() = 0;

	virtual ~Surface() {};
};

#endif