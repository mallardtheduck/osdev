#include <gui/slider.hpp>
#include <gui/drawing.hpp>
#include <gui/defaults.hpp>
#include <dev/mouse.h>
#include <dev/keyboard.h>
#include <wm/libwm.h>

#include <cmath>

namespace btos_api{
namespace gui{  
	
Slider::Slider(const gds::Rect &r, int32_t mi, int32_t ma, int32_t def, int32_t sT) : rect(r), min(mi), max(ma), value(def), snapTo(sT) {}

EventResponse Slider::HandleEvent(const wm_Event &e){
	bool handled = false;
	int32_t cvalue = value;
	if(e.type == wm_EventType::PointerMove || e.type == wm_EventType::PointerButtonUp){
		handled = true;
		if(e.type == wm_EventType::PointerMove){
			auto pinfo = WM_GetPointerInfo();
			if(!(pinfo.flags & MouseFlags::Button1)) return {true};
		}
		
		int32_t xpos = e.Pointer.x - rect.x;
		int32_t inW = rect.w - 1;
		int32_t lineLeft = 3;
		int32_t lineRight = inW - 3;
		
		if(xpos < lineLeft) value = min;
		else if(xpos > lineRight) value = max;
		else{
			xpos -= lineLeft;
			if(xpos < 0) xpos = 0;
			double scale = (((double)(lineRight - lineLeft) / (double)(max - min)));
			value = (xpos / scale) + min;
			if(value > max) value = max;
			if(value < min) value = min;
		}
	}else if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && value > min){
			value -= snapTo;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && value < max){
			value += snapTo;
			handled = true;
		}
	}
	if(cvalue != value){
		if((value - min) % snapTo){
			value -= min;
			value = round((double)value / (double)snapTo) * snapTo;
			value += min;
		}
		RaiseChangeEvent();
		IControl::Paint(rect);
	}
	return {handled};
}

void Slider::Paint(gds::Surface &s){
	int32_t inW = rect.w - 1;
	auto lineTop = 5;
	auto lineBottom = 9;
	auto lineLeft = 4;
	auto lineRight = inW - 4;
	
	if(!bkSurf){
		bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
	
		auto bkgCol = colours::GetBackground().Fix(*bkSurf);
		auto bkBorder = colours::GetBorder().Fix(*bkSurf);
		
		bkSurf->BeginQueue();
		bkSurf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		drawing::Border(*bkSurf, {lineLeft, lineTop, (uint32_t)(lineRight - lineLeft), (uint32_t)(lineBottom - lineTop)}, bkBorder);
		
		auto topLeft = colours::GetSliderLineLowLight().Fix(*bkSurf);
		auto bottomRight = colours::GetSliderLineHiLight().Fix(*bkSurf);
		drawing::BevelBox(*bkSurf, {lineLeft + 1, lineTop + 1, (uint32_t)(lineRight - lineLeft - 2), (uint32_t)(lineBottom - lineTop - 2)}, topLeft, bottomRight);
		
		int tickTop = lineBottom + 2;
		
		auto tick = colours::GetSliderTick().Fix(*bkSurf);
		bkSurf->Line({lineLeft, tickTop}, {lineLeft, (int32_t)rect.h}, tick);
		bkSurf->Line({lineRight, tickTop}, {lineRight, (int32_t)rect.h}, tick);
		auto mid = ((lineRight - lineLeft) / 2) + lineLeft;
		bkSurf->Line({mid, tickTop}, {mid, (int32_t)rect.h}, tick);
		
		bkSurf->CommitQueue();
		bkSurf->Compress();
	}
	
	auto border = colours::GetBorder().Fix(s);
	auto slider = colours::GetSliderColour().Fix(s);
	
	s.Blit(*bkSurf, {0, 0, rect.w, rect.h}, rect);
	
	if(focus){
		auto focusCol = colours::GetSliderFocus().Fix(s);
		s.Box(rect, focusCol, focusCol);
	}
	
	int32_t pos = lineLeft + ((double)(value - min) * (((double)(lineRight - lineLeft) / (double)(max - min))));
	std::vector<gds::Point> points = {{pos - 4, 1}, {pos - 4, 7}, {pos, 13}, {pos + 4, 7}, {pos + 4, 1}};
	
	for(auto &p : points){
		p.x += rect.x;
		p.y += rect.y;
	}
	
	s.Polygon(points, false, border, slider, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	s.Line({rect.x + pos - 3, rect.y}, {rect.x + pos + 3, rect.y}, border);
	
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect Slider::GetPaintRect(){
	return rect;
}
gds::Rect Slider::GetInteractRect(){
	return rect;
}

uint32_t Slider::GetSubscribed(){
	return wm_EventType::PointerMove | wm_EventType::PointerButtonUp | wm_EventType::Keyboard;
}

void Slider::Focus(){
	if(!focus){
		focus = true;
		IControl::Paint(rect);
	}
}

void Slider::Blur(){
	if(focus){
		focus = false;
		IControl::Paint(rect);
	}
}

int32_t Slider::GetValue(){
	return value;
}

uint32_t Slider::GetFlags(){
	return 0;
}

void Slider::Enable(){
	if(!enabled){
		enabled = true;
		IControl::Paint(rect);
	}
}

void Slider::Disable(){
	if(enabled){
		enabled = false;
		IControl::Paint(rect);
	}
}

bool Slider::IsEnabled(){
	return enabled;
}

void Slider::SetPosition(const gds::Rect &r){
	rect = r;
	bkSurf.reset();
}

}
}
