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

ListBox::ListBox(const gds::Rect &r, bool sH, bool mS) : 
	outerRect(r), 
	rect(sH ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h}),
	scrollHoriz(sH),
	multiSelect(mS)
	{
	auto info = fonts::GetListBoxFont().Info();
	fontHeight = (info.maxH * fonts::GetListBoxTextSize()) / info.scale;
	if(multiSelect && fontHeight < checkSize) fontHeight = checkSize;
	
	vscroll.reset(new Scrollbar({outerRect.x + (int32_t)outerRect.w - scrollbarSize, outerRect.y, scrollbarSize, outerRect.h - (scrollHoriz ? scrollbarSize : 0)}, 1, 1, 1, 1, false));
	IControl::BindToParent(*vscroll);
	
	vscroll->OnChange([this] (uint32_t v) {
		if(v != vOffset) update = true;
		vOffset = v;
	});
	
	if(scrollHoriz){
		hscroll.reset(new Scrollbar({outerRect.x, outerRect.y + (int32_t)outerRect.h - scrollbarSize, outerRect.w - scrollbarSize, scrollbarSize}, 1, 1, 1, 1, true));
		IControl::BindToParent(*hscroll);
		
		hscroll->OnChange([this] (uint32_t v) {
			if(v != hOffset + (multiSelect ? checkSize : 0)) update = true;
			hOffset = v - (multiSelect ? checkSize : 0);
		});
	}
	if(multiSelect) hOffset = -checkSize;
	
	UpdateDisplayState();
}

void ListBox::UpdateDisplayState(bool changePos){
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
		if(code == (KeyFlags::NonASCII | KeyCodes::DownArrow) && selectedItem < items.size() - 1){
			++selectedItem;
			update = true;
			handled = true;
			UpdateDisplayState();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::UpArrow) && selectedItem > 0){
			--selectedItem;
			update = true;
			handled = true;
			UpdateDisplayState();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp)){
			if(selectedItem != 0){
				if(selectedItem > visibleItems) selectedItem -= visibleItems;
				else selectedItem = 0;
				update = true;
				UpdateDisplayState();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown)){
			if(selectedItem < items.size() - 1){
				if(selectedItem + visibleItems < items.size()) selectedItem += visibleItems;
				else selectedItem = items.size() - 1;
				update = true;
				UpdateDisplayState();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::Home)){
			if(selectedItem != 0){
				selectedItem = 0;
				update = true;
				UpdateDisplayState();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::End)){
			if(selectedItem < items.size() - 1){
				selectedItem = items.size() - 1;
				update = true;
				UpdateDisplayState();
			}
			handled = true;
		}else if(!(code & KeyFlags::NonASCII)){
			auto oldSelectedItem = selectedItem;
			char c = KB_char(e.Key.code);
			if(multiSelect && (c == ' ' || c == '\n')){
				multiSelection[selectedItem] = !multiSelection[selectedItem];
				update = true;
			}else{
				c = std::tolower(c);
				auto finder = [&](const std::string &item){return !item.empty() && std::tolower(item.front()) == c;};
				auto it = std::find_if(begin(items) + selectedItem + 1, end(items), finder);
				if(it == end(items)) it = std::find_if(begin(items), end(items), finder);
				if(it != end(items)) selectedItem = it - begin(items);
				update = oldSelectedItem != selectedItem;
			}
			handled = true;
			UpdateDisplayState();
		}
	}else if(e.type & wm_PointerEvents){
		if(InRect(e.Pointer.x, e.Pointer.y, rect)){
			if(e.type == wm_EventType::PointerButtonUp){
				auto oldSelectedItem = selectedItem;
				selectedItem = ((e.Pointer.y - outerRect.y) / fontHeight) + vOffset;
				if(selectedItem < items.size()) update = oldSelectedItem != selectedItem;
				if(multiSelect && (e.Pointer.x - outerRect.x) < checkSize + 1){
					multiSelection[selectedItem] = !multiSelection[selectedItem];
					update = true;
				}
				handled = true;
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

void ListBox::Paint(gds::Surface &s){
	if(update || !surf){
		if(!surf) surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		UpdateDisplayState(false);
		
		uint32_t inW = rect.w - 1;
		uint32_t inH = rect.h - 1;
		
		auto bkgCol = colours::GetBackground().Fix(*surf);
		auto txtCol = colours::GetListBoxText().Fix(*surf);
		auto border = colours::GetBorder().Fix(*surf);
		auto selCol = colours::GetSelection().Fix(*surf);
		
		auto topLeft = colours::GetListBoxLowLight().Fix(*surf);
		auto bottomRight = colours::GetListBoxHiLight().Fix(*surf);
		surf->Clear();
		surf->BeginQueue();
		surf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		for(auto i = vOffset; i < items.size() && i < vOffset + (inH / fontHeight) + 1; ++i){
			auto &cItem = drawItems[i];
			
			auto textY = std::max<int32_t>(((fontHeight + cItem.measures.h) / 2), 0);
			textY += (i - vOffset) * fontHeight;
			if(i == selectedItem){
				auto selFocus = colours::GetSelectionFocus().Fix(*surf);
				int32_t selY = fontHeight * (i - vOffset);
				if(hasFocus){
					surf->Box({1, selY, inW, fontHeight}, selCol, selCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				}
				surf->Box({1, selY, inW, fontHeight}, selFocus, selFocus, 1, gds_LineStyle::Solid);
			}
			surf->Text({2 - (int32_t)hOffset, textY}, cItem.text, fonts::GetListBoxFont(), fonts::GetListBoxTextSize(), txtCol);
			
			if(multiSelect){
				int32_t chkY = fontHeight * (i - vOffset);
				surf->Box({1, chkY, checkSize, checkSize}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				drawing::BevelBox(*surf, {2, chkY + 1, checkSize - 2, checkSize - 2}, topLeft, bottomRight);
				if(multiSelection[i]){
					surf->Line({5, chkY + 5}, {checkSize - 3, (chkY + checkSize) - 4}, txtCol, 2);
					surf->Line({5,  (chkY + checkSize) - 4}, {checkSize - 3, chkY + 5}, txtCol, 2);
				}
			}
		}
		drawing::Border(*surf, {0, 0, inW, inH}, border);
		drawing::BevelBox(*surf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);
		
		surf->CommitQueue();
		update = false;
	}
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);

	if(hscroll) hscroll->Paint(s);
	if(vscroll) vscroll->Paint(s);
	
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(outerRect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect ListBox::GetPaintRect(){
	return outerRect;
}

gds::Rect ListBox::GetInteractRect(){
	return outerRect;
}

uint32_t ListBox::GetSubscribed(){
	auto ret = wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown;
	if(hscroll) ret |= hscroll->GetSubscribed();
	if(vscroll) ret |= vscroll->GetSubscribed();
	return ret;
}

void ListBox::Focus(){
	if(!hasFocus){
		update = true;
		hasFocus = true;
		IControl::Paint(outerRect);
	}
}

void ListBox::Blur(){
	if(hasFocus){
		update = true;
		hasFocus = false;
		IControl::Paint(outerRect);
	}
}

uint32_t ListBox::GetFlags(){
	return 0;
}

void ListBox::Enable(){
	if(!enabled){
		enabled = true;
		IControl::Paint(rect);
	}
}

void ListBox::Disable(){
	if(enabled){
		enabled = false;
		IControl::Paint(rect);
	}
}

bool ListBox::IsEnabled(){
	return enabled;
}

size_t ListBox::GetValue(){
	return selectedItem;
}

void ListBox::SetValue(size_t idx){
	if(selectedItem == idx) return;
	selectedItem = idx;
	update = true;
}

std::vector<bool> &ListBox::MulitSelections(){
	return multiSelection;
}

std::vector<std::string> &ListBox::Items(){
	return items;
}

void ListBox::Refresh(){
	update = true;
	IControl::Paint(outerRect);
	multiSelection.resize(items.size());
}

}
}