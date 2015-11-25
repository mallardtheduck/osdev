#include <gds/libgds.h>
#include <wm/libwm.h>
#include <btos_stubs.h>

#include <cstring>
#include <sstream>

using namespace std;

int main(){
	uint64_t sid = GDS_NewSurface(gds_SurfaceType::Bitmap, 160, 90);
	GDS_Box(0, 0, 159, 89, GDS_GetColour(0, 0, 0), GDS_GetColour(0, 0, 0), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	wm_WindowInfo info;
	info.x = 10;
	info.y = 10;
	info.gds_id = sid;
	info.subscriptions = wm_EventType::Close | wm_EventType::PointerButtonUp;
	strcpy(info.title, "EXTERNAL TEST WINDOW");
	uint64_t id = WM_CreateWindow(info);
	while(true){
		wm_Event e = WM_GetEvent();
		stringstream ss;
		ss << "Event on window: " << e.window_id << endl;
		ss << "Event type: " << e.type << endl;
		if(e.window_id == id && e.type == wm_EventType::Close) break;
		if(e.window_id == id && e.type == wm_EventType::PointerButtonUp){
			ss << "Position: (" << e.Pointer.x << ", " << e.Pointer.y << ")." << endl;
			GDS_Dot(e.Pointer.x, e.Pointer.y, GDS_GetColour(255, 255, 255));
			WM_Update();
		}
		bt_zero(ss.str().c_str());
	}
	return 0;
}