#include <gds/libgds.h>
#include <wm/libwm.h>
#include <btos.h>

#include <cstring>
#include <sstream>
#include <cstdlib>
#include <malloc.h>

using namespace std;

uint32_t create_shm_surface(){
	bt_handle_t shm_region_handle = bt_create_shm(bt_shm_flags::Normal);
	uint64_t shmRegion = bt_shm_id(shm_region_handle);
	uint32_t rows = 200;
	uint32_t cols = 200;
	size_t size = rows * cols * 4;
	size_t pages = size / 4096;
	if(pages < size) ++pages;
	uint32_t *data = (uint32_t*)memalign(4096, pages * 4096);
	bt_shm_map(shmRegion, (void*)data, 0, pages, bt_shm_flags::Normal);
	for(size_t y = 0; y < rows; ++y){
		uint32_t col = GDS_GetColour(y, 0, 0);
		for(size_t x = 0; x < cols; ++x){
			data[(y * rows) + x] = col;
		}
	}
	return GDS_NewSurface(gds_SurfaceType::Memory, rows, cols, 100, gds_ColourType::True, shmRegion, 0);
}

int main(){
	uint32_t font = GDS_GetFontID("DejaVu Sans", gds_FontStyle::Normal);
	uint64_t sid = GDS_NewSurface(gds_SurfaceType::Bitmap, 320, 180);
	GDS_Box(0, 0, 319, 179, GDS_GetColour(0, 0, 0), GDS_GetColour(0, 0, 0), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_Text(10, 10, "Hello world!", font, 8, GDS_GetColour(255, 255, 255));
	GDS_Text(10, 20, "Hello world!", font, 10, GDS_GetColour(255, 255, 255));
	GDS_Text(10, 32, "Hello world!", font, 12, GDS_GetColour(255, 255, 255));
	GDS_Text(10, 45, "Hello world!", font, 14, GDS_GetColour(255, 255, 255));
	GDS_Text(10, 60, "Hello world!", font, 16, GDS_GetColour(255, 255, 255));
	wm_WindowInfo info;
	info.x = 10;
	info.y = 10;
	info.gds_id = sid;
	info.subscriptions = wm_EventType::Close | wm_EventType::PointerButtonDown | wm_EventType::PointerButtonUp | wm_EventType::PointerMove;
	strcpy(info.title, "WM Test Application");
	uint64_t id = WM_CreateWindow(info);
	uint64_t vsid = GDS_NewSurface(gds_SurfaceType::Vector, 200, 100, 100, gds_ColourType::True);
	for(size_t i = 0; i < 100; ++i){
		GDS_Line(0, i, 199, i, GDS_GetColour(0, 0, i * 2));
	}
	GDS_Line(0, 0, 199, 0, GDS_GetColour(255, 255, 255));
	//GDS_Box(0, 0, 199, 99, GDS_GetColour(255, 255, 255), GDS_GetColour(255, 255, 255), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_Line(0, 0, 199, 99, GDS_GetColour(255, 0, 255));
	GDS_Line(0, 99, 199, 0, GDS_GetColour(0, 255, 255));
	uint32_t font2 = GDS_GetFontID("DejaVu Sans", gds_FontStyle::Bold);
	GDS_Text(5, 50, "TrueColour Vector!", font2, 16, GDS_GetColour(255, 255, 0));
	wm_WindowInfo vinfo;
	vinfo.x = 100;
	vinfo.y = 100;
	vinfo.gds_id = vsid;
	vinfo.subscriptions = wm_EventType::Close | wm_EventType::PointerButtonUp;
	strcpy(vinfo.title, "WM Vector Test");
	uint64_t vid = WM_CreateWindow(vinfo);
	uint32_t shmsurf = create_shm_surface();
	wm_WindowInfo shminfo;
	shminfo.x = 200;
	shminfo.y = 200;
	shminfo.gds_id = shmsurf;
	shminfo.subscriptions = wm_EventType::Close;
	strcpy(shminfo.title, "SHM Test");
	uint64_t shmwin = WM_CreateWindow(shminfo);
	GDS_SelectSurface(sid);
	WM_SelectWindow(id);
	bool draw = false;
	uint32_t x, y;
	while(true){
		wm_Event e = WM_GetEvent();
		if(e.window_id == id || e.window_id == vid || e.window_id == shmwin){
			if(e.type == wm_EventType::Close) break;
			if(e.type == wm_EventType::PointerButtonDown && e.window_id == id){
				draw = true;
				x = e.Pointer.x;
				y = e.Pointer.y;
			}
			if(e.type == wm_EventType::PointerButtonUp){
				if(e.window_id == id){
					GDS_Line(x, y, e.Pointer.x, e.Pointer.y, GDS_GetColour(255, 255, 255));
					draw = false;
					WM_Update();
				}else{
					
				}
			}
			if(e.type == wm_EventType::PointerMove && draw){
				GDS_Line(x, y, e.Pointer.x, e.Pointer.y, GDS_GetColour(255, 255, 255));
				WM_UpdateRect(min(x, e.Pointer.x), min(y, e.Pointer.y), abs((int32_t)e.Pointer.x - (int32_t)x) + 1, abs((int32_t)e.Pointer.y - (int32_t)y) + 1);
				x = e.Pointer.x;
				y = e.Pointer.y;
			}
		}
	}
	return 0;
}
