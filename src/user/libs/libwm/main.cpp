#include <gds/libgds.h>
#include <wm/libwm.h>
#include <btos.h>

#include <cstring>
#include <sstream>
#include <cstdlib>

using namespace std;

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
	vinfo.subscriptions = wm_EventType::Close;
	strcpy(vinfo.title, "WM Vector Test");
	uint64_t vid = WM_CreateWindow(vinfo);
	GDS_SelectSurface(sid);
	bool draw = false;
	uint32_t x, y;
	while(true){
		wm_Event e = WM_GetEvent();
		if(e.window_id == id || e.window_id == vid){
			if(e.type == wm_EventType::Close) break;
			if(e.type == wm_EventType::PointerButtonDown){
				draw = true;
				x = e.Pointer.x;
				y = e.Pointer.y;
			}
			if(e.type == wm_EventType::PointerButtonUp){
				GDS_Line(x, y, e.Pointer.x, e.Pointer.y, GDS_GetColour(255, 255, 255));
				draw = false;
				WM_Update();
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
