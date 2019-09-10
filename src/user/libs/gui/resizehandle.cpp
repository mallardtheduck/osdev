#include <btos.h>
#include <gui/resizehandle.hpp>
#include <gui/drawing.hpp>
#include <gui/defaults.hpp>
#include <dev/mouse.h>
#include <dev/keyboard.h>
#include <wm/libwm.h>

namespace btos_api{
namespace gui{
	
ResizeHandle::ResizeHandle(const gds::Rect &r) :  rect(r){
}

EventResponse ResizeHandle::HandleEvent(const wm_Event &e){
	auto oldDown = down;
	if(e.type == wm_EventType::PointerButtonDown && e.Pointer.button == 1){
		down = true;
		RaiseActionEvent();
	}
	if(e.type == wm_EventType::PointerButtonUp && e.Pointer.button == 1){
		down = false;
	}
	if(e.type == wm_EventType::PointerLeave){
		if(down) down = false;
	}
	if(e.type == wm_EventType::PointerEnter){
		auto pinfo = WM_GetPointerInfo();
		if(pinfo.flags & MouseFlags::Button1) down = true;
	}
	if(down != oldDown) IControl::Paint(rect);
	return {true};
}

void ResizeHandle::Paint(gds::Surface &s){
	if(!surf || down != paintDown){
		int32_t inW = rect.w - 1;
		int32_t inH = rect.h - 1;
		
		if(!surf || !bkSurf){
			surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));               
			bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
			
			bkSurf->BeginQueue();
			
			auto handleCol = colours::GetResizeHandleBackground().Fix(*bkSurf);
			auto border = colours::GetBorder().Fix(*bkSurf);
			
			bkSurf->Box({1, 1, (uint32_t)inW - 1, (uint32_t)inH - 1}, handleCol, handleCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
			bkSurf->Box({0, 0, rect.w, rect.h}, border, border);
			
			bkSurf->CommitQueue();
			bkSurf->Compress();
			
		}else surf->Clear();
		
		surf->BeginQueue();
		
		surf->Blit(*bkSurf, {0, 0, rect.w, rect.h}, {0, 0, rect.w, rect.h});
		
		if(down){
			auto downCol = colours::GetResizeHandleDown().Fix(*surf);
			surf->Box({1, 1, (uint32_t)inW - 1, (uint32_t)inH - 1}, downCol, downCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		}
		
		auto fgCol = colours::GetResizeHandleForeground().Fix(*surf);
		surf->Line({3, inH - 3}, {inW - 3, 3}, fgCol);
		surf->Line({9, inH - 3}, {inW - 3, 9}, fgCol);
		surf->Line({15, inH - 3}, {inW - 3, 15}, fgCol);
		
		surf->CommitQueue();
		surf->Compress();
		
		paintDown = down;
	}
	
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect ResizeHandle::GetPaintRect(){
	return rect;
}

gds::Rect ResizeHandle::GetInteractRect(){
	return rect;
}

uint32_t ResizeHandle::GetSubscribed(){
	return (wm_EventType::PointerButtonDown | wm_EventType::PointerButtonUp | wm_EventType::PointerLeave | wm_EventType::PointerEnter);
}

void ResizeHandle::Focus(){
}

void ResizeHandle::Blur(){
}

uint32_t ResizeHandle::GetFlags(){
	return ControlFlags::NoFocus;
}

void ResizeHandle::Enable(){
	if(!enabled){
		enabled = true;
		IControl::Paint(rect);
	}
}

void ResizeHandle::Disable(){
	if(enabled){
		enabled = false;
		IControl::Paint(rect);
	}
}

bool ResizeHandle::IsEnabled(){
	return enabled;
}

size_t ResizeHandle::GetZOrder(){
	return ZOrder::Foreground;
}

void ResizeHandle::SetPosition(const gds::Rect &r){
	rect = r;
	surf.reset();
	bkSurf.reset();
	down = false;
}

}
}
