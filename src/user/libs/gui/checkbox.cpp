#include <gui/checkbox.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

namespace btos_api{
namespace gui{

struct CheckboxImpl{
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> bkSurf;
	
	bool value;
	gds::TextMeasurements textMeasures;
	bool focus = false;
	bool enabled = true;
};

PIMPL_IMPL(CheckboxImpl);

const auto checkSize = 15;

Checkbox::Checkbox(const gds::Rect &r, const std::string &t, bool v) : impl(new CheckboxImpl){
	impl->rect = r;
	impl->text = t;
	impl->value = v;
}
	
EventResponse Checkbox::HandleEvent(const wm_Event &e){
	if(e.type == wm_EventType::PointerButtonUp){
		impl->value = !impl->value;
		RaiseChangeEvent();
	}
	if(e.type == wm_EventType::Keyboard){
		uint16_t code = KB_code(e.Key.code);
		if(!(code & KeyFlags::NonASCII)){
			char c = KB_char(e.Key.code);
			if(c == ' ' || c == '\n'){
				impl->value = !impl->value;
				RaiseChangeEvent();
				IControl::Paint(impl->rect);
				return {true};
			}
		}
		return {false};
	}
	IControl::Paint(impl->rect);
	return {true};
}

void Checkbox::Paint(gds::Surface &s){
	uint32_t inW = impl->rect.w - 1;
	uint32_t inH = impl->rect.h - 1;
	int32_t chkY = std::max<int32_t>((impl->rect.h - checkSize) / 2, 0);
	
	if(!impl->bkSurf){
		impl->bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, impl->rect.w, impl->rect.h, 100, gds_ColourType::True));
		impl->bkSurf->BeginQueue();
		
		impl->textMeasures = impl->bkSurf->MeasureText(impl->text, fonts::GetCheckboxFont(), fonts::GetCheckboxTextSize());
		auto bkgCol = colours::GetBackground().Fix(*impl->bkSurf);
		auto txtCol = colours::GetCheckboxText().Fix(*impl->bkSurf);
			
		int32_t textX = checkSize + 3;
		int32_t textY = std::max<int32_t>(((impl->rect.h + impl->textMeasures.h) / 2), 0);
		
		impl->bkSurf->Box(impl->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		impl->bkSurf->Text({textX, textY}, impl->text, fonts::GetCheckboxFont(), fonts::GetCheckboxTextSize(), txtCol);
		
		auto border = colours::GetBorder().Fix(*impl->bkSurf);
		drawing::Border(*impl->bkSurf, {1, chkY, checkSize, checkSize}, border);
		
		auto topLeft = colours::GetCheckboxLowLight().Fix(*impl->bkSurf);
		auto bottomRight = colours::GetCheckboxHiLight().Fix(*impl->bkSurf);
		drawing::BevelBox(*impl->bkSurf, {2, chkY + 1, checkSize - 2, checkSize - 2}, topLeft, bottomRight);
		
		impl->bkSurf->CommitQueue();
		impl->bkSurf->Compress();
	}
	
	s.Blit(*impl->bkSurf, impl->rect.AtZero(), impl->rect);
	
	if(impl->value){
		auto chkCol = colours::GetCheckboxCheck().Fix(s);
		auto chkTop = chkY;
		auto chkBottom = chkY + checkSize;
		
		s.Line({impl->rect.x + 5, impl->rect.y + chkTop + 5}, {impl->rect.x + checkSize - 3, impl->rect.y +  chkBottom - 4}, chkCol, 2);
		s.Line({impl->rect.x + 5, impl->rect.y +  chkBottom - 4}, {impl->rect.x + checkSize - 3, impl->rect.y + chkTop + 5}, chkCol, 2);
	}
	
	if(impl->focus){
		auto focusCol = colours::GetCheckboxFocus().Fix(s);
		
		int32_t boxTop = std::max<int32_t>(std::min<int32_t>(chkY - 1, (impl->rect.h - impl->textMeasures.h) / 2), 0);
		int32_t boxLeft = 0;
		uint32_t boxWidth = impl->textMeasures.w + checkSize + 3;
		if(boxLeft + boxWidth > inW) boxWidth = inW - boxLeft;
		uint32_t boxHeight = std::max<int32_t>(impl->textMeasures.h, checkSize + 3);
		if(boxTop + boxHeight > inH) boxHeight = inH - boxTop;
		s.Box({impl->rect.x + boxLeft, impl->rect.y + boxTop, boxWidth, boxHeight}, focusCol, focusCol);
	}
		
	if(!impl->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(impl->rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect Checkbox::GetPaintRect(){
	return impl->rect;
}

gds::Rect Checkbox::GetInteractRect(){
	if(impl->textMeasures.w){
		uint32_t inW = impl->rect.w - 1;
		uint32_t inH = impl->rect.h - 1;
		int32_t chkY = std::max<int32_t>((impl->rect.h - checkSize) / 2, 0);
		
		int32_t boxTop = std::max<int32_t>(std::min<int32_t>(chkY - 1, (impl->rect.h - impl->textMeasures.h) / 2), 0);
		int32_t boxLeft = 0;
		uint32_t boxWidth = impl->textMeasures.w + checkSize + 3;
		if(boxLeft + boxWidth > inW) boxWidth = inW - boxLeft;
		uint32_t boxHeight = std::max<int32_t>(impl->textMeasures.h, checkSize + 3);
		if(boxTop + boxHeight > inH) boxHeight = inH - boxTop;
		return {impl->rect.x + boxLeft, impl->rect.y + boxTop, boxWidth, boxHeight};
	}else return impl->rect;
}

uint32_t Checkbox::GetSubscribed(){
	return wm_EventType::PointerButtonUp | wm_EventType::Keyboard;
}

void Checkbox::Focus(){
	impl->focus = true;
	IControl::Paint(impl->rect);
}
void Checkbox::Blur(){
	impl->focus = false;
	IControl::Paint(impl->rect);
}
	
void Checkbox::SetText(const std::string &t){
	impl->text = t;
	impl->bkSurf.reset();
	IControl::Paint(impl->rect);
}

bool Checkbox::GetValue(){
	return impl->value;
}

uint32_t Checkbox::GetFlags(){
	return 0;
}

void Checkbox::Enable(){
	if(!impl->enabled){
		impl->enabled = true;
		IControl::Paint(impl->rect);
	}
}

void Checkbox::Disable(){
	if(impl->enabled){
		impl->enabled = false;
		IControl::Paint(impl->rect);
	}
}

bool Checkbox::IsEnabled(){
	return impl->enabled;
}

void Checkbox::SetPosition(const gds::Rect &r){
	impl->rect = r;
	impl->bkSurf.reset();
}

void Checkbox::SetValue(bool v){
	if(impl->value != v){
		impl->value = v;
		IControl::Paint(impl->rect);
	}
}

}
}
