#include <gds/screen.hpp>
#include <gds/libgds.h>

namespace btos_api{
namespace gds{

static bool cursorState = false;

	Screen Screen::Get(){
		return Screen();
	}
	void Screen::Select(){
		GDS_SelectScreen();
	}

	void Screen::Update(){
		GDS_UpdateScreen();
	}
	void Screen::Update(const Rect &r){
		GDS_UpdateScreen(r.x, r.y, r.w, r.h);
	}
	void Screen::SetMode(bt_vidmode mode){
		GDS_SetScreenMode(mode);
	}
	void Screen::SetCursor(const Surface &surf, const Point &hotspot){
		GDS_SetCursor(surf.GetID(), hotspot.x, hotspot.y);
	}

	void Screen::SetCursorVisibility(bool state){
		GDS_CursorVisibility(state);
		cursorState = state;
	}
	bool Screen::GetCursorVisibility(){
		return cursorState;
	}

}
}
