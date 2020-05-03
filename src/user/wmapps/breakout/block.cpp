#include <gds/libgds.h>
#include <wm/libwm.h>
#include "block.hpp"
#include "game.hpp"

using namespace std;
using namespace btos_api;

void Block::Draw(){
	surf->Box({(int32_t)x, (int32_t)y, width, height}, colour, colour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
}

gds::Rect Block::GetBoundingRect(){
	return {(int32_t)x, (int32_t)y, width, height};
}

bool Block::Step(){
	if(Overlaps(GetBoundingRect(), ball->GetBoundingRect())){
		ball->BounceEdge();
		RemoveSprite(shared_from_this());
		RemoveBlock();
	}
	return false;
}
