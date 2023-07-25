#include <gui/detaillist.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

#include <cctype>
#include <algorithm>
#include <numeric>

#include <util/tinyformat.hpp>

namespace btos_api{
namespace gui{

struct DetailListImpl{
	gds::Rect outerRect;
	gds::Rect rect;
	std::unique_ptr<gds::Surface> bkSurf;
	std::unique_ptr<gds::Surface> checkSurf;
	std::unique_ptr<gds::Surface> checkedSurf;
	
	std::vector<std::vector<std::string>> items;
	std::vector<std::shared_ptr<gds::Surface>> icons;
	std::vector<std::string> cols;
	
	std::vector<bool> multiSelection;
	
	struct DrawItem{
		std::string text;
		gds::TextMeasurements measures;
		std::string fittedText;
		uint32_t fittedWidth;
	};
	
	struct DrawCacheItem{
		std::unique_ptr<gds::Surface> surf;
		bool selected;
		bool focussed;
		uint32_t width;
	};
	
	std::vector<std::vector<DrawItem>> drawItems;
	std::vector<DrawCacheItem> drawCache;
	std::vector<uint32_t> colWidths;
	std::vector<DrawItem> colItems;
	
	std::shared_ptr<gds::Surface> defaultIcon;
	
	size_t fontHeight;
	
	size_t selectedItem = 0;
	size_t vOffset = 0;
	int32_t hOffset = 0;
	size_t visibleItems = 0;
	size_t iconsize = 0;
	
	bool hasFocus = false;
	bool enabled = true;
	bool fireCurrentSelection = true;
	bool measured = false;
	bool updateBkg = false;
	
	std::unique_ptr<Scrollbar> hscroll;
	std::unique_ptr<Scrollbar> vscroll;
	
	bool scrollHoriz;
	bool multiSelect;
	
	std::function<void()> onActivate;
	std::function<void()> onInspect;
	
	void UpdateDisplayState(bool changePos = true);
	void CalculateColumnWidths();
	std::string FitTextToCol(DrawItem &item, size_t colIndex);
	
	gds::Surface *CheckBox(bool checked);
};

PIMPL_IMPL(DetailListImpl);
	
const uint32_t scrollbarSize = 17;
const uint32_t checkSize = 17;

DetailList::DetailList(const gds::Rect &r, const std::vector<std::string> &c, bool sH, size_t is, bool mS) : im(new DetailListImpl()){
	im->outerRect = r;
	im->rect = (sH ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h});
	im->cols =c; im->iconsize = is; im->scrollHoriz = sH; im->multiSelect = mS;
	auto info = fonts::GetDetailListFont().Info();
	im->fontHeight = (info.maxH * fonts::GetDetailListTextSize()) / info.scale;
	if(im->multiSelect && im->fontHeight < checkSize) im->fontHeight = checkSize;
	
	im->vscroll.reset(new Scrollbar({im->outerRect.x + (int32_t)im->outerRect.w - (int32_t)scrollbarSize, im->outerRect.y, scrollbarSize, im->outerRect.h - (im->scrollHoriz ? scrollbarSize : 0)}, 1, 1, 1, 1, false));

	im->vscroll->OnChange([this] (uint32_t v) {
		im->vOffset = v;
	});
	
	im->UpdateDisplayState();
	
	if(im->scrollHoriz){
		im->CalculateColumnWidths();
		im->hscroll.reset(new Scrollbar({im->outerRect.x, im->outerRect.y + (int32_t)im->outerRect.h - (int32_t)scrollbarSize, im->outerRect.w - scrollbarSize, scrollbarSize}, 1, 1, 1, 1, true));
		
		im->hscroll->OnChange([this] (uint32_t v) {
			im->hOffset = v - (im->multiSelect ? checkSize : 0);
			im->updateBkg = true;
		});
	}
	if(im->multiSelect) im->hOffset = -checkSize;
}

void DetailListImpl::CalculateColumnWidths(){
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

void DetailListImpl::UpdateDisplayState(bool changePos){
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

std::string DetailListImpl::FitTextToCol(DrawItem &item, size_t colIndex){
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

gds::Surface *DetailListImpl::CheckBox(bool checked){
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
		if(code == (KeyFlags::NonASCII | KeyCodes::DownArrow) && im->selectedItem < im->items.size() - 1){
			++im->selectedItem;
			update = true;
			handled = true;
			im->UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::UpArrow) && im->selectedItem > 0){
			--im->selectedItem;
			update = true;
			handled = true;
			im->UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp)){
			if(im->selectedItem != 0){
				if(im->selectedItem > im->visibleItems) im->selectedItem -= im->visibleItems;
				else im->selectedItem = 0;
				update = true;
				im->UpdateDisplayState();
				RaiseChangeEvent();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown)){
			if(im->selectedItem < im->items.size() - 1){
				if(im->selectedItem + im->visibleItems < im->items.size()) im->selectedItem += im->visibleItems;
				else im->selectedItem = im->items.size() - 1;
				update = true;
				im->UpdateDisplayState();
				RaiseChangeEvent();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::Home)){
			if(im->selectedItem != 0){
				im->selectedItem = 0;
				update = true;
				im->UpdateDisplayState();
				RaiseChangeEvent();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::End)){
			if(im->selectedItem < im->items.size() - 1){
				im->selectedItem = im->items.size() - 1;
				update = true;
				im->UpdateDisplayState();
				RaiseChangeEvent();
			}
			handled = true;
		}else if(!(code & KeyFlags::NonASCII)){
			auto oldSelectedItem = im->selectedItem;
			char c = KB_char(e.Key.code);
			if(c == ' ' || c == '\n'){
				if(im->multiSelect){
					im->multiSelection[im->selectedItem] = !im->multiSelection[im->selectedItem];
					update = true;
				}else if(im->onActivate) im->onActivate();
			}else{
				c = std::tolower(c);
				auto finder = [&](const std::vector<std::string> &item){
					return !item.empty() && !item.front().empty() && std::tolower(item.front().front()) == c;
				};
				auto it = std::find_if(begin(im->items) + im->selectedItem + 1, end(im->items), finder);
				if(it == end(im->items)) it = std::find_if(begin(im->items), end(im->items), finder);
				if(it != end(im->items)) im->selectedItem = it - begin(im->items);
				if(oldSelectedItem != im->selectedItem || im->fireCurrentSelection){
					update = true;
					RaiseChangeEvent();
					im->fireCurrentSelection = false;
				}
			}
			handled = true;
			im->UpdateDisplayState();
		}
	}else if(e.type & wm_PointerEvents){
		if(InRect(e.Pointer.x, e.Pointer.y, im->rect)){
			if(e.type == wm_EventType::PointerButtonUp){
				auto oldSelectedItem = im->selectedItem;
				im->selectedItem = ((e.Pointer.y - im->outerRect.y) / im->fontHeight) + im->vOffset - 1;
				if(im->selectedItem < im->items.size()){
					if(oldSelectedItem != im->selectedItem || im->fireCurrentSelection){
						update = true;
						RaiseChangeEvent();
						im->fireCurrentSelection = false;
					}
				}
				if(im->multiSelect && (e.Pointer.x - im->outerRect.x) < checkSize + 1){
					im->multiSelection[im->selectedItem] = !im->multiSelection[im->selectedItem];
					update = true;
				}
				handled = true;
				if(IsDoubleClick() && im->onActivate) im->onActivate();
				im->UpdateDisplayState();
			}
		}else if(im->hscroll && im->hscroll->IsEnabled() && InRect(e.Pointer.x, e.Pointer.y, im->hscroll->GetInteractRect()) && (e.type & im->hscroll->GetSubscribed())){
			auto ret = im->hscroll->HandleEvent(e);
			update = ret.IsFinishedProcessing();
			handled = handled || update;
		}else if(im->vscroll && im->vscroll->IsEnabled() && InRect(e.Pointer.x, e.Pointer.y, im->vscroll->GetInteractRect()) && (e.type & im->vscroll->GetSubscribed())){
			auto ret = im->vscroll->HandleEvent(e);
			update = ret.IsFinishedProcessing();
			handled = handled || update;
		}
	}
	if(update) IControl::Paint(im->outerRect);
	return {handled};
}

void DetailList::Paint(gds::Surface &s){
	im->UpdateDisplayState(false);
	
	uint32_t inW = im->rect.w - 1;
	uint32_t inH = im->rect.h - 1;

	if(!im->bkSurf || im->updateBkg){
		if(!im->bkSurf) im->bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
		else im->bkSurf->Clear();

		auto bkgCol = colours::GetBackground().Fix(*im->bkSurf);
		auto txtCol = colours::GetDetailListText().Fix(*im->bkSurf);
		auto border = colours::GetBorder().Fix(*im->bkSurf);
		auto hdrCol = colours::GetDetailListHeader().Fix(*im->bkSurf);
		auto topLeft = colours::GetDetailListLowLight().Fix(*im->bkSurf);
		auto bottomRight = colours::GetDetailListHiLight().Fix(*im->bkSurf);
			
		im->bkSurf->BeginQueue();

		im->bkSurf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		im->bkSurf->Box({1, 1, inW, im->fontHeight}, hdrCol, hdrCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);

		for(size_t i = 0; i < im->cols.size(); ++i){
			auto &cItem = im->colItems[i];
			
			auto colOffset = std::accumulate(im->colWidths.begin(), im->colWidths.begin() + i, i + im->iconsize + 3);
			auto textX = ((int32_t)colOffset + 2) - (int32_t)im->hOffset;
			auto textY = std::max<int32_t>(((im->fontHeight + cItem.measures.h) / 2), 0);
			if((int32_t)colOffset + (int32_t)im->colWidths[i] < 0) continue;
			
			auto text = im->FitTextToCol(cItem, i);
			
			im->bkSurf->Text({textX, textY}, text, fonts::GetDetailListFont(), fonts::GetDetailListTextSize(), txtCol);
		}

		im->bkSurf->Line({1, (int32_t)im->fontHeight}, {(int32_t)inW, (int32_t)im->fontHeight}, border);
		drawing::Border(*im->bkSurf, {0, 0, inW, inH}, border);
		drawing::BevelBox(*im->bkSurf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);

		im->bkSurf->CommitQueue();
		if(!im->scrollHoriz) im->bkSurf->Compress();
		im->updateBkg = false;
	}
	s.Blit(*im->bkSurf,im->rect.AtZero(), im->rect);
		
	auto visibleItems = (inH / im->fontHeight);
	uint32_t itemWidth = std::accumulate(im->colWidths.begin(), im->colWidths.end(), im->colWidths.size()) + im->iconsize;
	if(itemWidth < inW) itemWidth = inW;
	
	for(auto i = im->vOffset; i < im->items.size() && i < im->vOffset + visibleItems; ++i){
		auto &dci = im->drawCache[i];
		if(!dci.surf || dci.width != itemWidth || dci.selected != (i == im->selectedItem) || (dci.selected && dci.focussed != im->hasFocus)){
			dci.surf.reset(new gds::Surface(gds_SurfaceType::Vector, itemWidth, im->fontHeight, 100, gds_ColourType::True));
			dci.width = itemWidth;
			dci.surf->BeginQueue();
			
			auto itemBkgCol = colours::GetBackground().Fix(*dci.surf);
			
			if(i == im->selectedItem){
				auto selCol = colours::GetSelection().Fix(*dci.surf);
				auto selFocus = colours::GetSelectionFocus().Fix(*dci.surf);
				if(im->hasFocus){
					dci.surf->Box({0, 0, itemWidth, im->fontHeight}, selCol, selCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				}else{
					dci.surf->Box({0, 0, itemWidth, im->fontHeight}, itemBkgCol, itemBkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				}
				dci.surf->Box({0, 0, itemWidth, im->fontHeight}, selFocus, selFocus, 1, gds_LineStyle::Solid);
				dci.selected = true;
				dci.focussed = im->hasFocus;
			}else{
				dci.surf->Box({0, 0, itemWidth, im->fontHeight}, itemBkgCol, itemBkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				dci.selected = false;
			}
		
			if(im->icons[i] || im->defaultIcon){
				auto icon = im->icons[i] ? im->icons[i] : im->defaultIcon;
				dci.surf->Blit(*icon, {0, 0, im->iconsize, im->iconsize}, {2, 0, im->iconsize, im->iconsize});
			}	
			
			auto itemTxtCol = colours::GetDetailListText().Fix(*dci.surf);
			
			for(size_t j = 0; j < im->items[i].size(); ++j){
				if(j > im->cols.size()) continue;
				auto &cItem = im->drawItems[i][j];
				auto colOffset = std::accumulate(im->colWidths.begin(), im->colWidths.begin() + j, j + im->iconsize + 1);
				
				auto textX = ((int32_t)colOffset + 2);
				auto textY = std::max<int32_t>(((im->fontHeight + cItem.measures.h) / 2), 0);
				
				auto text = im->FitTextToCol(cItem, j);
				
				dci.surf->Text({textX, textY}, text, fonts::GetDetailListFont(), fonts::GetDetailListTextSize(), itemTxtCol);
			}
			dci.surf->CommitQueue();
			if(i != im->selectedItem) dci.surf->Compress();
		}
		int32_t itemX = im->rect.x - im->hOffset;
		int32_t itemY = im->rect.y + ((i - im->vOffset) + 1) * im->fontHeight;
		uint32_t drawWidth = std::min(itemWidth, im->rect.w) - (im->multiSelect ? checkSize : 0) - 3;
		uint32_t drawHeight = std::min<uint32_t>(im->fontHeight, ((im->rect.y + im->rect.h) - itemY) - 3);
		s.Blit(*dci.surf, {0, 0, drawWidth, drawHeight}, {itemX + 2, itemY + 1, drawWidth, drawHeight});

		if(im->multiSelect){
			int32_t chkY = im->rect.y + 1 + im->fontHeight * ((i + 1) - im->vOffset);
			auto checkHeight = std::min(checkSize, drawHeight);
			auto check = im->CheckBox(im->multiSelection[i]);
			s.Blit(*check, {0, 0, checkSize, checkHeight}, {im->rect.x + 2, chkY, checkSize, checkHeight});
		}
	}

	if(im->hscroll) im->hscroll->Paint(s);
	if(im->vscroll) im->vscroll->Paint(s);
	
	if(!im->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(im->outerRect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect DetailList::GetPaintRect(){
	return im->outerRect;
}

gds::Rect DetailList::GetInteractRect(){
	return im->outerRect;
}

uint32_t DetailList::GetSubscribed(){
	auto ret = wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown;
	if(im->hscroll) ret |= im->hscroll->GetSubscribed();
	if(im->vscroll) ret |= im->vscroll->GetSubscribed();
	return ret;
}

void DetailList::Focus(){
	if(!im->hasFocus){
		im->hasFocus = true;
		IControl::Paint(im->outerRect);
	}
}

void DetailList::Blur(){
	if(im->hasFocus){
		im->hasFocus = false;
		IControl::Paint(im->outerRect);
	}
}

uint32_t DetailList::GetFlags(){
	return 0;
}

void DetailList::Enable(){
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(im->rect);
	}
}

void DetailList::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(im->rect);
	}
}

bool DetailList::IsEnabled(){
	return im->enabled;
}

void DetailList::SetPosition(const gds::Rect &r){
	im->outerRect = r;
	im->rect = im->scrollHoriz ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h};
	if(im->vscroll) im->vscroll->SetPosition({im->outerRect.x + (int32_t)im->outerRect.w - (int32_t)scrollbarSize, im->outerRect.y, scrollbarSize, im->outerRect.h - (im->scrollHoriz ? scrollbarSize : 0)});
	if(im->hscroll) im->hscroll->SetPosition({im->outerRect.x, im->outerRect.y + (int32_t)im->outerRect.h - (int32_t)scrollbarSize, im->outerRect.w - scrollbarSize, scrollbarSize});
	im->bkSurf.reset();
}

size_t DetailList::GetValue(){
	return im->selectedItem;
}

void DetailList::SetValue(size_t idx){
	if(im->selectedItem == idx) return;
	im->selectedItem = idx;
	im->UpdateDisplayState(true);
	im->fireCurrentSelection = true;
}

std::vector<bool> &DetailList::MulitSelections(){
	return im->multiSelection;
}

std::vector<std::vector<std::string>> &DetailList::Items(){
	return im->items;
}

std::vector<std::string> &DetailList::Columns(){
	return im->cols;
}

std::vector<uint32_t> &DetailList::ColumnWidths(){
	return im->colWidths;
}

void DetailList::Refresh(){
	im->colWidths.resize(im->cols.size());
	im->icons.resize(im->items.size());
	im->multiSelection.resize(im->items.size());
	im->fireCurrentSelection = true;
	im->drawCache.clear();
	im->drawCache.resize(im->items.size());
	im->measured = false;
	im->bkSurf.reset();
	IControl::Paint(im->outerRect);
}

void DetailList::SetDefaultIcon(std::shared_ptr<gds::Surface> img){
	im->defaultIcon = img;
}

void DetailList::SetItemIcon(size_t idx, std::shared_ptr<gds::Surface> img){
	if(im->icons.size() < im->items.size()) im->icons.resize(im->items.size());
	im->icons[idx] = img;
}

void DetailList::ClearItemIcons(){
	im->icons.clear();
	im->icons.resize(im->items.size());
}

void DetailList::OnActivate(std::function<void()> oA){
	im->onActivate = oA;
}

void DetailList::OnInspect(std::function<void()> oI){
	im->onInspect = oI;
}

}
}