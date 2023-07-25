#include <btos.h>
#include <gui/imagebutton.hpp>
#include <gui/drawing.hpp>
#include <gui/defaults.hpp>
#include <dev/mouse.h>
#include <dev/keyboard.h>
#include <wm/libwm.h>

namespace btos_api{
namespace gui{
	
struct ImageButtonImpl{
	bool down = false;
	bool focus = false;
	bool enabled = true;

	gds::Rect rect;
	
	std::unique_ptr<gds::Surface> bkSurf;
	std::shared_ptr<gds::Surface> img;
	gds_SurfaceInfo info;
};
PIMPL_IMPL(ImageButtonImpl);

ImageButton::ImageButton(const gds::Rect &r, std::shared_ptr<gds::Surface> i) : im(new ImageButtonImpl()){
	im->rect = r; im->img = i;
}

EventResponse ImageButton::HandleEvent(const wm_Event &e){
	auto oldDown = im->down;
	if(e.type == wm_EventType::PointerButtonDown && e.Pointer.button == 1){
		im->down = true;
	}
	if(e.type == wm_EventType::PointerButtonUp && e.Pointer.button == 1){
		im->down = false;
		RaiseActionEvent();
	}
	if(e.type == wm_EventType::PointerLeave){
		if(im->down) im->down = false;
	}
	if(e.type == wm_EventType::PointerEnter){
		auto pinfo = WM_GetPointerInfo();
		if(pinfo.flags & MouseFlags::Button1) im->down = true;
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
	if(im->down != oldDown) IControl::Paint(im->rect);
	return {true};
}

void ImageButton::Paint(gds::Surface &s){
	int32_t inW = im->rect.w - 1;
	int32_t inH = im->rect.h - 1;
	
	if(!im->bkSurf){
		im->bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
		im->info = im->img->Info();
		
		int32_t imgX = std::max<int32_t>(((im->rect.w - im->info.w) / 2), 0);
		int32_t imgY = std::max<int32_t>(((im->rect.h - im->info.h) / 2), 0);
		
		im->bkSurf->BeginQueue();
		
		auto bkgCol = colours::GetBackground().Fix(*im->bkSurf);
		auto buttonColour = colours::GetImageButtonColour().Fix(*im->bkSurf);
		auto border = colours::GetBorder().Fix(*im->bkSurf);
		
		im->bkSurf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		im->bkSurf->Box({1, 1, (uint32_t)inW - 2, (uint32_t)inH - 2}, buttonColour, buttonColour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		drawing::Border(*im->bkSurf, {0, 0, (uint32_t)inW, (uint32_t)inH}, border);
		
		im->bkSurf->Blit(*im->img, {0, 0, im->info.w, im->info.h}, {imgX, imgY, im->info.w, im->info.h});
		im->bkSurf->CommitQueue();
		im->bkSurf->Compress();
	}
	s.Blit(*im->bkSurf, im->rect.AtZero(), im->rect);
	
	auto topLeft = colours::GetImageButtonHiLight().Fix(s);
	auto bottomRight = colours::GetImageButtonLowLight().Fix(s);
	if(im->down) std::swap(topLeft, bottomRight);
	
	drawing::BevelBox(s, {im->rect.x + 1, im->rect.y + 1, (uint32_t)inW - 2, (uint32_t)inH - 2}, topLeft, bottomRight);
	
	if(im->focus){
		auto focusCol = colours::GetImageButtonFocus().Fix(s);
			
		int32_t labelX = std::max<int32_t>(((im->rect.w - im->info.w) / 2), 0);
		int32_t labelY = std::max<int32_t>(((im->rect.h + im->info.h) / 2), 0);
			
		int32_t focusX = im->rect.x + std::max<uint32_t>(labelX - 3, 0);
		int32_t focusY = im->rect.y + std::max<uint32_t>(labelY - im->info.h - 3, 0);
		uint32_t focusW = im->info.w + 6;
		uint32_t focusH = im->info.h + 6;
		
		s.Box({focusX, focusY, focusW, focusH}, focusCol, focusCol);
	}
	
	if(!im->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(im->rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect ImageButton::GetPaintRect(){
	return im->rect;
}

gds::Rect ImageButton::GetInteractRect(){
	return im->rect;
}

uint32_t ImageButton::GetSubscribed(){
	return (wm_EventType::PointerButtonDown | wm_EventType::PointerButtonUp | wm_EventType::PointerLeave | wm_EventType::PointerEnter | wm_EventType::Keyboard);
}

void ImageButton::Focus(){
	im->focus = true;
	IControl::Paint(im->rect);
}

void ImageButton::Blur(){
	im->focus = false;
	IControl::Paint(im->rect);
}

uint32_t ImageButton::GetFlags(){
	return 0;
}

void ImageButton::Enable(){
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(im->rect);
	}
}

void ImageButton::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(im->rect);
	}
}

bool ImageButton::IsEnabled(){
	return im->enabled;
}

void ImageButton::SetPosition(const gds::Rect &r){
	im->rect = r;
	im->bkSurf.reset();
}

}
}
