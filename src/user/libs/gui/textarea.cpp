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

struct TextAreaImpl{
	TextArea *that;

	gds::Rect outerRect;
	gds::Rect rect; 
	std::unique_ptr<gds::Surface> bkSurf;
	std::unique_ptr<gds::Surface> cachedSurf;
	
	std::function<bool(uint32_t)> onKeyPress;
	
	struct Line{
		std::string text;
		std::string measuredText;
		gds::TextMeasurements textMeasures;
		std::unique_ptr<gds::Surface> surf;
		uint64_t selSerial = 0;
		uint64_t updSerial = 0;
		
		Line(const std::string &t) : text(t) {};
		Line() = default;
	};
	
	uint32_t fontHeight;
	
	std::vector<Line> lines;
	size_t lastLineCount = 0;
	
	bool inSelectMode = false;
	bool haveSelection = false;
	size_t selPos = 0;
	size_t selLine = 0;
	
	size_t cursorPos = 0;
	size_t lastCursorPos = 0;
	size_t cursorLine = 0;
	size_t lastCursorLine = 0;
	size_t prevCursorPos = 0;
	size_t prevCursorLine = 0;

	size_t lineOffset = 0;
	size_t textOffset = 0;
	size_t lastLineOffset = 0;
	size_t lastTextOffset = 0;
	
	uint32_t textOffsetPxls = 0;
	uint32_t cursorPosPxls = 0;
	uint32_t perferredPosPxls = 0;
	uint32_t selPosPxls = 0;
	
	bool hasFocus = false;
	bool enabled = true;
	
	uint64_t selSerial = 0;
	uint64_t updSerial = 0;
	
	std::unique_ptr<Scrollbar> hscroll;
	std::unique_ptr<Scrollbar> vscroll;
	
	gds::Rect UpdateDisplayState();
	size_t MapPosToLine(uint32_t pxlPos, const Line &line);
	void MergeLines(size_t a, size_t b);
	void SplitLine(size_t i, size_t pos);
	
	void HandleScroll(bool horiz, uint32_t v);

	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
};
PIMPL_IMPL(TextAreaImpl);

TextArea::TextArea(const gds::Rect &r, const std::string &t, bool scrollbars) : im(new TextAreaImpl()){
	im->that = this;
	im->outerRect = r;
	im->rect = scrollbars ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : r;
	if(scrollbars){
		im->hscroll.reset(new Scrollbar({im->outerRect.x, im->outerRect.y + (int32_t)im->outerRect.h - scrollbarSize, im->outerRect.w - scrollbarSize, scrollbarSize}, 1, 1, 1, 1, true));
		im->vscroll.reset(new Scrollbar({im->outerRect.x + (int32_t)im->outerRect.w - scrollbarSize, im->outerRect.y, scrollbarSize, im->outerRect.h - scrollbarSize}, 1, 1, 1, 1, false));
		
		im->hscroll->OnChange([this] (uint32_t v) {
			im->HandleScroll(true, v);
		});
		
		im->vscroll->OnChange([this] (uint32_t v) {
			im->HandleScroll(false, v);
		});
	}
	SetText(t);
	auto info = fonts::GetTextAreaFont().Info();
	im->fontHeight = (info.maxH * fonts::GetTextAreaTextSize()) / info.scale;
}
	
gds::Rect TextAreaImpl::UpdateDisplayState(){
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
	size_t visibleLines = (rect.h - 4) / (fontHeight * 1.25);
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
			if(overflow && cursorPos > textOffset + std::max<int32_t>((int32_t)visibleChars - 2, 0)){
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
		int32_t updY = ((cursorLine - lineOffset) * (fontHeight * 1.25)) + 2;
		uint32_t updH = std::min(fontHeight, rect.h - updY);
		return {rect.x, rect.y + updY, rect.w, updH};
	}else{
		return {0, 0, 0, 0};
	}
}

size_t TextAreaImpl::MapPosToLine(uint32_t pxlPos, const TextAreaImpl::Line &line){
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

void TextAreaImpl::MergeLines(size_t a, size_t b){
	auto &la = lines[a];
	auto &lb = lines[b];
	la.text += lb.text;
	la.textMeasures = gds::TextMeasurements();
	auto it = lines.begin();
	std::advance(it, b);
	lines.erase(it);
}

void TextAreaImpl::SplitLine(size_t i, size_t pos){
	auto &l = lines[i];
	std::string ntext = pos < l.text.length() ? l.text.substr(pos) : "";
	l.text = l.text.substr(0, pos);
	l.textMeasures = gds::TextMeasurements();
	auto it = lines.begin();
	std::advance(it, i + 1);
	lines.emplace(it, Line{ntext});
}
	
EventResponse TextAreaImpl::HandleEvent(const wm_Event &e){
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
				size_t visibleLines = rect.h / (fontHeight * 1.25);
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
				size_t visibleLines = rect.h / (fontHeight * 1.25);
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
				that->RaiseChangeEvent();
				update = true;
				handled = true;
			}else if(code == (KeyFlags::NonASCII | KeyCodes::Delete) && cursorLine < lines.size() - 1){
				perferredPosPxls = 0;
				MergeLines(cursorLine, cursorLine + 1);
				that->RaiseChangeEvent();
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
					that->RaiseChangeEvent();
					--cursorPos;
					handled = true;
					update = true;
				}else if(c == 0x08 && cursorLine > 0){
					--cursorLine;
					cursorPos = lines[cursorLine].text.length();
					MergeLines(cursorLine, cursorLine + 1);
					that->RaiseChangeEvent();
					update = true;
					handled = true;
				}else if(c == '\n'){
					SplitLine(cursorLine, cursorPos);
					that->RaiseChangeEvent();
					++cursorLine;
					cursorPos = 0;
					update = true;
					handled = true;
				}else if(c > 31){
					text.insert(cursorPos, 1, c);
					that->RaiseChangeEvent();
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
			auto pointerLine = (pointerY / (fontHeight * 1.25)) + lineOffset;
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
			that->IControl::Paint(outerRect);
			handled = handled || ret.IsFinishedProcessing();
		}else if(vscroll && InRect(e.Pointer.x, e.Pointer.y, vscroll->GetInteractRect()) && (e.type & vscroll->GetSubscribed())){
			auto ret = vscroll->HandleEvent(e);
			that->IControl::Paint(outerRect);
			handled = handled || ret.IsFinishedProcessing();
		}
	}
	
	
	if(update || updateCursor){
		auto updateRect = UpdateDisplayState();
		if(updateRect) that->IControl::Paint(updateRect);
		if(vscroll && (lastLineCount != lines.size() || lastLineOffset != lineOffset)) that->IControl::Paint(vscroll->GetPaintRect());
		if(hscroll && (lastTextOffset != textOffset)) that->IControl::Paint(hscroll->GetPaintRect());
	}
	return {handled};
}

EventResponse TextArea::HandleEvent(const wm_Event &e){
	return im->HandleEvent(e);
}

void TextAreaImpl::Paint(gds::Surface &formSurf){
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
	bool fullRedrawNeeded = !cachedSurf || lastLineCount != lines.size() || lastLineOffset != lineOffset || lastTextOffset != textOffset;
	if(!cachedSurf) cachedSurf.reset(new gds::Surface(gds_SurfaceType::Bitmap, rect.w, rect.h, 100, gds_ColourType::True));
	
	auto &s = *cachedSurf;
	s.BeginQueue();
	if(fullRedrawNeeded) s.Blit(*bkSurf, {0, 0, rect.w, rect.h}, {0, 0, rect.w, rect.h});
	
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
		if((i - lineOffset) * (fontHeight * 1.25) > rect.h) break;
		uint32_t lsW = 0, lsH =  fontHeight * 1.25;
		if(!lines[i].text.empty()){
			auto &m = lines[i].textMeasures;
			bool redraw = false;
			if(!m.w || lines[i].text != lines[i].measuredText){
				m = bkSurf->MeasureText(lines[i].text, fonts::GetTextAreaFont(), fonts::GetTextAreaTextSize());
				lines[i].measuredText = lines[i].text;
				redraw = true;
			}
			lsW = m.w + 2;
			
			bool inSelectionArea = haveSelection && (i >= selStartLine && i <= selEndLine);
			
			if(redraw || !lines[i].surf || inSelectionArea || (lines[i].selSerial && lines[i].selSerial != selSerial)){
				auto &ls = lines[i].surf;
				lines[i].selSerial = inSelectionArea ? selSerial : 0;
				auto surfW = ((lsW / 100) + 1) * 100;
				if(!ls || ls->Info().w < surfW) ls.reset(new gds::Surface(gds_SurfaceType::Bitmap, surfW, lsH, 100, gds_ColourType::True));
				ls->BeginQueue();
				auto lsBkg = colours::GetBackground().Fix(*ls);
				ls->Box({0, 0, surfW, lsH}, lsBkg, lsBkg, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
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
				lines[i].updSerial = updSerial;
			}
		}
		int32_t lsY = (i - lineOffset) * (fontHeight * 1.25);
		bool lineNeedsRedraw = fullRedrawNeeded || lines[i].updSerial == updSerial || 
			((prevCursorLine == i || cursorLine == i) && cursorLine != prevCursorLine) ||
			(cursorLine == i && cursorPos != prevCursorPos);
		if(lineNeedsRedraw && (uint32_t)lsY < rect.h - 4){
			auto bkgCol = colours::GetBackground().Fix(s);
			uint32_t drawWidth = std::min((lsW - textOffsetPxls), rect.w - 5);
			uint32_t drawHeight = std::min(lsH, (rect.h - lsY) - 4);
			if(lines[i].surf) s.Blit(*lines[i].surf, {(int32_t)textOffsetPxls, 0, drawWidth, drawHeight}, {2, lsY + 2, drawWidth, drawHeight});
			s.Box({(int32_t)drawWidth + 2, lsY + 2, rect.w - drawWidth - 4, drawHeight}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		}else if((uint32_t)lsY >= rect.h - 4){
			break;
		}
	}

	lastLineCount = lines.size(); lastLineOffset = lineOffset; lastTextOffset = textOffset; ++updSerial;
	prevCursorLine = cursorLine; prevCursorPos = cursorPos;

	if(hasFocus && cursorPos >= textOffset && cursorPosPxls < rect.w){
		auto cursorCol = colours::GetTextCursor().Fix(s);
		auto top = (cursorLine - lineOffset) * (fontHeight * 1.25);
		auto bottom = top + fontHeight;
		s.Line({(int32_t)cursorPosPxls, (int32_t)(top + 2)}, {(int32_t)cursorPosPxls, (int32_t)(bottom + 1)}, cursorCol);
	}
	s.CommitQueue();
	formSurf.Blit(s, {0, 0, rect.w, rect.h}, rect);

	if(hscroll) hscroll->Paint(formSurf);
	if(vscroll) vscroll->Paint(formSurf);
	
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		formSurf.Box(outerRect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

void TextArea::Paint(gds::Surface &formSurf){
	im->Paint(formSurf);
}

gds::Rect TextArea::GetPaintRect(){
	return im->outerRect;
}

gds::Rect TextArea::GetInteractRect(){
	return im->outerRect;
}

uint32_t TextArea::GetSubscribed(){
	auto ret = wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown | wm_EventType::PointerMove;
	if(im->hscroll) ret |= im->hscroll->GetSubscribed();
	if(im->vscroll) ret |= im->vscroll->GetSubscribed();
	return ret;
}

void TextArea::Focus(){
	if(!im->hasFocus){
		im->hasFocus = true;
		IControl::Paint(im->rect);
	}
}

void TextArea::Blur(){
	if(im->hasFocus){
		im->hasFocus = false;
		IControl::Paint(im->rect);
	}
}
	
void TextArea::SetText(const std::string &t){
	im->haveSelection = false;
	++im->selSerial;
	im->lines.clear();
	std::stringstream ss(t);
	std::string l;
	while(std::getline(ss, l)){
		im->lines.emplace_back(TextAreaImpl::Line{l});
	}
	im->cursorLine = 0;
	im->cursorPos = 0;
	IControl::Paint(im->outerRect);
}

void TextArea::InsertText(const std::string &text){
	im->haveSelection = false;
	++im->selSerial;
	
	size_t lineNo = im->cursorLine;
	size_t insertPos = im->cursorPos;
	auto *lineText = &im->lines[lineNo].text;
	for(auto c : text){
		std::string cStr = {c, 0};
		if(c != '\n') lineText->insert(insertPos++, cStr);
		else{
			im->SplitLine(lineNo, insertPos);
			++lineNo; insertPos = 0;
			lineText = &im->lines[lineNo].text;
		}
	}
	
	IControl::Paint(im->outerRect);
}

std::string TextArea::GetText(){
	std::stringstream ss;
	for(const auto &l : im->lines){
		ss << l.text << '\n';
	}
	return ss.str();
}

void TextArea::OnKeyPress(const std::function<bool(uint32_t)> &oKP){
	im->onKeyPress = oKP;
}

uint32_t TextArea::GetFlags(){
	return 0;
}

void TextArea::Enable(){
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(im->rect);
	}
}

void TextArea::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(im->rect);
	}
}

bool TextArea::IsEnabled(){
	return im->enabled;
}

void TextArea::SetPosition(const gds::Rect &r){
	im->outerRect = r;
	im->rect = (im->hscroll || im->vscroll) ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : r;
	if(im->vscroll) im->vscroll->SetPosition({im->outerRect.x + (int32_t)im->outerRect.w - scrollbarSize, im->outerRect.y, scrollbarSize, im->outerRect.h - scrollbarSize});
	if(im->hscroll) im->hscroll->SetPosition({im->outerRect.x, im->outerRect.y + (int32_t)im->outerRect.h - scrollbarSize, im->outerRect.w - scrollbarSize, scrollbarSize});
	im->bkSurf.reset();
	im->cachedSurf.reset();
}

std::string TextArea::GetSelection(){
	if(!im->haveSelection) return "";
	
	size_t selStartLine, selEndLine;
	size_t selStartPos, selEndPos;
	if(im->selLine < im->cursorLine){
		selStartLine = im->selLine;
		selEndLine = im->cursorLine;
		selStartPos = im->selPos;
		selEndPos = im->cursorPos;
	}else if(im->selLine > im->cursorLine){
		selStartLine = im->cursorLine;
		selEndLine = im->selLine;
		selStartPos = im->cursorPos;
		selEndPos = im->selPos;
	}else{
		selStartLine = selEndLine = im->selLine;
		selStartPos = std::min(im->selPos, im->cursorPos);
		selEndPos = std::max(im->selPos, im->cursorPos);
	}
	
	std::stringstream ret;
	for(auto i = selStartLine; i <= selEndLine; ++i){
		const auto &text = im->lines[i].text;
		size_t start = 0, len = std::string::npos;
		if(i == selStartLine) start = selStartPos;
		if(i == selEndLine) len = (selEndPos - start);
		ret << text.substr(start, len);
		if(i != selEndLine) ret << '\n';
	}
	return ret.str();
}

void TextArea::CutSelection(){
	if(!im->haveSelection) return;
	
	size_t selStartLine, selEndLine;
	size_t selStartPos, selEndPos;
	if(im->selLine < im->cursorLine){
		selStartLine = im->selLine;
		selEndLine = im->cursorLine;
		selStartPos = im->selPos;
		selEndPos = im->cursorPos;
	}else if(im->selLine > im->cursorLine){
		selStartLine = im->cursorLine;
		selEndLine = im->selLine;
		selStartPos = im->cursorPos;
		selEndPos = im->selPos;
	}else{
		selStartLine = selEndLine = im->selLine;
		selStartPos = std::min(im->selPos, im->cursorPos);
		selEndPos = std::max(im->selPos, im->cursorPos);
	}
	
	auto firstLine = im->lines[selStartLine].text;
	auto lastLine = im->lines[selEndLine].text;
	im->lines.erase(im->lines.begin() + selStartLine, im->lines.begin() + (selEndLine + 1));
	if(selEndPos < lastLine.length()){
		lastLine = lastLine.substr(selEndPos);
		im->lines.insert(im->lines.begin() + selStartLine, lastLine);
	}
	if(selStartPos != 0){
		firstLine = firstLine.substr(0, selStartPos);
		im->lines.insert(im->lines.begin() + selStartLine, firstLine);
	}
	
	im->cursorLine = selStartLine;
	im->cursorPos = selStartPos;
	if(im->cursorLine > im->lines.size() - 1) im->cursorLine = im->lines.size() - 1;
	IControl::Paint(im->outerRect);
}

void TextAreaImpl::HandleScroll(bool horiz, uint32_t v){
	if(horiz && v != textOffset){
		textOffset = v;
		that->IControl::Paint(rect);
	}
	
	if(!horiz && v != lineOffset){
		lineOffset = v;
		that->IControl::Paint(rect);
	}
}

}
}
