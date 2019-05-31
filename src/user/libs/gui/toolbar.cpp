#include <gui/toolbar.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/mouse.h>
#include <wm/libwm.h>

namespace btos_api{
namespace gui{

Toolbar::Toolbar(uint32_t s) : size(s) {
	height = (size / 3) * 4;
}

EventResponse Toolbar::HandleEvent(const wm_Event &evt){
	EventResponse response = {false};
	if((evt.type & wm_PointerEvents)){
		auto e = evt;
		auto br = GetContainerRect();
		e.Pointer.x -= br.x;
		e.Pointer.y -= br.y;
		
		if(e.type == wm_EventType::PointerMove){
			if(mouseOver && !gds::InRect(e.Pointer.x, e.Pointer.y, mouseOver->GetInteractRect())){
				auto leaveEvt = e;
				leaveEvt.type = wm_EventType::PointerLeave;
				HandleEvent(leaveEvt);
				mouseOver.reset();
			}
		}
		
		if(mouseOver && mouseOver->IsEnabled() && e.type == wm_EventType::PointerLeave){
			response = mouseOver->HandleEvent(e);
		}
		
		if(!response.IsFinishedProcessing()){
			for(auto &c : controls){
				if(!c->IsEnabled()) continue;
				if(e.type == wm_EventType::PointerMove && mouseOver != c && gds::InRect(e.Pointer.x, e.Pointer.y, c->GetInteractRect()) && (c->GetSubscribed() & wm_EventType::PointerEnter)){
					mouseOver = c;
					auto enterEvt = evt;
					enterEvt.type = wm_EventType::PointerEnter;
					HandleEvent(enterEvt);
				}
				if((c->GetSubscribed() & e.type) && gds::InRect(e.Pointer.x, e.Pointer.y, c->GetInteractRect())){
					response = c->HandleEvent(e);
				}
			}
		}
	}
	return response;
}

void Toolbar::Paint(gds::Surface &s){
	auto containerRect = GetContainerRect();
	if(rect.w != containerRect.w){
		surf.reset();
		rect = {0, 0, containerRect.w, height};
	}
	if((!surf || update) && containerRect.w){
		if(!surf) surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		else surf->Clear();
		
		surf->BeginQueue();
		
		uint32_t inW = rect.w - 1;
		uint32_t inH = rect.h - 1;
		
		auto bkgCol = colours::GetToolbarBackground().Fix(*surf);
		auto bdrCol = colours::GetBorder().Fix(*surf);
		
		surf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		surf->Line({0, (int32_t)inH}, {(int32_t)inW, (int32_t)inH}, bdrCol);
		
		int32_t margin = size / 6;
		
		int32_t cXpos = margin;
		
		for(auto &ctrl : controls){
			ctrl->size = size;
			ctrl->margin = margin;
			auto width = ctrl->GetWidth();
			
			ctrl->rect = {cXpos, margin, width, size};
			ctrl->Paint(*surf);
			cXpos += width + margin;
		}
		
		surf->CommitQueue();
	}
	s.Blit(*surf, {0, 0, rect.w, rect.h}, {0, 0, rect.w, rect.h});
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect Toolbar::GetPaintRect(){
	return rect;
}

gds::Rect Toolbar::GetInteractRect(){
	return rect;
}

uint32_t Toolbar::GetSubscribed(){
	uint32_t ret = 0;
	for(auto &ctrl : controls) ret |= ctrl->GetSubscribed();
	return ret;
}

void Toolbar::Focus() {}
void Toolbar::Blur(){}

uint32_t Toolbar::GetFlags(){
	return ControlFlags::NoFocus;
}

void Toolbar::Enable(){
	enabled = true;
}

void Toolbar::Disable(){
	enabled = false;
}

bool Toolbar::IsEnabled(){
	return enabled;
}

std::vector<std::shared_ptr<IToolbarControlBase>> &Toolbar::Controls(){
	return controls;
}

void Toolbar::Refresh(){
	for(auto &ctrl : controls) BindToParent(*ctrl);
	update = true;
}

void Toolbar::OnBind(){
	for(auto &ctrl : controls) BindToParent(*ctrl);
}

ToolbarButton::ToolbarButton(std::shared_ptr<gds::Surface> i, const std::string &l) : icon(i), label(l){
	if(!label.empty()) labelMeasures = gds::Surface(gds_SurfaceType::Vector, 1, 1, 100, gds_ColourType::True)
		.MeasureText(l, fonts::GetToolbarButtonFont(), fonts::GetToolbarButtonTextSize());
	if(icon) info = icon->Info();
}
	
EventResponse ToolbarButton::HandleEvent(const wm_Event &e){
	auto oldDown = down;
	if(e.type == wm_EventType::PointerButtonDown && e.Pointer.button == 1){
		down = true;
	}else if(e.type == wm_EventType::PointerButtonUp && e.Pointer.button == 1){
		down = false;
		RaiseActionEvent();
	}else if(e.type == wm_EventType::PointerLeave){
		if(down) down = false;
	}else if(e.type == wm_EventType::PointerEnter){
		auto pinfo = WM_GetPointerInfo();
		if(pinfo.flags & MouseFlags::Button1) down = true;
	}
	if(down != oldDown){
		IControl::Paint(rect);	
	}
	return {true};
}

void ToolbarButton::Paint(gds::Surface &s){
	if(!surf || down != paintDown){
		int32_t inW = rect.w - 1;
		int32_t inH = rect.h - 1;
		
		if(!surf || !bkSurf){
			surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));               
			bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
			
			bkSurf->BeginQueue();
			
			auto bkgCol = colours::GetToolbarBackground().Fix(*bkSurf);
			auto buttonColour = colours::GetToolbarButtonColour().Fix(*bkSurf);
			auto border = colours::GetBorder().Fix(*bkSurf);
			
			bkSurf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
			bkSurf->Box({1, 1, (uint32_t)inW - 2, (uint32_t)inH - 2}, buttonColour, buttonColour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
			drawing::Border(*bkSurf, {0, 0, (uint32_t)inW, (uint32_t)inH}, border);
			
			if(icon){
				int32_t imgX = margin;
				int32_t imgY = std::max<int32_t>(((rect.h - info.h) / 2), 0);
				bkSurf->Blit(*icon, {0, 0, info.w, info.h}, {imgX, imgY, info.w, info.h});
			}
			
			if(!label.empty()){
				int32_t labelX = margin;
				int32_t labelY = std::max<int32_t>(((rect.h + labelMeasures.h) / 2), 0);
			
				if(icon) labelX += info.w + margin;
				
				auto textColour = colours::GetToolbarButtonText().Fix(*bkSurf);
				bkSurf->Text({labelX, labelY}, label, fonts::GetToolbarButtonFont(), fonts::GetToolbarButtonTextSize(), textColour);
			}
			
			bkSurf->CommitQueue();
			
		}else surf->Clear();
		
		surf->BeginQueue();
		
		surf->Blit(*bkSurf, {0, 0, rect.w, rect.h}, {0, 0, rect.w, rect.h});
		
		auto topLeft = colours::GetToolbarButtonHiLight().Fix(*surf);
		auto bottomRight = colours::GetToolbarButtonLowLight().Fix(*surf);
		if(down) std::swap(topLeft, bottomRight);
		
		drawing::BevelBox(*surf, {1, 1, (uint32_t)inW - 2, (uint32_t)inH - 2}, topLeft, bottomRight);
		
		surf->CommitQueue();
		
		paintDown = down;
	}
	
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect ToolbarButton::GetPaintRect(){
	return rect;
}

gds::Rect ToolbarButton::GetInteractRect(){
	return rect;
}

uint32_t ToolbarButton::GetSubscribed(){
	return (wm_EventType::PointerButtonDown | wm_EventType::PointerButtonUp | wm_EventType::PointerLeave | wm_EventType::PointerEnter);
}

void ToolbarButton::Enable(){
	enabled = true;
}

void ToolbarButton::Disable(){
	enabled = false;
}

bool ToolbarButton::IsEnabled(){
	return enabled;
}

uint32_t ToolbarButton::GetWidth(){
	uint32_t ret = margin * 2;
	
	if(icon) ret += info.w;
	if(!label.empty()) ret += labelMeasures.w;
	if(icon && !label.empty()) ret += margin;
	
	return ret;
}

ToolbarSpacer::ToolbarSpacer(){}
	
EventResponse ToolbarSpacer::HandleEvent(const wm_Event&){
	return {false};
}

void ToolbarSpacer::Paint(gds::Surface &surf) {
	auto col = colours::GetBorder().Fix(surf);
	int32_t smargin = margin;
	surf.Line({rect.x + smargin, rect.y + smargin}, {rect.x + smargin, rect.y + ((int32_t)rect.h - smargin)}, col);
}

gds::Rect ToolbarSpacer::GetPaintRect(){
	return rect;
}

gds::Rect ToolbarSpacer::GetInteractRect(){
	return {};
}

uint32_t ToolbarSpacer::GetSubscribed(){
	return 0;
}

uint32_t ToolbarSpacer::GetWidth(){
	return (margin * 2) + 1;
}

}
}