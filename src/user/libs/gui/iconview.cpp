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
	itemSize = iconSize * 2;
	
	vscroll.reset(new Scrollbar({outerRect.x + (int32_t)outerRect.w - scrollbarSize, outerRect.y, scrollbarSize, outerRect.h}, 1, 1, 1, 1, false));
	IControl::BindToParent(*vscroll);
	
	vscroll->OnChange([this] (uint32_t v) {
		if(v != vOffset) update = true;
		vOffset = v;
	});
	
	UpdateDisplayState();
}

void IconView::UpdateDisplayState(bool changePos){
	visibleLines = (rect.h / itemSize) + 1;
	visibleCols = rect.w / itemSize;
	if(changePos){
		auto selectionLine = selectedItem / visibleCols; 
		if(selectionLine < vOffset) vOffset = selectionLine;
		if(selectionLine >= vOffset + (visibleLines - 1)) vOffset = std::max<int32_t>(0, (int32_t)(selectionLine - (visibleLines - 2)));
	}
	
	drawItems.resize(items.size());
	for(size_t i = 0; i < items.size(); ++i){
		auto &di = drawItems[i];
		auto &it = items[i];
		if(di.text != it || !di.measures.w){
			di.text = it;
			di.measures = surf->MeasureText(it, fonts::GetIconViewFont(), fonts::GetIconViewTextSize());
			di.fittedText = FitTextToWidth(di, itemSize - (multiSelect ? checkSize : 0));
		}
	}
	
	if(vscroll){
		auto lines = items.size() / visibleCols;
		if(visibleLines < lines){
			vscroll->Enable();
			vscroll->SetLines(std::max<int32_t>(lines - (visibleLines - 1), 1));
			vscroll->SetPage(visibleLines - 1);
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

std::string IconView::FitTextToWidth(DrawItem &item, size_t width){;
	if(item.fittedWidth == width) return item.fittedText;
	if(item.measures.w < width){
		item.fittedWidth = width;
		item.fittedText = item.text;
		return item.text;	
	}
	
	std::string suffix = "...";
	if(width < surf->MeasureText(suffix, fonts::GetDetailListFont(), fonts::GetDetailListTextSize()).w) suffix = "";
	std::string text = item.text;
	while((item.measures = surf->MeasureText(text + suffix, fonts::GetDetailListFont(), fonts::GetDetailListTextSize())).w > width){
		text.pop_back();
	}
	
	item.fittedText = text + suffix;
	item.fittedWidth = width;
	return item.fittedText;
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
		}else if(code == (KeyFlags::NonASCII | KeyCodes::UpArrow) && selectedItem > 0){
			selectedItem -= std::min(selectedItem, visibleCols);
			update = true;
			handled = true;
			UpdateDisplayState();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && selectedItem < items.size() - 1){
			++selectedItem;
			update = true;
			handled = true;
			UpdateDisplayState();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && selectedItem > 0){
			--selectedItem;
			update = true;
			handled = true;
			UpdateDisplayState();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp)){
			if(selectedItem != 0){
				auto visibleItems = (visibleLines - 1) * visibleCols;
				if(selectedItem > visibleItems) selectedItem -= visibleItems;
				else selectedItem = 0;
				update = true;
				UpdateDisplayState();
			}
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown)){
			if(selectedItem < items.size() - 1){
				auto visibleItems = (visibleLines - 1) * visibleCols;
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
			auto pX = e.Pointer.x - outerRect.x;
			auto pY = e.Pointer.y - outerRect.y;
			auto col = pX / itemSize;
			if(col >= visibleCols) col = visibleCols - 1;
			auto line = (pY / itemSize) + vOffset;
			auto idx = (line * visibleCols) + col;
			if(e.type == wm_EventType::PointerButtonUp && idx < items.size()){
				auto oldSelectedItem = selectedItem;
				selectedItem = idx;
				if(selectedItem < items.size()) update = oldSelectedItem != selectedItem;
				if(multiSelect){
					auto xPos = pX - (col * itemSize);
					auto yPos = pY - (line * itemSize);
					if(xPos < checkSize && yPos > (itemSize - checkSize)){
						multiSelection[selectedItem] = !multiSelection[selectedItem];
						update = true;
					}
				}
				handled = true;
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
	if(update || !surf){
		if(!surf) surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		UpdateDisplayState(false);
		
		uint32_t inW = rect.w - 1;
		uint32_t inH = rect.h - 1;
		
		auto bkgCol = colours::GetBackground().Fix(*surf);
		auto txtCol = colours::GetIconViewText().Fix(*surf);
		auto border = colours::GetBorder().Fix(*surf);
		auto selCol = colours::GetSelection().Fix(*surf);
		
		auto topLeft = colours::GetIconViewLowLight().Fix(*surf);
		auto bottomRight = colours::GetIconViewHiLight().Fix(*surf);
		surf->Clear();
		surf->BeginQueue();
		surf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		for(size_t line = vOffset; line < vOffset + visibleLines; ++line){
			int32_t yPos = (line - vOffset) * itemSize;
			for(size_t col = 0; col < visibleCols; ++col){
				size_t idx = (line * visibleCols) + col;
				if(idx >= drawItems.size()) break;
				auto &item = drawItems[idx];
				
				int32_t xPos = (col * itemSize) + 1;
				
				if(idx == selectedItem){
					auto selFocus = colours::GetSelectionFocus().Fix(*surf);
					if(hasFocus){
						surf->Box({xPos, yPos, itemSize, itemSize}, selCol, selCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
					}
					surf->Box({xPos, yPos, itemSize, itemSize}, selFocus, selFocus, 1, gds_LineStyle::Solid);
				}
				
				if(icons[idx] || defaultIcon){
					auto &icon = icons[idx] ? icons[idx] : defaultIcon;
					int32_t iconX = xPos + (iconSize / 2);
					int32_t iconY = yPos + ((itemSize - fontHeight - iconSize) / 2);
					if(iconY < (int32_t)rect.h) surf->Blit(*icon, {0, 0, iconSize, iconSize}, {iconX, iconY, iconSize, iconSize});
				}
				
				int32_t textX = xPos + ((itemSize - item.measures.w - (multiSelect ? checkSize : 0)) / 2) + (multiSelect ? checkSize : 0);
				int32_t textY = yPos + (itemSize - fontHeight) + ((fontHeight + item.measures.h) / 2);
				if(textY - fontHeight < rect.h) surf->Text({textX, textY}, item.fittedText, fonts::GetIconViewFont(), fonts::GetIconViewTextSize(), txtCol);
				
				if(multiSelect){
					int32_t chkY = yPos + (itemSize - checkSize);
					if(chkY < (int32_t)rect.h){
						surf->Box({xPos, chkY + 1, checkSize - 2, checkSize - 2}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
						drawing::BevelBox(*surf, {xPos, chkY + 1, checkSize - 2, checkSize - 2}, topLeft, bottomRight);
						if(multiSelection[idx]){
							surf->Line({xPos + 3, chkY + 5}, {xPos + checkSize - 5, (chkY + checkSize) - 4}, txtCol, 2);
							surf->Line({xPos + 3,  (chkY + checkSize) - 4}, {xPos + checkSize - 5, chkY + 5}, txtCol, 2);
						}
					}
				}
			}
		}
		drawing::Border(*surf, {0, 0, inW, inH}, border);
		drawing::BevelBox(*surf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);
		
		surf->CommitQueue();
		update = false;
	}
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);

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

size_t IconView::GetValue(){
	return selectedItem;
}

void IconView::SetValue(size_t idx){
	if(selectedItem == idx) return;
	selectedItem = idx;
	update = true;
}

std::vector<bool> &IconView::MulitSelections(){
	return multiSelection;
}

std::vector<std::string> &IconView::Items(){
	return items;
}

void IconView::Refresh(){
	update = true;
	IControl::Paint(outerRect);
	multiSelection.resize(items.size());
	icons.resize(items.size());
}

void IconView::SetDefaultIcon(std::shared_ptr<gds::Surface> img){
	defaultIcon = img;
}

void IconView::SetItemIcon(size_t idx, std::shared_ptr<gds::Surface> img){
	icons[idx] = img;
}

void IconView::ClearItemIcons(){
	icons.clear();
	icons.resize(items.size());
}


}
}