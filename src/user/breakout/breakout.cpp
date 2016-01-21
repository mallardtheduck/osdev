#include <gds/libgds.h>
#include <wm/libwm.h>
#include <dev/rtc.h>
#include <iostream>
#include "game.hpp"

USE_BT_RTC_API;

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
	bt_handle_t timer = bt_rtc_create_timer(100);
	gamestate state = gamestate::Title;
	while(true){
		btos_api::bt_msg_header msg = bt_recv(true);
		wm_Event e = WM_ParseMessage(&msg);
		if(e.type == wm_EventType::Close) break;
		switch(state){
			case gamestate::Title:{
				if(e.type == wm_EventType::Keyboard) state = gamestate::GameStart;
				break;
			}
			case gamestate::GameStart:{
				InitGame();
				state = gamestate::GamePlay;
				bt_rtc_reset_timer(timer);
				break;
			}
			case gamestate::GamePlay:{
				if(msg.from == 0 && msg.source == bt_rtc_ext_id){
					bt_rtc_reset_timer(timer);
					bool end = GameStep();
					GameDraw();
					if(end) state = gamestate::Finish;
				}else{
					GameEvent(e);
				}
				break;
			}
			case gamestate::Finish:{
				EndGame();
				DrawBackground();
				DrawEndScreen();
				WM_Update();
				bt_rtc_sleep(2000);
				DrawBackground();
				DrawTitle();
				WM_Update();
				state = gamestate::Title;
				break;
			}
		}
		bt_msg_ack(&msg);
	}
    return 0;
}