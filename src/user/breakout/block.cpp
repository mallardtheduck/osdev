#include <gds/libgds.h>
#include <wm/libwm.h>
#include "block.hpp"
#include "game.hpp"

using namespace std;

void Block::Draw(){
	GDS_Box(x, y, width, height, colour, colour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
}

wm_Rect Block::GetBoundingRect(){
	return wm_Rect {(int32_t)x, (int32_t)y, width, height};
}

bool Block::Step(){
	if(Overlaps(GetBoundingRect(), ball->GetBoundingRect())){
		ball->BounceEdge();
		RemoveSprite(shared_from_this());
	}
	return false;
}