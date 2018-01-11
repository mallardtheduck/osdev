#ifndef _RECT_HPP
#define _RECT_HPP

#include <cstdint>
#include <vector>
#include <gds/geom.hpp>

using namespace btos_api;

bool InRect(int32_t x, int32_t y, const gds::Rect &r);
bool InRect(const gds::Point &p, const gds::Rect &r);
bool Overlaps(const gds::Rect &r1, const gds::Rect &r2);
bool Contains(const gds::Rect &r1, const gds::Rect &r2);
gds::Rect Reoriginate(const gds::Rect &r, const gds::Point &p);
gds::Point Reoriginate(const gds::Point &pr, const gds::Point &po);
std::vector<gds::Rect> TileRects(const gds::Rect &r1, const gds::Rect &r2);
gds::Rect Constrain(gds::Rect r, const gds::Rect &bounds);
gds::Rect Intersection(const gds::Rect &r1, const gds::Rect &r2);

#endif
