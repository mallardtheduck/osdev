#ifndef _DRAWING_HPP
#define _DRAWING_HPP

#include <gds/surface.hpp>

namespace btos_api{
namespace gui{
namespace drawing{
	
void Border(gds::Surface &surf, gds::Rect rect, gds::Colour c);
void BevelBox(gds::Surface &surf, gds::Rect rect, gds::Colour topLeft, gds::Colour bottomRight);
	
}
}
}

#endif