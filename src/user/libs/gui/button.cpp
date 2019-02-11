#include <btos.h>
#include <gui/button.hpp>
#include <gui/defaults.hpp>

namespace btos_api{
namespace gui{
	
Button::Button(const gds::Rect &r, const std::string &l, std::function<void()> oC) :  rect(r), label(l), onClick(oC){
}

bool Button::HandleEvent(const wm_Event &e){
	if(e.type == wm_EventType::PointerButtonDown){
		state = ButtonState::Down;
	}
	if(e.type == wm_EventType::PointerButtonUp){
		state = ButtonState::Focus;
		onClick();
	}
	return true;
}

void Button::Paint(gds::Surface &s){
	if(!surf || state != paintState){
		if(!surf) surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		
		surf->BeginQueue();
		
		auto buttonColour = colours::GetButtonColour().Fix(*surf);
		auto border = colours::GetBorder().Fix(*surf);
		
		surf->Box({0, 0, rect.w, rect.h}, buttonColour, buttonColour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		surf->Line({1, 0}, {(int32_t)rect.w - 1, 0}, border);
		surf->Line({0, 1}, {0, (int32_t)rect.h - 1}, border);
		surf->Line({1, (int32_t)rect.h}, {(int32_t)rect.w - 1, (int32_t)rect.h}, border);
		surf->Line({(int32_t)rect.w, 1}, {(int32_t)rect.w, (int32_t)rect.h - 1}, border);
		
		auto topLeft = colours::GetButtonHiLight().Fix(*surf);
		auto bottomRight = colours::GetButtonLowLight().Fix(*surf);
		if(state == ButtonState::Down) std::swap(topLeft, bottomRight);
		
		surf->Line({1, 1}, {(int32_t)rect.w - 1, 1}, topLeft);
		surf->Line({1, 1}, {1, (int32_t)rect.h - 1}, topLeft);
		surf->Line({1, (int32_t)rect.h - 1}, {(int32_t)rect.w - 1, (int32_t)rect.h - 1}, bottomRight);
		surf->Line({(int32_t)rect.w - 1, 1}, {(int32_t)rect.w - 1, (int32_t)rect.h - 1}, bottomRight);
		
		surf->CommitQueue();
		
		paintState = state;
	}
	
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
}

gds::Rect Button::GetRect(){
	return rect;
}

uint32_t Button::GetSubscribed(){
	return (wm_EventType::PointerButtonDown | wm_EventType::PointerButtonUp);
}

void Button::Focus(){
	if(state != ButtonState::Down) state = ButtonState::Focus;
}

void Button::Blur(){
	if(state != ButtonState::Down) state = ButtonState::Rest;
}

}
}