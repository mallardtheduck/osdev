#include <gui/scrollbar.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/mouse.h>
#include <dev/keyboard.h>
#include <wm/libwm.h>

namespace btos_api{
namespace gui{

struct ScrollbarImpl{
	gds::Rect rect;
	
	uint32_t lines, step, page, value;
	bool horiz;
	bool focus = false;
	bool enabled = true;

	bool topBtnDown = false;
	bool btmBtnDown = false;
	bool grabbed = false;
	
	std::shared_ptr<gds::Surface> bkSurf;
};
PIMPL_IMPL(ScrollbarImpl);

static inline gds::Point swapXY(bool swap, gds::Point p){
	if(swap) std::swap(p.x, p.y);
	return p;
}

static inline gds::Rect swapXY(bool swap, gds::Rect r){
	if(swap){
		std::swap(r.x, r.y);
		std::swap(r.w, r.h);
	}
	return r;
}

template<typename T>
static inline void swapXY(bool swap, T &a, T &b){
	if(swap) std::swap(a, b);
}

Scrollbar::Scrollbar(const gds::Rect &r, uint32_t l, uint32_t s, uint32_t p, uint32_t v, bool h) : im(new ScrollbarImpl()){
	im->rect = r; im->lines = l; im->step = s; im->page = p; im->value = v; im->horiz = h;
}

EventResponse Scrollbar::HandleEvent(const wm_Event &e){
	bool handled = false;
	bool update = false;
	uint32_t oldValue = im->value;
	
	if(e.type & wm_PointerEvents){
		int32_t p = im->horiz ? e.Pointer.x - im->rect.x : e.Pointer.y - im->rect.y;
		auto h = im->horiz ? im->rect.w : im->rect.h;
		auto w = im->horiz ? im->rect.h : im->rect.w;
		
		int32_t sqSize = w;
		double scale = (double)(h - (3 * sqSize)) / (double)im->lines;
		int32_t pos = ((double)im->value * scale) + sqSize;
		uint32_t possValue = (double)((double)p - ((double)sqSize * 1.5)) * (1.0 / scale);
		if(sqSize * 1.5 > p) possValue = 0;
		if(possValue > im->lines) possValue = im->lines;
		
		enum class Area{
			TopButton, UpperSpace, Box, LowerSpace, BottomButton
		} over;
		
		if(p < sqSize) over = Area::TopButton;
		else if(p < pos) over = Area::UpperSpace;
		else if(p < pos + sqSize) over = Area::Box;
		else if(p < (int32_t)h - sqSize) over = Area::LowerSpace;
		else over = Area::BottomButton;
		
		if(e.type == wm_EventType::PointerButtonUp && e.Pointer.button == 1){
			handled = true;
			if(im->grabbed){
				im->value = possValue;
			}else{
				switch(over){
					case Area::TopButton:
						im->value = std::max<int32_t>(0, im->value - im->step);
						break;
					case Area::UpperSpace:
						im->value = std::max<int32_t>(0, im->value - im->page);
						break;
					case Area::Box:
						// Handled by "grabbed" case
						break;
					case Area::LowerSpace:
						im->value = std::min(im->lines, im->value + im->page);
						break;
					case Area::BottomButton:
						im->value = std::min(im->lines, im->value + im->step);
						break;
				}
			}
			if(im->topBtnDown || im->btmBtnDown || im->grabbed) update = true;
			im->topBtnDown = im->btmBtnDown = im->grabbed = false;
		}else if(e.type == wm_EventType::PointerButtonDown && e.Pointer.button == 1){
			handled = true;
			im->topBtnDown = im->btmBtnDown = im->grabbed = false;
			switch(over){
				case Area::TopButton:
					im->topBtnDown = true;
					update = true;
					break;
				case Area::BottomButton:
					im->btmBtnDown = true;
					update = true;
					break;
				case Area::Box:
					im->grabbed = true;
				default:
					break;
			}
		}else if(e.type == wm_EventType::PointerMove || e.type == wm_EventType::PointerEnter){
			auto pinfo = WM_GetPointerInfo();
			if(pinfo.flags & MouseFlags::Button1){
				handled = true;
				if(im->grabbed) im->value = possValue;
				else{
					if(im->topBtnDown | im->btmBtnDown) update = true;
					im->topBtnDown = im->btmBtnDown = false;
					switch(over){
						case Area::TopButton:
							im->topBtnDown = true;
							update = true;
							break;
						case Area::BottomButton:
							im->btmBtnDown = true;
							update = true;
							break;
						default:
							break;
					}
				}
			}else im->grabbed = false;
		}else if(e.type == wm_EventType::PointerLeave){
			handled = true;
			im->topBtnDown = im->btmBtnDown = false;
			update = true;
		}
	}else if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(code == (KeyFlags::NonASCII | KeyCodes::LeftArrow) || code == (KeyFlags::NonASCII | KeyCodes::UpArrow)){
			im->value = std::max<int32_t>(0, im->value - im->step);
			update = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::RightArrow) || code == (KeyFlags::NonASCII | KeyCodes::DownArrow)){
			im->value = std::min(im->lines, im->value + im->step); 
			update = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp)){
			im->value = std::max<int32_t>(0, im->value - im->page);
			update = true;
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown)){
			im->value = std::min(im->lines, im->value + im->page);
			update = true;
			handled = true;
		}
	}
	
	if(im->value != oldValue){
		RaiseChangeEvent();
		update = true;
	}
	if(update){
		IControl::Paint(im->rect);
	}
	return {handled};
}

void Scrollbar::Paint(gds::Surface &s){
	uint32_t w = im->rect.w;
	uint32_t h = im->rect.h;
	swapXY(im->horiz, w, h);
	int32_t x = im->rect.x;
	int32_t y = im->rect.y;
	swapXY(im->horiz, x, y);
	uint32_t inW = im->rect.w - 1;
	uint32_t inH = im->rect.h - 1;
	swapXY(im->horiz, inW, inH);
	int32_t sqSize = w;
	
	if(!im->bkSurf){
		im->bkSurf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
		im->bkSurf->BeginQueue();
		
		auto bkgCol = colours::GetBackground().Fix(*im->bkSurf);
		im->bkSurf->Box(swapXY(im->horiz, {0, 0, w, h}), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		
		auto scrCol = colours::GetScrollbarBackground().Fix(*im->bkSurf);
		im->bkSurf->Box(swapXY(im->horiz, {0, sqSize - 1, w, inH - (sqSize * 2) + 3}), scrCol, scrCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		
		auto btn = colours::GetScrollbarButton().Fix(*im->bkSurf);
		im->bkSurf->Box(swapXY(im->horiz, {0, 1, (uint32_t)sqSize, (uint32_t)sqSize - 2}), btn, btn, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		im->bkSurf->Box(swapXY(im->horiz, {0, (int32_t)h - sqSize + 2, (uint32_t)sqSize, (uint32_t)sqSize - 3}), btn, btn, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		
		auto bdr = colours::GetBorder().Fix(*im->bkSurf);
		drawing::Border(*im->bkSurf, swapXY(im->horiz, {0, 0, (uint32_t)sqSize - 1, (uint32_t)sqSize - 1}), bdr);
		drawing::Border(*im->bkSurf, swapXY(im->horiz, {0, (int32_t)h - sqSize, (uint32_t)sqSize - 1, (uint32_t)sqSize - 1}), bdr);
		
		auto arw = colours::GetScrollbarArrow().Fix(*im->bkSurf);
		int32_t half = sqSize / 2;
		int32_t third = sqSize / 3;
		std::vector<gds::Point> topArrow = {swapXY(im->horiz, {half, third}), swapXY(im->horiz, {2 * third + 1, 2 * third}), swapXY(im->horiz, {third, 2 * third})};
		im->bkSurf->Polygon(topArrow, true, arw, arw, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);

		int32_t btmTop = h - sqSize;
		std::vector<gds::Point> btmArrow = {swapXY(im->horiz, {half, btmTop + (2 * third) + 1}), swapXY(im->horiz, {2 * third + 1, btmTop + third + 1}), swapXY(im->horiz, {third, btmTop + third + 1})};
		im->bkSurf->Polygon(btmArrow, true, arw, arw, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		
		im->bkSurf->CommitQueue();
		im->bkSurf->Compress();
	}
	
	s.Blit(*im->bkSurf, im->rect.AtZero(), im->rect);
	
	auto topLeft = colours::GetScrollbarHiLight().Fix(s);
	auto bottomRight = colours::GetScrollbarLowLight().Fix(s);
	
	auto topBtnTL = topLeft;
	auto topBtnBR = bottomRight;
	if(im->topBtnDown) std::swap(topBtnTL, topBtnBR);
	drawing::BevelBox(s, swapXY(im->horiz, {x + 1,  y + 1, (uint32_t)sqSize - 3, (uint32_t)sqSize - 3}), topBtnTL, topBtnBR);
	
	auto btmBtnTL = topLeft;
	auto btmBtnBR = bottomRight;
	if(im->btmBtnDown) std::swap(btmBtnTL, btmBtnBR);
	drawing::BevelBox(s, swapXY(im->horiz, {x+ 1, y + (int32_t)(h - sqSize) + 1, (uint32_t)sqSize - 3, (uint32_t)sqSize - 3}), btmBtnTL, btmBtnBR);
	
	double scale = (double)(h - (3 * sqSize)) / (double)im->lines;
	auto v = std::min(im->value, im->lines);
	int32_t pos = ((double)v * scale) + sqSize;
	
	auto bdr = colours::GetBorder().Fix(s);
	auto btn = colours::GetScrollbarButton().Fix(s);
	s.Box(swapXY(im->horiz, {x + 1, y + pos + 1, (uint32_t)sqSize - 2, (uint32_t)sqSize - 2}), btn, btn, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	drawing::Border(s, swapXY(im->horiz, {x, y + pos, (uint32_t)sqSize - 1, (uint32_t)sqSize - 1}), bdr);
	drawing::BevelBox(s, swapXY(im->horiz, {x + 1, y + pos + 1, (uint32_t)sqSize - 3, (uint32_t)sqSize - 3}), topLeft, bottomRight);
	if(im->focus){
		auto fcs = colours::GetScrollbarFocus().Fix(s);
		s.Box(swapXY(im->horiz, {x + 3, y + pos + 3, (uint32_t)sqSize - 6, (uint32_t)sqSize - 6}), fcs, fcs);
	}
	
	if(!im->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(im->rect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect Scrollbar::GetPaintRect(){
	return im->rect;
}

gds::Rect Scrollbar::GetInteractRect(){
	return im->rect;
}

uint32_t Scrollbar::GetSubscribed(){
	return wm_EventType::PointerMove | wm_EventType::PointerButtonDown | wm_EventType::PointerButtonUp | wm_EventType::Keyboard | wm_EventType::PointerLeave | wm_EventType::PointerEnter;
}

void Scrollbar::Focus(){
	if(!im->focus){
		im->focus = true;
		IControl::Paint(im->rect);
	}
}

void Scrollbar::Blur(){
	if(im->focus){
		im->focus = false;
		IControl::Paint(im->rect);
	}
}
	
void Scrollbar::SetLines(uint32_t l){
	if(l != im->lines){
		im->lines = l;
		IControl::Paint(im->rect);
	}
}

void Scrollbar::SetStep(uint32_t s){
	if(s != im->step){
		im->step = s;
		IControl::Paint(im->rect);
	}
}

void Scrollbar::SetPage(uint32_t p){
	if(p != im->page){
		im->page = p;
		IControl::Paint(im->rect);
	}
}

void Scrollbar::SetValue(uint32_t v){
	if(v != im->value){
		im->value = v;
		IControl::Paint(im->rect);
	}
}

uint32_t Scrollbar::GetValue(){
	return im->value;
}

uint32_t Scrollbar::GetFlags(){
	return 0;
}

void Scrollbar::Enable(){
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(im->rect);
	}
}

void Scrollbar::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(im->rect);
	}
}

bool Scrollbar::IsEnabled(){
	return im->enabled;
}

void Scrollbar::Refresh(){
	IControl::Paint(im->rect);
}

void Scrollbar::SetPosition(const gds::Rect &r){
	im->rect = r;
	im->bkSurf.reset();
	IControl::Paint(im->rect);
}

}
}
