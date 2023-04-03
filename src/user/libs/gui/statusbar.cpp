#include <gui/statusbar.hpp>
#include <gui/defaults.hpp>

namespace btos_api{
namespace gui{

struct StatusBarImpl{
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> surf;
	
	uint32_t height;
};
PIMPL_IMPL(StatusBarImpl);

StatusBar::StatusBar(const std::string &t) : im(new StatusBarImpl()){
	im->text = t; im->height = fonts::GetStatusBarTextSize() * 1.5;
}

EventResponse StatusBar::HandleEvent(const wm_Event&){
	return {false};
}

void StatusBar::Paint(gds::Surface &s){
	auto containerRect = GetContainerRect();
	if(im->rect.w != containerRect.w || im->rect.y != (int32_t)(containerRect.h - im->height)){
		im->surf.reset();
		im->rect = {0, (int32_t)(containerRect.h - im->height), containerRect.w, im->height};
	}
	if(!im->surf && containerRect.w){
		if(!im->surf) im->surf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
		else im->surf->Clear();
		
		uint32_t inW = im->rect.w - 1;
		
		auto bkgCol = colours::GetStatusBarBackground().Fix(*im->surf);
		auto bdrCol = colours::GetBorder().Fix(*im->surf);
		auto txtCol = colours::GetStatusBarText().Fix(*im->surf);
		
		auto textMeasures = im->surf->MeasureText(im->text, fonts::GetStatusBarFont(), fonts::GetStatusBarTextSize());
		int32_t textX = std::max<int32_t>(((im->rect.w - textMeasures.w) / 2), 0);
		int32_t textY = std::max<int32_t>(((im->rect.h + textMeasures.h) / 2), 0);
		
		im->surf->BeginQueue();
		
		im->surf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		im->surf->Line({0, 0}, {(int32_t)inW, 0}, bdrCol);
		
		im->surf->Text({textX, textY}, im->text, fonts::GetStatusBarFont(), fonts::GetStatusBarTextSize(), txtCol);
		
		im->surf->CommitQueue();
		im->surf->Compress();
	}
	s.Blit(*im->surf, im->rect.AtZero(), im->rect);
}

gds::Rect StatusBar::GetPaintRect(){
	return im->rect;
}

gds::Rect StatusBar::GetInteractRect(){
	return {};
}

uint32_t StatusBar::GetSubscribed(){
	return 0;
}

void StatusBar::SetText(const std::string &t){
	im->text = t;
	im->surf.reset();
	IControl::Paint(im->rect);
}

}
}