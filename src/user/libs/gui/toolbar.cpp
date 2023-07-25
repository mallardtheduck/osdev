#include <gui/toolbar.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/mouse.h>
#include <wm/libwm.h>

namespace btos_api{
namespace gui{

struct ToolbarImpl{
	gds::Rect rect;
	std::unique_ptr<gds::Surface> bkSurf;
	bool enabled = true;
	
	uint32_t size;
	uint32_t height;
	
	std::vector<std::shared_ptr<IToolbarControlBase>> controls;
	std::shared_ptr<IToolbarControlBase> mouseOver;
};
PIMPL_IMPL(ToolbarImpl);

Toolbar::Toolbar(uint32_t s) : im(new ToolbarImpl()){
	im->size = s;
	im->height = (im->size / 3.0) * 4;
}

EventResponse Toolbar::HandleEvent(const wm_Event &evt){
	EventResponse response = {false};
	if((evt.type & wm_PointerEvents)){
		auto e = evt;
		auto br = GetContainerRect();
		e.Pointer.x -= br.x;
		e.Pointer.y -= br.y;
		
		if(e.type == wm_EventType::PointerMove){
			if(im->mouseOver && !gds::InRect(e.Pointer.x, e.Pointer.y, im->mouseOver->GetInteractRect())){
				auto leaveEvt = e;
				leaveEvt.type = wm_EventType::PointerLeave;
				HandleEvent(leaveEvt);
				im->mouseOver.reset();
			}
		}
		
		if(im->mouseOver && im->mouseOver->IsEnabled() && e.type == wm_EventType::PointerLeave){
			response = im->mouseOver->HandleEvent(e);
		}
		
		if(!response.IsFinishedProcessing()){
			for(auto &c : im->controls){
				if(!c->IsEnabled()) continue;
				if(e.type == wm_EventType::PointerMove && im->mouseOver != c && gds::InRect(e.Pointer.x, e.Pointer.y, c->GetInteractRect()) && (c->GetSubscribed() & wm_EventType::PointerEnter)){
					im->mouseOver = c;
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
	if(!containerRect.w) return;
	
	if(im->rect.w != containerRect.w){
		im->bkSurf.reset();
		im->rect = {0, 0, containerRect.w, im->height};
	}
	if(!im->bkSurf){
		im->bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
		
		im->bkSurf->BeginQueue();
		
		uint32_t inW = im->rect.w - 1;
		uint32_t inH = im->rect.h - 1;
		
		auto bkgCol = colours::GetToolbarBackground().Fix(*im->bkSurf);
		auto bdrCol = colours::GetBorder().Fix(*im->bkSurf);
		
		im->bkSurf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		im->bkSurf->Line({0, (int32_t)inH}, {(int32_t)inW, (int32_t)inH}, bdrCol);
		
		im->bkSurf->CommitQueue();
		im->bkSurf->Compress();
	}
	s.Blit(*im->bkSurf, im->rect.AtZero(), im->rect);
	
	int32_t margin = im->size / 6;
		
	int32_t cXpos = im->rect.x + margin;
	
	for(auto &ctrl : im->controls){
		ctrl->size = im->size;
		ctrl->margin = margin;
		auto width = ctrl->GetWidth();
		
		ctrl->rect = {cXpos, im->rect.y + margin, width, im->size};
		ctrl->Paint(s);
		cXpos += width + (margin / 2);
	}
	
	if(!im->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(im->rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect Toolbar::GetPaintRect(){
	return im->rect;
}

gds::Rect Toolbar::GetInteractRect(){
	return im->rect;
}

uint32_t Toolbar::GetSubscribed(){
	uint32_t ret = 0;
	for(auto &ctrl : im->controls) ret |= ctrl->GetSubscribed();
	return ret;
}

void Toolbar::Focus() {}
void Toolbar::Blur(){}

uint32_t Toolbar::GetFlags(){
	return ControlFlags::NoFocus;
}

void Toolbar::Enable(){
	im->enabled = true;
}

void Toolbar::Disable(){
	im->enabled = false;
}

bool Toolbar::IsEnabled(){
	return im->enabled;
}

std::vector<std::shared_ptr<IToolbarControlBase>> &Toolbar::Controls(){
	return im->controls;
}

void Toolbar::Refresh(){
	for(auto &ctrl : im->controls) BindToParent(*ctrl);
	IControl::Paint(im->rect);
}

void Toolbar::OnBind(){
	for(auto &ctrl : im->controls) BindToParent(*ctrl);
}

struct ToolbarButtonImpl{
	bool down = false;
	bool enabled = true;

	std::shared_ptr<gds::Surface> icon;
	std::string label;
	
	std::unique_ptr<gds::Surface> bkSurf;
	gds::TextMeasurements labelMeasures;
	gds_SurfaceInfo info;
};
PIMPL_IMPL(ToolbarButtonImpl);

ToolbarButton::ToolbarButton(std::shared_ptr<gds::Surface> i, const std::string &l) : im(new ToolbarButtonImpl()){
	im->icon = i; im->label = l;
	if(!im->label.empty()) im->labelMeasures = gds::Surface(gds_SurfaceType::Vector, 1, 1, 100, gds_ColourType::True)
		.MeasureText(l, fonts::GetToolbarButtonFont(), fonts::GetToolbarButtonTextSize());
	if(im->icon) im->info = im->icon->Info();
}
	
EventResponse ToolbarButton::HandleEvent(const wm_Event &e){
	auto oldDown = im->down;
	if(e.type == wm_EventType::PointerButtonDown && e.Pointer.button == 1){
		im->down = true;
	}else if(e.type == wm_EventType::PointerButtonUp && e.Pointer.button == 1){
		im->down = false;
		RaiseActionEvent();
	}else if(e.type == wm_EventType::PointerLeave){
		if(im->down) im->down = false;
	}else if(e.type == wm_EventType::PointerEnter){
		auto pinfo = WM_GetPointerInfo();
		if(pinfo.flags & MouseFlags::Button1) im->down = true;
	}
	if(im->down != oldDown){
		IControl::Paint(rect);	
	}
	return {true};
}

void ToolbarButton::Paint(gds::Surface &s){
	int32_t inW = rect.w - 1;
	int32_t inH = rect.h - 1;
	
	if(!im->bkSurf){
		im->bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		
		im->bkSurf->BeginQueue();
		
		auto bkgCol = colours::GetToolbarBackground().Fix(*im->bkSurf);
		auto buttonColour = colours::GetToolbarButtonColour().Fix(*im->bkSurf);
		auto border = colours::GetBorder().Fix(*im->bkSurf);
		
		im->bkSurf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		im->bkSurf->Box({1, 1, (uint32_t)inW - 2, (uint32_t)inH - 2}, buttonColour, buttonColour, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		drawing::Border(*im->bkSurf, {0, 0, (uint32_t)inW, (uint32_t)inH}, border);
		
		if(im->icon){
			int32_t imgX = margin;
			int32_t imgY = std::max<int32_t>(((rect.h - im->info.h) / 2), 0);
			im->bkSurf->Blit(*im->icon, {0, 0, im->info.w, im->info.h}, {imgX, imgY, im->info.w, im->info.h});
		}
		
		if(!im->label.empty()){
			int32_t labelX = margin;
			int32_t labelY = std::max<int32_t>(((rect.h + im->labelMeasures.h) / 2), 0);
		
			if(im->icon) labelX += im->info.w + margin;
			
			auto textColour = colours::GetToolbarButtonText().Fix(*im->bkSurf);
			im->bkSurf->Text({labelX, labelY}, im->label, fonts::GetToolbarButtonFont(), fonts::GetToolbarButtonTextSize(), textColour);
		}
		
		im->bkSurf->CommitQueue();
		im->bkSurf->Compress();
	}
	s.Blit(*im->bkSurf, {0, 0, rect.w, rect.h}, rect);
	
	auto topLeft = colours::GetToolbarButtonHiLight().Fix(s);
	auto bottomRight = colours::GetToolbarButtonLowLight().Fix(s);
	if(im->down) std::swap(topLeft, bottomRight);
	
	drawing::BevelBox(s, {rect.x + 1, rect.y + 1, (uint32_t)inW - 2, (uint32_t)inH - 2}, topLeft, bottomRight);
		
	if(!im->enabled){
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
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(rect);
	}
}

void ToolbarButton::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(rect);
	}
}

bool ToolbarButton::IsEnabled(){
	return im->enabled;
}

uint32_t ToolbarButton::GetWidth(){
	uint32_t ret = margin * 2;
	
	if(im->icon) ret += im->info.w;
	if(!im->label.empty()) ret += im->labelMeasures.w;
	if(im->icon && !im->label.empty()) ret += margin;
	
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