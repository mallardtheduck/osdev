#include <gui/slider.hpp>
#include <gui/defaults.hpp>
#include <dev/terminal.hpp>
#include <dev/mouse.h>
#include <dev/keyboard.h>

#include <iostream>

namespace btos_api{
namespace gui{	
	
Slider::Slider(const gds::Rect &r, int32_t mi, int32_t ma, int32_t def) : rect(r), min(mi), max(ma), value(def) {}

EventResponse Slider::HandleEvent(const wm_Event &e){
	int32_t cvalue = value;
	if(e.type == wm_EventType::PointerMove || e.type == wm_EventType::PointerButtonUp){
		if(e.type == wm_EventType::PointerMove){
			auto pinfo = Terminal().GetPointerInfo();
			if(!(pinfo.flags & MouseFlags::Button1)) return {true};
		}
		
		int32_t xpos = e.Pointer.x  - rect.x;
		int32_t inW = rect.w - 1;
		int32_t lineLeft = 3;
		int32_t lineRight = inW - 3;
		
		if(xpos < lineLeft) value = min;
		else if(xpos > lineRight) value = max;
		else{
			xpos -= min;
			double scale = (((double)(lineRight - lineLeft) / (double)(max - min)));
			value = (xpos / scale) + min;
			if(value > max) value = max;
			if(value < min) value = min;
		}
	}else if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && value > min){
			--value;
			update = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && value < max){
			++value;
			update = true;
		}
	}
	if(cvalue != value){
		update = true;
		return {true, rect};
	}else return {true};
}

void Slider::Paint(gds::Surface &s){
	if(!surf || update){
		if(!surf) surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		else surf->Clear();
		
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
			bkSurf->Line({lineLeft + 1, lineTop}, {lineRight - 1, lineTop}, bkBorder);
			bkSurf->Line({lineLeft, lineTop + 1}, {lineLeft, lineBottom - 1}, bkBorder);
			bkSurf->Line({lineLeft + 1, lineBottom}, {lineRight - 1, lineBottom}, bkBorder);
			bkSurf->Line({lineRight, lineTop + 1}, {lineRight, lineBottom - 1}, bkBorder);
			
			auto topLeft = colours::GetSliderLineLowLight().Fix(*bkSurf);
			auto bottomRight = colours::GetSliderLineHiLight().Fix(*bkSurf);
			
			bkSurf->Line({lineLeft + 1, lineTop + 1}, {lineRight - 1, lineTop + 1}, topLeft);
			bkSurf->Line({lineLeft + 1, lineTop + 1}, {lineLeft + 1, lineBottom - 1}, topLeft);
			bkSurf->Line({lineLeft + 1, lineBottom - 1}, {lineRight - 1, lineBottom - 1}, bottomRight);
			bkSurf->Line({lineRight - 1, lineTop + 1}, {lineRight - 1, lineBottom - 1}, bottomRight);
			
			int tickTop = lineBottom + 2;
			
			auto tick = colours::GetSliderTick().Fix(*bkSurf);
			bkSurf->Line({lineLeft, tickTop}, {lineLeft, (int32_t)rect.h}, tick);
			bkSurf->Line({lineRight, tickTop}, {lineRight, (int32_t)rect.h}, tick);
			auto mid = ((lineRight - lineLeft) / 2) + lineLeft;
			bkSurf->Line({mid, tickTop}, {mid, (int32_t)rect.h}, tick);
			
			bkSurf->CommitQueue();
		}
		
		auto border = colours::GetBorder().Fix(*surf);
		auto slider = colours::GetSliderColour().Fix(*surf);
		
		surf->BeginQueue();
		
		surf->Blit(*bkSurf, {0, 0, rect.w, rect.h}, {0, 0, rect.w, rect.h});
		
		int32_t pos = lineLeft + ((double)(value - min) * (((double)(lineRight - lineLeft) / (double)(max - min))));
		std::vector<gds::Point> points = {{pos - 4, 1}, {pos - 4, 7}, {pos, 13}, {pos + 4, 7}, {pos + 4, 1}};
		
		surf->Polygon(points, false, border, slider, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		surf->Line({pos - 3, 0}, {pos + 3, 0}, border);
		
		if(focus){
			auto focusCol = colours::GetSliderFocus().Fix(*surf);
			surf->Box({0, 0, rect.w, rect.h}, focusCol, focusCol);
		}

		surf->CommitQueue();
		
		update = false;
	}
	
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
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
	if(!focus) update = true;
	focus = true;
}

void Slider::Blur(){
	if(focus) update = true;
	focus = false;
}

int32_t Slider::GetValue(){
	return value;
}

void Slider::OnChange(const std::function<void(int32_t)> &oC){
	onChange = oC;
}

}
}