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

Tabs::Tabs(const gds::Rect &r) :  rect(r){
}


void Tabs::SwitchTab(){
	std::shared_ptr<IControl> newContent;
	if(tabs.size() > currentTab && tabs[currentTab].content){
		newContent = tabs[currentTab].content;
		if(currentContent != newContent) RemoveFromParent(currentContent);
		AddToParent(newContent);
	}
	currentContent = newContent;
}

EventResponse Tabs::HandleEvent(const wm_Event &e){
	auto oldCurrent = currentTab;
	if(e.type == wm_EventType::PointerButtonUp && e.Pointer.button == 1){
		auto xpos = e.Pointer.x - rect.x;
		uint32_t curX = TabMargin;
		for(size_t i = 0; i < tabs.size(); ++i){
			auto width = (TabMargin * 4) + tabs[i].labelMeasures.w;
			if(xpos >= curX && xpos <= curX + width){
				currentTab = i;
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
		}else if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) && currentTab > 0){
			--currentTab;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) && currentTab < tabs.size() - 1){
			++currentTab;
		}
	}
	if(oldCurrent != currentTab){
		SwitchTab();
		IControl::Paint(rect);
	}
	return {true};
}

void Tabs::Paint(gds::Surface &s){
	int32_t inW = rect.w - 1;
	int32_t inH = rect.h - 1;
		
	if(!surf || update){
		if(!surf) surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		else surf->Clear();

		surf->BeginQueue();
		
		auto bkgCol = colours::GetBackground().Fix(*surf);
		auto selected = colours::GetTabsSelectedBackground().Fix(*surf);
		auto unselected = colours::GetTabsUnselectedBackground().Fix(*surf);
		auto border = colours::GetBorder().Fix(*surf);
		auto textColour = colours::GetTabsText().Fix(*surf);
		
		surf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		drawing::Border(*surf, {0, TabHeight, (uint32_t)inW, (uint32_t)(inH - TabHeight)}, border);
		
		int32_t curX = TabMargin;
		
		for(size_t i = 0; i < tabs.size(); ++i){
			auto &tab = tabs[i];
			
			if(!tab.labelMeasures.w) tab.labelMeasures = surf->MeasureText(tab.label, fonts::GetTabsFont(), fonts::GetTabsTextSize());
			
			auto width = (TabMargin * 4) + tab.labelMeasures.w;
			
			auto tabCol = (i == currentTab ? selected : unselected);
			auto curTabHeight = (i == currentTab ? TabHeight : TabHeight - 1);
			
			drawing::Border(*surf, {curX, 0, width, TabHeight}, border);
			surf->Box({curX + 1, 1, width - 1, curTabHeight}, tabCol, tabCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
			
			int32_t labelX = curX + std::max<int32_t>(((width - tab.labelMeasures.w) / 2), 0);
			int32_t labelY = std::max<int32_t>(((TabHeight + tab.labelMeasures.h) / 2), 0);
			
			surf->Text({labelX, labelY}, tab.label, fonts::GetTabsFont(), fonts::GetTabsTextSize(), textColour);
			
			if(focus && i == currentTab){
				auto focusCol = colours::GetTabsFocus().Fix(*surf);
				
				int32_t focusX = std::max<uint32_t>(labelX - TabMargin, 0);
				int32_t focusY = std::max<uint32_t>(labelY - tab.labelMeasures.h - TabMargin, 0);
				uint32_t focusW = tab.labelMeasures.w + (TabMargin * 2);
				uint32_t focusH = tab.labelMeasures.h + (TabMargin * 2);
				
				surf->Box({focusX, focusY, focusW, focusH}, focusCol, focusCol);
			}
			
			curX += width + TabMargin;
		}
		
		surf->CommitQueue();
		surf->Compress();
	}
	
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect Tabs::GetPaintRect(){
	return rect;
}

gds::Rect Tabs::GetInteractRect(){
	return {rect.x, rect.y, rect.w, TabHeight};
}

uint32_t Tabs::GetSubscribed(){
	return (wm_EventType::PointerButtonUp | wm_EventType::Keyboard);
}

void Tabs::Focus(){
	if(!focus){
		focus = true;
		update = true;
		IControl::Paint(rect);
	}
}

void Tabs::Blur(){
	if(focus){
		focus = false;
		update = true;
		IControl::Paint(rect);
	}
}

uint32_t Tabs::GetFlags(){
	return 0;
}

void Tabs::Enable(){
	if(!enabled){
		enabled = true;
		IControl::Paint(rect);
	}
}

void Tabs::Disable(){
	if(enabled){
		enabled = false;
		IControl::Paint(rect);
	}
}

bool Tabs::IsEnabled(){
	return enabled;
}

void Tabs::SetPosition(const gds::Rect &r){
	rect = r;
	update = true;
	surf.reset();
}

void Tabs::OnBind(){
	if(currentContent) AddToParent(currentContent);
}

std::vector<Tab> &Tabs::TabItems(){
	return tabs;
}

void Tabs::Refresh(){
	SwitchTab();
	update = true;
}

gds::Rect Tabs::GetContentRect(){
	int32_t x = rect.x + TabMargin;
	int32_t y = rect.y + TabHeight + TabMargin;
	uint32_t w = rect.w - (2 * TabMargin);
	uint32_t h = rect.h - (2 * TabMargin) - TabHeight;
	if(w > rect.w) w = 0;
	if(h > rect.h) h = 0;
	return {x, y, w, h};
}

}
}
