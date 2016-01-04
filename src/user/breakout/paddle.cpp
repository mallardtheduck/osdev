#include <gds/libgds.h>
#include <wm/libwm.h>
#include <dev/keyboard.h>
#include "paddle.hpp"
#include "game.hpp"

void Paddle::Draw(){
	uint32_t colour = GDS_GetColour(128, 128, 128);
	GDS_Box(x, y, width, height, colour, colour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
}

void Paddle::Left(){
	dx = -speed;
}

void Paddle::Right(){
	dx = speed;
}

bool Paddle::Step(){
	if(Overlaps(ball->GetBoundingRect(), GetBoundingRect())){
		ball->BounceEdge();
	}
	if(dx){
		uint32_t lx = x;
		x += dx;
		if(dx < 0 && x > lx) x = 0;
		if(x > 320 - width) x = 320 - width;
		dx = 0;
		return true;
	}
	return false;
}

void Paddle::Input(const wm_Event &e){
	if(e.type == wm_EventType::Keyboard){
		uint16_t keycode = KB_code(e.Key.code);
		if(keycode == (KeyFlags::NonASCII | KeyCodes::LeftArrow)){
			Left();
		}else if(keycode == (KeyFlags::NonASCII | KeyCodes::RightArrow)){
			Right();
		}
	}
}

wm_Rect Paddle::GetBoundingRect(){
	return wm_Rect {(int32_t)x, (int32_t)y, width, height};
}

uint32_t Paddle::GetZOrder(){
	return 1;
}