#include <gds/surface.hpp>
#include <wm/window.hpp>
#include <btos/shm.hpp>
#include <wm/libwm.h>

#include <cstring>
#include <sstream>
#include <cstdlib>
#include <malloc.h>

using namespace std;
using namespace gds;
using namespace wm;

Surface create_shm_surface(){
	SHMSpace *space = new SHMSpace(bt_shm_flags::Normal);
	uint64_t shmRegion = space->ID();
	uint32_t rows = 200;
	uint32_t cols = 200;
	size_t size = rows * cols * 4;
	size_t pages = size / 4096;
	if(pages < size) ++pages;
	uint32_t *data = (uint32_t*)memalign(4096, pages * 4096);
	/*HMMapping *mapping =*/ new SHMMapping(shmRegion, (void*)data, 0, pages, bt_shm_flags::Normal);
	Surface surf(gds_SurfaceType::Memory, rows, cols, 100, gds_ColourType::True, shmRegion, 0);
	for(size_t y = 0; y < rows; ++y){
		uint32_t col = surf.GetColour(y, 0, 0);
		for(size_t x = 0; x < cols; ++x){
			data[(y * rows) + x] = col;
		}
	}
	return surf;
}

int main(){
	Font font = Font::Get("DejaVu Sans", gds_FontStyle::Normal);
	Surface s1(gds_SurfaceType::Bitmap, 320, 180);
	s1.Box({0, 0, 319, 179}, s1.GetColour(0, 0, 0), s1.GetColour(0, 0, 0), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	s1.Text({10, 10}, "Hello world!", font, 8, s1.GetColour(255, 255, 255));
	s1.Text({10, 20}, "Hello world!", font, 10, s1.GetColour(255, 255, 255));
	s1.Text({10, 32}, "Hello world!", font, 12, s1.GetColour(255, 255, 255));
	s1.Text({10, 45}, "Hello world!", font, 14, s1.GetColour(255, 255, 255));
	s1.Text({10, 60}, "Hello world!", font, 16, s1.GetColour(255, 255, 255));
	wm_WindowInfo info;
	info.x = 10;
	info.y = 10;
	info.gds_id = s1.GetID();
	info.options = wm_WindowOptions::Visible | wm_WindowOptions::NoExpand | wm_WindowOptions::NoHide | wm_WindowOptions::NoClose;// | wm_WindowOptions::NoMenu;
	info.subscriptions = wm_EventType::Close | wm_EventType::PointerButtonDown | wm_EventType::PointerButtonUp | wm_EventType::PointerMove;
	strcpy(info.title, "WM Test Application");
	Window w1(info);
	Surface s2(gds_SurfaceType::Vector, 200, 100, 100, gds_ColourType::True);
	for(size_t i = 0; i < 100; ++i){
		s2.Line({0, (int32_t)i}, {199, (int32_t)i}, s2.GetColour(0, 0, i * 2));
	}
	s2.Line({0, 0}, {199, 0}, s2.GetColour(255, 255, 255));
	//GDS_Box(0, 0, 199, 99, GDS_GetColour(255, 255, 255), GDS_GetColour(255, 255, 255), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	s2.Line({0, 0}, {199, 99}, s2.GetColour(255, 0, 255));
	s2.Line({0, 99}, {199, 0}, s2.GetColour(0, 255, 255));
	Font font2 = Font::Get("DejaVu Sans", gds_FontStyle::Bold);
	s2.Text({5, 50}, "TrueColour Vector!", font2, 16, s2.GetColour(255, 255, 0));
	wm_WindowInfo vinfo;
	vinfo.x = 100;
	vinfo.y = 100;
	vinfo.gds_id = s2.GetID();
	vinfo.options = wm_WindowOptions::Default;
	vinfo.subscriptions = wm_EventType::Close | wm_EventType::PointerButtonUp;
	strcpy(vinfo.title, "WM Vector Test");
	Window w2(vinfo);
	Surface shmsurf = create_shm_surface();
	Menu menu;
	menu.AddItem({1, "Hello menus!", wm_MenuItemFlags::Default, 0, 0});
	w2.SetMenu(menu);
	wm_WindowInfo shminfo;
	shminfo.x = 200;
	shminfo.y = 200;
	shminfo.gds_id = shmsurf.GetID();
	shminfo.options = wm_WindowOptions::NoFrame | wm_WindowOptions::Visible;
	shminfo.subscriptions = wm_EventType::Close;
	strcpy(shminfo.title, "SHM Test");
	Window w3(shminfo);
	bool draw = false;
	int32_t x, y;
	while(true){
		wm_Event e = WM_GetEvent();
		if(e.window_id == w1.GetID() || e.window_id == w2.GetID() || e.window_id == w3.GetID()){
			if(e.type == wm_EventType::Close) break;
			if(e.type == wm_EventType::PointerButtonDown && e.window_id == w1.GetID()){
				draw = true;
				x = e.Pointer.x;
				y = e.Pointer.y;
			}
			if(e.type == wm_EventType::PointerButtonUp){
				if(e.window_id == w1.GetID()){
					s1.Line({x, y}, {(int32_t)e.Pointer.x, (int32_t)e.Pointer.y}, s1.GetColour(255, 255, 255));
					draw = false;
					w1.Update();
				}else{
					w2.ShowMenu(menu, {(int32_t)e.Pointer.x, (int32_t)e.Pointer.y});
				}
			}
			if(e.type == wm_EventType::PointerMove && draw){
				s1.Line({x, y}, {(int32_t)e.Pointer.x, (int32_t)e.Pointer.y}, s1.GetColour(255, 255, 255));
				w1.Update({min<int32_t>(x, e.Pointer.x), min<int32_t>(y, e.Pointer.y), (uint32_t)abs((int32_t)e.Pointer.x - (int32_t)x) + 1, (uint32_t)abs((int32_t)e.Pointer.y - (int32_t)y) + 1});
				x = e.Pointer.x;
				y = e.Pointer.y;
			}
		}
	}
	return 0;
}
