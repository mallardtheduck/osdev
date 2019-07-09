#include <gui/statusbar.hpp>
#include <gui/defaults.hpp>

namespace btos_api{
namespace gui{

StatusBar::StatusBar(const std::string &t) : text(t), height(fonts::GetStatusBarTextSize() * 1.5) {}

EventResponse StatusBar::HandleEvent(const wm_Event&){
	return {false};
}

void StatusBar::Paint(gds::Surface &s){
	auto containerRect = GetContainerRect();
	if(rect.w != containerRect.w || rect.y != (int32_t)(containerRect.h - height)){
		surf.reset();
		rect = {0, (int32_t)(containerRect.h - height), containerRect.w, height};
	}
	if(!surf && containerRect.w){
		if(!surf) surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		else surf->Clear();
		
		uint32_t inW = rect.w - 1;
		
		auto bkgCol = colours::GetStatusBarBackground().Fix(*surf);
		auto bdrCol = colours::GetBorder().Fix(*surf);
		auto txtCol = colours::GetStatusBarText().Fix(*surf);
		
		auto textMeasures = surf->MeasureText(text, fonts::GetStatusBarFont(), fonts::GetStatusBarTextSize());
		int32_t textX = std::max<int32_t>(((rect.w - textMeasures.w) / 2), 0);
		int32_t textY = std::max<int32_t>(((rect.h + textMeasures.h) / 2), 0);
		
		surf->BeginQueue();
		
		surf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		surf->Line({0, 0}, {(int32_t)inW, 0}, bdrCol);
		
		surf->Text({textX, textY}, text, fonts::GetStatusBarFont(), fonts::GetStatusBarTextSize(), txtCol);
		
		surf->CommitQueue();
	}
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
}

gds::Rect StatusBar::GetPaintRect(){
	return rect;
}

gds::Rect StatusBar::GetInteractRect(){
	return {};
}

uint32_t StatusBar::GetSubscribed(){
	return 0;
}

void StatusBar::SetText(const std::string &t){
	text = t;
	surf.reset();
	IControl::Paint(rect);
}

}
}