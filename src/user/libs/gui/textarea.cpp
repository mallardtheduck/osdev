#include <gui/textarea.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

#include <iostream>
#include <cmath>
#include <sstream>

namespace btos_api{
namespace gui{
	
const auto scrollbarSize = 17;

TextArea::TextArea(const gds::Rect &r, const std::string &t, bool scrollbars) : 
	outerRect(r),
	rect(scrollbars ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : r)
{
	if(scrollbars){
		hscroll.reset(new Scrollbar({outerRect.x, outerRect.y + (int32_t)outerRect.h - scrollbarSize, outerRect.w - scrollbarSize, scrollbarSize}, 1, 1, 1, 1, true));
		IControl::BindToParent(*hscroll);
		vscroll.reset(new Scrollbar({outerRect.x + (int32_t)outerRect.w - scrollbarSize, outerRect.y, scrollbarSize, outerRect.h - scrollbarSize}, 1, 1, 1, 1, false));
		IControl::BindToParent(*vscroll);
		
		hscroll->OnChange([this] (uint32_t v) {
			if(v != cursorPos) update = true;
			cursorPos = v;
		});
		
		vscroll->OnChange([this] (uint32_t v) {
			if(v != cursorLine) update = true;
			cursorLine = v;
		});
	}
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
	if(cursorLine >= lines.size()) cursorLine = lines.size() - 1;
	auto &text = lines[cursorLine].text;
	auto &textMeasures = lines[cursorLine].textMeasures;
	
	if(textMeasures.w == 0 || update) textMeasures = surf->MeasureText(text, fonts::GetTextAreaFont(), fonts::GetTextAreaFontSize());
	
	auto oldLineOffset = lineOffset;
	size_t vlines = rect.h / fontHeight;
	while(cursorLine < lineOffset && lineOffset > 0) --lineOffset;
	while(cursorLine >= lineOffset + vlines && lineOffset < lines.size() - 1) ++lineOffset;
	if(oldLineOffset != lineOffset) update = true;
	
	if(vscroll){
		vscroll->SetLines(std::max<uint32_t>(lines.size() - 1, 1));
		vscroll->SetPage(vlines);
		vscroll->SetValue(cursorLine);
	}
	
	size_t vchars;
	auto oldTextOffset = textOffset;
	textOffset = 0;
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
			if(textOffset >= text.length()) break;
		}else if(underflow && cursorPos < textOffset + 1){
			--textOffset;
		}else if(textOffset > text.length()){
			--textOffset;
		}else break;
	}
	if(textOffset != oldTextOffset) update = true;
	
	if(hscroll){
		hscroll->SetLines(std::max<uint32_t>(text.length(), 1));
		hscroll->SetPage(vchars);
		hscroll->SetValue(cursorPos);
	}
	
	double textOffsetPxlsD = 0.0;
	double cursorPosPxlsD = 0.5;
	for(size_t i = 0; i < std::max(textOffset, cursorPos) && i < textMeasures.charX.size(); ++i){
		if(i < textOffset) textOffsetPxlsD += textMeasures.charX[i];
		else if(i < cursorPos) cursorPosPxlsD += textMeasures.charX[i];
	}
	textOffsetPxls = round(textOffsetPxlsD);
	cursorPosPxls = round(cursorPosPxlsD);
	if(cursorPosPxlsD == 0.5 && cursorPos == 1 && text.length() == 1) cursorPosPxls = textMeasures.w;
	//std::cout << "UpdateDisplayState: cursorPos: " << cursorPos << " cursorPosPxls: " << cursorPosPxls << " textOffset: " << textOffset << " textOffsetPxls: " << textOffsetPxls << " text.length(): " << text.length() << std::endl;//
}

size_t TextArea::MapPosToLine(uint32_t pxlPos, const TextArea::Line &line){
	size_t ret = line.text.length();
	double pxlCount = 0;
	for(size_t i = 0; i < line.textMeasures.charX.size(); ++i){
		pxlCount += line.textMeasures.charX[i];
		if(pxlCount > pxlPos){
			ret = i;
			break;
		}else ret = i + 1;
	}
	return ret;
}

void TextArea::MergeLines(size_t a, size_t b){
	auto &la = lines[a];
	auto &lb = lines[b];
	la.text += lb.text;
	la.textMeasures = gds::TextMeasurements();
	auto it = lines.begin();
	std::advance(it, b);
	lines.erase(it);
}

void TextArea::SplitLine(size_t i, size_t pos){
	auto &l = lines[i];
	std::string ntext = pos < l.text.length() ? l.text.substr(pos) : "";
	l.text = l.text.substr(0, pos);
	l.textMeasures = gds::TextMeasurements();
	auto it = lines.begin();
	std::advance(it, i + 1);
	lines.emplace(it, Line{ntext, gds::TextMeasurements()});
}
	
EventResponse TextArea::HandleEvent(const wm_Event &e){
	bool updateCursor = false;
	bool handled = false;
	
	if(cursorLine >= lines.size()) UpdateDisplayState();
	auto &text = lines[cursorLine].text;
	
	if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(onKeyPress){
			if(onKeyPress(e.Key.code)) handled = true;
		}
		if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && cursorPos > 0){
			perferredPosPxls = 0;
			--cursorPos;
			updateCursor = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && cursorLine > 0){
			perferredPosPxls = 0;
			--cursorLine;
			cursorPos = lines[cursorLine].text.length();
			updateCursor = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && cursorPos < text.length()){
			perferredPosPxls = 0;
			++cursorPos;
			updateCursor = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && cursorLine < lines.size() - 1){
			perferredPosPxls = 0;
			cursorPos = 0;
			++cursorLine;
			updateCursor = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::DownArrow) && cursorLine < lines.size() - 1){
			++cursorLine;
			if(!perferredPosPxls) perferredPosPxls = textOffsetPxls + cursorPosPxls;
			cursorPos = MapPosToLine(perferredPosPxls, lines[cursorLine]);
			updateCursor = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::UpArrow) && cursorLine > 0){
			--cursorLine;
			if(!perferredPosPxls) perferredPosPxls = textOffsetPxls + cursorPosPxls;
			cursorPos = MapPosToLine(perferredPosPxls, lines[cursorLine]);
			updateCursor = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp) && cursorLine > 0){
			size_t vlines = rect.h / fontHeight;
			cursorLine -= std::min(cursorLine, vlines);
			if(!perferredPosPxls) perferredPosPxls = textOffsetPxls + cursorPosPxls;
			cursorPos = MapPosToLine(perferredPosPxls, lines[cursorLine]);
			updateCursor = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown) && cursorLine < lines.size() - 1){
			size_t vlines = rect.h / fontHeight;
			cursorLine = std::min(cursorLine + vlines, lines.size() - 1);
			if(!perferredPosPxls) perferredPosPxls = textOffsetPxls + cursorPosPxls;
			cursorPos = MapPosToLine(perferredPosPxls, lines[cursorLine]);
			updateCursor = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::Delete) && cursorPos < text.length()){
			perferredPosPxls = 0;
			text.erase(cursorPos, 1);
			if(cursorPos > text.length()) cursorPos = text.length();
			if(onChange) onChange(text);
			update = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::Delete) && cursorLine < lines.size() - 1){
			perferredPosPxls = 0;
			MergeLines(cursorLine, cursorLine + 1);
			if(onChange) onChange(text);
			update = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::Home)){
			perferredPosPxls = 0;
			cursorPos = 0;
			updateCursor = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::End)){
			perferredPosPxls = 0;
			cursorPos = text.length();
			updateCursor = true;
			handled = true;
		}else if(!(code & KeyFlags::NonASCII)){
			perferredPosPxls = 0;
			char c = KB_char(e.Key.code);
			auto preText = text;
			if(c == 0x08 && cursorPos > 0){
				text.erase(cursorPos - 1, 1);
				if(onChange) onChange(text);
				--cursorPos;
				handled = true;
				update = true;
			}else if(c == 0x08 && cursorLine > 0){
				--cursorLine;
				cursorPos = lines[cursorLine].text.length();
				MergeLines(cursorLine, cursorLine + 1);
				if(onChange) onChange(text);
				update = true;
				handled = true;
			}else if(c == '\n'){
				SplitLine(cursorLine, cursorPos);
				if(onChange) onChange(text);
				++cursorLine;
				cursorPos = 0;
				update = true;
				handled = true;
			}else if(c > 31){
				text.insert(cursorPos, 1, c);
				if(onChange) onChange(text);
				++cursorPos;
				update = true;
				handled = true;
			}
			update = update || (preText != text);
		}
	}else if(e.type & wm_PointerEvents){
		handled = true;
		if(InRect(e.Pointer.x, e.Pointer.y, rect) && (e.type == wm_EventType::PointerButtonDown || e.type == wm_EventType::PointerButtonUp)){
			perferredPosPxls = 0;
			auto pointerX = e.Pointer.x - rect.x;
			auto pointerY = e.Pointer.y - rect.y;
			cursorLine = (pointerY / fontHeight) + lineOffset;
			if(cursorLine >= lines.size()) cursorLine = lines.size() - 1;
			auto &line = lines[cursorLine];
			double xpos = 0.5;
			auto newCursorPos = cursorPos;
			for(size_t i = textOffset; i < line.textMeasures.charX.size(); ++i){
				xpos += line.textMeasures.charX[i];
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
		}else if(hscroll && InRect(e.Pointer.x, e.Pointer.y, hscroll->GetInteractRect()) && (e.type & hscroll->GetSubscribed())){
			auto oldCursorPos = cursorPos;
			auto ret = hscroll->HandleEvent(e);
			if(cursorPos == oldCursorPos) return ret;
		}else if(vscroll && InRect(e.Pointer.x, e.Pointer.y, vscroll->GetInteractRect()) && (e.type & vscroll->GetSubscribed())){
			auto oldCursorLine = cursorLine;
			auto ret = vscroll->HandleEvent(e);
			if(cursorLine == oldCursorLine) return ret;
		}
	}
	
	
	if(update || updateCursor){
		IControl::Paint(outerRect);
	}
	return {handled};
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
			textY += (i - lineOffset) * fontHeight;
			surf->Text({2 - (int32_t)textOffsetPxls, textY}, lines[i].text, fonts::GetTextAreaFont(), fonts::GetTextAreaFontSize(), txtCol);
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
		auto top = (cursorLine - lineOffset) * fontHeight;
		auto bottom = top + fontHeight;
		s.Line({(int32_t)cursorPosPxls + rect.x, (int32_t)(rect.y + top + 2)}, {(int32_t)cursorPosPxls + rect.x, (int32_t)(rect.y + bottom - 1)}, cursorCol);
	}
	
	if(hscroll) hscroll->Paint(s);
	if(vscroll) vscroll->Paint(s);
}

gds::Rect TextArea::GetPaintRect(){
	return outerRect;
}

gds::Rect TextArea::GetInteractRect(){
	return outerRect;
}

uint32_t TextArea::GetSubscribed(){
	auto ret = wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown;
	if(hscroll) ret |= hscroll->GetSubscribed();
	if(vscroll) ret |= vscroll->GetSubscribed();
	return ret;
}

void TextArea::Focus(){
	hasFocus = true;
	IControl::Paint(outerRect);
}

void TextArea::Blur(){
	hasFocus = false;
	IControl::Paint(outerRect);
}
	
void TextArea::SetText(const std::string &t){
	std::stringstream ss(t);
	std::string l;
	while(std::getline(ss, l)){
		lines.emplace_back(Line{l, gds::TextMeasurements()});
	}
	update = true;
	IControl::Paint(outerRect);
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

uint32_t TextArea::GetFlags(){
	return 0;
}

}
}
