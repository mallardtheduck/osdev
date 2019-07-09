#include <gui/groupbox.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>

namespace btos_api{
namespace gui{

GroupBox::GroupBox(const gds::Rect &r, const std::string &t) : rect(r), text(t) {}
	
EventResponse GroupBox::HandleEvent(const wm_Event&){
	return {false};
}

void GroupBox::Paint(gds::Surface &s){
	if(!surf){
		if(!textMeasures.w){
			surf.reset(new gds::Surface(gds_SurfaceType::Vector, 1, 1, 100, gds_ColourType::True));
			textMeasures = surf->MeasureText(text, fonts::GetGroupBoxFont(), fonts::GetGroupBoxTextSize());
			textH = (double)textMeasures.h * 1.5;
		}
		surf.reset(new gds::Surface(gds_SurfaceType::Vector, textMeasures.w, textH, 100, gds_ColourType::True));
		
		auto bkgCol = colours::GetBackground().Fix(*surf);
		auto txtCol = colours::GetGroupBoxText().Fix(*surf);
		
		surf->Box({0, 0, textMeasures.w, textH}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		surf->Text({0, (int32_t)textMeasures.h}, text, fonts::GetGroupBoxFont(), fonts::GetGroupBoxTextSize(), txtCol);
	}
	int32_t textX = std::max<int32_t>(((rect.w - textMeasures.w) / 2), 0);
	
	auto bdrCol = colours::GetBorder().Fix(s);
	drawing::Border(s, {rect.x, rect.y + (int32_t)(textMeasures.h / 2), rect.w - 1, rect.h - 1 - (textMeasures.h / 2)}, bdrCol);
	s.Blit(*surf, {0, 0, textMeasures.w, textH}, {rect.x + textX, rect.y, textMeasures.w, textH});
}

gds::Rect GroupBox::GetPaintRect(){
	return rect;
}

gds::Rect GroupBox::GetInteractRect(){
	return {0, 0, 0, 0};
}

uint32_t GroupBox::GetSubscribed(){
	return 0;
}
	
void GroupBox::SetText(const std::string &t){
	text = t;
	surf.reset();
	IControl::Paint(rect);
}

void GroupBox::SetPosition(const gds::Rect &r){
	rect = r;
	surf.reset();
}


}
}
