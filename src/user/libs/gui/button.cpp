#include <btos.h>
#include <gui/button.hpp>
#include <gui/defaults.hpp>
#include <dev/terminal.hpp>
#include <dev/mouse.h>

namespace btos_api{
namespace gui{
	
Button::Button(const gds::Rect &r, const std::string &l, std::function<void()> oC) :  rect(r), label(l), onClick(oC){
}

EventResponse Button::HandleEvent(const wm_Event &e){
	if(e.type == wm_EventType::PointerButtonDown && e.Pointer.button == 1){
		state = ButtonState::Down;
	}
	if(e.type == wm_EventType::PointerButtonUp && e.Pointer.button == 1){
		state = ButtonState::Focus;
		onClick();
	}
	if(e.type == wm_EventType::PointerLeave){
		if(state == ButtonState::Down) state = ButtonState::Focus;
	}
	if(e.type == wm_EventType::PointerEnter){
		auto pinfo = Terminal().GetPointerInfo();
		if(pinfo.flags & MouseFlags::Button1) state = ButtonState::Down;
	}
	if(state != paintState) return {true, rect};
	else return {true};
}

void Button::Paint(gds::Surface &s){
	if(!surf || state != paintState){
		if(!surf){
			surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
			labelMeasures = surf->MeasureText(label, fonts::GetButtonFont(), fonts::GetButtonTextSize());
		}else surf->Clear();
		
		surf->BeginQueue();
		
		auto buttonColour = colours::GetButtonColour().Fix(*surf);
		auto border = colours::GetBorder().Fix(*surf);
		
		int32_t inW = rect.w - 1;
		int32_t inH = rect.h - 1;
		
		int32_t labelX = std::max<int32_t>(((rect.w - labelMeasures.w) / 2), 0);
		int32_t labelY = std::max<int32_t>(((rect.h + labelMeasures.h) / 2), 0);
		
		surf->Box({0, 0, rect.w, rect.h}, buttonColour, buttonColour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		surf->Line({1, 0}, {inW - 1, 0}, border);
		surf->Line({0, 1}, {0, inH - 1}, border);
		surf->Line({1, inH}, {inW - 1, inH}, border);
		surf->Line({inW, 1}, {inW, inH - 1}, border);
		
		auto textColour = colours::GetButtonText().Fix(*surf);
		surf->Text({labelX, labelY}, label, fonts::GetButtonFont(), fonts::GetButtonTextSize(), textColour);
		
		auto topLeft = colours::GetButtonHiLight().Fix(*surf);
		auto bottomRight = colours::GetButtonLowLight().Fix(*surf);
		if(state == ButtonState::Down) std::swap(topLeft, bottomRight);
		
		surf->Line({1, 1}, {inW - 1, 1}, topLeft);
		surf->Line({1, 1}, {1, inH - 1}, topLeft);
		surf->Line({1, inH - 1}, {inW - 1, inH - 1}, bottomRight);
		surf->Line({inW - 1, 1}, {inW - 1, inH - 1}, bottomRight);
		
		surf->CommitQueue();
		
		paintState = state;
	}
	
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
}

gds::Rect Button::GetPaintRect(){
	return rect;
}

gds::Rect Button::GetInteractRect(){
	return rect;
}

uint32_t Button::GetSubscribed(){
	return (wm_EventType::PointerButtonDown | wm_EventType::PointerButtonUp | wm_EventType::PointerLeave | wm_EventType::PointerEnter);
}

void Button::Focus(){
	if(state != ButtonState::Down) state = ButtonState::Focus;
}

void Button::Blur(){
	if(state != ButtonState::Down) state = ButtonState::Rest;
}

}
}
