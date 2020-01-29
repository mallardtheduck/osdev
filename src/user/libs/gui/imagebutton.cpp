#include <btos.h>
#include <gui/imagebutton.hpp>
#include <gui/drawing.hpp>
#include <gui/defaults.hpp>
#include <dev/mouse.h>
#include <dev/keyboard.h>
#include <wm/libwm.h>

namespace btos_api{
namespace gui{
	
ImageButton::ImageButton(const gds::Rect &r, std::shared_ptr<gds::Surface> i) :  rect(r), img(i){
}

EventResponse ImageButton::HandleEvent(const wm_Event &e){
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
	if(down != oldDown) IControl::Paint(rect);
	return {true};
}

void ImageButton::Paint(gds::Surface &s){
	int32_t inW = rect.w - 1;
	int32_t inH = rect.h - 1;
	
	if(!bkSurf){
		bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		info = img->Info();
		
		int32_t imgX = std::max<int32_t>(((rect.w - info.w) / 2), 0);
		int32_t imgY = std::max<int32_t>(((rect.h - info.h) / 2), 0);
		
		bkSurf->BeginQueue();
		
		auto bkgCol = colours::GetBackground().Fix(*bkSurf);
		auto buttonColour = colours::GetImageButtonColour().Fix(*bkSurf);
		auto border = colours::GetBorder().Fix(*bkSurf);
		
		bkSurf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		bkSurf->Box({1, 1, (uint32_t)inW - 2, (uint32_t)inH - 2}, buttonColour, buttonColour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		drawing::Border(*bkSurf, {0, 0, (uint32_t)inW, (uint32_t)inH}, border);
		
		bkSurf->Blit(*img, {0, 0, info.w, info.h}, {imgX, imgY, info.w, info.h});
		bkSurf->CommitQueue();
		bkSurf->Compress();
	}
	s.Blit(*bkSurf, {0, 0, rect.w, rect.h}, rect);
	
	auto topLeft = colours::GetImageButtonHiLight().Fix(s);
	auto bottomRight = colours::GetImageButtonLowLight().Fix(s);
	if(down) std::swap(topLeft, bottomRight);
	
	drawing::BevelBox(s, {rect.x + 1, rect.y + 1, (uint32_t)inW - 2, (uint32_t)inH - 2}, topLeft, bottomRight);
	
	if(focus){
		auto focusCol = colours::GetImageButtonFocus().Fix(s);
			
		int32_t labelX = std::max<int32_t>(((rect.w - info.w) / 2), 0);
		int32_t labelY = std::max<int32_t>(((rect.h + info.h) / 2), 0);
			
		int32_t focusX = rect.x + std::max<uint32_t>(labelX - 3, 0);
		int32_t focusY = rect.y + std::max<uint32_t>(labelY - info.h - 3, 0);
		uint32_t focusW = info.w + 6;
		uint32_t focusH = info.h + 6;
		
		s.Box({focusX, focusY, focusW, focusH}, focusCol, focusCol);
	}
	
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect ImageButton::GetPaintRect(){
	return rect;
}

gds::Rect ImageButton::GetInteractRect(){
	return rect;
}

uint32_t ImageButton::GetSubscribed(){
	return (wm_EventType::PointerButtonDown | wm_EventType::PointerButtonUp | wm_EventType::PointerLeave | wm_EventType::PointerEnter | wm_EventType::Keyboard);
}

void ImageButton::Focus(){
	focus = true;
	IControl::Paint(rect);
}

void ImageButton::Blur(){
	focus = false;
	IControl::Paint(rect);
}

uint32_t ImageButton::GetFlags(){
	return 0;
}

void ImageButton::Enable(){
	if(!enabled){
		enabled = true;
		IControl::Paint(rect);
	}
}

void ImageButton::Disable(){
	if(enabled){
		enabled = false;
		IControl::Paint(rect);
	}
}

bool ImageButton::IsEnabled(){
	return enabled;
}

void ImageButton::SetPosition(const gds::Rect &r){
	rect = r;
	bkSurf.reset();
}

}
}
