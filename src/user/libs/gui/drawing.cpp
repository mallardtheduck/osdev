#include <gui/drawing.hpp>

namespace btos_api{
namespace gui{
namespace drawing{
	
void Border(gds::Surface &surf, gds::Rect rect, gds::Colour c){
	int32_t x1 = rect.x;
	int32_t y1 = rect.y;
	int32_t x2 = rect.x + rect.w;
	int32_t y2 = rect.y + rect.h;
	
	surf.Line({x1 + 1, y1}, {x2 - 1, y1}, c);
	surf.Line({x1, y1 + 1}, {x1, y2 - 1}, c);
	surf.Line({x1 + 1, y2}, {x2 - 1, y2}, c);
	surf.Line({x2, y1 + 1}, {x2, y2 - 1}, c);
}

void BevelBox(gds::Surface &surf, gds::Rect rect, gds::Colour topLeft, gds::Colour bottomRight){
	int32_t x1 = rect.x;
	int32_t y1 = rect.y;
	int32_t x2 = rect.x + rect.w;
	int32_t y2 = rect.y + rect.h;
	
	surf.Line({x1, y1}, {x1, y2}, topLeft);
	surf.Line({x1, y2}, {x2, y2}, bottomRight);
	surf.Line({x2, y1}, {x2, y2}, bottomRight);		
	surf.Line({x1, y1}, {x2, y1}, topLeft);
}
	
}
}
}