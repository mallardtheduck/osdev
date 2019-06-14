#include <gui/progressbar.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>

namespace btos_api{
namespace gui{

ProgressBar::ProgressBar(const gds::Rect &r, int v) : rect(r), value(v) {}
	
EventResponse ProgressBar::HandleEvent(const wm_Event&){
	return {false};
}

void ProgressBar::Paint(gds::Surface &s){
	if(!surf){
		surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		
		surf->BeginQueue();
		auto border = colours::GetBorder().Fix(*surf);
		auto bkgCol = colours::GetBackground().Fix(*surf);
		auto selCol = colours::GetSelection().Fix(*surf);
		
		auto topLeft = colours::GetProgressBarLowLight().Fix(*surf);
		auto bottomRight = colours::GetProgressBarHiLight().Fix(*surf);
		
		auto inW = rect.w - 1;
		auto inH = rect.h - 1;
		
		auto pval = (uint32_t)(((double)value / 100.0) * inW);
		
		surf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		surf->Box({1, 1, pval, rect.h - 2}, selCol, selCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		drawing::Border(*surf, {0, 0, inW, inH}, border);
		drawing::BevelBox(*surf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);
		
		surf->CommitQueue();
	}
	
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
}

gds::Rect ProgressBar::GetPaintRect(){
	return rect;
}

gds::Rect ProgressBar::GetInteractRect(){
	return {0, 0, 0, 0};
}

uint32_t ProgressBar::GetSubscribed(){
	return 0;
}
	
void ProgressBar::SetValue(int v){
	if(value != v){
		value = v;
		surf.reset();
	}
}

void ProgressBar::SetPosition(const gds::Rect &r){
	rect = r;
	surf.reset();
}

}
}
