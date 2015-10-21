#include "windows.hpp"
#include "metrics.hpp"

#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

#include <gds/libgds.h>
#include <btos_stubs.h>

using namespace std;

map<uint64_t, shared_ptr<Window>> windows;
weak_ptr<Window> activeWindow;
weak_ptr<Window> pointerWindow;
uint64_t id_counter;
vector<weak_ptr<Window>> sortedWindows;

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
	return id;
}

void RemoveWindow(uint64_t id){
	windows.erase(id);
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

void DrawWindows(){
	vector<shared_ptr<Window>> wins = SortWindows();
	GDS_SelectScreen();
	gds_SurfaceInfo info = GDS_SurfaceInfo();
	GDS_Box(0, 0, info.w, info.h, GetColour(BackgroundColour), GetColour(BackgroundColour), 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
	shared_ptr<Window> awin = activeWindow.lock();
	for(auto w: wins){
		w->Draw(w == awin);
	}
}

void RefreshScreen(const Rect &r){
	GDS_UpdateScreen(r.x, r.y, r.w, r.h);
}

shared_ptr<Window> GetWindowAt(uint32_t x, uint32_t y){
	shared_ptr<Window> ret;
	for(auto w = sortedWindows.rbegin(); w != sortedWindows.rend(); ++w){
		shared_ptr<Window> win = w->lock();
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
	shared_ptr<Window> awin = activeWindow.lock();
	if(event.type == bt_terminal_event_type::Key && awin) awin->KeyInput(event.key);
	else if(event.type ==  bt_terminal_event_type::Pointer){
		shared_ptr<Window> win = GetWindowAt(event.pointer.x, event.pointer.y);
		shared_ptr<Window> pwin = pointerWindow.lock();
		if(win != pwin){
			if(pwin) pwin->PointerLeave();
			if(win) win->PointerEnter();
			pointerWindow = win;
		}
		if(!win) return;
		if(event.pointer.type == bt_terminal_pointer_event_type::ButtonDown){
			shared_ptr<Window> old = awin;
			activeWindow = win;
			BringToFront(win);
			DrawWindows();
			RefreshScreen(old->GetBoundingRect());
			RefreshScreen(win->GetBoundingRect());
		}
		win->PointerInput(event.pointer);
	}
}