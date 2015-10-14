#include "windows.hpp"

#include <map>
#include <vector>
#include <algorithm>

#include <gds/libgds.h>

using namespace std;

map<uint64_t, shared_ptr<Window>> windows;
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
	return id;
}

void RemoveWindow(uint64_t id){
	windows.erase(id);
}

shared_ptr<Window> GetWindow(uint64_t id){
	return windows[id];
}

shared_ptr<Window> GetActiveWindow(){
	return std::shared_ptr<Window>();
}

void DrawWindows(){
	vector<shared_ptr<Window>> wins;
	MapToVec(windows, wins);
	sort(begin(wins), end(wins), &ZOrderSort);
	
	GDS_SelectScreen();
	for(auto w: wins){
		w->Draw(false);
	}
	GDS_UpdateScreen();
}