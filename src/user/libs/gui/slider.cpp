#include <gui/slider.hpp>
#include <gui/drawing.hpp>
#include <gui/defaults.hpp>
#include <dev/mouse.h>
#include <dev/keyboard.h>
#include <wm/libwm.h>

#include <cmath>

namespace btos_api{
namespace gui{  

struct SliderImpl{
	gds::Rect rect;
	int32_t min;
	int32_t max;
	int32_t value;
	int32_t snapTo;
	
	bool focus = false;
	bool enabled = true;
	
	std::unique_ptr<gds::Surface> bkSurf;
};
PIMPL_IMPL(SliderImpl);
	
Slider::Slider(const gds::Rect &r, int32_t mi, int32_t ma, int32_t def, int32_t sT) : im(new SliderImpl()){
	im->rect = r; im->min = mi; im->max = ma; im->value = def; im->snapTo = sT;
}

EventResponse Slider::HandleEvent(const wm_Event &e){
	bool handled = false;
	int32_t cvalue = im->value;
	if(e.type == wm_EventType::PointerMove || e.type == wm_EventType::PointerButtonUp){
		handled = true;
		if(e.type == wm_EventType::PointerMove){
			auto pinfo = WM_GetPointerInfo();
			if(!(pinfo.flags & MouseFlags::Button1)) return {true};
		}
		
		int32_t xpos = e.Pointer.x - im->rect.x;
		int32_t inW = im->rect.w - 1;
		int32_t lineLeft = 3;
		int32_t lineRight = inW - 3;
		
		if(xpos < lineLeft) im->value = im->min;
		else if(xpos > lineRight) im->value = im->max;
		else{
			xpos -= lineLeft;
			if(xpos < 0) xpos = 0;
			double scale = (((double)(lineRight - lineLeft) / (double)(im->max - im->min)));
			im->value = (xpos / scale) + im->min;
			if(im->value > im->max) im->value = im->max;
			if(im->value < im->min) im->value = im->min;
		}
	}else if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && im->value > im->min){
			im->value -= im->snapTo;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && im->value < im->max){
			im->value += im->snapTo;
			handled = true;
		}
	}
	if(cvalue != im->value){
		if((im->value - im->min) % im->snapTo){
			im->value -= im->min;
			im->value = round((double)im->value / (double)im->snapTo) * im->snapTo;
			im->value += im->min;
		}
		RaiseChangeEvent();
		IControl::Paint(im->rect);
	}
	return {handled};
}

void Slider::Paint(gds::Surface &s){
	int32_t inW = im->rect.w - 1;
	auto lineTop = 5;
	auto lineBottom = 9;
	auto lineLeft = 4;
	auto lineRight = inW - 4;
	
	if(!im->bkSurf){
		im->bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
	
		auto bkgCol = colours::GetBackground().Fix(*im->bkSurf);
		auto bkBorder = colours::GetBorder().Fix(*im->bkSurf);
		
		im->bkSurf->BeginQueue();
		im->bkSurf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		drawing::Border(*im->bkSurf, {lineLeft, lineTop, (uint32_t)(lineRight - lineLeft), (uint32_t)(lineBottom - lineTop)}, bkBorder);
		
		auto topLeft = colours::GetSliderLineLowLight().Fix(*im->bkSurf);
		auto bottomRight = colours::GetSliderLineHiLight().Fix(*im->bkSurf);
		drawing::BevelBox(*im->bkSurf, {lineLeft + 1, lineTop + 1, (uint32_t)(lineRight - lineLeft - 2), (uint32_t)(lineBottom - lineTop - 2)}, topLeft, bottomRight);
		
		int tickTop = lineBottom + 2;
		
		auto tick = colours::GetSliderTick().Fix(*im->bkSurf);
		im->bkSurf->Line({lineLeft, tickTop}, {lineLeft, (int32_t)im->rect.h}, tick);
		im->bkSurf->Line({lineRight, tickTop}, {lineRight, (int32_t)im->rect.h}, tick);
		auto mid = ((lineRight - lineLeft) / 2) + lineLeft;
		im->bkSurf->Line({mid, tickTop}, {mid, (int32_t)im->rect.h}, tick);
		
		im->bkSurf->CommitQueue();
		im->bkSurf->Compress();
	}
	
	auto border = colours::GetBorder().Fix(s);
	auto slider = colours::GetSliderColour().Fix(s);
	
	s.Blit(*im->bkSurf, im->rect.AtZero(), im->rect);
	
	if(im->focus){
		auto focusCol = colours::GetSliderFocus().Fix(s);
		s.Box(im->rect, focusCol, focusCol);
	}
	
	int32_t pos = lineLeft + ((double)(im->value - im->min) * (((double)(lineRight - lineLeft) / (double)(im->max - im->min))));
	std::vector<gds::Point> points = {{pos - 4, 1}, {pos - 4, 7}, {pos, 13}, {pos + 4, 7}, {pos + 4, 1}};
	
	for(auto &p : points){
		p.x += im->rect.x;
		p.y += im->rect.y;
	}
	
	s.Polygon(points, false, border, slider, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	s.Line({im->rect.x + pos - 3, im->rect.y}, {im->rect.x + pos + 3, im->rect.y}, border);
	
	if(!im->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(im->rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect Slider::GetPaintRect(){
	return im->rect;
}
gds::Rect Slider::GetInteractRect(){
	return im->rect;
}

uint32_t Slider::GetSubscribed(){
	return wm_EventType::PointerMove | wm_EventType::PointerButtonUp | wm_EventType::Keyboard;
}

void Slider::Focus(){
	if(!im->focus){
		im->focus = true;
		IControl::Paint(im->rect);
	}
}

void Slider::Blur(){
	if(im->focus){
		im->focus = false;
		IControl::Paint(im->rect);
	}
}

int32_t Slider::GetValue(){
	return im->value;
}

uint32_t Slider::GetFlags(){
	return 0;
}

void Slider::Enable(){
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(im->rect);
	}
}

void Slider::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(im->rect);
	}
}

bool Slider::IsEnabled(){
	return im->enabled;
}

void Slider::SetPosition(const gds::Rect &r){
	im->rect = r;
	im->bkSurf.reset();
}

}
}
