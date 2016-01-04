#include <gds/libgds.h>
#include <wm/libwm.h>
#include "game.hpp"

using namespace std;

enum class gamestate{
	Title,
	GameStart,
	GamePlay,
	Finish,
};

int main(){
    uint64_t surface = GDS_NewSurface(gds_SurfaceType::Bitmap, 320, 240);
	/*uint64_t win =*/ WM_NewWindow(100, 100, wm_WindowOptions::Default, wm_EventType::Keyboard | wm_EventType::Close, surface, "Breakout");
	DrawBackground();
	DrawTitle();
	WM_Update();
	gamestate state = gamestate::Title;
	while(true){
		wm_Event e = WM_GetEvent();
		if(e.type == wm_EventType::Close) break;
		switch(state){
			case gamestate::Title:{
				if(e.type == wm_EventType::Keyboard) state = gamestate::GameStart;
				break;
			}
			case gamestate::GameStart:{
				InitGame();
				state = gamestate::GamePlay;
				break;
			}
			case gamestate::GamePlay:{
				GameEvent(e);
				GameStep();
				GameDraw();
				break;
			}
			case gamestate::Finish:{
				break;
			}
		}
	}
    return 0;
}