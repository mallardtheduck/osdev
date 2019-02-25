#include <gui/textbox.hpp>
#include <gui/defaults.hpp>
#include <dev/keyboard.h>

#include <iostream>
#include <cmath>

namespace btos_api{
namespace gui{

TextBox::TextBox(gds::Rect r, const std::string &t) : rect(r), text(t) {}
	
void TextBox::UpdateDisplayState(){
	if(!surf){
		surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		update = true;
	}
	
	textMeasures = surf->MeasureText(text, fonts::GetTextBoxFont(), fonts::GetTextBoxFontSize());
	textY = std::max<int32_t>(((rect.h + textMeasures.h) / 2), 0);
	
	while(true){
		auto textW = rect.w - 5;
		
		size_t vchars = 0;
		double cWidth = 0.0;
		
		for(size_t i = 0; i < textMeasures.charX.size(); ++i){
			if(i >= textOffset && round(cWidth) < textW){
				++vchars;
				cWidth += textMeasures.charX[i];
			}
		}
		
		if(cursorPos - textOffset > vchars - 1){
			++textOffset;
			update = true;
			if(textOffset >= text.length()) break;
		}else if(cursorPos < textOffset && textOffset > 0){
			--textOffset;
			update = true;
		}else break;
	}
	
	
}
	
EventResponse TextBox::HandleEvent(const wm_Event &e){
	bool updateCursor = false;
	if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(onKeyPress && !onKeyPress(e.Key.code)){
			//Do nothing
		}else if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && cursorPos > 0){
			--cursorPos;
			updateCursor = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && cursorPos < text.length()){
			++cursorPos;
			updateCursor = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::Delete) && cursorPos <= text.length()){
			text.erase(cursorPos, 1);
			if(cursorPos > text.length()) cursorPos = text.length();
			update = true;
		}else if(!(code & KeyFlags::NonASCII)){
			char c = KB_char(e.Key.code);
			if(c == 0x08 && cursorPos > 0){
				text.erase(cursorPos - 1, 1);
				--cursorPos;
				if(onChange) onChange();
				update = true;
			}else if(c > 31){
				text.insert(cursorPos, 1, c);
				++cursorPos;
				if(onChange) onChange();
				update = true;
			}
		}
	}
	if(update || updateCursor) return {true, rect};
	else return {true};
}

void TextBox::Paint(gds::Surface &s){
	UpdateDisplayState();
	
	if(update){
		int32_t inW = rect.w - 1;
		int32_t inH = rect.h - 1;
		
		auto bkgCol = colours::GetBackground().Fix(*surf);
		auto txtCol = colours::GetTextBoxText().Fix(*surf);
		auto border = colours::GetBorder().Fix(*surf);
		
		surf->BeginQueue();
		surf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		if(textOffset < text.length()) surf->Text({2, textY}, text.substr(textOffset), fonts::GetTextBoxFont(), fonts::GetTextBoxFontSize(), txtCol);
		surf->Line({1, 0}, {inW - 1, 0}, border);
		surf->Line({0, 1}, {0, inH - 1}, border);
		surf->Line({1, inH}, {inW - 1, inH}, border);
		surf->Line({inW, 1}, {inW, inH - 1}, border);
		
		auto topLeft = colours::GetTextBoxLowLight().Fix(*surf);
		auto bottomRight = colours::GetTextBoxHiLight().Fix(*surf);
		
		surf->Line({1, 1}, {inW - 1, 1}, topLeft);
		surf->Line({1, 1}, {1, inH - 1}, topLeft);
		surf->Line({1, inH - 1}, {inW - 1, inH - 1}, bottomRight);
		surf->Line({inW - 1, 1}, {inW - 1, inH - 1}, bottomRight);

		surf->CommitQueue();
		update = false;
	}
	
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
	
	if(hasFocus){
		auto cusorCol = colours::GetTextCursor().Fix(*surf);
		
		double cursorXd = 0.0;
		for(size_t i = textOffset; i < (cursorPos + textOffset) && i < textMeasures.charX.size(); ++i){
			cursorXd += textMeasures.charX[i];
		}
		int32_t cursorX = round(cursorXd);
		s.Line({(int32_t)cursorX + rect.x, (int32_t)2 + rect.y}, {(int32_t)cursorX + rect.x, (int32_t)(rect.h - 3) + rect.y}, cusorCol);
	}
}

gds::Rect TextBox::GetPaintRect(){
	return rect;
}

gds::Rect TextBox::GetInteractRect(){
	return rect;
}

uint32_t TextBox::GetSubscribed(){
	return wm_KeyboardEvents | wm_EventType::PointerButtonUp;
}

void TextBox::Focus(){
	hasFocus = true;
}

void TextBox::Blur(){
	hasFocus = false;
}
	
void TextBox::SetText(const std::string &t){
	text = t;
	update = true;
}

std::string TextBox::GetText(){
	return text;
}
	
void TextBox::OnChange(const std::function<void()> &oC){
	onChange = oC;
}

void TextBox::OnKeyPress(const std::function<bool(uint32_t)> &oKP){
	onKeyPress = oKP;
}

}
}