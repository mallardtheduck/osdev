#include <btos.h>
#include <gui/button.hpp>
#include <gui/drawing.hpp>
#include <gui/defaults.hpp>
#include <dev/mouse.h>
#include <dev/keyboard.h>
#include <wm/libwm.h>

#include <util/tinyformat.hpp>

namespace btos_api{
namespace gui{
	
Button::Button(const gds::Rect &r, const std::string &l) :  rect(r), label(l){
}

EventResponse Button::HandleEvent(const wm_Event &e){
	auto oldDown = down;
	if(e.type == wm_EventType::PointerButtonDown && e.Pointer.button == 1){
		down = true;
	}
	if(e.type == wm_EventType::PointerButtonUp && e.Pointer.button == 1){
		down = false;
		RaiseActionEvent();
	}
	if(e.type == wm_EventType::PointerLeave){
		if(down) down = false;
	}
	if(e.type == wm_EventType::PointerEnter){
		auto pinfo = WM_GetPointerInfo();
		if(pinfo.flags & MouseFlags::Button1) down = true;
	}
	if(e.type == wm_EventType::Keyboard){
		uint16_t code = KB_code(e.Key.code);
		if(!(code & KeyFlags::NonASCII)){
			char c = KB_char(e.Key.code);
			if(c == ' ' || c == '\n'){
				RaiseActionEvent();
				return {true};
			}
		}
		return {false};
	}
	/*if(down != oldDown)*/ IControl::Paint(rect);
	(void)oldDown;
	return {true};
}

void Button::Paint(gds::Surface &s){
	int32_t inW = rect.w - 1;
	int32_t inH = rect.h - 1;
	
	if(!bkSurf){        
		bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		labelMeasures = bkSurf->MeasureText(label, fonts::GetButtonFont(), fonts::GetButtonTextSize());
		
		int32_t labelX = std::max<int32_t>(((rect.w - labelMeasures.w) / 2), 0);
		int32_t labelY = std::max<int32_t>(((rect.h + labelMeasures.h) / 2), 0);
		
		bkSurf->BeginQueue();
		
		auto bkgCol = colours::GetBackground().Fix(*bkSurf);
		auto buttonColour = colours::GetButtonColour().Fix(*bkSurf);
		auto border = colours::GetBorder().Fix(*bkSurf);
		
		bkSurf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		bkSurf->Box({1, 1, (uint32_t)inW - 2, (uint32_t)inH - 2}, buttonColour, buttonColour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		drawing::Border(*bkSurf, {0, 0, (uint32_t)inW, (uint32_t)inH}, border);
		
		auto textColour = colours::GetButtonText().Fix(*bkSurf);
		bkSurf->Text({labelX, labelY}, label, fonts::GetButtonFont(), fonts::GetButtonTextSize(), textColour);
		bkSurf->CommitQueue();
		bkSurf->Compress();
	}
	s.Blit(*bkSurf, {0, 0, rect.w, rect.h}, rect);
	
	auto topLeft = colours::GetButtonHiLight().Fix(s);
	auto bottomRight = colours::GetButtonLowLight().Fix(s);
	if(down) std::swap(topLeft, bottomRight);
	
	drawing::BevelBox(s, {rect.x + 1, rect.y + 1, (uint32_t)inW - 2, (uint32_t)inH - 2}, topLeft, bottomRight);
	
	if(focus){
		auto focusCol = colours::GetButtonFocus().Fix(s);
			
		int32_t labelX = std::max<int32_t>(((rect.w - labelMeasures.w) / 2), 0);
		int32_t labelY = std::max<int32_t>(((rect.h + labelMeasures.h) / 2), 0);
			
		int32_t focusX = std::max<uint32_t>(labelX - 3, 0) + rect.x;
		int32_t focusY = std::max<uint32_t>(labelY - labelMeasures.h - 3, 0) + rect.y;
		uint32_t focusW = labelMeasures.w + 6;
		uint32_t focusH = labelMeasures.h + 6;
		
		s.Box({focusX, focusY, focusW, focusH}, focusCol, focusCol);
	}
	
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect Button::GetPaintRect(){
	return rect;
}

gds::Rect Button::GetInteractRect(){
	return rect;
}

uint32_t Button::GetSubscribed(){
	return (wm_EventType::PointerButtonDown | wm_EventType::PointerButtonUp | wm_EventType::PointerLeave | wm_EventType::PointerEnter | wm_EventType::Keyboard);
}

void Button::Focus(){
	focus = true;
	IControl::Paint(rect);
}

void Button::Blur(){
	focus = false;
	IControl::Paint(rect);
}

uint32_t Button::GetFlags(){
	return 0;
}

void Button::Enable(){
	if(!enabled){
		enabled = true;
		IControl::Paint(rect);
	}
}

void Button::Disable(){
	if(enabled){
		enabled = false;
		IControl::Paint(rect);
	}
}

bool Button::IsEnabled(){
	return enabled;
}

void Button::SetPosition(const gds::Rect &r){
	rect = r;
	bkSurf.reset();
}

}
}
