#ifndef _GEOM_HPP
#define _GEOM_HPP

#include "gds.h"
#include <string>

namespace btos_api{
namespace gds{

	struct Point : public gds_Point{
		Point(int32_t _x, int32_t _y){
			x = _x;
			y = _y;
		}
	};

	struct Rect{
		int32_t x, y;
		uint32_t w, h;

		Rect(int32_t _x, int32_t _y, uint32_t _w, uint32_t _h) : x(_x), y(_y), w(_w), h(_h) {}
		Rect(Point p, uint32_t _w, uint32_t _h) : x(p.x), y(p.y), w(_w), h(_h) {}

		Point TopLeft(){
			return {x, y};
		}

		Point BottomRight(){
			return {static_cast<int32_t>(x + w), static_cast<int32_t>(y + h)};
		}
	};

	struct Colour{
		uint32_t id;
		int32_t r, g, b, a;
	};

	struct Font{
		uint32_t id;
		
		std::string GetName();
		gds_FontStyle::Enum GetStyle();
		gds_FontInfo Info();
	};

}
}

#endif
