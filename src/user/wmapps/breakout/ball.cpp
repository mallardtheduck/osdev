#include <dev/keyboard.h>
#include <gds/libgds.h>
#include <wm/libwm.h>
#include "ball.hpp"
#include <cmath>

void Ball::Launch(){
	if(!launched){
		xvel = 10;
		yvel = -10;
		launched = true;
	}
}

void Ball::Reset(){
	x = 170; y = 120;
	launched = false;
	reset = true;
}

void Ball::Draw(){
	uint32_t green = GDS_GetColour(0, 255, 0);
	GDS_Ellipse(x, y, size, size, green, green, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
}

void Ball::BounceSide(){
	if(!bounced){
		xvel = -xvel;
		bounced = true;
	}
}
void Ball::BounceEdge(){
	if(!bounced){
		yvel = -yvel;
		bounced = true;
	}
}

void Ball::BounceAngle(float angle){
	if(!bounced){
		xvel = angle * 10;
		double cosval = xvel / sqrt(200);
		double sinval = sin(acos(cosval));
		yvel = -(sqrt(200) * sinval);
		bounced = true;
	}
}

bool Ball::Step(){
	bool ret = false;
	if(launched){
		lx = x;
		ly = y;
		x += xvel;
		y += yvel;
		if(x < 0) {
			x = 0;
			BounceSide();
		}else if(x > 320){
			x = 320;
			BounceSide();
		}
		if(y < 0){
			y = 0;
			BounceEdge();
		}
		if(y > 240) Reset();
		ret = true;
	}else if(reset){
		reset = false;
		ret = true;
	}
	bounced = false;
	return ret;
}

void Ball::Input(const wm_Event &e){
	if(KB_char(e.Key.code) == ' '){
		Launch();
	}
}

wm_Rect Ball::GetBoundingRect(){
	return wm_Rect{x - (int32_t)size/2 - 1, y - (int32_t)size/2 - 1, size + 2, size + 2};
}

uint32_t Ball::GetZOrder(){
	return 2;
}