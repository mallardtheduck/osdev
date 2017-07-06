#include <gds/geom.hpp>
#include "gds/libgds.h"

namespace btos_api{
namespace gds{

	std::string Font::GetName(){
		return Info().name;
	}

	gds_FontStyle::Enum Font::GetStyle(){
		return static_cast<gds_FontStyle::Enum>(Info().fontStyle);
	}

	gds_FontInfo Font::Info(){
		return GDS_GetFontInfo(id);
	}

	Font Font::Get(const std::string &name, gds_FontStyle::Enum style){
		Font ret;
		ret.id = GDS_GetFontID(name.c_str(), style);
		return ret;
	}

	bool operator==(const Rect &r1, const Rect &r2){
		return r1.x == r2.y && r1.y == r2.y && r1.w == r2.w && r1.h == r2.h;
	}

	bool operator<(const Rect &r1, const Rect &r2){
		if (r1.x < r2.x) return true;
		else if (r1.x > r2.x) return false;
		else if (r1.y < r2.y) return true;
		else if (r1.y > r2.y) return false;
		else if ((r1.x + r1.w) < (r2.x + r2.w)) return true;
		else if ((r1.x + r1.w) > (r2.x + r2.w)) return false;
		else if ((r1.y + r1.h) < (r2.y + r2.h)) return true;
		else if ((r1.y + r1.h) > (r2.y + r2.h)) return false;
		else return false;
	}

	Point operator+(const Point &p1, const Point &p2){
		return {p1.x + p2.x, p1.y + p2.y};
	}

}
}
