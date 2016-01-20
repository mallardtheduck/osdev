#include <btos.h>
#include <wm/libwm.h>
#include <gds/libgds.h>
#include <string>
#include <vector>
#include <utility>

using namespace std;

const uint32_t LineHeight = 20;

vector<pair<string, string>> options = {
	{"Test application", "hdd:/btos/tests/wmtest.elx"},
	{"Terminal window", "hdd:/btos/bin/termwin.elx"},
	{"Breakout", "hdd:/btos/bin/breakout.elx"},
	{"Quit", "QUIT"},
};

size_t RenderMenu(uint64_t surf, uint32_t ypos = UINT32_MAX, bool down = true){
	GDS_SelectSurface(surf);
	gds_SurfaceInfo info = GDS_SurfaceInfo();
	uint32_t pos = 0;
	size_t ret = SIZE_MAX;
	for(size_t i = 0; i<options.size(); ++i){
		auto &o = options[i];
		uint32_t itemColour = GDS_GetColour(255, 255, 255);
		if(ypos > pos && ypos < pos +LineHeight){
			if(down) itemColour = GDS_GetColour(128, 128, 255);
			ret = i;
		}
		GDS_Box(0, pos, info.w, LineHeight, 0, itemColour, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
		GDS_Line(0, pos, info.w, pos, GDS_GetColour(128, 128, 128));
		GDS_Text(5, pos + 2, o.first.c_str(), gds_TEMPFonts::Small, 0, GDS_GetColour(0, 0, 0));
		pos += LineHeight;
	}
	return ret;
}

int main(){
	uint64_t surf = GDS_NewSurface(gds_SurfaceType::Bitmap, 200, LineHeight * options.size());
	/*uint64_t win =*/ WM_NewWindow(5, 5, wm_WindowOptions::Default, wm_EventType::PointerButtonDown | wm_EventType::PointerButtonUp | wm_EventType::Close, surf, "WM Menu");
	RenderMenu(surf);
	WM_Update();
	size_t buttonIndex = SIZE_MAX;
	while(true){
		wm_Event e = WM_GetEvent();
		if(e.type == wm_EventType::Close) break;
		if(e.type == wm_EventType::PointerButtonDown){
			buttonIndex = RenderMenu(surf, e.Pointer.y);
			WM_Update();
		}
		if(e.type == wm_EventType::PointerButtonUp){
			if(RenderMenu(surf, e.Pointer.y, false) == buttonIndex && buttonIndex != SIZE_MAX){
				auto &o = options[buttonIndex];
				if(o.second == "QUIT") break;
				else{
					bt_spawn(o.second.c_str(), 0, NULL);
				}
			}
			WM_Update();
		}
	}
	return 0;
}