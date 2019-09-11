#include <gui/textarea.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>

namespace btos_api{
namespace gui{
	
const auto scrollbarSize = 17;

TextArea::TextArea(const gds::Rect &r, const std::string &t, bool scrollbars) : 
	outerRect(r),
	rect(scrollbars ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : r)
{
	if(scrollbars){
		hscroll.reset(new Scrollbar({outerRect.x, outerRect.y + (int32_t)outerRect.h - scrollbarSize, outerRect.w - scrollbarSize, scrollbarSize}, 1, 1, 1, 1, true));
		vscroll.reset(new Scrollbar({outerRect.x + (int32_t)outerRect.w - scrollbarSize, outerRect.y, scrollbarSize, outerRect.h - scrollbarSize}, 1, 1, 1, 1, false));
		
		hscroll->OnChange([this] (uint32_t v) {
			HandleScroll(true, v);
		});
		
		vscroll->OnChange([this] (uint32_t v) {
			HandleScroll(false, v);
		});
	}
	SetText(t);
	auto info = fonts::GetTextAreaFont().Info();
	fontHeight = (info.maxH * fonts::GetTextAreaTextSize()) / info.scale;
}
	
gds::Rect TextArea::UpdateDisplayState(){
	bool update = false;
	std::unique_ptr<gds::Surface> measureSurf;
	gds::Surface *surf;
	if(!bkSurf){
		measureSurf.reset(new gds::Surface(gds_SurfaceType::Vector, 1, 1, 100, gds_ColourType::True));
		surf = measureSurf.get();
	}else{
		surf = bkSurf.get();
	}
	
	if(!lines.size()){
		cursorPos = 0;
		textOffset = 0;
		lines.emplace_back(Line{""});
		return {0, 0, 0, 0};
	}

	uint32_t maxLength = 0;
	Line *longLine = nullptr;
	for(auto &line : lines){		
		if(line.textMeasures.w == 0 || line.text != line.measuredText){
			line.textMeasures = surf->MeasureText(line.text, fonts::GetTextAreaFont(), fonts::GetTextAreaTextSize());
			line.measuredText = line.text;
			line.surf.reset();
		}
		if(line.text.length() > maxLength){
			maxLength = line.text.length();
			longLine = &line;
		}
	}

	if(cursorLine >= lines.size()) cursorLine = lines.size() - 1;
	auto &text = lines[cursorLine].text;
	auto &textMeasures = lines[cursorLine].textMeasures;

	auto oldLineOffset = lineOffset;
	size_t visibleLines = rect.h / fontHeight;
	bool cursorMoved = false;
	if(cursorLine != lastCursorLine || cursorPos != lastCursorPos) cursorMoved = true;
	if(cursorMoved){
		while(cursorLine < lineOffset && lineOffset > 0) --lineOffset;
		while(cursorLine >= lineOffset + visibleLines && lineOffset < lines.size() - 1) ++lineOffset;
		if(oldLineOffset != lineOffset) update = true;
	}
	if(cursorLine != lastCursorLine) update = true;
	lastCursorLine = cursorLine;
	
	if(vscroll){
		if(lines.size() > visibleLines){
			vscroll->Enable();
			vscroll->SetLines(std::max<uint32_t>(lines.size() - visibleLines, 1));
			vscroll->SetPage(visibleLines);
			vscroll->SetValue(lineOffset);
		}else{
			vscroll->Disable();
			vscroll->SetLines(1);
			vscroll->SetPage(1);
			vscroll->SetValue(0);
		}
	}
	
	size_t visibleChars;
	auto oldTextOffset = textOffset;
	while(true){
		auto textW = rect.w - 5;
		
		visibleChars = 0;
		double cWidth = 0.0;
		bool overflow = false;
		bool underflow = false;
		
		for(size_t i = 0; i < textMeasures.charX.size(); ++i){
			if(i >= textOffset){
				++visibleChars;
				cWidth += textMeasures.charX[i];
				if(cWidth > textW){
					overflow = true;
					break;
				}
			}else{
				underflow = true;
			}
		}
		if(longLine && cWidth < textW){
			for(size_t i = textMeasures.charX.size(); i < longLine->textMeasures.charX.size(); ++i){
				++visibleChars;
				cWidth += longLine->textMeasures.charX[i];
				if(cWidth > textW) break;
			}
		}
		if(cursorMoved){
			if(overflow && cursorPos > textOffset + std::max((int32_t)visibleChars - 2, 0)){
				++textOffset;
				if(textOffset >= text.length()) break;
			}else if(underflow && cursorPos < textOffset + 1){
				--textOffset;
			}else if(textOffset > text.length()){
				textOffset = text.length();
			}else break;
		}else break;
	}
	lastCursorPos = cursorPos;
	if(textOffset != oldTextOffset) update = true;
	
	if(hscroll){
		if(maxLength > visibleChars){
			hscroll->Enable();
			hscroll->SetLines(std::max<uint32_t>(1, maxLength - visibleChars));
			hscroll->SetPage(visibleChars);
			hscroll->SetValue(textOffset);
		}else{
			hscroll->Disable();
			hscroll->SetLines(1);
			hscroll->SetPage(1);
			hscroll->SetValue(0);
		}
	}
	
	double textOffsetPxlsD = 0.0;
	double cursorPosPxlsD = 1.5;
	for(size_t i = 0; i < std::max(textOffset, cursorPos); ++i){
		if(i < textMeasures.charX.size()){
			if(i < textOffset) textOffsetPxlsD += textMeasures.charX[i];
			else if(i < cursorPos) cursorPosPxlsD += textMeasures.charX[i];
		}else if(longLine && i < longLine->textMeasures.charX.size()){
			if(i < textOffset) textOffsetPxlsD += longLine->textMeasures.charX[i];
			else if(i < cursorPos) cursorPosPxlsD += longLine->textMeasures.charX[i];
		}
	}
	textOffsetPxls = round(textOffsetPxlsD);
	cursorPosPxls = round(cursorPosPxlsD) + 2;
	if(cursorPosPxlsD == 1.5 && cursorPos == 1 && text.length() == 1) cursorPosPxls = textMeasures.w + 2;
	
	if(haveSelection){
		double selPosPxlsD = 0.0;
		auto selMeasures = lines[selLine].textMeasures;
		if(selPos > textOffset){
			for(size_t i = textOffset; i < selPos; ++i){
				if(i < selMeasures.charX.size() && i < selPos) selPosPxlsD += selMeasures.charX[i];
				else break;
			}
		}
		selPosPxls = round(selPosPxlsD);
	}
	if(update) return rect;
	else if(cursorLine >= lineOffset && cursorLine < lineOffset + visibleLines){
		int32_t updY = ((cursorLine - lineOffset) * fontHeight) + 2;
		uint32_t updH = std::min(fontHeight, rect.h - updY);
		return {rect.x, rect.y + updY, updH, rect.w};
	}else{
		return {0, 0, 0, 0};
	}
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
	lines.emplace(it, Line{ntext});
}
	
EventResponse TextArea::HandleEvent(const wm_Event &e){
	bool update = false;
	bool updateCursor = false;
	bool handled = false;
	
	if(cursorLine >= lines.size()) UpdateDisplayState();
	auto &text = lines[cursorLine].text;
	
	if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(onKeyPress){
			if(onKeyPress(e.Key.code)) handled = true;
		}
		if(!handled){
			bool shiftPressed = (code & KeyFlags::Shift);
			code &= ~KeyFlags::Shift;
			if(!shiftPressed && haveSelection){
				++selSerial;
				haveSelection = false;
				update = true;
			}
			if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && cursorPos > 0){
				if(shiftPressed && !haveSelection){
					selPos = cursorPos;
					selLine = cursorLine;
					haveSelection = true;
					++selSerial;
				}
				perferredPosPxls = 0;
				--cursorPos;
				updateCursor = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && cursorLine > 0){
				if(shiftPressed && !haveSelection){
					selPos = cursorPos;
					selLine = cursorLine;
					haveSelection = true;
					++selSerial;
				}
				perferredPosPxls = 0;
				--cursorLine;
				cursorPos = lines[cursorLine].text.length();
				updateCursor = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && cursorPos < text.length()){
				if(shiftPressed && !haveSelection){
					selPos = cursorPos;
					selLine = cursorLine;
					haveSelection = true;
					++selSerial;
				}
				perferredPosPxls = 0;
				++cursorPos;
				updateCursor = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && cursorLine < lines.size() - 1){
				if(shiftPressed && !haveSelection){
					selPos = cursorPos;
					selLine = cursorLine;
					haveSelection = true;
					++selSerial;
				}
				perferredPosPxls = 0;
				cursorPos = 0;
				++cursorLine;
				updateCursor = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::DownArrow) && cursorLine < lines.size() - 1){
				if(shiftPressed && !haveSelection){
					selPos = cursorPos;
					selLine = cursorLine;
					haveSelection = true;
					++selSerial;
				}
				++cursorLine;
				if(!perferredPosPxls) perferredPosPxls = textOffsetPxls + cursorPosPxls;
				cursorPos = MapPosToLine(perferredPosPxls, lines[cursorLine]);
				updateCursor = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::UpArrow) && cursorLine > 0){
				if(shiftPressed && !haveSelection){
					selPos = cursorPos;
					selLine = cursorLine;
					haveSelection = true;
					++selSerial;
				}
				--cursorLine;
				if(!perferredPosPxls) perferredPosPxls = textOffsetPxls + cursorPosPxls;
				cursorPos = MapPosToLine(perferredPosPxls, lines[cursorLine]);
				updateCursor = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp) && cursorLine > 0){
				if(shiftPressed && !haveSelection){
					selPos = cursorPos;
					selLine = cursorLine;
					haveSelection = true;
					++selSerial;
				}
				size_t visibleLines = rect.h / fontHeight;
				cursorLine -= std::min(cursorLine, visibleLines);
				if(!perferredPosPxls) perferredPosPxls = textOffsetPxls + cursorPosPxls;
				cursorPos = MapPosToLine(perferredPosPxls, lines[cursorLine]);
				updateCursor = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown) && cursorLine < lines.size() - 1){
				if(shiftPressed && !haveSelection){
					selPos = cursorPos;
					selLine = cursorLine;
					haveSelection = true;
					++selSerial;
				}
				size_t visibleLines = rect.h / fontHeight;
				cursorLine = std::min(cursorLine + visibleLines, lines.size() - 1);
				if(!perferredPosPxls) perferredPosPxls = textOffsetPxls + cursorPosPxls;
				cursorPos = MapPosToLine(perferredPosPxls, lines[cursorLine]);
				updateCursor = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::Delete) && cursorPos < text.length()){
				if(haveSelection){
					haveSelection = false;
					++selSerial;
				}
				perferredPosPxls = 0;
				text.erase(cursorPos, 1);
				if(cursorPos > text.length()) cursorPos = text.length();
				RaiseChangeEvent();
				update = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::Delete) && cursorLine < lines.size() - 1){
				perferredPosPxls = 0;
				MergeLines(cursorLine, cursorLine + 1);
				RaiseChangeEvent();
				update = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::Home)){
				if(shiftPressed && !haveSelection){
					selPos = cursorPos;
					selLine = cursorLine;
					haveSelection = true;
					++selSerial;
				}
				perferredPosPxls = 0;
				cursorPos = 0;
				updateCursor = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::End)){
				if(shiftPressed && !haveSelection){
					selPos = cursorPos;
					selLine = cursorLine;
					haveSelection = true;
					++selSerial;
				}
				perferredPosPxls = 0;
				cursorPos = text.length();
				updateCursor = true;
				handled = true;
			}else if(!(code & KeyFlags::NonASCII)){
				if(haveSelection){
					haveSelection = false;
					update = true;
					++selSerial;
				}
				perferredPosPxls = 0;
				char c = KB_char(e.Key.code);
				auto preText = text;
				if(c == 0x08 && cursorPos > 0){
					text.erase(cursorPos - 1, 1);
					RaiseChangeEvent();
					--cursorPos;
					handled = true;
					update = true;
				}else if(c == 0x08 && cursorLine > 0){
					--cursorLine;
					cursorPos = lines[cursorLine].text.length();
					MergeLines(cursorLine, cursorLine + 1);
					RaiseChangeEvent();
					update = true;
					handled = true;
				}else if(c == '\n'){
					SplitLine(cursorLine, cursorPos);
					RaiseChangeEvent();
					++cursorLine;
					cursorPos = 0;
					update = true;
					handled = true;
				}else if(c > 31){
					text.insert(cursorPos, 1, c);
					RaiseChangeEvent();
					++cursorPos;
					update = true;
					handled = true;
				}
				update = update || (preText != text);
			}
		}
	}else if(e.type & wm_PointerEvents){
		handled = true;
		if(InRect(e.Pointer.x, e.Pointer.y, rect) 
			&& (e.type == wm_EventType::PointerButtonDown || e.type == wm_EventType::PointerButtonUp || e.type == wm_EventType::PointerMove)){
			perferredPosPxls = 0;
			auto pointerX = e.Pointer.x - rect.x;
			auto pointerY = e.Pointer.y - rect.y;
			auto pointerLine = (pointerY / fontHeight) + lineOffset;
			if(pointerLine >= lines.size()) pointerLine = lines.size() - 1;
			auto &line = lines[pointerLine];
			double xpos = 0.5;
			auto pointerPos = cursorPos;
			for(size_t i = textOffset; i < line.textMeasures.charX.size(); ++i){
				xpos += line.textMeasures.charX[i];
				if(xpos > pointerX){
					pointerPos = i;
					break;
				}else{
					pointerPos = i + 1;
				}
			}
			auto oldCursorLine = cursorLine;
			auto oldCursorPos = cursorPos;
			auto oldSelLine = selLine;
			auto oldSelPos = selPos;
			auto oldHaveSelection = haveSelection;
			if(e.type == wm_EventType::PointerButtonDown){
				cursorLine = pointerLine;
				cursorPos = pointerPos;
				inSelectMode = true;
				haveSelection = false;
				++selSerial;
			}else if(inSelectMode){
				selLine = pointerLine;
				selPos = pointerPos;
				haveSelection = (selLine != cursorLine || selPos != cursorPos);
				if(e.type == wm_EventType::PointerButtonUp) inSelectMode = false;
			}
			if(oldCursorLine != cursorLine || oldCursorPos != cursorPos) updateCursor = true;
			if((haveSelection && (oldSelLine != selLine || oldSelPos != selPos)) || haveSelection != oldHaveSelection){
				++selSerial;
				update = true;
			}
		}else if(hscroll && InRect(e.Pointer.x, e.Pointer.y, hscroll->GetInteractRect()) && (e.type & hscroll->GetSubscribed())){
			auto ret = hscroll->HandleEvent(e);
			IControl::Paint(outerRect);
			handled = handled || ret.IsFinishedProcessing();
		}else if(vscroll && InRect(e.Pointer.x, e.Pointer.y, vscroll->GetInteractRect()) && (e.type & vscroll->GetSubscribed())){
			auto ret = vscroll->HandleEvent(e);
			IControl::Paint(outerRect);
			handled = handled || ret.IsFinishedProcessing();
		}
	}
	
	
	if(update || updateCursor){
		auto updateRect = UpdateDisplayState();
		if(updateRect) IControl::Paint(outerRect);
	}
	return {handled};
}

void TextArea::Paint(gds::Surface &s){
	UpdateDisplayState();
	
	uint32_t inW = rect.w - 1;
	uint32_t inH = rect.h - 1;
	
	if(!bkSurf){
		bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		bkSurf->BeginQueue();
		
		auto bkgCol = colours::GetBackground().Fix(*bkSurf);
		auto border = colours::GetBorder().Fix(*bkSurf);
		
		bkSurf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		drawing::Border(*bkSurf, {0, 0, inW, inH}, border);
		auto topLeft = colours::GetTextAreaLowLight().Fix(*bkSurf);
		auto bottomRight = colours::GetTextAreaHiLight().Fix(*bkSurf);
		drawing::BevelBox(*bkSurf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);
		
		bkSurf->CommitQueue();
		bkSurf->Compress();
	}
	s.Blit(*bkSurf, {0, 0, rect.w, rect.h}, rect);
	
	size_t selStartLine, selEndLine;
	size_t selStartPos, selEndPos;
	if(haveSelection){
		if(selLine < cursorLine){
			selStartLine = selLine;
			selEndLine = cursorLine;
			selStartPos = selPos;
			selEndPos = cursorPos;
		}else if(selLine > cursorLine){
			selStartLine = cursorLine;
			selEndLine = selLine;
			selStartPos = cursorPos;
			selEndPos = selPos;
		}else{
			selStartLine = selEndLine = selLine;
			selStartPos = std::min(selPos, cursorPos);
			selEndPos = std::max(selPos, cursorPos);
		}
	}

	for(size_t i = lineOffset; i < lines.size(); ++i){
		if((i - lineOffset) * fontHeight > rect.h) break;
		
		auto &m = lines[i].textMeasures;
		bool redraw = false;
		if(!m.w || lines[i].text != lines[i].measuredText){
			m = bkSurf->MeasureText(lines[i].text, fonts::GetTextAreaFont(), fonts::GetTextAreaTextSize());
			lines[i].measuredText = lines[i].text;
			redraw = true;
		}
		uint32_t lsW = m.w + 2;
		uint32_t lsH = fontHeight * 1.5;
		
		bool inSelectionArea = haveSelection && (i >= selStartLine && i <= selEndLine);
		
		if(redraw || !lines[i].surf || inSelectionArea || (lines[i].selSerial && lines[i].selSerial != selSerial)){
			auto &ls = lines[i].surf;
			lines[i].selSerial = inSelectionArea ? selSerial : 0;
			ls.reset(new gds::Surface(gds_SurfaceType::Vector, lsW, lsH, 100, gds_ColourType::True));
			ls->BeginQueue();
			auto lsBkg = colours::GetBackground().Fix(*ls);
			ls->Box({0, 0, lsW, lsH}, lsBkg, lsBkg, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
			if(inSelectionArea){
				int32_t selX1 = 2; 
				int32_t selX2 = lsW;
				if(i == selStartLine || i == selEndLine){
					double selX1D = 1.5, selX2D = 1.5;
					for(size_t j = 0; j < m.charX.size(); ++j){
						if(i == selStartLine && j < selStartPos) selX1D += m.charX[j];
						if(i == selEndLine && j < selEndPos) selX2D += m.charX[j];
					}
					if(i == selStartLine) selX1 = round(selX1D);
					if(i == selEndLine) selX2 = round(selX2D);
				}
				uint32_t selW = selX2 - selX1;
				
				if(hasFocus){
					auto selBkg = colours::GetSelection().Fix(*ls);
					ls->Box({selX1, 0, selW, lsH - 2}, selBkg, selBkg, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				}else{
					auto selBdr = colours::GetSelectionFocus().Fix(*ls);
					ls->Box({selX1, 0, selW, lsH - 2}, selBdr, selBdr, 1, gds_LineStyle::Solid, gds_FillStyle::None);
				}
			}
			auto lsTxt = colours::GetTextAreaText().Fix(*ls);
			auto textY = std::max<int32_t>(((fontHeight + m.h) / 2), 0);
			ls->Text({2, textY}, lines[i].text, fonts::GetTextAreaFont(), fonts::GetTextAreaTextSize(), lsTxt);
			ls->CommitQueue();
			if(i != cursorLine && !inSelectionArea) ls->Compress();
		}
		
		int32_t lsY = (i - lineOffset) * fontHeight;
		if((uint32_t)lsY < rect.h - 4){
			uint32_t drawWidth = std::min((lsW - textOffsetPxls), rect.w - 4);
			uint32_t drawHeight = std::min(lsH, (rect.h - lsY) - 4);
			s.Blit(*lines[i].surf, {(int32_t)textOffsetPxls, 0, drawWidth, drawHeight}, {rect.x + 2, rect.y + lsY + 2, drawWidth, drawHeight});
		}else{
			break;
		}
	}

	if(hasFocus && cursorPos >= textOffset && cursorPosPxls < rect.w){
		auto cursorCol = colours::GetTextCursor().Fix(s);
		auto top = (cursorLine - lineOffset) * fontHeight;
		auto bottom = top + fontHeight;
		s.Line({(int32_t)cursorPosPxls + rect.x, (int32_t)(rect.y + top + 2)}, {(int32_t)cursorPosPxls + rect.x, (int32_t)(rect.y + bottom + 1)}, cursorCol);
	}
	
	if(hscroll) hscroll->Paint(s);
	if(vscroll) vscroll->Paint(s);
	
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(outerRect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect TextArea::GetPaintRect(){
	return outerRect;
}

gds::Rect TextArea::GetInteractRect(){
	return outerRect;
}

uint32_t TextArea::GetSubscribed(){
	auto ret = wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown | wm_EventType::PointerMove;
	if(hscroll) ret |= hscroll->GetSubscribed();
	if(vscroll) ret |= vscroll->GetSubscribed();
	return ret;
}

void TextArea::Focus(){
	if(!hasFocus){
		hasFocus = true;
		IControl::Paint(rect);
	}
}

void TextArea::Blur(){
	if(hasFocus){
		hasFocus = false;
		IControl::Paint(rect);
	}
}
	
void TextArea::SetText(const std::string &t){
	haveSelection = false;
	++selSerial;
	lines.clear();
	std::stringstream ss(t);
	std::string l;
	while(std::getline(ss, l)){
		lines.emplace_back(Line{l});
	}
	cursorLine = 0;
	cursorPos = 0;
	IControl::Paint(outerRect);
}

void TextArea::InsertText(const std::string &text){
	haveSelection = false;
	++selSerial;
	
	size_t lineNo = cursorLine;
	size_t insertPos = cursorPos;
	auto *lineText = &lines[lineNo].text;
	for(auto c : text){
		std::string cStr = {c, 0};
		if(c != '\n') lineText->insert(insertPos++, cStr);
		else{
			SplitLine(lineNo, insertPos);
			++lineNo; insertPos = 0;
			lineText = &lines[lineNo].text;
		}
	}
	
	IControl::Paint(outerRect);
}

std::string TextArea::GetText(){
	std::stringstream ss;
	for(const auto &l : lines){
		ss << l.text << '\n';
	}
	return ss.str();
}

void TextArea::OnKeyPress(const std::function<bool(uint32_t)> &oKP){
	onKeyPress = oKP;
}

uint32_t TextArea::GetFlags(){
	return 0;
}

void TextArea::Enable(){
	if(!enabled){
		enabled = true;
		IControl::Paint(rect);
	}
}

void TextArea::Disable(){
	if(enabled){
		enabled = false;
		IControl::Paint(rect);
	}
}

bool TextArea::IsEnabled(){
	return enabled;
}

void TextArea::SetPosition(const gds::Rect &r){
	outerRect = r;
	rect = (hscroll || vscroll) ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : r;
	if(vscroll) vscroll->SetPosition({outerRect.x + (int32_t)outerRect.w - scrollbarSize, outerRect.y, scrollbarSize, outerRect.h - scrollbarSize});
	if(hscroll) hscroll->SetPosition({outerRect.x, outerRect.y + (int32_t)outerRect.h - scrollbarSize, outerRect.w - scrollbarSize, scrollbarSize});
	bkSurf.reset();
}

std::string TextArea::GetSelection(){
	if(!haveSelection) return "";
	
	size_t selStartLine, selEndLine;
	size_t selStartPos, selEndPos;
	if(selLine < cursorLine){
		selStartLine = selLine;
		selEndLine = cursorLine;
		selStartPos = selPos;
		selEndPos = cursorPos;
	}else if(selLine > cursorLine){
		selStartLine = cursorLine;
		selEndLine = selLine;
		selStartPos = cursorPos;
		selEndPos = selPos;
	}else{
		selStartLine = selEndLine = selLine;
		selStartPos = std::min(selPos, cursorPos);
		selEndPos = std::max(selPos, cursorPos);
	}
	
	std::stringstream ret;
	for(auto i = selStartLine; i <= selEndLine; ++i){
		const auto &text = lines[i].text;
		size_t start = 0, len = std::string::npos;
		if(i == selStartLine) start = selStartPos;
		if(i == selEndLine) len = (selEndPos - start);
		ret << text.substr(start, len);
		if(i != selEndLine) ret << '\n';
	}
	return ret.str();
}

void TextArea::CutSelection(){
	if(!haveSelection) return;
	
	size_t selStartLine, selEndLine;
	size_t selStartPos, selEndPos;
	if(selLine < cursorLine){
		selStartLine = selLine;
		selEndLine = cursorLine;
		selStartPos = selPos;
		selEndPos = cursorPos;
	}else if(selLine > cursorLine){
		selStartLine = cursorLine;
		selEndLine = selLine;
		selStartPos = cursorPos;
		selEndPos = selPos;
	}else{
		selStartLine = selEndLine = selLine;
		selStartPos = std::min(selPos, cursorPos);
		selEndPos = std::max(selPos, cursorPos);
	}
	
	auto firstLine = lines[selStartLine].text;
	auto lastLine = lines[selEndLine].text;
	lines.erase(lines.begin() + selStartLine, lines.begin() + (selEndLine + 1));
	if(selEndPos < lastLine.length()){
		lastLine = lastLine.substr(selEndPos);
		lines.insert(lines.begin() + selStartLine, lastLine);
	}
	if(selStartPos != 0){
		firstLine = firstLine.substr(0, selStartPos);
		lines.insert(lines.begin() + selStartLine, firstLine);
	}
	
	cursorLine = selStartLine;
	cursorPos = selStartPos;
	if(cursorLine > lines.size() - 1) cursorLine = lines.size() - 1;
	IControl::Paint(outerRect);
}

void TextArea::HandleScroll(bool horiz, uint32_t v){
	if(horiz && v != textOffset){
		textOffset = v;
		IControl::Paint(rect);
	}
	
	if(!horiz && v != lineOffset){
		lineOffset = v;
		IControl::Paint(rect);
	}
}

}
}
