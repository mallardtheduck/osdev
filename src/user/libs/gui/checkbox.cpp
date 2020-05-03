#include <gui/checkbox.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

namespace btos_api{
namespace gui{
	
const auto checkSize = 15;

Checkbox::Checkbox(const gds::Rect &r, const std::string &t, bool v) : rect(r), text(t), value(v) {}
	
EventResponse Checkbox::HandleEvent(const wm_Event &e){
	if(e.type == wm_EventType::PointerButtonUp){
		value = !value;
		RaiseChangeEvent();
	}
	if(e.type == wm_EventType::Keyboard){
		uint16_t code = KB_code(e.Key.code);
		if(!(code & KeyFlags::NonASCII)){
			char c = KB_char(e.Key.code);
			if(c == ' ' || c == '\n'){
				value = !value;
				RaiseChangeEvent();
				IControl::Paint(rect);
				return {true};
			}
		}
		return {false};
	}
	IControl::Paint(rect);
	return {true};
}

void Checkbox::Paint(gds::Surface &s){
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
		bkSurf->Compress();
	}
	
	s.Blit(*bkSurf, {0, 0, rect.w, rect.h}, rect);
	
	if(value){
		auto chkCol = colours::GetCheckboxCheck().Fix(s);
		auto chkTop = chkY;
		auto chkBottom = chkY + checkSize;
		
		s.Line({rect.x + 5, rect.y + chkTop + 5}, {rect.x + checkSize - 3, rect.y +  chkBottom - 4}, chkCol, 2);
		s.Line({rect.x + 5, rect.y +  chkBottom - 4}, {rect.x + checkSize - 3, rect.y + chkTop + 5}, chkCol, 2);
	}
	
	if(focus){
		auto focusCol = colours::GetCheckboxFocus().Fix(s);
		
		int32_t boxTop = std::max<int32_t>(std::min<int32_t>(chkY - 1, (rect.h - textMeasures.h) / 2), 0);
		int32_t boxLeft = 0;
		uint32_t boxWidth = textMeasures.w + checkSize + 3;
		if(boxLeft + boxWidth > inW) boxWidth = inW - boxLeft;
		uint32_t boxHeight = std::max<int32_t>(textMeasures.h, checkSize + 3);
		if(boxTop + boxHeight > inH) boxHeight = inH - boxTop;
		s.Box({rect.x + boxLeft, rect.y + boxTop, boxWidth, boxHeight}, focusCol, focusCol);
	}
		
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect Checkbox::GetPaintRect(){
	return rect;
}

gds::Rect Checkbox::GetInteractRect(){
	if(textMeasures.w){
		uint32_t inW = rect.w - 1;
		uint32_t inH = rect.h - 1;
		int32_t chkY = std::max<int32_t>((rect.h - checkSize) / 2, 0);
		
		int32_t boxTop = std::max<int32_t>(std::min<int32_t>(chkY - 1, (rect.h - textMeasures.h) / 2), 0);
		int32_t boxLeft = 0;
		uint32_t boxWidth = textMeasures.w + checkSize + 3;
		if(boxLeft + boxWidth > inW) boxWidth = inW - boxLeft;
		uint32_t boxHeight = std::max<int32_t>(textMeasures.h, checkSize + 3);
		if(boxTop + boxHeight > inH) boxHeight = inH - boxTop;
		return {rect.x + boxLeft, rect.y + boxTop, boxWidth, boxHeight};
	}else return rect;
}

uint32_t Checkbox::GetSubscribed(){
	return wm_EventType::PointerButtonUp | wm_EventType::Keyboard;
}

void Checkbox::Focus(){
	focus = true;
	IControl::Paint(rect);
}
void Checkbox::Blur(){
	focus = false;
	IControl::Paint(rect);
}
	
void Checkbox::SetText(const std::string &t){
	text = t;
	bkSurf.reset();
	IControl::Paint(rect);
}

bool Checkbox::GetValue(){
	return value;
}

uint32_t Checkbox::GetFlags(){
	return 0;
}

void Checkbox::Enable(){
	if(!enabled){
		enabled = true;
		IControl::Paint(rect);
	}
}

void Checkbox::Disable(){
	if(enabled){
		enabled = false;
		IControl::Paint(rect);
	}
}

bool Checkbox::IsEnabled(){
	return enabled;
}

void Checkbox::SetPosition(const gds::Rect &r){
	rect = r;
	bkSurf.reset();
}

void Checkbox::SetValue(bool v){
	if(value != v){
		value = v;
		IControl::Paint(rect);
	}
}

}
}
