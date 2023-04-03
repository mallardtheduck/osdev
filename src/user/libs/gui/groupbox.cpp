#include <gui/groupbox.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>

namespace btos_api{
namespace gui{

struct GroupBoxImpl{
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> surf;
	gds::TextMeasurements textMeasures = {};
	uint32_t textH;
};
PIMPL_IMPL(GroupBoxImpl);

GroupBox::GroupBox(const gds::Rect &r, const std::string &t) : im(new GroupBoxImpl){
	im->rect = r; im->text = t;
}
	
EventResponse GroupBox::HandleEvent(const wm_Event&){
	return {false};
}

void GroupBox::Paint(gds::Surface &s){
	if(!im->surf){
		if(!im->textMeasures.w){
			im->surf.reset(new gds::Surface(gds_SurfaceType::Vector, 1, 1, 100, gds_ColourType::True));
			im->textMeasures = im->surf->MeasureText(im->text, fonts::GetGroupBoxFont(), fonts::GetGroupBoxTextSize());
			im->textH = (double)im->textMeasures.h * 1.5;
		}
		im->surf.reset(new gds::Surface(gds_SurfaceType::Vector, im->textMeasures.w, im->textH, 100, gds_ColourType::True));
		
		auto bkgCol = colours::GetBackground().Fix(*im->surf);
		auto txtCol = colours::GetGroupBoxText().Fix(*im->surf);
		
		im->surf->Box({0, 0, im->textMeasures.w, im->textH}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		im->surf->Text({0, (int32_t)im->textMeasures.h}, im->text, fonts::GetGroupBoxFont(), fonts::GetGroupBoxTextSize(), txtCol);
	}
	int32_t textX = std::max<int32_t>(((im->rect.w - im->textMeasures.w) / 2), 0);

	auto bdrCol = colours::GetBorder().Fix(s);
	drawing::Border(s, {im->rect.x, im->rect.y + (int32_t)(im->textMeasures.h / 2), im->rect.w - 1, im->rect.h - 1 - (im->textMeasures.h / 2)}, bdrCol);
	s.Blit(*im->surf, {0, 0, im->textMeasures.w, im->textH}, {im->rect.x + textX, im->rect.y, im->textMeasures.w, im->textH});
	im->surf->Compress();
}

gds::Rect GroupBox::GetPaintRect(){
	return im->rect;
}

gds::Rect GroupBox::GetInteractRect(){
	return {0, 0, 0, 0};
}

uint32_t GroupBox::GetSubscribed(){
	return 0;
}
	
void GroupBox::SetText(const std::string &t){
	im->text = t;
	im->surf.reset();
	IControl::Paint(im->rect);
}

void GroupBox::SetPosition(const gds::Rect &r){
	im->rect = r;
	im->surf.reset();
}


}
}
