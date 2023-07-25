#include <gui/progressbar.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>

namespace btos_api{
namespace gui{

struct ProgressBarImpl{
	gds::Rect rect;
	int value;
	std::unique_ptr<gds::Surface> surf;
};
PIMPL_IMPL(ProgressBarImpl);

ProgressBar::ProgressBar(const gds::Rect &r, int v) : im(new ProgressBarImpl()){
	im->rect = r; im->value = v;
}
	
EventResponse ProgressBar::HandleEvent(const wm_Event&){
	return {false};
}

void ProgressBar::Paint(gds::Surface &s){
	if(!im->surf){
		im->surf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
		
		im->surf->BeginQueue();
		auto border = colours::GetBorder().Fix(*im->surf);
		auto bkgCol = colours::GetBackground().Fix(*im->surf);
		auto selCol = colours::GetSelection().Fix(*im->surf);
		
		auto topLeft = colours::GetProgressBarLowLight().Fix(*im->surf);
		auto bottomRight = colours::GetProgressBarHiLight().Fix(*im->surf);
		
		auto inW = im->rect.w - 1;
		auto inH = im->rect.h - 1;
		
		auto pval = (uint32_t)(((double)im->value / 100.0) * inW);
		
		im->surf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		im->surf->Box({1, 1, pval, im->rect.h - 2}, selCol, selCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		drawing::Border(*im->surf, {0, 0, inW, inH}, border);
		drawing::BevelBox(*im->surf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);
		
		im->surf->CommitQueue();
		im->surf->Compress();
	}
	
	s.Blit(*im->surf, im->rect.AtZero(), im->rect);
}

gds::Rect ProgressBar::GetPaintRect(){
	return im->rect;
}

gds::Rect ProgressBar::GetInteractRect(){
	return {0, 0, 0, 0};
}

uint32_t ProgressBar::GetSubscribed(){
	return 0;
}
	
void ProgressBar::SetValue(int v){
	if(im->value != v){
		im->value = v;
		im->surf.reset();
	}
}

void ProgressBar::SetPosition(const gds::Rect &r){
	im->rect = r;
	im->surf.reset();
}

}
}
