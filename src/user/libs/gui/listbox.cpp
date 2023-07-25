#include <gui/listbox.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

#include <cctype>
#include <algorithm>

namespace btos_api{
namespace gui{
	
const auto scrollbarSize = 17;
const auto checkSize = 17;

struct ListBoxImpl{
	gds::Rect outerRect;
	gds::Rect rect; 
	std::unique_ptr<gds::Surface> surf;
	
	std::vector<std::string> items;
	std::vector<bool> multiSelection;
	
	struct DrawItem{
		std::string text;
		gds::TextMeasurements measures;
	};
	
	std::vector<DrawItem> drawItems;
	
	size_t fontHeight;
	
	size_t selectedItem = 0;
	size_t vOffset = 0;
	size_t hOffset = 0;
	size_t visibleItems = 0;
	
	bool update = false;
	bool hasFocus = false;
	bool enabled = true;
	
	std::unique_ptr<Scrollbar> hscroll;
	std::unique_ptr<Scrollbar> vscroll;
	
	bool scrollHoriz;
	bool multiSelect;
	
	void UpdateDisplayState(bool changePos = true);
};
PIMPL_IMPL(ListBoxImpl);

ListBox::ListBox(const gds::Rect &r, bool sH, bool mS) : im(new ListBoxImpl()){
	im->outerRect = r; 
	im->rect = sH ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h};
	im->scrollHoriz = sH;
	im->multiSelect = mS;
	auto info = fonts::GetListBoxFont().Info();
	im->fontHeight = (info.maxH * fonts::GetListBoxTextSize()) / info.scale;
	if(im->multiSelect && im->fontHeight < checkSize) im->fontHeight = checkSize;
	
	im->vscroll.reset(new Scrollbar({im->outerRect.x + (int32_t)im->outerRect.w - scrollbarSize, im->outerRect.y, scrollbarSize, im->outerRect.h - (im->scrollHoriz ? scrollbarSize : 0)}, 1, 1, 1, 1, false));
	
	im->vscroll->OnChange([this] (uint32_t v) {
		if(v != im->vOffset) im->update = true;
		im->vOffset = v;
	});
	
	if(im->scrollHoriz){
		im->hscroll.reset(new Scrollbar({im->outerRect.x, im->outerRect.y + (int32_t)im->outerRect.h - scrollbarSize, im->outerRect.w - scrollbarSize, scrollbarSize}, 1, 1, 1, 1, true));
		
		im->hscroll->OnChange([this] (uint32_t v) {
			if(v != im->hOffset + (im->multiSelect ? checkSize : 0)) im->update = true;
			im->hOffset = v - (im->multiSelect ? checkSize : 0);
		});
	}
	if(im->multiSelect) im->hOffset = -checkSize;
	
	im->UpdateDisplayState();
}

void ListBoxImpl::UpdateDisplayState(bool changePos){
	visibleItems = rect.h / fontHeight;
	if(changePos){
		if(selectedItem < vOffset) vOffset = selectedItem;
		if(selectedItem >= vOffset + (visibleItems - 1)) vOffset = std::max<int32_t>(0, (int32_t)(selectedItem - (visibleItems - 1)));
	}
	
	uint32_t maxTextW = 0;
	drawItems.resize(items.size());
	for(size_t i = 0; i < items.size(); ++i){
		auto &di = drawItems[i];
		auto &it = items[i];
		if(di.text != it || !di.measures.w){
			di.text = it;
			di.measures = surf->MeasureText(it, fonts::GetListBoxFont(), fonts::GetListBoxTextSize());
		}
		if(di.measures.w > maxTextW) maxTextW = di.measures.w;
	}
	
	if(vscroll){
		if(visibleItems < items.size()){
			vscroll->Enable();
			vscroll->SetLines(std::max<int32_t>((int32_t)items.size() - visibleItems, 1));
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
		if(maxTextW > rect.w - 2){
			hscroll->Enable();
		 	hscroll->SetLines(maxTextW - (rect.w - 2));
		 	hscroll->SetPage(rect.w - 2);
		 	hscroll->SetValue(hOffset + (multiSelect ? checkSize : 0));
		 	hscroll->SetStep(fonts::GetListBoxTextSize() / 2);
		}else{
			hscroll->Disable();
			hscroll->SetLines(1);
			hscroll->SetPage(1);
			hscroll->SetValue(0);
			hOffset = (multiSelect ? -checkSize : 0);
		}
	}
}

EventResponse ListBox::HandleEvent(const wm_Event &e){
	bool handled = false;
	if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(code == (KeyFlags::NonASCII | KeyCodes::DownArrow) && im->selectedItem < im->items.size() - 1){
			++im->selectedItem;
			im->update = true;
			handled = true;
			im->UpdateDisplayState();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::UpArrow) && im->selectedItem > 0){
			--im->selectedItem;
			im->update = true;
			handled = true;
			im->UpdateDisplayState();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp)){
			if(im->selectedItem != 0){
				if(im->selectedItem > im->visibleItems) im->selectedItem -= im->visibleItems;
				else im->selectedItem = 0;
				im->update = true;
				im->UpdateDisplayState();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown)){
			if(im->selectedItem < im->items.size() - 1){
				if(im->selectedItem + im->visibleItems < im->items.size()) im->selectedItem += im->visibleItems;
				else im->selectedItem = im->items.size() - 1;
				im->update = true;
				im->UpdateDisplayState();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::Home)){
			if(im->selectedItem != 0){
				im->selectedItem = 0;
				im->update = true;
				im->UpdateDisplayState();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::End)){
			if(im->selectedItem < im->items.size() - 1){
				im->selectedItem = im->items.size() - 1;
				im->update = true;
				im->UpdateDisplayState();
			}
			handled = true;
		}else if(!(code & KeyFlags::NonASCII)){
			auto oldSelectedItem = im->selectedItem;
			char c = KB_char(e.Key.code);
			if(im->multiSelect && (c == ' ' || c == '\n')){
				im->multiSelection[im->selectedItem] = !im->multiSelection[im->selectedItem];
				im->update = true;
			}else{
				c = std::tolower(c);
				auto finder = [&](const std::string &item){return !item.empty() && std::tolower(item.front()) == c;};
				auto it = std::find_if(begin(im->items) + im->selectedItem + 1, end(im->items), finder);
				if(it == end(im->items)) it = std::find_if(begin(im->items), end(im->items), finder);
				if(it != end(im->items)) im->selectedItem = it - begin(im->items);
				im->update = oldSelectedItem != im->selectedItem;
			}
			handled = true;
			im->UpdateDisplayState();
		}
	}else if(e.type & wm_PointerEvents){
		if(InRect(e.Pointer.x, e.Pointer.y, im->rect)){
			if(e.type == wm_EventType::PointerButtonUp){
				auto oldSelectedItem = im->selectedItem;
				im->selectedItem = ((e.Pointer.y - im->outerRect.y) / im->fontHeight) + im->vOffset;
				if(im->selectedItem < im->items.size()) im->update = oldSelectedItem != im->selectedItem;
				if(im->multiSelect && (e.Pointer.x - im->outerRect.x) < checkSize + 1){
					im->multiSelection[im->selectedItem] = !im->multiSelection[im->selectedItem];
					im->update = true;
				}
				handled = true;
				im->UpdateDisplayState();
			}
		}else if(im->hscroll && im->hscroll->IsEnabled() && InRect(e.Pointer.x, e.Pointer.y, im->hscroll->GetInteractRect()) && (e.type & im->hscroll->GetSubscribed())){
			auto ret = im->hscroll->HandleEvent(e);
			im->update = ret.IsFinishedProcessing();
			handled = handled || im->update;
		}else if(im->vscroll && im->vscroll->IsEnabled() && InRect(e.Pointer.x, e.Pointer.y, im->vscroll->GetInteractRect()) && (e.type & im->vscroll->GetSubscribed())){
			auto ret = im->vscroll->HandleEvent(e);
			im->update = ret.IsFinishedProcessing();
			handled = handled || im->update;
		}
	}
	if(im->update) IControl::Paint(im->outerRect);
	return {handled};
}

void ListBox::Paint(gds::Surface &s){
	if(im->update || !im->surf){
		if(!im->surf) im->surf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
		im->UpdateDisplayState(false);
		
		uint32_t inW = im->rect.w - 1;
		uint32_t inH = im->rect.h - 1;
		
		auto bkgCol = colours::GetBackground().Fix(*im->surf);
		auto txtCol = colours::GetListBoxText().Fix(*im->surf);
		auto border = colours::GetBorder().Fix(*im->surf);
		auto selCol = colours::GetSelection().Fix(*im->surf);
		
		auto topLeft = colours::GetListBoxLowLight().Fix(*im->surf);
		auto bottomRight = colours::GetListBoxHiLight().Fix(*im->surf);
		im->surf->Clear();
		im->surf->BeginQueue();
		im->surf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		for(auto i = im->vOffset; i < im->items.size() && i < im->vOffset + (inH / im->fontHeight) + 1; ++i){
			auto &cItem = im->drawItems[i];
			
			auto textY = std::max<int32_t>(((im->fontHeight + cItem.measures.h) / 2), 0);
			textY += (i - im->vOffset) * im->fontHeight;
			if(i == im->selectedItem){
				auto selFocus = colours::GetSelectionFocus().Fix(*im->surf);
				int32_t selY = im->fontHeight * (i - im->vOffset);
				if(im->hasFocus){
					im->surf->Box({1, selY, inW, im->fontHeight}, selCol, selCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				}
				im->surf->Box({1, selY, inW, im->fontHeight}, selFocus, selFocus, 1, gds_LineStyle::Solid);
			}
			im->surf->Text({2 - (int32_t)im->hOffset, textY}, cItem.text, fonts::GetListBoxFont(), fonts::GetListBoxTextSize(), txtCol);
			
			if(im->multiSelect){
				int32_t chkY = im->fontHeight * (i - im->vOffset);
				im->surf->Box({1, chkY, checkSize, checkSize}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				drawing::BevelBox(*im->surf, {2, chkY + 1, checkSize - 2, checkSize - 2}, topLeft, bottomRight);
				if(im->multiSelection[i]){
					im->surf->Line({5, chkY + 5}, {checkSize - 3, (chkY + checkSize) - 4}, txtCol, 2);
					im->surf->Line({5,  (chkY + checkSize) - 4}, {checkSize - 3, chkY + 5}, txtCol, 2);
				}
			}
		}
		drawing::Border(*im->surf, {0, 0, inW, inH}, border);
		drawing::BevelBox(*im->surf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);
		
		im->surf->CommitQueue();
		im->update = false;
	}
	s.Blit(*im->surf, im->rect.AtZero(), im->rect);

	if(im->hscroll) im->hscroll->Paint(s);
	if(im->vscroll) im->vscroll->Paint(s);
	
	if(!im->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(im->outerRect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect ListBox::GetPaintRect(){
	return im->outerRect;
}

gds::Rect ListBox::GetInteractRect(){
	return im->outerRect;
}

uint32_t ListBox::GetSubscribed(){
	auto ret = wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown;
	if(im->hscroll) ret |= im->hscroll->GetSubscribed();
	if(im->vscroll) ret |= im->vscroll->GetSubscribed();
	return ret;
}

void ListBox::Focus(){
	if(!im->hasFocus){
		im->update = true;
		im->hasFocus = true;
		IControl::Paint(im->outerRect);
	}
}

void ListBox::Blur(){
	if(im->hasFocus){
		im->update = true;
		im->hasFocus = false;
		IControl::Paint(im->outerRect);
	}
}

uint32_t ListBox::GetFlags(){
	return 0;
}

void ListBox::Enable(){
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(im->rect);
	}
}

void ListBox::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(im->rect);
	}
}

bool ListBox::IsEnabled(){
	return im->enabled;
}

size_t ListBox::GetValue(){
	return im->selectedItem;
}

void ListBox::SetValue(size_t idx){
	if(im->selectedItem == idx) return;
	im->selectedItem = idx;
	im->update = true;
}

std::vector<bool> &ListBox::MulitSelections(){
	return im->multiSelection;
}

std::vector<std::string> &ListBox::Items(){
	return im->items;
}

void ListBox::Refresh(){
	im->update = true;
	IControl::Paint(im->outerRect);
	im->multiSelection.resize(im->items.size());
}

void ListBox::SetPosition(const gds::Rect &r){
	im->outerRect = r;
	im->rect = im->scrollHoriz ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h};
	if(im->vscroll) im->vscroll->SetPosition({im->outerRect.x + (int32_t)im->outerRect.w - scrollbarSize, im->outerRect.y, scrollbarSize, im->outerRect.h - (im->scrollHoriz ? scrollbarSize : 0)});
	if(im->hscroll) im->hscroll->SetPosition({im->outerRect.x, im->outerRect.y + (int32_t)im->outerRect.h - scrollbarSize, im->outerRect.w - scrollbarSize, scrollbarSize});
	im->update = true;
	im->surf.reset();
}

}
}