#include <gui/iconview.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

#include <cctype>
#include <algorithm>

namespace btos_api{
namespace gui{
	
const auto scrollbarSize = 17;
const auto checkSize = 17;

IconView::IconView(const gds::Rect &r, size_t iS, bool mS) : 
	outerRect(r), 
	rect(r.x, r.y, r.w - scrollbarSize, r.h),
	iconSize(iS),
	multiSelect(mS)
	{
	auto info = fonts::GetIconViewFont().Info();
	fontHeight = (info.maxH * fonts::GetIconViewTextSize()) / info.scale;
	if(multiSelect && fontHeight < checkSize) fontHeight = checkSize;
	itemWidth = iconSize * 2;
	itemHeight = std::max<size_t>((iconSize * 2), (iconSize * 1.5) + (fontHeight * 2));
	
	vscroll.reset(new Scrollbar({outerRect.x + (int32_t)outerRect.w - scrollbarSize, outerRect.y, scrollbarSize, outerRect.h}, 1, 1, 1, 1, false));
	
	vscroll->OnChange([this] (uint32_t v) {
		if(v != vOffset) update = true;
		vOffset = v;
	});
	
	UpdateDisplayState();
}

void IconView::UpdateDisplayState(bool changePos){
	visibleLines = (rect.h / itemHeight);
	visibleCols = rect.w / itemWidth;
	if(changePos){
		auto selectionLine = selectedItem / visibleCols; 
		if(selectionLine < vOffset) vOffset = selectionLine;
		if(selectionLine >= vOffset + (visibleLines)) vOffset = std::max<int32_t>(0, (int32_t)(selectionLine - (visibleLines - 1)));
	}
	
	drawItems.resize(items.size());
	for(size_t i = 0; i < items.size(); ++i){
		auto &di = drawItems[i];
		auto &it = items[i];
		if(di.text != it || !di.measures1.w){
			di.text = it;
			FitTextToWidth(di, itemWidth - (multiSelect ? checkSize : 0));
		}
	}
	
	if(vscroll){
		auto lines = items.size() / visibleCols;
		if(lines * visibleCols < items.size()) ++lines;
		auto scrollLines = std::max<int32_t>(lines - (visibleLines), 1);
		if((int32_t)vOffset > scrollLines) vOffset = scrollLines;
		if(visibleLines < lines){
			vscroll->Enable();
			vscroll->SetLines(scrollLines);
			vscroll->SetPage(visibleLines);
			vscroll->SetValue(vOffset);
		}else{
			vscroll->Disable();
			vscroll->SetLines(1);
			vscroll->SetPage(1);
			vscroll->SetValue(0);
			vOffset = 0;
		}
	}
}

void IconView::FitTextToWidth(DrawItem &item, size_t width){
	auto surf = gds::Surface(gds_SurfaceType::Vector, 1, 1, 100, gds_ColourType::True);
	if(item.fittedWidth == width) return;

	const std::string suffix = "\xE2\x80\xA6";
	
	item.measures1.w = 0;
	size_t curChar = 0;
	item.fittedText1.clear();
	for(; curChar < item.text.length(); ++curChar){
		auto newLine = item.fittedText1 + item.text[curChar];
		auto newMeasures = surf.MeasureText(newLine, fonts::GetIconViewFont(), fonts::GetIconViewTextSize());
		if(newMeasures.w > width) break;
		item.fittedText1 = newLine;
		item.measures1 = newMeasures;
	}
	
	if(curChar >= item.text.length()){
		item.fittedText2.clear();
		item.measures2 = surf.MeasureText(item.fittedText2, fonts::GetIconViewFont(), fonts::GetIconViewTextSize());
		return;
	}
	
	item.fittedText2 = item.text.substr(curChar);
	item.measures2 = surf.MeasureText(item.fittedText2, fonts::GetIconViewFont(), fonts::GetIconViewTextSize());
	if(item.measures2.w < width) return;
	
	std::string text = item.fittedText2;
	while((item.measures2 = surf.MeasureText(text + suffix, fonts::GetIconViewFont(), fonts::GetIconViewTextSize())).w > width){
		text.pop_back();
	}

	item.fittedText2 = text + suffix;
	item.fittedWidth = width;
}

EventResponse IconView::HandleEvent(const wm_Event &e){
	bool handled = false;
	if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(code == (KeyFlags::NonASCII | KeyCodes::DownArrow) && selectedItem < items.size() - 1){
			selectedItem += visibleCols;
			if(selectedItem >= items.size()) selectedItem = items.size() - 1;
			update = true;
			handled = true;
			UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::UpArrow) && selectedItem > 0){
			selectedItem -= std::min(selectedItem, visibleCols);
			update = true;
			handled = true;
			UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && selectedItem < items.size() - 1){
			++selectedItem;
			update = true;
			handled = true;
			UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && selectedItem > 0){
			--selectedItem;
			update = true;
			handled = true;
			UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp)){
			if(selectedItem != 0){
				auto visibleItems = (visibleLines - 1) * visibleCols;
				if(selectedItem > visibleItems) selectedItem -= visibleItems;
				else selectedItem = 0;
				update = true;
				UpdateDisplayState();
				RaiseChangeEvent();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown)){
			if(selectedItem < items.size() - 1){
				auto visibleItems = (visibleLines - 1) * visibleCols;
				if(selectedItem + visibleItems < items.size()) selectedItem += visibleItems;
				else selectedItem = items.size() - 1;
				update = true;
				UpdateDisplayState();
				RaiseChangeEvent();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::Home)){
			if(selectedItem != 0){
				selectedItem = 0;
				update = true;
				UpdateDisplayState();
				RaiseChangeEvent();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::End)){
			if(selectedItem < items.size() - 1){
				selectedItem = items.size() - 1;
				update = true;
				UpdateDisplayState();
				RaiseChangeEvent();
			}
			handled = true;
		}else if(!(code & KeyFlags::NonASCII)){
			auto oldSelectedItem = selectedItem;
			char c = KB_char(e.Key.code);
			if(c == ' ' || c == '\n'){
				if(multiSelect){
					multiSelection[selectedItem] = !multiSelection[selectedItem];
					update = true;
				}else if(onActivate) onActivate();
			}else{
				c = std::tolower(c);
				auto finder = [&](const std::string &item){return !item.empty() && std::tolower(item.front()) == c;};
				auto it = std::find_if(begin(items) + selectedItem + 1, end(items), finder);
				if(it == end(items)) it = std::find_if(begin(items), end(items), finder);
				if(it != end(items)) selectedItem = it - begin(items);
				update = oldSelectedItem != selectedItem;
				if(update || fireCurrentSelection){ 
					RaiseChangeEvent();
					fireCurrentSelection = false;
				}
			}
			handled = true;
			UpdateDisplayState();
		}
	}else if(e.type & wm_PointerEvents){
		if(InRect(e.Pointer.x, e.Pointer.y, rect)){
			auto pX = e.Pointer.x - outerRect.x;
			auto pY = e.Pointer.y - outerRect.y;
			auto col = pX / itemWidth;
			if(col >= visibleCols) col = visibleCols - 1;
			auto line = (pY / itemHeight) + vOffset;
			auto idx = (line * visibleCols) + col;
			if(e.type == wm_EventType::PointerButtonUp && idx < items.size()){
				auto oldSelectedItem = selectedItem;
				selectedItem = idx;
				if(selectedItem < items.size()) update = oldSelectedItem != selectedItem;
				if(update || fireCurrentSelection){ 
					RaiseChangeEvent();
					fireCurrentSelection = false;
				}
				if(multiSelect){
					auto xPos = pX - (col * itemWidth);
					auto yPos = pY - (line * itemHeight);
					if(xPos < checkSize && yPos > (itemHeight - checkSize)){
						multiSelection[selectedItem] = !multiSelection[selectedItem];
						update = true;
					}
				}
				handled = true;
				if(IsDoubleClick() && onActivate) onActivate();
				UpdateDisplayState();
			}
		}else if(vscroll && vscroll->IsEnabled() && InRect(e.Pointer.x, e.Pointer.y, vscroll->GetInteractRect()) && (e.type & vscroll->GetSubscribed())){
			auto ret = vscroll->HandleEvent(e);
			update = ret.IsFinishedProcessing();
			handled = handled || update;
		}
	}
	if(update) IControl::Paint(outerRect);
	return {handled};
}

void IconView::Paint(gds::Surface &s){
	if(update || !bkSurf){
		uint32_t inW = rect.w - 1;
		uint32_t inH = rect.h - 1;

		if(!bkSurf){
			bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
			auto bkgCol = colours::GetBackground().Fix(*bkSurf);
			auto border = colours::GetBorder().Fix(*bkSurf);
			
			auto topLeft = colours::GetIconViewLowLight().Fix(*bkSurf);
			auto bottomRight = colours::GetIconViewHiLight().Fix(*bkSurf);

			bkSurf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
			drawing::Border(*bkSurf, {0, 0, inW, inH}, border);
			drawing::BevelBox(*bkSurf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);
		}
		s.Blit(*bkSurf, {0, 0, rect.w, rect.h}, rect);
		UpdateDisplayState(false);
		
		for(size_t line = vOffset; line < vOffset + visibleLines + 1; ++line){
			int32_t yPos = rect.y + (line - vOffset) * itemHeight;
			for(size_t col = 0; col < visibleCols; ++col){
				size_t idx = (line * visibleCols) + col;
				if(idx >= drawItems.size()) break;
				auto &item = drawItems[idx];
				
				int32_t xPos = rect.x + (col * itemWidth) + 1;
				
				if(!item.surf || item.selected != (idx == selectedItem) || (item.selected && item.focussed != hasFocus)){
					item.surf.reset(new gds::Surface(gds_SurfaceType::Vector, itemWidth, itemHeight, 100, gds_ColourType::True));
					auto txtCol = colours::GetIconViewText().Fix(*item.surf);
					auto itemBkgCol = colours::GetBackground().Fix(*item.surf);
					item.surf->BeginQueue();
					
					if(idx == selectedItem){
						auto selCol = colours::GetSelection().Fix(*item.surf);
						auto selFocus = colours::GetSelectionFocus().Fix(*item.surf);
						if(hasFocus){
							item.surf->Box({0, 0, itemWidth, itemHeight}, selCol, selCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
						}else{
							item.surf->Box({0, 0, itemWidth, itemHeight}, itemBkgCol, itemBkgCol, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
						}
						item.surf->Box({0, 0, itemWidth, itemHeight}, selFocus, selFocus, 1, gds_LineStyle::Solid);
						item.selected = true;
						item.focussed = hasFocus;
					}else{
						item.surf->Box({0, 0, itemWidth, itemHeight}, itemBkgCol, itemBkgCol, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
						item.selected = false;
					}
					
					
					if(icons[idx] || defaultIcon){
						auto &icon = icons[idx] ? icons[idx] : defaultIcon;
						int32_t iconX = (iconSize / 2);
						int32_t iconY = (iconSize / 3);
						if(iconY < (int32_t)rect.h) item.surf->Blit(*icon, {0, 0, iconSize, iconSize}, {iconX, iconY, iconSize, iconSize});
					}
					
					int32_t textX1 = ((itemWidth - item.measures1.w - (multiSelect ? checkSize : 0)) / 2) + (multiSelect ? checkSize : 0);
					int32_t textX2 = ((itemWidth - item.measures2.w - (multiSelect ? checkSize : 0)) / 2) + (multiSelect ? checkSize : 0);
					int32_t textY1 = (itemHeight - (fontHeight * 2)) + ((fontHeight + item.measures1.h) / 2);
					int32_t textY2 = (itemHeight - (fontHeight * 2)) + item.measures1.h + ((fontHeight + item.measures2.h) / 2);
					if(textY1 - fontHeight < rect.h) item.surf->Text({textX1, textY1}, item.fittedText1, fonts::GetIconViewFont(), fonts::GetIconViewTextSize(), txtCol);
					if(textY2 - fontHeight < rect.h) item.surf->Text({textX2, textY2}, item.fittedText2, fonts::GetIconViewFont(), fonts::GetIconViewTextSize(), txtCol);
					
					if(multiSelect){
						auto itemTopLeft = colours::GetIconViewLowLight().Fix(*item.surf);
						auto itemBottomRight = colours::GetIconViewHiLight().Fix(*item.surf);
						
						int32_t chkY = (itemHeight - checkSize);
						if(chkY < (int32_t)rect.h){
							auto bkgCol = colours::GetBackground().Fix(*item.surf);
							item.surf->Box({0, chkY + 1, checkSize - 2, checkSize - 2}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
							drawing::BevelBox(*item.surf, {0, chkY + 1, checkSize - 2, checkSize - 2}, itemTopLeft, itemBottomRight);
							if(multiSelection[idx]){
								item.surf->Line({0 + 3, chkY + 5}, {0 + checkSize - 5, (chkY + checkSize) - 4}, txtCol, 2);
								item.surf->Line({0 + 3,  (chkY + checkSize) - 4}, {0 + checkSize - 5, chkY + 5}, txtCol, 2);
							}
						}
					}
					item.surf->CommitQueue();
				}
				s.Blit(*item.surf, {0, 0, itemWidth, itemHeight}, {xPos, yPos, itemWidth, itemHeight});
			}
		}
		update = false;
	}

	if(vscroll) vscroll->Paint(s);
	
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(outerRect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect IconView::GetPaintRect(){
	return outerRect;
}

gds::Rect IconView::GetInteractRect(){
	return outerRect;
}

uint32_t IconView::GetSubscribed(){
	auto ret = wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown;
	if(vscroll) ret |= vscroll->GetSubscribed();
	return ret;
}

void IconView::Focus(){
	if(!hasFocus){
		update = true;
		hasFocus = true;
		IControl::Paint(outerRect);
	}
}

void IconView::Blur(){
	if(hasFocus){
		update = true;
		hasFocus = false;
		IControl::Paint(outerRect);
	}
}

uint32_t IconView::GetFlags(){
	return 0;
}

void IconView::Enable(){
	if(!enabled){
		enabled = true;
		IControl::Paint(rect);
	}
}

void IconView::Disable(){
	if(enabled){
		enabled = false;
		IControl::Paint(rect);
	}
}

bool IconView::IsEnabled(){
	return enabled;
}

void IconView::SetPosition(const gds::Rect &r){
	outerRect = r;
	rect = {r.x, r.y, r.w - scrollbarSize, r.h};
	if(vscroll) vscroll->SetPosition({outerRect.x + (int32_t)outerRect.w - scrollbarSize, outerRect.y, scrollbarSize, outerRect.h});
	update = true;
}

size_t IconView::GetValue(){
	return selectedItem;
}

void IconView::SetValue(size_t idx){
	if(selectedItem == idx) return;
	selectedItem = idx;
	update = true;
	UpdateDisplayState(true);
	fireCurrentSelection = true;
}

std::vector<bool> &IconView::MulitSelections(){
	return multiSelection;
}

std::vector<std::string> &IconView::Items(){
	return items;
}

void IconView::Refresh(){
	update = true;
	multiSelection.resize(items.size());
	icons.resize(items.size());
	drawItems.clear();
	fireCurrentSelection = true;
	IControl::Paint(outerRect);
}

void IconView::SetDefaultIcon(std::shared_ptr<gds::Surface> img){
	defaultIcon = img;
}

void IconView::SetItemIcon(size_t idx, std::shared_ptr<gds::Surface> img){
	if(icons.size() < items.size()) icons.resize(items.size());
	icons[idx] = img;
}

void IconView::ClearItemIcons(){
	icons.clear();
	icons.resize(items.size());
}

void IconView::OnActivate(std::function<void()> oA){
	onActivate = oA;
}

void IconView::OnInspect(std::function<void()> oI){
	onInspect = oI;
}

}
}