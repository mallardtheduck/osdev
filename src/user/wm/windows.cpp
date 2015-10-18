#include "windows.hpp"
#include "metrics.hpp"

#include <map>
#include <vector>
#include <algorithm>

#include <gds/libgds.h>

using namespace std;

map<uint64_t, shared_ptr<Window>> windows;
shared_ptr<Window> activeWindow;
uint64_t id_counter;

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
	if(!activeWindow) activeWindow = win;
	return id;
}

void RemoveWindow(uint64_t id){
	windows.erase(id);
}

shared_ptr<Window> GetWindow(uint64_t id){
	return windows[id];
}

shared_ptr<Window> GetActiveWindow(){
	return activeWindow;
}

vector<shared_ptr<Window>> SortWindows(){
	vector<shared_ptr<Window>> wins;
	MapToVec(windows, wins);
	sort(begin(wins), end(wins), &ZOrderSort);
	return wins;
}

void DrawWindows(const Rect &r){
	vector<shared_ptr<Window>> wins = SortWindows();
	
	GDS_SelectScreen();
	gds_SurfaceInfo info = GDS_SurfaceInfo();
	GDS_Box(0, 0, info.w, info.h, GetColour(BackgroundColour), GetColour(BackgroundColour), 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
	for(auto w: wins){
		w->Draw(w == activeWindow);
	}
	GDS_UpdateScreen(r.x, r.y, r.w, r.h);
}

shared_ptr<Window> GetWindowAt(uint32_t x, uint32_t y){
	shared_ptr<Window> ret;
	for(auto w: windows){
		Rect wrect = w.second->GetBoundingRect();
		if(x >= wrect.x && x <=wrect.x + wrect.w && y >= wrect.y && y <= wrect.y + wrect.h){
			if(!ret || w.second->GetZOrder() > ret->GetZOrder()) ret = w.second;
		}
	}
	return ret;
}

void BringToFront(shared_ptr<Window> win){
	vector<shared_ptr<Window>> wins = SortWindows();
	uint32_t zcounter = 0;
	for(auto w: wins){
		w->SetZOrder(++zcounter);
	}
	win->SetZOrder(++zcounter);
}

void HandleInput(const bt_terminal_event &event){
	if(event.type == bt_terminal_event_type::Key && activeWindow) activeWindow->KeyInput(event.key);
	else if(event.type ==  bt_terminal_event_type::Pointer){
		shared_ptr<Window> win = GetWindowAt(event.pointer.x, event.pointer.y);
		if(!win) return;
		if(event.pointer.type == bt_terminal_pointer_event_type::ButtonDown){
			shared_ptr<Window> old = activeWindow;
			activeWindow = win;
			BringToFront(win);
			DrawWindows(old->GetBoundingRect());
			DrawWindows(activeWindow->GetBoundingRect());
		}
		win->PointerInput(event.pointer);
	}
}