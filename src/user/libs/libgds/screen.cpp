#include <gds/screen.hpp>
#include <gds/libgds.h>

namespace btos_api{
namespace gds{

static bool cursorState = false;

	ScreenClass ScreenClass::Get(){
		return ScreenClass();
	}
	void ScreenClass::Select() const{
		GDS_SelectScreen();
	}

	void ScreenClass::Update(){
		GDS_UpdateScreen();
	}
	void ScreenClass::Update(const Rect &r){
		GDS_UpdateScreen(r.x, r.y, r.w, r.h);
	}
	void ScreenClass::SetMode(bt_vidmode mode){
		GDS_SetScreenMode(mode);
	}
	void ScreenClass::SetCursor(const Surface &surf, const Point &hotspot){
		GDS_SetCursor(surf.GetID(), hotspot.x, hotspot.y);
	}

	void ScreenClass::SetCursorVisibility(bool state){
		GDS_CursorVisibility(state);
		cursorState = state;
	}
	bool ScreenClass::GetCursorVisibility(){
		return cursorState;
	}
	
	ScreenClass Screen = ScreenClass::Get();

}
}
