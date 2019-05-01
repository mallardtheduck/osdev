#include <gui/listbox.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

namespace btos_api{
namespace gui{
	
const auto scrollbarSize = 17;

ListBox::ListBox(const gds::Rect &r, bool sH) : 
	outerRect(r), 
	rect(sH ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h}),
	scrollHoriz(sH){
	auto info = fonts::GetListBoxFont().Info();
	fontHeight = (info.maxH * fonts::GetListBoxTextSize()) / info.scale;
	
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
			if(v != hOffset) update = true;
			hOffset = v;
		});
	}
	
	UpdateDisplayState();
}

void ListBox::UpdateDisplayState(bool changePos){
	auto visibleItems = rect.h / fontHeight;
	if(changePos){
		if(selectedItem < vOffset) vOffset = selectedItem;
		if(selectedItem >= vOffset + (visibleItems - 1)) vOffset = std::max<int32_t>(0, (int32_t)(selectedItem - (visibleItems - 1)));
	}
	
	if(vscroll){
		vscroll->SetLines(std::max<int32_t>((int32_t)items.size() - visibleItems, 1));
		vscroll->SetPage(visibleItems);
		vscroll->SetValue(vOffset);
	}
	
	// if(hscroll){
	// 	hscroll->SetLines(std::max<uint32_t>(text.length(), 1));
	// 	hscroll->SetPage(vchars);
	// 	hscroll->SetValue(cursorPos);
	// }
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
		}
	}else if(e.type & wm_PointerEvents){
		if(InRect(e.Pointer.x, e.Pointer.y, rect)){
			if(e.type == wm_EventType::PointerButtonUp){
				auto oldSelectedItem = selectedItem;
				selectedItem = ((e.Pointer.y - outerRect.y) / fontHeight) + vOffset;
				update = oldSelectedItem != selectedItem;
				handled = true;
				UpdateDisplayState();
			}
		}else if(hscroll && InRect(e.Pointer.x, e.Pointer.y, hscroll->GetInteractRect()) && (e.type & hscroll->GetSubscribed())){
			auto ret = hscroll->HandleEvent(e);
			update = ret.IsFinishedProcessing();
			handled = handled || update;
		}else if(vscroll && InRect(e.Pointer.x, e.Pointer.y, vscroll->GetInteractRect()) && (e.type & vscroll->GetSubscribed())){
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
		
		drawItems.resize(items.size());
		for(size_t i = 0; i < items.size(); ++i){
			auto &di = drawItems[i];
			auto &it = items[i];
			if(di.text != it || !di.measures.w){
				di.text = it;
				di.measures = surf->MeasureText(it, fonts::GetListBoxFont(), fonts::GetListBoxTextSize());
			}
		}
		
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
				int32_t selY = fontHeight * (i - vOffset);
				surf->Box({0, selY, inW, fontHeight}, selCol, selCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				if(hasFocus){
					auto selFocus = colours::GetSelectionFocus().Fix(*surf);
					surf->Box({0, selY, inW, fontHeight}, selFocus, selFocus, 1, gds_LineStyle::Solid);
				}
			}
			surf->Text({2 - (int32_t)hOffset, textY}, cItem.text, fonts::GetListBoxFont(), fonts::GetListBoxTextSize(), txtCol);
		}
		drawing::Border(*surf, {0, 0, inW, inH}, border);
		drawing::BevelBox(*surf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);
		
		surf->CommitQueue();
		update = false;
	}
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);

	if(hscroll) hscroll->Paint(s);
	if(vscroll) vscroll->Paint(s);
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

size_t ListBox::GetValue(){
	return selectedItem;
}

void ListBox::SetValue(size_t idx){
	if(selectedItem == idx) return;
	selectedItem = idx;
	update = true;
}

std::vector<std::string> &ListBox::Items(){
	return items;
}

void ListBox::Refresh(){
	update = true;
	IControl::Paint(outerRect);
}

}
}