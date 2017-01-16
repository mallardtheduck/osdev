#ifndef _RECT_HPP
#define _RECT_HPP

#include <cstdint>
#include <vector>

struct Rect{
	int32_t x, y;
	uint32_t w, h;
	Rect(): x(0), y(0), w(0), h(0) {};
	Rect(int32_t _x, int32_t _y, uint32_t _w, uint32_t _h) : x(_x), y(_y), w(_w), h(_h) {} 
};

bool operator==(const Rect &r1, const Rect &r2);
bool operator<(const Rect &r1, const Rect &r2);

struct Point{
	int32_t x, y;
	Point(): x(0), y(0) {}
	Point(int32_t _x, int32_t _y): x(_x), y(_y) {}
};

bool InRect(int32_t x, int32_t y, const Rect &r);
bool InRect(const Point &p, const Rect &r);
bool Overlaps(const Rect &r1, const Rect &r2);
bool Contains(const Rect &r1, const Rect &r2);
Rect Reoriginate(const Rect &r, const Point &p);
Point Reoriginate(const Point &pr, const Point &po);
std::vector<Rect> TileRects(const Rect &r1, const Rect &r2);
Rect Constrain(Rect r, const Rect &bounds);

#endif