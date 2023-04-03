#include <btos.h>
#include <gui/tabs.hpp>
#include <gui/drawing.hpp>
#include <gui/defaults.hpp>
#include <dev/mouse.h>
#include <dev/keyboard.h>
#include <wm/libwm.h>

namespace btos_api{
namespace gui{

const uint32_t TabHeight = 24;
const uint32_t TabMargin = 2;

struct TabsImpl{
	Tabs *that;

	bool focus = false;
	bool enabled = true;
	bool update = false;

	size_t currentTab = 0;

	gds::Rect rect;
	
	std::vector<Tab> tabs;
	std::shared_ptr<IControl> currentContent;
	
	std::unique_ptr<gds::Surface> surf;
	
	void SwitchTab();
};
PIMPL_IMPL(TabsImpl);

Tabs::Tabs(const gds::Rect &r) : im(new TabsImpl()){
	im->that = this;
	im->rect = r;
}


void TabsImpl::SwitchTab(){
	std::shared_ptr<IControl> newContent;
	if(tabs.size() > currentTab && tabs[currentTab].content){
		newContent = tabs[currentTab].content;
		if(currentContent != newContent) that->RemoveFromParent(currentContent);
		that->AddToParent(newContent);
	}
	currentContent = newContent;
}

EventResponse Tabs::HandleEvent(const wm_Event &e){
	auto oldCurrent = im->currentTab;
	if(e.type == wm_EventType::PointerButtonUp && e.Pointer.button == 1){
		auto xpos = e.Pointer.x - im->rect.x;
		uint32_t curX = TabMargin;
		for(size_t i = 0; i < im->tabs.size(); ++i){
			auto width = (TabMargin * 4) + im->tabs[i].labelMeasures.w;
			if(xpos >= curX && xpos <= curX + width){
				im->currentTab = i;
				break;
			}
			curX += width + TabMargin;
		}
	}else if(e.type == wm_EventType::Keyboard){
		uint16_t code = KB_code(e.Key.code);
		if(!(code & KeyFlags::NonASCII)){
			char c = KB_char(e.Key.code);
			if(c == ' ' || c == '\n'){
				RaiseActionEvent();
				return {true};
			}
			return {false};
		}else if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && im->currentTab > 0){
			--im->currentTab;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && im->currentTab < im->tabs.size() - 1){
			++im->currentTab;
		}
	}
	if(oldCurrent != im->currentTab){
		im->SwitchTab();
		IControl::Paint(im->rect);
	}
	return {true};
}

void Tabs::Paint(gds::Surface &s){
	int32_t inW = im->rect.w - 1;
	int32_t inH = im->rect.h - 1;
		
	if(!im->surf || im->update){
		if(!im->surf) im->surf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
		else im->surf->Clear();

		im->surf->BeginQueue();
		
		auto bkgCol = colours::GetBackground().Fix(*im->surf);
		auto selected = colours::GetTabsSelectedBackground().Fix(*im->surf);
		auto unselected = colours::GetTabsUnselectedBackground().Fix(*im->surf);
		auto border = colours::GetBorder().Fix(*im->surf);
		auto textColour = colours::GetTabsText().Fix(*im->surf);
		
		im->surf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		drawing::Border(*im->surf, {0, TabHeight, (uint32_t)inW, (uint32_t)(inH - TabHeight)}, border);
		
		int32_t curX = TabMargin;
		
		for(size_t i = 0; i < im->tabs.size(); ++i){
			auto &tab = im->tabs[i];
			
			if(!tab.labelMeasures.w) tab.labelMeasures = im->surf->MeasureText(tab.label, fonts::GetTabsFont(), fonts::GetTabsTextSize());
			
			auto width = (TabMargin * 4) + tab.labelMeasures.w;
			
			auto tabCol = (i == im->currentTab ? selected : unselected);
			auto curTabHeight = (i == im->currentTab ? TabHeight : TabHeight - 1);
			
			drawing::Border(*im->surf, {curX, 0, width, TabHeight}, border);
			im->surf->Box({curX + 1, 1, width - 1, curTabHeight}, tabCol, tabCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
			
			int32_t labelX = curX + std::max<int32_t>(((width - tab.labelMeasures.w) / 2), 0);
			int32_t labelY = std::max<int32_t>(((TabHeight + tab.labelMeasures.h) / 2), 0);
			
			im->surf->Text({labelX, labelY}, tab.label, fonts::GetTabsFont(), fonts::GetTabsTextSize(), textColour);
			
			if(im->focus && i == im->currentTab){
				auto focusCol = colours::GetTabsFocus().Fix(*im->surf);
				
				int32_t focusX = std::max<uint32_t>(labelX - TabMargin, 0);
				int32_t focusY = std::max<uint32_t>(labelY - tab.labelMeasures.h - TabMargin, 0);
				uint32_t focusW = tab.labelMeasures.w + (TabMargin * 2);
				uint32_t focusH = tab.labelMeasures.h + (TabMargin * 2);
				
				im->surf->Box({focusX, focusY, focusW, focusH}, focusCol, focusCol);
			}
			
			curX += width + TabMargin;
		}
		
		im->surf->CommitQueue();
		im->surf->Compress();
	}
	
	s.Blit(*im->surf, im->rect.AtZero(), im->rect);
	if(!im->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(im->rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect Tabs::GetPaintRect(){
	return im->rect;
}

gds::Rect Tabs::GetInteractRect(){
	return {im->rect.x, im->rect.y, im->rect.w, TabHeight};
}

uint32_t Tabs::GetSubscribed(){
	return (wm_EventType::PointerButtonUp | wm_EventType::Keyboard);
}

void Tabs::Focus(){
	if(!im->focus){
		im->focus = true;
		im->update = true;
		IControl::Paint(im->rect);
	}
}

void Tabs::Blur(){
	if(im->focus){
		im->focus = false;
		im->update = true;
		IControl::Paint(im->rect);
	}
}

uint32_t Tabs::GetFlags(){
	return 0;
}

void Tabs::Enable(){
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(im->rect);
	}
}

void Tabs::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(im->rect);
	}
}

bool Tabs::IsEnabled(){
	return im->enabled;
}

void Tabs::SetPosition(const gds::Rect &r){
	im->rect = r;
	im->update = true;
	im->surf.reset();
}

void Tabs::OnBind(){
	if(im->currentContent) AddToParent(im->currentContent);
}

std::vector<Tab> &Tabs::TabItems(){
	return im->tabs;
}

void Tabs::Refresh(){
	im->SwitchTab();
	im->update = true;
}

gds::Rect Tabs::GetContentRect(){
	int32_t x = im->rect.x + TabMargin;
	int32_t y = im->rect.y + TabHeight + TabMargin;
	uint32_t w = im->rect.w - (2 * TabMargin);
	uint32_t h = im->rect.h - (2 * TabMargin) - TabHeight;
	if(w > im->rect.w) w = 0;
	if(h > im->rect.h) h = 0;
	return {x, y, w, h};
}

}
}
