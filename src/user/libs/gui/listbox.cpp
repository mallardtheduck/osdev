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
	if(scrollHoriz){
		hscroll.reset(new Scrollbar({outerRect.x, outerRect.y + (int32_t)outerRect.h - scrollbarSize, outerRect.w - scrollbarSize, scrollbarSize}, 1, 1, 1, 1, true));
		IControl::BindToParent(*hscroll);
	}
}

EventResponse ListBox::HandleEvent(const wm_Event&){
	return {true};
}

void ListBox::Paint(gds::Surface &s){
	if(update || !surf){
	if(!surf) surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
	
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
			auto &cItem = items[i];
			auto tm = surf->MeasureText(cItem, fonts::GetListBoxFont(), fonts::GetListBoxTextSize());
			
			auto textY = std::max<int32_t>(((fontHeight + tm.h) / 2), 0);
			textY += (i - vOffset) * fontHeight;
			if(i == selectedItem){
				int32_t selY = fontHeight * (i - vOffset);
				surf->Box({0, selY, inW, fontHeight}, selCol, selCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
			}
			surf->Text({2 - (int32_t)hOffset, textY}, cItem, fonts::GetListBoxFont(), fonts::GetListBoxTextSize(), txtCol);
		}
		drawing::Border(*surf, {0, 0, inW, inH}, border);
		drawing::BevelBox(*surf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);
		
		surf->CommitQueue();
		
	if(vscroll){
		vscroll->SetLines(std::max<uint32_t>(items.size() - 1, 1));
		vscroll->SetPage(vlines);
		vscroll->SetValue(vOffset);
	}
	
	if(hscroll){
		hscroll->SetLines(std::max<uint32_t>(text.length(), 1));
		hscroll->SetPage(vchars);
		hscroll->SetValue(cursorPos);
	}
		
	}
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
	
	if(hscroll) hscroll->Paint(s);
	if(vscroll) vscroll->Paint(s);
}

gds::Rect ListBox::GetPaintRect(){
	return rect;
}

gds::Rect ListBox::GetInteractRect(){
	return rect;
}

uint32_t ListBox::GetSubscribed(){
	return 0;
}

void ListBox::Focus(){
}

void ListBox::Blur(){
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

}
}