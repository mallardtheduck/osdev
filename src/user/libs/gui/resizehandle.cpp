#include <btos.h>
#include <gui/resizehandle.hpp>
#include <gui/drawing.hpp>
#include <gui/defaults.hpp>
#include <dev/mouse.h>
#include <dev/keyboard.h>
#include <wm/libwm.h>

namespace btos_api{
namespace gui{

struct ResizeHandleImpl{
	bool down = false;
	bool enabled = true;
	bool paintDown;

	gds::Rect rect;
	
	std::unique_ptr<gds::Surface> surf;
	std::unique_ptr<gds::Surface> bkSurf;
	gds_SurfaceInfo info;
};
PIMPL_IMPL(ResizeHandleImpl);

ResizeHandle::ResizeHandle(const gds::Rect &r) : im(new ResizeHandleImpl()){
	im->rect = r;
}

EventResponse ResizeHandle::HandleEvent(const wm_Event &e){
	auto oldDown = im->down;
	if(e.type == wm_EventType::PointerButtonDown && e.Pointer.button == 1){
		im->down = true;
		RaiseActionEvent();
	}
	if(e.type == wm_EventType::PointerButtonUp && e.Pointer.button == 1){
		im->down = false;
	}
	if(e.type == wm_EventType::PointerLeave){
		if(im->down) im->down = false;
	}
	if(e.type == wm_EventType::PointerEnter){
		auto pinfo = WM_GetPointerInfo();
		if(pinfo.flags & MouseFlags::Button1) im->down = true;
	}
	if(im->down != oldDown) IControl::Paint(im->rect);
	return {true};
}

void ResizeHandle::Paint(gds::Surface &s){
	if(!im->surf || im->down != im->paintDown){
		int32_t inW = im->rect.w - 1;
		int32_t inH = im->rect.h - 1;
		
		if(!im->surf || !im->bkSurf){
			im->surf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
			im->bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
			
			im->bkSurf->BeginQueue();
			
			auto handleCol = colours::GetResizeHandleBackground().Fix(*im->bkSurf);
			auto border = colours::GetBorder().Fix(*im->bkSurf);
			
			im->bkSurf->Box({1, 1, (uint32_t)inW - 1, (uint32_t)inH - 1}, handleCol, handleCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
			im->bkSurf->Box({0, 0, im->rect.w, im->rect.h}, border, border);
			
			im->bkSurf->CommitQueue();
			im->bkSurf->Compress();
			
		}else im->surf->Clear();
		
		im->surf->BeginQueue();
		
		im->surf->Blit(*im->bkSurf, im->rect.AtZero(), im->rect.AtZero());
		
		if(im->down){
			auto downCol = colours::GetResizeHandleDown().Fix(*im->surf);
			im->surf->Box({1, 1, (uint32_t)inW - 1, (uint32_t)inH - 1}, downCol, downCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		}
		
		auto fgCol = colours::GetResizeHandleForeground().Fix(*im->surf);
		im->surf->Line({3, inH - 3}, {inW - 3, 3}, fgCol);
		im->surf->Line({9, inH - 3}, {inW - 3, 9}, fgCol);
		im->surf->Line({15, inH - 3}, {inW - 3, 15}, fgCol);
		
		im->surf->CommitQueue();
		im->surf->Compress();
		
		im->paintDown = im->down;
	}
	
	s.Blit(*im->surf, im->rect.AtZero(), im->rect);
	if(!im->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(im->rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect ResizeHandle::GetPaintRect(){
	return im->rect;
}

gds::Rect ResizeHandle::GetInteractRect(){
	return im->rect;
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
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(im->rect);
	}
}

void ResizeHandle::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(im->rect);
	}
}

bool ResizeHandle::IsEnabled(){
	return im->enabled;
}

size_t ResizeHandle::GetZOrder(){
	return ZOrder::Foreground;
}

void ResizeHandle::SetPosition(const gds::Rect &r){
	im->rect = r;
	im->surf.reset();
	im->bkSurf.reset();
	im->down = false;
}

}
}
