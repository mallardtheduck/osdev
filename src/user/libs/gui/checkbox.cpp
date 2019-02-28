#include <gui/checkbox.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>

namespace btos_api{
namespace gui{
	
const auto checkSize = 15;

Checkbox::Checkbox(const gds::Rect &r, const std::string &t, bool v) : rect(r), text(t), value(v) {}
	
EventResponse Checkbox::HandleEvent(const wm_Event &e){
	if(e.type == wm_EventType::PointerButtonUp){
		value = !value;
		update = true;
		if(onChange) onChange(value);
	}
	return {true, rect};
}

void Checkbox::Paint(gds::Surface &s){
	if(!surf || update){
		uint32_t inW = rect.w - 1;
		uint32_t inH = rect.h - 1;
		int32_t chkY = std::max<int32_t>((rect.h - checkSize) / 2, 0);
		
		if(!bkSurf){
			bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
			bkSurf->BeginQueue();
			
			textMeasures = bkSurf->MeasureText(text, fonts::GetCheckboxFont(), fonts::GetCheckboxTextSize());
			auto bkgCol = colours::GetBackground().Fix(*bkSurf);
			auto txtCol = colours::GetCheckboxText().Fix(*bkSurf);
				
			int32_t textX = checkSize + 3;
			int32_t textY = std::max<int32_t>(((rect.h + textMeasures.h) / 2), 0);
			
			bkSurf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
			bkSurf->Text({textX, textY}, text, fonts::GetCheckboxFont(), fonts::GetCheckboxTextSize(), txtCol);
			
			auto border = colours::GetBorder().Fix(*bkSurf);
			drawing::Border(*bkSurf, {1, chkY, checkSize, checkSize}, border);
			
			auto topLeft = colours::GetCheckboxLowLight().Fix(*bkSurf);
			auto bottomRight = colours::GetCheckboxHiLight().Fix(*bkSurf);
			drawing::BevelBox(*bkSurf, {2, chkY + 1, checkSize - 2, checkSize - 2}, topLeft, bottomRight);
			
			bkSurf->CommitQueue();
		}
		
		if(!surf) surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		else surf->Clear();
		
		surf->BeginQueue();
		
		surf->Blit(*bkSurf, {0, 0, rect.w, rect.h}, {0, 0, rect.w, rect.h});
		
		if(value){
			auto chkCol = colours::GetCheckboxCheck().Fix(*surf);
			auto chkTop = chkY;
			auto chkBottom = chkY + checkSize;
			
			surf->Line({5, chkTop + 5}, {checkSize - 3, chkBottom - 4}, chkCol, 2);
			surf->Line({5, chkBottom - 4}, {checkSize - 3, chkTop + 5}, chkCol, 2);
		}
		
		if(focus){
			auto focusCol = colours::GetCheckboxFocus().Fix(*surf);
			
			int32_t boxTop = std::max(std::min<int32_t>(chkY - 1, (rect.h - textMeasures.h) / 2), 0);
			int32_t boxLeft = 0;
			uint32_t boxWidth = textMeasures.w + checkSize + 3;
			if(boxLeft + boxWidth > inW) boxWidth = inW - boxLeft;
			uint32_t boxHeight = std::max<int32_t>(textMeasures.h, checkSize + 3);
			if(boxTop + boxHeight > inH) boxHeight = inH - boxTop;
			surf->Box({boxLeft, boxTop, boxWidth, boxHeight}, focusCol, focusCol);
		}
		
		surf->CommitQueue();
		
		update = false;
	}
	
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
}

gds::Rect Checkbox::GetPaintRect(){
	return rect;
}

gds::Rect Checkbox::GetInteractRect(){
	if(textMeasures.w){
		uint32_t inW = rect.w - 1;
		uint32_t inH = rect.h - 1;
		int32_t chkY = std::max<int32_t>((rect.h - checkSize) / 2, 0);
		
		int32_t boxTop = std::max(std::min<int32_t>(chkY - 1, (rect.h - textMeasures.h) / 2), 0);
		int32_t boxLeft = 0;
		uint32_t boxWidth = textMeasures.w + checkSize + 3;
		if(boxLeft + boxWidth > inW) boxWidth = inW - boxLeft;
		uint32_t boxHeight = std::max<int32_t>(textMeasures.h, checkSize + 3);
		if(boxTop + boxHeight > inH) boxHeight = inH - boxTop;
		return {rect.x + boxLeft, rect.y + boxTop, boxWidth, boxHeight};
	}else return rect;
}

uint32_t Checkbox::GetSubscribed(){
	return wm_EventType::PointerButtonUp;
}

void Checkbox::Focus(){
	if(!focus) update = true;
	focus = true;
}
void Checkbox::Blur(){
	if(focus) update = true;
	focus = false;
}
	
void Checkbox::SetText(const std::string &t){
	text = t;
	bkSurf.reset();
}

bool Checkbox::GetValue(){
	return value;
}

void Checkbox::OnChange(const std::function<void(bool)> &oC){
	onChange = oC;
}

}
}
