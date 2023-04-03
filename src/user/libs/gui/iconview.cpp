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

struct IconViewImpl{
	gds::Rect outerRect;
	gds::Rect rect; 
	std::unique_ptr<gds::Surface> bkSurf;
	
	std::vector<std::string> items;
	std::vector<bool> multiSelection;
	
	struct DrawItem{
		std::string text;
		gds::TextMeasurements measures1;
		gds::TextMeasurements measures2;
		std::string fittedText1;
		std::string fittedText2;
		uint32_t fittedWidth;
		std::unique_ptr<gds::Surface> surf;
		bool selected;
		bool focussed;
	};
	
	std::vector<DrawItem> drawItems;
	std::shared_ptr<gds::Surface> defaultIcon;
	std::vector<std::shared_ptr<gds::Surface>> icons;
	
	size_t fontHeight;
	size_t iconSize;
	
	size_t itemWidth, itemHeight;
	size_t selectedItem = 0;
	size_t vOffset = 0;
	size_t visibleLines = 0;
	size_t visibleCols = 0;
	
	bool hasFocus = false;
	bool enabled = true;
	bool fireCurrentSelection = true;
	
	std::unique_ptr<Scrollbar> vscroll;
	
	bool multiSelect;
	
	std::function<void()> onActivate;
	std::function<void()> onInspect;
	
	void UpdateDisplayState(bool changePos = true);
	void FitTextToWidth(DrawItem &item, size_t width);
};
PIMPL_IMPL(IconViewImpl);

IconView::IconView(const gds::Rect &r, size_t iS, bool mS) : im(new IconViewImpl()) {
	im->outerRect = r;
	im->rect = {r.x, r.y, r.w - scrollbarSize, r.h};
	im->iconSize = iS;
	im->multiSelect = mS;
	auto info = fonts::GetIconViewFont().Info();
	im->fontHeight = (info.maxH * fonts::GetIconViewTextSize()) / info.scale;
	if(im->multiSelect && im->fontHeight < checkSize) im->fontHeight = checkSize;
	im->itemWidth = im->iconSize * 2;
	im->itemHeight = std::max<size_t>((im->iconSize * 2), (im->iconSize * 1.5) + (im->fontHeight * 2));
	
	im->vscroll.reset(new Scrollbar({im->outerRect.x + (int32_t)im->outerRect.w - scrollbarSize, im->outerRect.y, scrollbarSize, im->outerRect.h}, 1, 1, 1, 1, false));
	
	im->vscroll->OnChange([this] (uint32_t v) {
		im->vOffset = v;
	});
	
	im->UpdateDisplayState();
}

void IconViewImpl::UpdateDisplayState(bool changePos){
	visibleLines = (rect.h - 4) / itemHeight;
	visibleCols = (rect.w - 4) / itemWidth;
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

void IconViewImpl::FitTextToWidth(DrawItem &item, size_t width){
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
	bool update = false;
	if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(code == (KeyFlags::NonASCII | KeyCodes::DownArrow) && im->selectedItem < im->items.size() - 1){
			im->selectedItem += im->visibleCols;
			if(im->selectedItem >= im->items.size()) im->selectedItem = im->items.size() - 1;
			update = true;
			handled = true;
			im->UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::UpArrow) && im->selectedItem > 0){
			im->selectedItem -= std::min(im->selectedItem, im->visibleCols);
			update = true;
			handled = true;
			im->UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && im->selectedItem < im->items.size() - 1){
			++im->selectedItem;
			update = true;
			handled = true;
			im->UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && im->selectedItem > 0){
			--im->selectedItem;
			update = true;
			handled = true;
			im->UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp)){
			if(im->selectedItem != 0){
				auto visibleItems = (im->visibleLines - 1) * im->visibleCols;
				if(im->selectedItem > visibleItems) im->selectedItem -= visibleItems;
				else im->selectedItem = 0;
				update = true;
				im->UpdateDisplayState();
				RaiseChangeEvent();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown)){
			if(im->selectedItem < im->items.size() - 1){
				auto visibleItems = (im->visibleLines - 1) * im->visibleCols;
				if(im->selectedItem + visibleItems < im->items.size()) im->selectedItem += visibleItems;
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
				auto finder = [&](const std::string &item){return !item.empty() && std::tolower(item.front()) == c;};
				auto it = std::find_if(begin(im->items) + im->selectedItem + 1, end(im->items), finder);
				if(it == end(im->items)) it = std::find_if(begin(im->items), end(im->items), finder);
				if(it != end(im->items)) im->selectedItem = it - begin(im->items);
				update = oldSelectedItem != im->selectedItem;
				if(update || im->fireCurrentSelection){ 
					RaiseChangeEvent();
					im->fireCurrentSelection = false;
				}
			}
			handled = true;
			im->UpdateDisplayState();
		}
	}else if(e.type & wm_PointerEvents){
		if(InRect(e.Pointer.x, e.Pointer.y, im->rect)){
			auto pX = e.Pointer.x - im->outerRect.x;
			auto pY = e.Pointer.y - im->outerRect.y;
			auto col = pX / im->itemWidth;
			if(col >= im->visibleCols) col = im->visibleCols - 1;
			auto line = (pY / im->itemHeight) + im->vOffset;
			auto idx = (line * im->visibleCols) + col;
			if(e.type == wm_EventType::PointerButtonUp && idx < im->items.size()){
				auto oldSelectedItem = im->selectedItem;
				im->selectedItem = idx;
				if(im->selectedItem < im->items.size()) update = oldSelectedItem != im->selectedItem;
				if(update || im->fireCurrentSelection){ 
					RaiseChangeEvent();
					im->fireCurrentSelection = false;
				}
				if(im->multiSelect){
					auto xPos = pX - (col * im->itemWidth);
					auto yPos = pY - (line * im->itemHeight);
					if(xPos < checkSize && yPos > (im->itemHeight - checkSize)){
						im->multiSelection[im->selectedItem] = !im->multiSelection[im->selectedItem];
						update = true;
					}
				}
				handled = true;
				if(IsDoubleClick() && im->onActivate) im->onActivate();
				im->UpdateDisplayState();
			}
		}else if(im->vscroll && im->vscroll->IsEnabled() && InRect(e.Pointer.x, e.Pointer.y, im->vscroll->GetInteractRect()) && (e.type & im->vscroll->GetSubscribed())){
			auto ret = im->vscroll->HandleEvent(e);
			update = ret.IsFinishedProcessing();
			handled = handled || update;
		}
	}
	if(update) IControl::Paint(im->outerRect);
	return {handled};
}

void IconView::Paint(gds::Surface &s){
	uint32_t inW = im->rect.w - 1;
	uint32_t inH = im->rect.h - 1;

	if(!im->bkSurf){
		im->bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
		auto bkgCol = colours::GetBackground().Fix(*im->bkSurf);
		auto border = colours::GetBorder().Fix(*im->bkSurf);
		
		auto topLeft = colours::GetIconViewLowLight().Fix(*im->bkSurf);
		auto bottomRight = colours::GetIconViewHiLight().Fix(*im->bkSurf);

		im->bkSurf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		drawing::Border(*im->bkSurf, {0, 0, inW, inH}, border);
		drawing::BevelBox(*im->bkSurf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);
	}
	s.Blit(*im->bkSurf, im->rect.AtZero(), im->rect);
	im->UpdateDisplayState(false);
	
	for(size_t line = im->vOffset; line < im->vOffset + im->visibleLines + 1; ++line){
		int32_t yPos = im->rect.y + (line - im->vOffset) * im->itemHeight;
		for(size_t col = 0; col < im->visibleCols; ++col){
			size_t idx = (line * im->visibleCols) + col;
			if(idx >= im->drawItems.size()) break;
			auto &item = im->drawItems[idx];
			
			int32_t xPos = im->rect.x + (col * im->itemWidth) + 1;
			
			if(!item.surf || item.selected != (idx == im->selectedItem) || (item.selected && item.focussed != im->hasFocus)){
				item.surf.reset(new gds::Surface(gds_SurfaceType::Vector, im->itemWidth, im->itemHeight, 100, gds_ColourType::True));
				auto txtCol = colours::GetIconViewText().Fix(*item.surf);
				auto itemBkgCol = colours::GetBackground().Fix(*item.surf);
				item.surf->BeginQueue();
				
				if(idx == im->selectedItem){
					auto selCol = colours::GetSelection().Fix(*item.surf);
					auto selFocus = colours::GetSelectionFocus().Fix(*item.surf);
					if(im->hasFocus){
						item.surf->Box({0, 0, im->itemWidth, im->itemHeight}, selCol, selCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
					}else{
						item.surf->Box({0, 0, im->itemWidth, im->itemHeight}, itemBkgCol, itemBkgCol, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
					}
					item.surf->Box({0, 0, im->itemWidth, im->itemHeight}, selFocus, selFocus, 1, gds_LineStyle::Solid);
					item.selected = true;
					item.focussed = im->hasFocus;
				}else{
					item.surf->Box({0, 0, im->itemWidth, im->itemHeight}, itemBkgCol, itemBkgCol, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
					item.selected = false;
				}
				
				
				if(im->icons[idx] || im->defaultIcon){
					auto &icon = im->icons[idx] ? im->icons[idx] : im->defaultIcon;
					int32_t iconX = (im->iconSize / 2);
					int32_t iconY = (im->iconSize / 3);
					if(iconY < (int32_t)im->rect.h) item.surf->Blit(*icon, {0, 0, im->iconSize, im->iconSize}, {iconX, iconY, im->iconSize, im->iconSize});
				}
				
				int32_t textX1 = ((im->itemWidth - item.measures1.w - (im->multiSelect ? checkSize : 0)) / 2) + (im->multiSelect ? checkSize : 0);
				int32_t textX2 = ((im->itemWidth - item.measures2.w - (im->multiSelect ? checkSize : 0)) / 2) + (im->multiSelect ? checkSize : 0);
				int32_t textY1 = (im->itemHeight - (im->fontHeight * 2)) + ((im->fontHeight + item.measures1.h) / 2);
				int32_t textY2 = (im->itemHeight - (im->fontHeight * 2)) + item.measures1.h + ((im->fontHeight + item.measures2.h) / 2);
				if(textY1 - im->fontHeight < im->rect.h) item.surf->Text({textX1, textY1}, item.fittedText1, fonts::GetIconViewFont(), fonts::GetIconViewTextSize(), txtCol);
				if(textY2 - im->fontHeight < im->rect.h) item.surf->Text({textX2, textY2}, item.fittedText2, fonts::GetIconViewFont(), fonts::GetIconViewTextSize(), txtCol);
				
				if(im->multiSelect){
					auto itemTopLeft = colours::GetIconViewLowLight().Fix(*item.surf);
					auto itemBottomRight = colours::GetIconViewHiLight().Fix(*item.surf);
					
					int32_t chkY = (im->itemHeight - checkSize);
					if(chkY < (int32_t)im->rect.h){
						auto bkgCol = colours::GetBackground().Fix(*item.surf);
						item.surf->Box({0, chkY + 1, checkSize - 2, checkSize - 2}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
						drawing::BevelBox(*item.surf, {0, chkY + 1, checkSize - 2, checkSize - 2}, itemTopLeft, itemBottomRight);
						if(im->multiSelection[idx]){
							item.surf->Line({0 + 3, chkY + 5}, {0 + checkSize - 5, (chkY + checkSize) - 4}, txtCol, 2);
							item.surf->Line({0 + 3,  (chkY + checkSize) - 4}, {0 + checkSize - 5, chkY + 5}, txtCol, 2);
						}
					}
				}
				item.surf->CommitQueue();
				if(idx != im->selectedItem) item.surf->Compress();
			}
			int32_t itemLTrim = (col == 0 ? 1 : 0);
			int32_t itemTTrim = (line == im->vOffset ? 2 : 0);
			uint32_t drawHeight = std::min<uint32_t>(im->itemHeight, ((im->rect.y + im->rect.h) - yPos) - 2);
			s.Blit(*item.surf, {itemLTrim, itemTTrim, im->itemWidth, drawHeight}, {xPos + itemLTrim, yPos + itemTTrim, im->itemWidth, drawHeight});
		}
	}

	if(im->vscroll) im->vscroll->Paint(s);
	
	if(!im->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(im->outerRect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect IconView::GetPaintRect(){
	return im->outerRect;
}

gds::Rect IconView::GetInteractRect(){
	return im->outerRect;
}

uint32_t IconView::GetSubscribed(){
	auto ret = wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown;
	if(im->vscroll) ret |= im->vscroll->GetSubscribed();
	return ret;
}

void IconView::Focus(){
	if(!im->hasFocus){
		im->hasFocus = true;
		IControl::Paint(im->outerRect);
	}
}

void IconView::Blur(){
	if(im->hasFocus){
		im->hasFocus = false;
		IControl::Paint(im->outerRect);
	}
}

uint32_t IconView::GetFlags(){
	return 0;
}

void IconView::Enable(){
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(im->rect);
	}
}

void IconView::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(im->rect);
	}
}

bool IconView::IsEnabled(){
	return im->enabled;
}

void IconView::SetPosition(const gds::Rect &r){
	im->outerRect = r;
	im->rect = {r.x, r.y, r.w - scrollbarSize, r.h};
	if(im->vscroll) im->vscroll->SetPosition({im->outerRect.x + (int32_t)im->outerRect.w - scrollbarSize, im->outerRect.y, scrollbarSize, im->outerRect.h});
	im->bkSurf.reset();
}

size_t IconView::GetValue(){
	return im->selectedItem;
}

void IconView::SetValue(size_t idx){
	if(im->selectedItem == idx) return;
	im->selectedItem = idx;
	im->UpdateDisplayState(true);
	im->fireCurrentSelection = true;
}

std::vector<bool> &IconView::MulitSelections(){
	return im->multiSelection;
}

std::vector<std::string> &IconView::Items(){
	return im->items;
}

void IconView::Refresh(){
	im->multiSelection.resize(im->items.size());
	im->icons.resize(im->items.size());
	im->drawItems.clear();
	im->fireCurrentSelection = true;
	IControl::Paint(im->outerRect);
}

void IconView::SetDefaultIcon(std::shared_ptr<gds::Surface> img){
	im->defaultIcon = img;
}

void IconView::SetItemIcon(size_t idx, std::shared_ptr<gds::Surface> img){
	if(im->icons.size() < im->items.size()) im->icons.resize(im->items.size());
	im->icons[idx] = img;
}

void IconView::ClearItemIcons(){
	im->icons.clear();
	im->icons.resize(im->items.size());
}

void IconView::OnActivate(std::function<void()> oA){
	im->onActivate = oA;
}

void IconView::OnInspect(std::function<void()> oI){
	im->onInspect = oI;
}

}
}