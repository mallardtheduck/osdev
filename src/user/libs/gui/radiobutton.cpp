#include <gui/radiobutton.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

namespace btos_api{
namespace gui{
	
const auto checkSize = 15;

struct RadioButtonImpl{
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> bkSurf;
	
	bool value;
	gds::TextMeasurements textMeasures;
	bool focus = false;
	bool enabled = true;
};
PIMPL_IMPL(RadioButtonImpl);

RadioButton::RadioButton(const gds::Rect &r, const std::string &t, bool v) : im(new RadioButtonImpl){
	im->rect = r; im->text = t; im->value = v;
}
	
EventResponse RadioButton::HandleEvent(const wm_Event &e){
	if(e.type == wm_EventType::PointerButtonUp){
		auto oldValue = im->value;
		im->value = true;
		if(im->value != oldValue){
			RaiseChangeEvent();
		}
		if(getAllRects){ 
			auto allRects = getAllRects();
			for(auto &rect : allRects) IControl::Paint(rect);
		}
		else IControl::Paint(im->rect);
		return {true};
	}
	if(e.type == wm_EventType::Keyboard){
		uint16_t code = KB_code(e.Key.code);
		if(!(code & KeyFlags::NonASCII)){
			char c = KB_char(e.Key.code);
			if(c == ' ' || c == '\n'){
				auto oldValue = im->value;
				im->value = true;
				if(im->value != oldValue){
					RaiseChangeEvent();
				}
				if(getAllRects){ 
					auto allRects = getAllRects();
					for(auto &rect : allRects) IControl::Paint(rect);
				}
				else IControl::Paint(im->rect);
				return {true};
			}
		}
		return {false};
	}
	return {true};
}

void RadioButton::Paint(gds::Surface &s){
	uint32_t inW = im->rect.w - 1;
	uint32_t inH = im->rect.h - 1;
	int32_t chkY = std::max<int32_t>((im->rect.h - checkSize) / 2, 0);
	
	if(!im->bkSurf){
		im->bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
		im->bkSurf->BeginQueue();
		
		im->textMeasures = im->bkSurf->MeasureText(im->text, fonts::GetRadioButtonFont(), fonts::GetRadioButtonTextSize());
		auto bkgCol = colours::GetBackground().Fix(*im->bkSurf);
		auto txtCol = colours::GetRadioButtonText().Fix(*im->bkSurf);
			
		int32_t textX = checkSize + 3;
		int32_t textY = std::max<int32_t>(((im->rect.h + im->textMeasures.h) / 2), 0);
		
		im->bkSurf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		im->bkSurf->Text({textX, textY}, im->text, fonts::GetRadioButtonFont(), fonts::GetRadioButtonTextSize(), txtCol);
		
		auto cx = (checkSize / 2) + 1;
		auto cy = chkY + (checkSize / 2);
		
		auto topLeft = colours::GetRadioButtonLowLight().Fix(*im->bkSurf);
		auto bottomRight = colours::GetRadioButtonHiLight().Fix(*im->bkSurf);
		im->bkSurf->Arc({cx, cy, checkSize - 1, checkSize - 1}, 135, 315, topLeft, topLeft, 1);
		im->bkSurf->Arc({cx, cy, checkSize - 1, checkSize - 1}, 315, 135, bottomRight, topLeft, 1);
		
		auto border = colours::GetBorder().Fix(*im->bkSurf);
		im->bkSurf->Ellipse({cx, cy, checkSize, checkSize}, border, border);
		
		im->bkSurf->CommitQueue();
		im->bkSurf->Compress();
	}
	
	s.Blit(*im->bkSurf, im->rect.AtZero(), im->rect);
	
	if(im->value){
		auto chkCol = colours::GetRadioButtonCheck().Fix(s);
		auto cx = im->rect.x + (checkSize / 2) + 1;
		auto cy = im->rect.y + chkY + (checkSize / 2);
		
		s.Ellipse({cx, cy, checkSize - 8, checkSize - 8}, chkCol, chkCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
	
	if(im->focus){
		auto focusCol = colours::GetRadioButtonFocus().Fix(s);
		
		int32_t boxTop = std::max<int32_t>(std::min<int32_t>(chkY - 1, (im->rect.h - im->textMeasures.h) / 2), 0);
		int32_t boxLeft = 0;
		uint32_t boxWidth = im->textMeasures.w + checkSize + 3;
		if(boxLeft + boxWidth > inW) boxWidth = inW - boxLeft;
		uint32_t boxHeight = std::max<int32_t>(im->textMeasures.h, checkSize + 3);
		if(boxTop + boxHeight > inH) boxHeight = inH - boxTop;
		s.Box({im->rect.x + boxLeft, im->rect.y + boxTop, boxWidth, boxHeight}, focusCol, focusCol);
	}
	
	if(!im->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(im->rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect RadioButton::GetPaintRect(){
	return im->rect;
}

gds::Rect RadioButton::GetInteractRect(){
	if(im->textMeasures.w){
		uint32_t inW = im->rect.w - 1;
		uint32_t inH = im->rect.h - 1;
		int32_t chkY = std::max<int32_t>((im->rect.h - checkSize) / 2, 0);
		
		int32_t boxTop = std::max<int32_t>(std::min<int32_t>(chkY - 1, (im->rect.h - im->textMeasures.h) / 2), 0);
		int32_t boxLeft = 0;
		uint32_t boxWidth = im->textMeasures.w + checkSize + 3;
		if(boxLeft + boxWidth > inW) boxWidth = inW - boxLeft;
		uint32_t boxHeight = std::max<int32_t>(im->textMeasures.h, checkSize + 3);
		if(boxTop + boxHeight > inH) boxHeight = inH - boxTop;
		return {im->rect.x + boxLeft, im->rect.y + boxTop, boxWidth, boxHeight};
	}else return im->rect;
}

uint32_t RadioButton::GetSubscribed(){
	return wm_EventType::PointerButtonUp | wm_EventType::Keyboard;
}

void RadioButton::Focus(){
	im->focus = true;
	IControl::Paint(im->rect);
}
void RadioButton::Blur(){
	im->focus = false;
	IControl::Paint(im->rect);
}
	
void RadioButton::SetText(const std::string &t){
	im->text = t;
	im->bkSurf.reset();
	IControl::Paint(im->rect);
}

void RadioButton::SetValue(bool v){
	im->value = v;
	IControl::Paint(im->rect);
}

bool RadioButton::GetValue(){
	return im->value;
}

uint32_t RadioButton::GetFlags(){
	return 0;
}

void RadioButton::Enable(){
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(im->rect);
	}
}

void RadioButton::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(im->rect);
	}
}

bool RadioButton::IsEnabled(){
	return im->enabled;
}

void RadioButton::SetPosition(const gds::Rect &r){
	im->rect = r;
	im->bkSurf.reset();
}

}
}
