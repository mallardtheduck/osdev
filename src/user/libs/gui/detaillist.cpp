#include <gui/detaillist.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

#include <cctype>
#include <algorithm>

#include <util/tinyformat.hpp>

namespace btos_api{
namespace gui{
	
const uint32_t scrollbarSize = 17;
const uint32_t checkSize = 17;

DetailList::DetailList(const gds::Rect &r, const std::vector<std::string> &c, bool sH, size_t is, bool mS) : 
	outerRect(r), 
	rect(sH ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h}),
	cols(c), iconsize(is), scrollHoriz(sH), multiSelect(mS){
	auto info = fonts::GetDetailListFont().Info();
	fontHeight = (info.maxH * fonts::GetDetailListTextSize()) / info.scale;
	if(multiSelect && fontHeight < checkSize) fontHeight = checkSize;
	
	vscroll.reset(new Scrollbar({outerRect.x + (int32_t)outerRect.w - (int32_t)scrollbarSize, outerRect.y, scrollbarSize, outerRect.h - (scrollHoriz ? scrollbarSize : 0)}, 1, 1, 1, 1, false));

	vscroll->OnChange([this] (uint32_t v) {
		vOffset = v;
	});
	
	UpdateDisplayState();
	
	if(scrollHoriz){
		CalculateColumnWidths();
		hscroll.reset(new Scrollbar({outerRect.x, outerRect.y + (int32_t)outerRect.h - (int32_t)scrollbarSize, outerRect.w - scrollbarSize, scrollbarSize}, 1, 1, 1, 1, true));
		
		hscroll->OnChange([this] (uint32_t v) {
			hOffset = v - (multiSelect ? checkSize : 0);
			updateBkg = true;
		});
	}
	if(multiSelect) hOffset = -checkSize;
}

void DetailList::CalculateColumnWidths(){
	colWidths.resize(cols.size());
	for(size_t i = 0; i < cols.size(); ++i){
		uint32_t maxW = colItems[i].measures.w;
		for(const auto &di : drawItems){
			if(di.size() > i && di[i].measures.w > maxW) maxW = di[i].measures.w;
		}
		colWidths[i] = maxW + 1;
	}
	auto availableWidth = rect.w - iconsize - (multiSelect ? checkSize : 0);
	while(std::accumulate(colWidths.begin(), colWidths.end(), colWidths.size()) > availableWidth){
		auto maxIt = std::max_element(colWidths.begin(), colWidths.end());
		--*maxIt;
	}
}

void DetailList::UpdateDisplayState(bool changePos){
	auto surf = gds::Surface(gds_SurfaceType::Vector, 1, 1, 100, gds_ColourType::True);
	
	visibleItems = (rect.h / fontHeight) - 1;
	if(changePos){
		if(selectedItem < vOffset) vOffset = selectedItem;
		if(selectedItem >= vOffset + (visibleItems - 1)) vOffset = std::max<int32_t>(0, (int32_t)(selectedItem - (visibleItems - 1)));
	}
	
	if(!measured){
		drawItems.resize(items.size());
		for(size_t i = 0; i < items.size(); ++i){
			drawItems[i].resize(items[i].size());
			for(size_t j = 0; j < items[i].size(); ++j){
				auto &di = drawItems[i][j];
				auto &it = items[i][j];
				if(di.text != it || !di.measures.w){
					di.text = it;
					di.measures = surf.MeasureText(it, fonts::GetDetailListFont(), fonts::GetDetailListTextSize());
					di.fittedText = "";
					di.fittedWidth = 0;
				}
			}
		}
		
		colItems.resize(cols.size());
		for(size_t i = 0; i < cols.size(); ++i){
			auto &di = colItems[i];
			auto &ci = cols[i];
			if(di.text != ci || !di.measures.w){
				di.text = ci;
				di.measures = surf.MeasureText(ci, fonts::GetDetailListFont(), fonts::GetDetailListTextSize());
				di.fittedText = "";
				di.fittedWidth = 0;
			}
		}
		measured = true;
	}
	
	if(vscroll){
		if(visibleItems < items.size()){
			auto scrollLines = std::max<int32_t>((int32_t)items.size() - visibleItems, 1);
			if((int32_t)vOffset > scrollLines) vOffset = scrollLines;
			vscroll->Enable();
			vscroll->SetLines(scrollLines);
			vscroll->SetPage(visibleItems);
			vscroll->SetValue(vOffset);
		}else{
			vscroll->Disable();
			vscroll->SetLines(1);
			vscroll->SetPage(1);
			vscroll->SetValue(0);
			vOffset = 0;
		}
	}
	
	if(hscroll){
		auto overallWidth = std::accumulate(colWidths.begin(), colWidths.end(), colWidths.size());
		if(overallWidth > rect.w - 2){
			hscroll->Enable();
		 	hscroll->SetLines(overallWidth - (rect.w - 2));
		 	hscroll->SetPage(rect.w - 2);
		 	hscroll->SetValue(hOffset + (multiSelect ? checkSize : 0));
		 	hscroll->SetStep(fonts::GetDetailListTextSize() / 2);
		}else{
			hscroll->Disable();
			hscroll->SetLines(1);
			hscroll->SetPage(1);
			hscroll->SetValue(0);
			hOffset = (multiSelect ? -checkSize : 0);
		}
	}else{
		CalculateColumnWidths();
	}
}

std::string DetailList::FitTextToCol(DrawItem &item, size_t colIndex){
	auto surf = gds::Surface(gds_SurfaceType::Vector, 1, 1, 100, gds_ColourType::True);
	auto width = colWidths[colIndex];
	if(item.fittedWidth == width) return item.fittedText;
	if(item.measures.w < width){
		item.fittedWidth = width;
		item.fittedText = item.text;
		return item.text;	
	}
	
	std::string suffix = "\xE2\x80\xA6";
	if(width < surf.MeasureText(suffix, fonts::GetDetailListFont(), fonts::GetDetailListTextSize()).w) suffix = "";
	std::string text = item.text;
	while(surf.MeasureText(text + suffix, fonts::GetDetailListFont(), fonts::GetDetailListTextSize()).w > width){
		text.pop_back();
	}
	
	item.fittedText = text + suffix;
	item.fittedWidth = width;
	return item.fittedText;
}

gds::Surface *DetailList::CheckBox(bool checked){
	if(checked && checkedSurf) return checkedSurf.get();
	if(!checked && checkSurf) return checkSurf.get();
	
	std::unique_ptr<gds::Surface> surf(new gds::Surface(gds_SurfaceType::Vector, checkSize, checkSize, 100, gds_ColourType::True));
	
	surf->BeginQueue();
	auto topLeft = colours::GetDetailListLowLight().Fix(*surf);
	auto bottomRight = colours::GetDetailListHiLight().Fix(*surf);
	auto bkgCol = colours::GetBackground().Fix(*surf);
	auto txtCol = colours::GetDetailListText().Fix(*surf);
	
	surf->Box({0, 0, checkSize, checkSize}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	drawing::BevelBox(*surf, {1, 1, checkSize - 2, checkSize - 2}, topLeft, bottomRight);
	if(checked){
		surf->Line({4, 4}, {checkSize - 4, checkSize - 4}, txtCol, 2);
		surf->Line({4,  checkSize - 4}, {checkSize - 4, 4}, txtCol, 2);
	}
	surf->CommitQueue();
	surf->Compress();
	
	if(checked){
		checkedSurf = std::move(surf);
		return checkedSurf.get();
	}else{
		checkSurf = std::move(surf);
		return checkSurf.get();
	}
}

EventResponse DetailList::HandleEvent(const wm_Event &e){
	bool handled = false;
	bool update = true;
	if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(code == (KeyFlags::NonASCII | KeyCodes::DownArrow) && selectedItem < items.size() - 1){
			++selectedItem;
			update = true;
			handled = true;
			UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::UpArrow) && selectedItem > 0){
			--selectedItem;
			update = true;
			handled = true;
			UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp)){
			if(selectedItem != 0){
				if(selectedItem > visibleItems) selectedItem -= visibleItems;
				else selectedItem = 0;
				update = true;
				UpdateDisplayState();
				RaiseChangeEvent();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown)){
			if(selectedItem < items.size() - 1){
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
				auto finder = [&](const std::vector<std::string> &item){
					return !item.empty() && !item.front().empty() && std::tolower(item.front().front()) == c;
				};
				auto it = std::find_if(begin(items) + selectedItem + 1, end(items), finder);
				if(it == end(items)) it = std::find_if(begin(items), end(items), finder);
				if(it != end(items)) selectedItem = it - begin(items);
				if(oldSelectedItem != selectedItem || fireCurrentSelection){
					update = true;
					RaiseChangeEvent();
					fireCurrentSelection = false;
				}
			}
			handled = true;
			UpdateDisplayState();
		}
	}else if(e.type & wm_PointerEvents){
		if(InRect(e.Pointer.x, e.Pointer.y, rect)){
			if(e.type == wm_EventType::PointerButtonUp){
				auto oldSelectedItem = selectedItem;
				selectedItem = ((e.Pointer.y - outerRect.y) / fontHeight) + vOffset - 1;
				if(selectedItem < items.size()){
					if(oldSelectedItem != selectedItem || fireCurrentSelection){
						update = true;
						RaiseChangeEvent();
						fireCurrentSelection = false;
					}
				}
				if(multiSelect && (e.Pointer.x - outerRect.x) < checkSize + 1){
					multiSelection[selectedItem] = !multiSelection[selectedItem];
					update = true;
				}
				handled = true;
				if(IsDoubleClick() && onActivate) onActivate();
				UpdateDisplayState();
			}
		}else if(hscroll && hscroll->IsEnabled() && InRect(e.Pointer.x, e.Pointer.y, hscroll->GetInteractRect()) && (e.type & hscroll->GetSubscribed())){
			auto ret = hscroll->HandleEvent(e);
			update = ret.IsFinishedProcessing();
			handled = handled || update;
		}else if(vscroll && vscroll->IsEnabled() && InRect(e.Pointer.x, e.Pointer.y, vscroll->GetInteractRect()) && (e.type & vscroll->GetSubscribed())){
			auto ret = vscroll->HandleEvent(e);
			update = ret.IsFinishedProcessing();
			handled = handled || update;
		}
	}
	if(update) IControl::Paint(outerRect);
	return {handled};
}

void DetailList::Paint(gds::Surface &s){
	UpdateDisplayState(false);
	
	uint32_t inW = rect.w - 1;
	uint32_t inH = rect.h - 1;

	if(!bkSurf || updateBkg){
		if(!bkSurf) bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		else bkSurf->Clear();

		auto bkgCol = colours::GetBackground().Fix(*bkSurf);
		auto txtCol = colours::GetDetailListText().Fix(*bkSurf);
		auto border = colours::GetBorder().Fix(*bkSurf);
		auto hdrCol = colours::GetDetailListHeader().Fix(*bkSurf);
		auto topLeft = colours::GetDetailListLowLight().Fix(*bkSurf);
		auto bottomRight = colours::GetDetailListHiLight().Fix(*bkSurf);
			
		bkSurf->BeginQueue();

		bkSurf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		bkSurf->Box({1, 1, inW, fontHeight}, hdrCol, hdrCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);

		for(size_t i = 0; i < cols.size(); ++i){
			auto &cItem = colItems[i];
			
			auto colOffset = std::accumulate(colWidths.begin(), colWidths.begin() + i, i + iconsize + 3);
			auto textX = ((int32_t)colOffset + 2) - (int32_t)hOffset;
			auto textY = std::max<int32_t>(((fontHeight + cItem.measures.h) / 2), 0);
			if((int32_t)colOffset + (int32_t)colWidths[i] < 0) continue;
			
			auto text = FitTextToCol(cItem, i);
			
			bkSurf->Text({textX, textY}, text, fonts::GetDetailListFont(), fonts::GetDetailListTextSize(), txtCol);
		}

		bkSurf->Line({1, (int32_t)fontHeight}, {(int32_t)inW, (int32_t)fontHeight}, border);
		drawing::Border(*bkSurf, {0, 0, inW, inH}, border);
		drawing::BevelBox(*bkSurf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);

		bkSurf->CommitQueue();
		if(!scrollHoriz) bkSurf->Compress();
		updateBkg = false;
	}
	s.Blit(*bkSurf, {0, 0, rect.w, rect.h}, rect);
		
	auto visibleItems = (inH / fontHeight);
	uint32_t itemWidth = std::accumulate(colWidths.begin(), colWidths.end(), colWidths.size()) + iconsize;
	if(itemWidth < inW) itemWidth = inW;
	
	for(auto i = vOffset; i < items.size() && i < vOffset + visibleItems; ++i){
		auto &dci = drawCache[i];
		if(!dci.surf || dci.width != itemWidth || dci.selected != (i == selectedItem) || (dci.selected && dci.focussed != hasFocus)){
			dci.surf.reset(new gds::Surface(gds_SurfaceType::Vector, itemWidth, fontHeight, 100, gds_ColourType::True));
			dci.width = itemWidth;
			dci.surf->BeginQueue();
			
			auto itemBkgCol = colours::GetBackground().Fix(*dci.surf);
			
			if(i == selectedItem){
				auto selCol = colours::GetSelection().Fix(*dci.surf);
				auto selFocus = colours::GetSelectionFocus().Fix(*dci.surf);
				if(hasFocus){
					dci.surf->Box({0, 0, itemWidth, fontHeight}, selCol, selCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				}else{
					dci.surf->Box({0, 0, itemWidth, fontHeight}, itemBkgCol, itemBkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				}
				dci.surf->Box({0, 0, itemWidth, fontHeight}, selFocus, selFocus, 1, gds_LineStyle::Solid);
				dci.selected = true;
				dci.focussed = hasFocus;
			}else{
				dci.surf->Box({0, 0, itemWidth, fontHeight}, itemBkgCol, itemBkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				dci.selected = false;
			}
		
			if(icons[i] || defaultIcon){
				auto icon = icons[i] ? icons[i] : defaultIcon;
				dci.surf->Blit(*icon, {0, 0, iconsize, iconsize}, {2, 0, iconsize, iconsize});
			}	
			
			auto itemTxtCol = colours::GetDetailListText().Fix(*dci.surf);
			
			for(size_t j = 0; j < items[i].size(); ++j){
				if(j > cols.size()) continue;
				auto &cItem = drawItems[i][j];
				auto colOffset = std::accumulate(colWidths.begin(), colWidths.begin() + j, j + iconsize + 1);
				
				auto textX = ((int32_t)colOffset + 2);
				auto textY = std::max<int32_t>(((fontHeight + cItem.measures.h) / 2), 0);
				
				auto text = FitTextToCol(cItem, j);
				
				dci.surf->Text({textX, textY}, text, fonts::GetDetailListFont(), fonts::GetDetailListTextSize(), itemTxtCol);
			}
			dci.surf->CommitQueue();
			if(i != selectedItem) dci.surf->Compress();
		}
		int32_t itemX = rect.x - hOffset;
		int32_t itemY = rect.y + ((i - vOffset) + 1) * fontHeight;
		uint32_t drawWidth = std::min(itemWidth, rect.w) - (multiSelect ? checkSize : 0) - 3;
		uint32_t drawHeight = std::min<uint32_t>(fontHeight, ((rect.y + rect.h) - itemY) - 3);
		s.Blit(*dci.surf, {0, 0, drawWidth, drawHeight}, {itemX + 2, itemY + 1, drawWidth, drawHeight});

		if(multiSelect){
			int32_t chkY = rect.y + 1 + fontHeight * ((i + 1) - vOffset);
			auto checkHeight = std::min(checkSize, drawHeight);
			auto check = CheckBox(multiSelection[i]);
			s.Blit(*check, {0, 0, checkSize, checkHeight}, {rect.x + 2, chkY, checkSize, checkHeight});
		}
	}

	if(hscroll) hscroll->Paint(s);
	if(vscroll) vscroll->Paint(s);
	
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(outerRect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect DetailList::GetPaintRect(){
	return outerRect;
}

gds::Rect DetailList::GetInteractRect(){
	return outerRect;
}

uint32_t DetailList::GetSubscribed(){
	auto ret = wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown;
	if(hscroll) ret |= hscroll->GetSubscribed();
	if(vscroll) ret |= vscroll->GetSubscribed();
	return ret;
}

void DetailList::Focus(){
	if(!hasFocus){
		hasFocus = true;
		IControl::Paint(outerRect);
	}
}

void DetailList::Blur(){
	if(hasFocus){
		hasFocus = false;
		IControl::Paint(outerRect);
	}
}

uint32_t DetailList::GetFlags(){
	return 0;
}

void DetailList::Enable(){
	if(!enabled){
		enabled = true;
		IControl::Paint(rect);
	}
}

void DetailList::Disable(){
	if(enabled){
		enabled = false;
		IControl::Paint(rect);
	}
}

bool DetailList::IsEnabled(){
	return enabled;
}

void DetailList::SetPosition(const gds::Rect &r){
	outerRect = r;
	rect = scrollHoriz ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h};
	if(vscroll) vscroll->SetPosition({outerRect.x + (int32_t)outerRect.w - (int32_t)scrollbarSize, outerRect.y, scrollbarSize, outerRect.h - (scrollHoriz ? scrollbarSize : 0)});
	if(hscroll) hscroll->SetPosition({outerRect.x, outerRect.y + (int32_t)outerRect.h - (int32_t)scrollbarSize, outerRect.w - scrollbarSize, scrollbarSize});
	bkSurf.reset();
}

size_t DetailList::GetValue(){
	return selectedItem;
}

void DetailList::SetValue(size_t idx){
	if(selectedItem == idx) return;
	selectedItem = idx;
	UpdateDisplayState(true);
	fireCurrentSelection = true;
}

std::vector<bool> &DetailList::MulitSelections(){
	return multiSelection;
}

std::vector<std::vector<std::string>> &DetailList::Items(){
	return items;
}

std::vector<std::string> &DetailList::Columns(){
	return cols;
}

std::vector<uint32_t> &DetailList::ColumnWidths(){
	return colWidths;
}

void DetailList::Refresh(){
	colWidths.resize(cols.size());
	icons.resize(items.size());
	multiSelection.resize(items.size());
	fireCurrentSelection = true;
	drawCache.clear();
	drawCache.resize(items.size());
	measured = false;
	bkSurf.reset();
	IControl::Paint(outerRect);
}

void DetailList::SetDefaultIcon(std::shared_ptr<gds::Surface> img){
	defaultIcon = img;
}

void DetailList::SetItemIcon(size_t idx, std::shared_ptr<gds::Surface> img){
	if(icons.size() < items.size()) icons.resize(items.size());
	icons[idx] = img;
}

void DetailList::ClearItemIcons(){
	icons.clear();
	icons.resize(items.size());
}

void DetailList::OnActivate(std::function<void()> oA){
	onActivate = oA;
}

void DetailList::OnInspect(std::function<void()> oI){
	onInspect = oI;
}

}
}