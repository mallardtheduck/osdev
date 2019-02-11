#ifndef _GEOM_HPP
#define _GEOM_HPP

#include "gds.h"
#include <string>
#include <vector>

namespace btos_api{
namespace gds{

	struct Point : public gds_Point{
		Point(int32_t _x, int32_t _y){
			x = _x;
			y = _y;
		}
		Point(){
			x = 0;
			y = 0;
		}

		operator bool() const{return x != 0 || y != 0;}
	};
	Point operator+(const Point &p1, const Point &p2);

	struct Rect{
		int32_t x, y;
		uint32_t w, h;

		Rect(int32_t _x, int32_t _y, uint32_t _w, uint32_t _h) : x(_x), y(_y), w(_w), h(_h) {}
		Rect(Point p, uint32_t _w, uint32_t _h) : x(p.x), y(p.y), w(_w), h(_h) {}
		Rect() : x(0), y(0), w(0), h(0) {}

		Point TopLeft(){
			return {x, y};
		}

		Point BottomRight(){
			return {static_cast<int32_t>(x + w), static_cast<int32_t>(y + h)};
		}

		operator bool() const{return x != 0 || y != 0 || w != 0 || h != 0;}
	};

	bool operator==(const Rect &r1, const Rect &r2);
	bool operator<(const Rect &r1, const Rect &r2);

	inline bool operator!=(const Rect &r1, const Rect &r2){
		return !(r1 == r2);
	}

	struct Colour{
		uint32_t id;
		uint8_t r, g, b, a;

		Colour() {}
		Colour(uint32_t _id, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : id(_id), r(_r), g(_g), b(_b), a(_a) {}
		explicit Colour(uint32_t i) : id(i) {}
	};

	struct Font{
		uint32_t id;
		
		std::string GetName();
		gds_FontStyle::Enum GetStyle();
		gds_FontInfo Info();
		gds_GlyphInfo GetGlyphInfo(uint32_t size, char c);
		static Font Get(const std::string &name, gds_FontStyle::Enum style = gds_FontStyle::Normal);
	};
	
	bool InRect(int32_t x, int32_t y, const gds::Rect &r);
	bool InRect(const gds::Point &p, const gds::Rect &r);
	bool Overlaps(const gds::Rect &r1, const gds::Rect &r2);
	bool Contains(const gds::Rect &r1, const gds::Rect &r2);
	gds::Rect Reoriginate(const gds::Rect &r, const gds::Point &p);
	gds::Point Reoriginate(const gds::Point &pr, const gds::Point &po);
	std::vector<gds::Rect> TileRects(const gds::Rect &r1, const gds::Rect &r2);
	std::vector<gds::Rect> TileRects(const std::vector<gds::Rect> &rects);
	std::vector<gds::Rect> SubtractRect(const gds::Rect &r1, const gds::Rect &r2);
	std::vector<gds::Rect> SubtractRect(const std::vector<gds::Rect> &from, const gds::Rect &r);
	gds::Rect Constrain(gds::Rect r, const gds::Rect &bounds);
	gds::Rect Intersection(const gds::Rect &r1, const gds::Rect &r2);

}
}

#endif
