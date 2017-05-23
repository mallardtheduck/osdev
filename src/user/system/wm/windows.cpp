#include "windows.hpp"
#include "metrics.hpp"
#include "service.hpp"
#include "menus.hpp"

#define DBG(x) do{std::stringstream dbgss; dbgss << x << std::endl; bt_zero(dbgss.str().c_str());}while(0)

#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

#include <gds/libgds.h>
#include <btos.h>

#include <dev/rtc.h>

using namespace std;

static map<uint64_t, shared_ptr<Window>> windows;
static weak_ptr<Window> activeWindow;
static weak_ptr<Window> pointerWindow;
static weak_ptr<Window> grabbedWindow;
static uint64_t id_counter;
static vector<weak_ptr<Window>> sortedWindows;
static uint32_t backgroundColour;

void InitWindws(){
	GDS_SelectScreen();
	backgroundColour = GetColour(BackgroundColour);
}

template <typename M, typename V> 
void MapToVec( const  M & m, V & v ) {
    for( typename M::const_iterator it = m.begin(); it != m.end(); ++it ) {
    	v.push_back( it->second );
    }
}

bool ZOrderSort(shared_ptr<Window> a, shared_ptr<Window> b){
	if(!a) return true;
	if(!b) return false;
	return a->GetZOrder() < b->GetZOrder();
}

uint64_t AddWindow(shared_ptr<Window> win){
	uint64_t id = ++id_counter;
	windows[id] = win;
	shared_ptr<Window> awin = activeWindow.lock();
	if(!awin) activeWindow = win;
	win->id = id;
	return id;
}

void RemoveWindow(uint64_t id){
	Rect bounds = GetWindow(id)->GetBoundingRect();
	windows.erase(id);
	DrawAndRefreshWindows(bounds);
}

shared_ptr<Window> GetWindow(uint64_t id){
	return windows[id];
}

shared_ptr<Window> GetActiveWindow(){
	return activeWindow.lock();
}

vector<shared_ptr<Window>> SortWindows(){
	vector<shared_ptr<Window>> wins;
	MapToVec(windows, wins);
	sort(begin(wins), end(wins), &ZOrderSort);
	sortedWindows = vector<weak_ptr<Window>>(wins.begin(), wins.end());
	return wins;
}

void DrawWindows(const Rect &r, uint64_t above, bool ignoreGrab){
	bool rect = (r.x != 0 || r.y != 0 || r.w != 0 || r.h != 0);
	vector<shared_ptr<Window>> wins = SortWindows();
	GDS_SelectScreen();
	shared_ptr<Window> lastWin;
	bool drawing = true;
	if(rect && !above){
		for(auto i = wins.rbegin(); i != wins.rend(); ++i){
			if(!(*i)->GetVisible()) continue;
			if(Contains((*i)->GetBoundingRect(), r)) {
				lastWin = *i;
				drawing = false;
				break;
			}
		}
	}else if(above){
		for(auto w : wins){
			if(w->id == above){
				lastWin = w;
				drawing = false;
				break;
			}
		}
	}
	if(drawing){
		if(rect) GDS_Box(r.x, r.y, r.w, r.h, backgroundColour, backgroundColour, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
		else{
			gds_SurfaceInfo info = GDS_SurfaceInfo();
			GDS_Box(0, 0, info.w, info.h, backgroundColour, backgroundColour, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
		}
	}
	shared_ptr<Window> awin = activeWindow.lock();
	for(auto w: wins){
		if(!w->GetVisible()) continue;
		if((rect || above) && w == lastWin) drawing = true;
		if(drawing){
			if(rect && Overlaps(r, w->GetBoundingRect())){
				w->Draw(w == awin, r); 

			}
			else if(!rect) w->Draw(w == awin);
		}
	}
	if(!ignoreGrab){
		if(auto gwin = grabbedWindow.lock())gwin->DrawGrabbed(r);
	}
	RedrawMenus(r);
}

void DrawWindows(const vector<Rect> &v){
	vector<shared_ptr<Window>> wins = SortWindows();
	GDS_SelectScreen();
	for(auto r: v) GDS_Box(r.x, r.y, r.w, r.h, backgroundColour, backgroundColour, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
	shared_ptr<Window> awin = activeWindow.lock();
	for(auto w: wins){
		if(!w->GetVisible()) continue;
		for(auto r: v) if(Overlaps(r, w->GetBoundingRect())){
			w->Draw(w==awin, r);
		}
	}
}

void RefreshScreen(Rect r){
	if(r.x < 0){
		r.w += r.x;
		r.x = 0;
	}
	if(r.y < 0){
		r.h += r.y;
		r.y = 0;
	}
	GDS_UpdateScreen(r.x, r.y, r.w, r.h);
}

void RefreshScreen(const vector<Rect> &v){
	for(auto r: v) RefreshScreen(r);
}

shared_ptr<Window> GetWindowAt(uint32_t x, uint32_t y){
	shared_ptr<Window> ret;
	for(auto w = sortedWindows.rbegin(); w != sortedWindows.rend(); ++w){
		shared_ptr<Window> win = w->lock();
		if(!win) continue;
		Rect wrect = win->GetBoundingRect();
		if(InRect(x, y, wrect)) return win;
	}
	return ret;
}

void BringToFront(shared_ptr<Window> win){
	vector<shared_ptr<Window>> wins = SortWindows();
	uint32_t zcounter = 0;
	for(auto w: wins){
		w->SetZOrder(++zcounter, false);
	}
	win->SetZOrder(++zcounter, false);
}

void HandleInput(const bt_terminal_event &event){
	if(event.type == bt_terminal_event_type::Pointer && MenuPointerInput(event.pointer)) return;
	static Point curpos = {INT32_MAX, INT32_MAX};
	if(auto gwin = grabbedWindow.lock()){
		if(event.type == bt_terminal_event_type::Key) gwin->KeyInput(event.key);
		else if(event.type == bt_terminal_event_type::Pointer) {
			if(event.pointer.type == bt_terminal_pointer_event_type::Move && event.pointer.x == (uint32_t)curpos.x && event.pointer.y == (uint32_t)curpos.y) return;
			gwin->PointerInput(event.pointer);
			curpos.x = event.pointer.x; curpos.y = event.pointer.y;
			bt_terminal_pointer_info info;
			bt_fioctl(stdin_handle, bt_terminal_ioctl::GetPointerInfo, sizeof(info), (char*)&info);
			while((info.x != (uint32_t)curpos.x || info.y != (uint32_t)curpos.y) && (info.flags & 1 << event.pointer.button)){
				bt_terminal_pointer_event e;
				e.type = bt_terminal_pointer_event_type::Move;
				e.x = info.x;
				e.y = info.y;
				gwin->PointerInput(e);
				curpos.x = info.x;
				curpos.y = info.y;
				bt_fioctl(stdin_handle, bt_terminal_ioctl::GetPointerInfo, sizeof(info), (char*)&info);
			}
		}
		return;
	}
	shared_ptr<Window> awin = activeWindow.lock();
	if(event.type == bt_terminal_event_type::Key && awin) awin->KeyInput(event.key);
	else if(event.type == bt_terminal_event_type::Pointer){
		uint64_t pointer_start = bt_rtc_millis();
		if(event.pointer.type == bt_terminal_pointer_event_type::Move && event.pointer.x == (uint32_t)curpos.x && event.pointer.y == (uint32_t)curpos.y) return;
		curpos.x = event.pointer.x; curpos.y = event.pointer.y;
		shared_ptr<Window> win = GetWindowAt(event.pointer.x, event.pointer.y);
		shared_ptr<Window> pwin = pointerWindow.lock();
		if(win != pwin){
			if(pwin) pwin->PointerLeave();
			if(win) win->PointerEnter();
			pointerWindow = win;
		}
		if(!win) return;
		uint64_t pointer_s1 = bt_rtc_millis();
		if(event.pointer.type == bt_terminal_pointer_event_type::ButtonDown && win != activeWindow.lock()){
			uint64_t activate_start = bt_rtc_millis();
			shared_ptr<Window> old = awin;
			activeWindow = win;
			BringToFront(win);
			if(old){
				DrawAndRefreshWindows(win->GetBoundingRect(), win->id);
				DrawAndRefreshWindows(old->GetBoundingRect(), old->id);
			}else{
				DrawAndRefreshWindows(win->GetBoundingRect(), win->id);
			}
			uint64_t activate_end = bt_rtc_millis();
			DBG("WM Activate: " << activate_end - activate_start << "ms");
		}
		win->PointerInput(event.pointer);
		uint64_t pointer_end = bt_rtc_millis();
		DBG("WM: Pointer input stage1: " << pointer_s1 - pointer_start << "ms stage2: " << pointer_end - pointer_s1 << "ms");
	}
}

void WindowGrab(uint64_t id){
	grabbedWindow = GetWindow(id);
}

void UnGrab(){
	grabbedWindow.reset();
}

void DrawAndRefreshWindows(const Rect &r, uint64_t above){
	DrawWindows(r, above);
	RefreshScreen(r);
}

void DrawAndRefreshWindows(const vector<Rect> &v){
	DrawWindows(v);
	RefreshScreen(v);
}
