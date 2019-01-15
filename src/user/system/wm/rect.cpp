#include "rect.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <btos.h>

using namespace std;
using namespace gds;

#define DBG(x) do{std::stringstream dbgss; dbgss << x << std::endl; bt_zero(dbgss.str().c_str());}while(0)

bool InRect(int32_t x, int32_t y, const Rect &r){
	if(x >= r.x && x < (r.x + (int32_t)r.w) && y >= r.y && y < (r.y + (int32_t)r.h)) return true;
	else return false;
}

bool InRect(const Point &p, const Rect &r){
	return InRect(p.x, p.y, r);
}

bool Overlaps(const Rect &r1, const Rect &r2){
	return !(r1.x + (int32_t)r1.w - 1 < r2.x || r1.y + (int32_t)r1.h - 1 < r2.y || r1.x > r2.x + (int32_t)r2.w - 1 || r1.y > r2.y + (int32_t)r2.h - 1);
}

bool Contains(const Rect &r1, const Rect &r2){
	if(r1 == r2) return true;
	return (InRect(r2.x, r2.y, r1) && InRect(r2.x + r2.w, r2.y + r2.h, r1));
}

Rect Reoriginate(const Rect &r, const Point &p){
	Rect ret = r;
	ret.x -= p.x;
	ret.y -= p.y;
	return ret;
}

Point Reoriginate(const Point &pr, const Point &po){
	Point ret = pr;
	ret.x -= po.x;
	ret.y -= po.y;
	return ret;
}

vector<Rect> TileRects(const Rect &r1, const Rect &r2){
	vector<Rect> ret;
	if(!Overlaps(r1, r2)){
		ret.push_back(r1);
		ret.push_back(r2);
	}else{
		if(Contains(r1, r2)){
			ret.push_back(r1);
		}else if(Contains(r2, r1)){
			ret.push_back(r2);
		}else{
			vector<int32_t> ys;
			ys.push_back(r1.y);
			ys.push_back(r2.y);
			ys.push_back(r1.y + r1.h);
			ys.push_back(r2.y + r2.h);
			std::sort(ys.begin(), ys.end());
			Rect cr;
			bool first = true;
			for(int32_t y : ys){
				if(first) first = false;
				else{
					cr.h = y - cr.y;
					if(cr.h > 0) ret.push_back(cr);
					cr = Rect();
				}
				cr.y = y;
				int32_t minx = INT32_MAX;
				bool inr1 = false;
				if(InRect(r1.x, y, r1)){
					minx = r1.x;
					inr1 = true;
				}
				bool inr2 = false;
				if(InRect(r2.x, y, r2)){
					minx = min(minx, r2.x);
					inr2 = true;
				}
				cr.x = minx;
				int32_t maxx = 0;
				if(inr1){
					maxx = r1.x + r1.w;
				}
				if(inr2){
					maxx = max(maxx, (int32_t)(r2.x + r2.w));
				}
				cr.w = maxx - minx;
			}
			/*DBG("Input rects: ");
			DBG("(" << r1.x << ", " << r1.y << ") " << r1.w << " x " << r1.h);
			DBG("(" << r2.x << ", " << r2.y << ") " << r2.w << " x " << r2.h);
			DBG("Output rects: ");
			for(auto r : ret){
				DBG("(" << r.x << ", " << r.y << ") " << r.w << " x " << r.h);
			}*/
		}
	}
	return ret;
}

vector<Rect> TileRects(const vector<Rect> &rects){
	vector<Rect> ret;
	vector<Rect> tmp = rects;
	vector<Rect> *in = &tmp;
	vector<Rect> *out = &ret;
	bool overlaps = true;
	while(overlaps){
		overlaps = false;
		out->clear();
		for(auto i = in->begin(); i != in->end(); ++i){
			auto &r1 = *i;
			bool co = false;
			for(auto j = in->begin(); j != in->end(); ++j){
				if(i == j) continue;
				auto &r2 = *j;
				if(Overlaps(r1, r2)){
					co = true;
					overlaps = true;
					auto tiles = TileRects(r1, r2);
					for(auto t : tiles){
						out->push_back(t);
					}
					in->erase(i);
					break;
				}
			}
			if(!co){
				out->push_back(r1);
			}
		}
		std::swap(in, out);
	}
	return *out;
}

vector<Rect> SubtractRect(const Rect &r1, const Rect &r2){
	if(!Overlaps(r1, r2)) return {r1};
	if(Contains(r2, r1)) return {};
	vector<Rect> ret;
	auto r1r = r1.x + r1.w;
	auto r1b = r1.y + r1.h;
	auto r2r = r2.x + r2.w;
	auto r2b = r2.y + r2.h;
	if(r1.y < r2.y){
		Rect top;
		top.x = r1.x;
		top.y = r1.y;
		top.w = r1.w;
		top.h = r2.y - r1.y;
		ret.push_back(top);
	}
	if(r1.x < r2.x){
		Rect left;
		left.x = r1.x;
		left.y = max(r1.y, r2.y);
		left.w = r2.x - r1.x;
		left.h = min(r1b, r2b) - left.y;
		ret.push_back(left);
	}
	if(r2r < r1r){
		Rect right;
		right.x = r2r;
		right.y = max(r1.y, r2.y);
		right.w = r1r - r2r;
		right.h = min(r1b, r2b) - right.y;
		ret.push_back(right);
	}
	if(r2b < r1b){
		Rect bottom;
		bottom.x = r1.x;
		bottom.y = r2b;
		bottom.w = r1.w;
		bottom.h = r1b - r2b;
		ret.push_back(bottom);
	}
/*	DBG("Input rects: ");
	DBG("(" << r1.x << ", " << r1.y << ") " << r1.w << " x " << r1.h);
	DBG("(" << r2.x << ", " << r2.y << ") " << r2.w << " x " << r2.h);
	DBG("Output rects: ");
	for(auto r : ret){
		DBG("(" << r.x << ", " << r.y << ") " << r.w << " x " << r.h);
	}*/
	return ret;
}

vector<Rect> SubtractRect(const vector<Rect> &from, const Rect &r){
	vector<Rect> ret;
	for(const auto &f : from){
		auto res = SubtractRect(f, r);
		for(auto &re : res) ret.push_back(re);
	}
	return ret;
}

Rect Constrain(Rect r, const Rect &bounds){
	if(r.x + r.w >= bounds.w) r.w = bounds.w - r.x;
	if(r.y + r.h >= bounds.h) r.h = bounds.h - r.y;
	return r;
}

Rect Intersection(const Rect &r1, const Rect &r2){
	if(!Overlaps(r1, r2)) return { 0, 0, 0, 0 };
	return { max(r1.x, r2.x), max(r1.y, r2.y), min(r1.x + r1.w, r2.x + r2.w), min(r1.y + r1.h, r2.y + r2.h) };
}
