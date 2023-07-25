#include <gui/label.hpp>
#include <gui/defaults.hpp>

namespace btos_api{
namespace gui{

struct LabelImpl{
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> surf;
	
	Label::Justification just;
};
PIMPL_IMPL(LabelImpl);

Label::Label(const gds::Rect &r, const std::string &t, Label::Justification j) : im(new LabelImpl()){
	im->rect = r; im->text = t; im->just = j;
}
	
EventResponse Label::HandleEvent(const wm_Event&){
	return {false};
}

void Label::Paint(gds::Surface &s){
	if(!im->surf){
		im->surf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
		
		auto textMeasures = im->surf->MeasureText(im->text, fonts::GetLabelFont(), fonts::GetLabelTextSize());
		auto bkgCol = colours::GetBackground().Fix(*im->surf);
		auto txtCol = colours::GetLabelText().Fix(*im->surf);
			
		int32_t textX;
		switch(im->just){
			case Label::Justification::Left:
				textX = 0;
				break;
			case Label::Justification::Right:
				textX = im->rect.w - textMeasures.w;
				break;
			case Label::Justification::Center:
				textX = std::max<int32_t>(((im->rect.w - textMeasures.w) / 2), 0);
				break;
		}
		
		int32_t textY = std::max<int32_t>(((im->rect.h + textMeasures.h) / 2), 0);
		
		im->surf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		im->surf->Text({textX, textY}, im->text, fonts::GetLabelFont(), fonts::GetLabelTextSize(), txtCol);
		im->surf->Compress();
	}
	
	s.Blit(*im->surf, im->rect.AtZero(), im->rect);
}

gds::Rect Label::GetPaintRect(){
	return im->rect;
}

gds::Rect Label::GetInteractRect(){
	return {0, 0, 0, 0};
}

uint32_t Label::GetSubscribed(){
	return 0;
}
	
void Label::SetText(const std::string &t){
	im->text = t;
	im->surf.reset();
	IControl::Paint(im->rect);
}

void Label::SetPosition(const gds::Rect &r){
	im->rect = r;
	im->surf.reset();
}

}
}
