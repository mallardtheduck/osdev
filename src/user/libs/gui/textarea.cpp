#include <gui/textarea.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

#include <iostream>
#include <cmath>
#include <sstream>

namespace btos_api{
namespace gui{

TextArea::TextArea(const gds::Rect &r, const std::string &t) : rect(r) {
	SetText(t);
	auto info = fonts::GetTextAreaFont().Info();
	fontHeight = (info.maxH * fonts::GetTextAreaFontSize()) / info.scale;
}
	
void TextArea::UpdateDisplayState(){
	if(!surf){
		surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		update = true;
	}
	
	if(!lines.size()){
		cursorPos = 0;
		textOffset = 0;
		lines.emplace_back(Line{"", gds::TextMeasurements()});
		return;
	}
	if(curLine >= lines.size()) curLine = lines.size() - 1;
	auto &text = lines[curLine].text;
	auto &textMeasures = lines[curLine].textMeasures;
	
	if(textMeasures.w == 0 || update) textMeasures = surf->MeasureText(text, fonts::GetTextAreaFont(), fonts::GetTextAreaFontSize());
	
	size_t vlines = rect.h / fontHeight;
	while(curLine < lineOffset && lineOffset > 0) --lineOffset;
	while(curLine > lineOffset + vlines && lineOffset < lines.size() - 1) ++lineOffset;
	
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
	
	double textOffsetPxlsD = 0.0;
	double cursorPosPxlsD = 0.5;
	for(size_t i = 0; i < std::max(textOffset, cursorPos) && i < textMeasures.charX.size(); ++i){
		if(i < textOffset) textOffsetPxlsD += textMeasures.charX[i];
		if(i < cursorPos) cursorPosPxlsD += textMeasures.charX[i];
	}
	if(cursorPosPxls == 0.5 && cursorPos == 1 && text.length() == 1) cursorPosPxls = textMeasures.w;
	textOffsetPxls = round(textOffsetPxlsD);
	cursorPosPxls = round(cursorPosPxlsD);
	//std::cout << "UpdateDisplayState: cursorPos: " << cursorPos << " textOffset: " << textOffset << " text.length():" << text.length() << std::endl;//
}
	
EventResponse TextArea::HandleEvent(const wm_Event &e){
	bool updateCursor = false;
	
	if(curLine >= lines.size()) UpdateDisplayState();
	auto &text = lines[curLine].text;
	auto &textMeasures = lines[curLine].textMeasures;
	
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
		}else if(code == (KeyFlags::NonASCII | KeyCodes::Home)){
			cursorPos = 0;
			updateCursor = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::End)){
			cursorPos = text.length();
			updateCursor = true;
		}else if(!(code & KeyFlags::NonASCII)){
			char c = KB_char(e.Key.code);
			auto preText = text;
			if(c == 0x08 && cursorPos > 0){
				text.erase(cursorPos - 1, 1);
				--cursorPos;
				if(onChange) onChange(text);
			}else if(c > 31){
				text.insert(cursorPos, 1, c);
				++cursorPos;
				if(onChange) onChange(text);
			}
			update = (preText != text);
		}
	}else if(e.type == wm_EventType::PointerButtonDown || e.type == wm_EventType::PointerButtonUp){
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
	
	
	if(update || updateCursor) return {true, rect};
	else return {true};
}

void TextArea::Paint(gds::Surface &s){
	UpdateDisplayState();
	
	if(update){
		uint32_t inW = rect.w - 1;
		uint32_t inH = rect.h - 1;
		
		auto bkgCol = colours::GetBackground().Fix(*surf);
		auto txtCol = colours::GetTextAreaText().Fix(*surf);
		auto border = colours::GetBorder().Fix(*surf);
		
		surf->Clear();
		
		surf->BeginQueue();
		surf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		for(size_t i = lineOffset; i < lines.size(); ++i){
			if((i - lineOffset) * fontHeight > rect.h) break;
			
			if(!lines[i].textMeasures.w) lines[i].textMeasures = surf->MeasureText(lines[i].text, fonts::GetTextAreaFont(), fonts::GetTextAreaFontSize());
			
			auto textY = std::max<int32_t>(((fontHeight + lines[i].textMeasures.h) / 2), 0);
			textY += i * fontHeight;
			size_t curTextOffset = 0;
			double curTextOffsetPxls = 0.0;
			for(;curTextOffsetPxls < textOffsetPxls && curTextOffset < lines[i].text.length() && curTextOffset < lines[i].textMeasures.charX.size(); textOffsetPxls += lines[i].textMeasures.charX[textOffset], ++curTextOffset);
			if(curTextOffset < lines[i].text.length()) surf->Text({2, textY}, lines[i].text.substr(curTextOffset), fonts::GetTextAreaFont(), fonts::GetTextAreaFontSize(), txtCol);
		}
		drawing::Border(*surf, {0, 0, inW, inH}, border);
		
		auto topLeft = colours::GetTextAreaLowLight().Fix(*surf);
		auto bottomRight = colours::GetTextAreaHiLight().Fix(*surf);
		drawing::BevelBox(*surf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);

		surf->CommitQueue();
		update = false;
	}
	
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
	
	if(hasFocus){
		auto cursorCol = colours::GetTextCursor().Fix(*surf);
		auto top = (curLine - lineOffset) * fontHeight;
		auto bottom = top + fontHeight;
		s.Line({(int32_t)cursorPosPxls + rect.x, (int32_t)(rect.y + top + 2)}, {(int32_t)cursorPosPxls + rect.x, (int32_t)(rect.y + bottom - 1)}, cursorCol);
	}
}

gds::Rect TextArea::GetPaintRect(){
	return rect;
}

gds::Rect TextArea::GetInteractRect(){
	return rect;
}

uint32_t TextArea::GetSubscribed(){
	return wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown;
}

void TextArea::Focus(){
	hasFocus = true;
}

void TextArea::Blur(){
	hasFocus = false;
}
	
void TextArea::SetText(const std::string &t){
	std::stringstream ss(t);
	std::string l;
	while(std::getline(ss, l)){
		lines.emplace_back(Line{l, gds::TextMeasurements()});
	}
	update = true;
}

std::string TextArea::GetText(){
	std::stringstream ss;
	for(const auto &l : lines){
		ss << l.text << '\n';
	}
	return ss.str();
}
	
void TextArea::OnChange(const std::function<void(const std::string &)> &oC){
	onChange = oC;
}

void TextArea::OnKeyPress(const std::function<bool(uint32_t)> &oKP){
	onKeyPress = oKP;
}

}
}