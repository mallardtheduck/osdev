#include <gui/textbox.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

#include <iostream>
#include <cmath>

namespace btos_api{
namespace gui{

TextBox::TextBox(const gds::Rect &r, const std::string &t) : rect(r), text(t) {}
	
void TextBox::UpdateDisplayState(){
	if(!surf){
		surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		update = true;
	}
	
	if(textMeasures.w == 0 || update) textMeasures = surf->MeasureText(text, fonts::GetTextBoxFont(), fonts::GetTextBoxFontSize());
	textY = std::max<int32_t>(((rect.h + textMeasures.h) / 2), 0);
	
	size_t vchars;
	while(true){
		auto textW = rect.w - 5;
		
		vchars = 0;
		double cWidth = 0.0;
		bool overflow = false;
		bool underflow = false;
		
		for(size_t i = 0; i < textMeasures.charX.size(); ++i){
			if(i >= textOffset){
				++vchars;
				cWidth += textMeasures.charX[i];
				if(cWidth > textW){
					overflow = true;
					break;
				}
			}else{
				underflow = true;
			}
		}
		
		if(overflow && cursorPos > textOffset + std::max((int32_t)vchars - 2, 0)){
			++textOffset;
			update = true;
			if(textOffset >= text.length()) break;
		}else if(underflow && cursorPos < textOffset + 1){
			--textOffset;
			update = true;
		}else if(textOffset > text.length()){
			--textOffset;
			update = true;
		}else break;
	}
	//std::cout << "UpdateDisplayState: cursorPos: " << cursorPos << " textOffset: " << textOffset << " text.length():" << text.length() << std::endl;//
}
	
EventResponse TextBox::HandleEvent(const wm_Event &e){
	bool updateCursor = false;
	bool handled = false;
	if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(onKeyPress){
			if(onKeyPress(e.Key.code)) handled = true;
		}
		if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && cursorPos > 0){
			--cursorPos;
			updateCursor = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && cursorPos < text.length()){
			++cursorPos;
			updateCursor = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::Delete) && cursorPos <= text.length()){
			text.erase(cursorPos, 1);
			if(onChange) onChange(text);
			if(cursorPos > text.length()) cursorPos = text.length();
			update = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::Home)){
			cursorPos = 0;
			updateCursor = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::End)){
			cursorPos = text.length();
			updateCursor = true;
			handled = true;
		}else if(!(code & KeyFlags::NonASCII)){
			char c = KB_char(e.Key.code);
			auto preText = text;
			if(c == 0x08 && cursorPos > 0){
				text.erase(cursorPos - 1, 1);
				if(onChange) onChange(text);
				--cursorPos;
				handled = true;
			}else if(c > 31){
				text.insert(cursorPos, 1, c);
				if(onChange) onChange(text);
				++cursorPos;
				handled = true;
			}
			update = (preText != text);
		}
	}else if(e.type == wm_EventType::PointerButtonDown || e.type == wm_EventType::PointerButtonUp){
		handled = true;
		auto pointerX = e.Pointer.x - rect.x;
		double xpos = 0.5;
		auto newCursorPos = cursorPos;
		for(size_t i = textOffset; i < textMeasures.charX.size(); ++i){
			xpos += textMeasures.charX[i];
			if(xpos > pointerX){
				newCursorPos = i;
				break;
			}else{
				newCursorPos = i + 1;
			}
		}
		if(newCursorPos != cursorPos){
			cursorPos = newCursorPos;
			updateCursor = true;
		}
	}
	
	
	if(update || updateCursor) GetContainer().Paint(rect);
	return {handled};
}

void TextBox::Paint(gds::Surface &s){
	UpdateDisplayState();
	
	if(update){
		uint32_t inW = rect.w - 1;
		uint32_t inH = rect.h - 1;
		
		auto bkgCol = colours::GetBackground().Fix(*surf);
		auto txtCol = colours::GetTextBoxText().Fix(*surf);
		auto border = colours::GetBorder().Fix(*surf);
		
		surf->Clear();
		
		surf->BeginQueue();
		surf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		if(textOffset < text.length()) surf->Text({2, textY}, text.substr(textOffset), fonts::GetTextBoxFont(), fonts::GetTextBoxFontSize(), txtCol);
		drawing::Border(*surf, {0, 0, inW, inH}, border);
		
		auto topLeft = colours::GetTextBoxLowLight().Fix(*surf);
		auto bottomRight = colours::GetTextBoxHiLight().Fix(*surf);
		drawing::BevelBox(*surf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);

		surf->CommitQueue();
		update = false;
	}
	
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
	
	if(hasFocus){
		auto cursorCol = colours::GetTextCursor().Fix(*surf);
		
		double cursorXd = 0.5;
		for(size_t i = textOffset; i < cursorPos && i < textMeasures.charX.size(); ++i){
			cursorXd += textMeasures.charX[i];
		}
		if(cursorXd == 0.5 && text.length() == 1 && cursorPos == 1) cursorXd = textMeasures.w;
		int32_t cursorX = round(cursorXd);
		s.Line({(int32_t)cursorX + rect.x, (int32_t)2 + rect.y}, {(int32_t)cursorX + rect.x, (int32_t)(rect.h - 3) + rect.y}, cursorCol);
	}
}

gds::Rect TextBox::GetPaintRect(){
	return rect;
}

gds::Rect TextBox::GetInteractRect(){
	return rect;
}

uint32_t TextBox::GetSubscribed(){
	return wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown;
}

void TextBox::Focus(){
	hasFocus = true;
	GetContainer().Paint(rect);
}

void TextBox::Blur(){
	hasFocus = false;
	GetContainer().Paint(rect);
}
	
void TextBox::SetText(const std::string &t){
	text = t;
	update = true;
	GetContainer().Paint(rect);
}

std::string TextBox::GetText(){
	return text;
}
	
void TextBox::OnChange(const std::function<void(const std::string &)> &oC){
	onChange = oC;
}

void TextBox::OnKeyPress(const std::function<bool(uint32_t)> &oKP){
	onKeyPress = oKP;
}

uint32_t TextBox::GetFlags(){
	return 0;
}

}
}
