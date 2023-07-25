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

struct ButtonImpl{
	bool down = false;
	bool focus = false;
	bool enabled = true;

	gds::Rect rect;
	std::string label;
	
	std::unique_ptr<gds::Surface> bkSurf;
	gds::TextMeasurements labelMeasures;
};

PIMPL_IMPL(ButtonImpl);
	
Button::Button(const gds::Rect &r, const std::string &l) : impl(new ButtonImpl){
	impl->rect = r;
	impl->label = l;
}

EventResponse Button::HandleEvent(const wm_Event &e){
	auto oldDown = impl->down;
	if(e.type == wm_EventType::PointerButtonDown && e.Pointer.button == 1){
		impl->down = true;
	}
	if(e.type == wm_EventType::PointerButtonUp && e.Pointer.button == 1){
		impl->down = false;
		RaiseActionEvent();
	}
	if(e.type == wm_EventType::PointerLeave){
		if(impl->down) impl->down = false;
	}
	if(e.type == wm_EventType::PointerEnter){
		auto pinfo = WM_GetPointerInfo();
		if(pinfo.flags & MouseFlags::Button1) impl->down = true;
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
	if(impl->down != oldDown) IControl::Paint(impl->rect);
	return {true};
}

void Button::Paint(gds::Surface &s){
	int32_t inW = impl->rect.w - 1;
	int32_t inH = impl->rect.h - 1;
	
	if(!impl->bkSurf){        
		impl->bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, impl->rect.w, impl->rect.h, 100, gds_ColourType::True));
		impl->labelMeasures = impl->bkSurf->MeasureText(impl->label, fonts::GetButtonFont(), fonts::GetButtonTextSize());
		
		int32_t labelX = std::max<int32_t>(((impl->rect.w - impl->labelMeasures.w) / 2), 0);
		int32_t labelY = std::max<int32_t>(((impl->rect.h + impl->labelMeasures.h) / 2), 0);
		
		impl->bkSurf->BeginQueue();
		
		auto bkgCol = colours::GetBackground().Fix(*impl->bkSurf);
		auto buttonColour = colours::GetButtonColour().Fix(*impl->bkSurf);
		auto border = colours::GetBorder().Fix(*impl->bkSurf);
		
		impl->bkSurf->Box(impl->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		impl->bkSurf->Box({1, 1, (uint32_t)inW - 2, (uint32_t)inH - 2}, buttonColour, buttonColour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		drawing::Border(*impl->bkSurf, {0, 0, (uint32_t)inW, (uint32_t)inH}, border);
		
		auto textColour = colours::GetButtonText().Fix(*impl->bkSurf);
		impl->bkSurf->Text({labelX, labelY}, impl->label, fonts::GetButtonFont(), fonts::GetButtonTextSize(), textColour);
		impl->bkSurf->CommitQueue();
		impl->bkSurf->Compress();
	}
	s.Blit(*impl->bkSurf, impl->rect.AtZero(), impl->rect);
	
	auto topLeft = colours::GetButtonHiLight().Fix(s);
	auto bottomRight = colours::GetButtonLowLight().Fix(s);
	if(impl->down) std::swap(topLeft, bottomRight);
	
	drawing::BevelBox(s, {impl->rect.x + 1, impl->rect.y + 1, (uint32_t)inW - 2, (uint32_t)inH - 2}, topLeft, bottomRight);

	if(impl->focus){
		auto focusCol = colours::GetButtonFocus().Fix(s);
			
		int32_t labelX = std::max<int32_t>(((impl->rect.w - impl->labelMeasures.w) / 2), 0);
		int32_t labelY = std::max<int32_t>(((impl->rect.h + impl->labelMeasures.h) / 2), 0);
			
		int32_t focusX = std::max<uint32_t>(labelX - 3, 0) + impl->rect.x;
		int32_t focusY = std::max<uint32_t>(labelY - impl->labelMeasures.h - 3, 0) + impl->rect.y;
		uint32_t focusW = impl->labelMeasures.w + 6;
		uint32_t focusH = impl->labelMeasures.h + 6;
		
		s.Box({focusX, focusY, focusW, focusH}, focusCol, focusCol);
	}
	
	if(!impl->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(impl->rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect Button::GetPaintRect(){
	return impl->rect;
}

gds::Rect Button::GetInteractRect(){
	return impl->rect;
}

uint32_t Button::GetSubscribed(){
	return (wm_EventType::PointerButtonDown | wm_EventType::PointerButtonUp | wm_EventType::PointerLeave | wm_EventType::PointerEnter | wm_EventType::Keyboard);
}

void Button::Focus(){
	impl->focus = true;
	IControl::Paint(impl->rect);
}

void Button::Blur(){
	impl->focus = false;
	IControl::Paint(impl->rect);
}

uint32_t Button::GetFlags(){
	return 0;
}

void Button::Enable(){
	if(!impl->enabled){
		impl->enabled = true;
		IControl::Paint(impl->rect);
	}
}

void Button::Disable(){
	if(impl->enabled){
		impl->enabled = false;
		IControl::Paint(impl->rect);
	}
}

bool Button::IsEnabled(){
	return impl->enabled;
}

void Button::SetPosition(const gds::Rect &r){
	impl->rect = r;
	impl->bkSurf.reset();
}

}
}
