#include <gds/libgds.h>
#include <wm/libwm.h>
#include <btos_stubs.h>

#include <cstring>
#include <sstream>
#include <cstdlib>

using namespace std;

int main(){
	uint64_t sid = GDS_NewSurface(gds_SurfaceType::Bitmap, 320, 180);
	GDS_Box(0, 0, 319, 179, GDS_GetColour(0, 0, 0), GDS_GetColour(0, 0, 0), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_Text(10, 10, "Hello world!", gds_TEMPFonts::Tiny, 0, GDS_GetColour(255, 255, 255));
	GDS_Text(10, 20, "Hello world!", gds_TEMPFonts::Small, 0, GDS_GetColour(255, 255, 255));
	GDS_Text(10, 32, "Hello world!", gds_TEMPFonts::MediumBold, 0, GDS_GetColour(255, 255, 255));
	GDS_Text(10, 45, "Hello world!", gds_TEMPFonts::Large, 0, GDS_GetColour(255, 255, 255));
	GDS_Text(10, 60, "Hello world!", gds_TEMPFonts::Giant, 0, GDS_GetColour(255, 255, 255));
	wm_WindowInfo info;
	info.x = 10;
	info.y = 10;
	info.gds_id = sid;
	info.subscriptions = wm_EventType::Close | wm_EventType::PointerButtonDown | wm_EventType::PointerButtonUp | wm_EventType::PointerMove;
	strcpy(info.title, "WM Test Application");
	uint64_t id = WM_CreateWindow(info);
	bool draw = false;
	uint32_t x, y;
	while(true){
		wm_Event e = WM_GetEvent();
		if(e.window_id == id){
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