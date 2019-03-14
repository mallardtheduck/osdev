#include <dev/rtc.h>
#include <iostream>
#include <btos/message.hpp>
#include <gds/surface.hpp>
#include <gds/geom.hpp>
#include <wm/window.hpp>
#include <btos/timer.hpp>
#include <btos/messageloop.hpp>
#include <wm/eventloop.hpp>
#include <memory>
#include <util/tinyformat.hpp>
#include "game.hpp"

using namespace std;
using namespace gds;
using namespace wm;

enum class gamestate{
	Title,
	GameStart,
	GamePlay,
	Finish,
};

int main(){
    auto surface = make_shared<Surface>(gds_SurfaceType::Bitmap, 320, 240);
	auto win = make_shared<Window>(Point{100, 100}, wm_WindowOptions::Default, wm_EventType::Keyboard | wm_EventType::Close, *surface, "Breakout");
	font = Font::Get("DejaVu Sans", gds_FontStyle::Bold);
	surface->BeginQueue();
	DrawBackground(surface);
	DrawTitle(surface);
	surface->CommitQueue();
	win->Update();
	auto timer = make_shared<Timer>(100);
	gamestate state = gamestate::Title;
	win->SetEventHandler([&](const wm_Event &e)->bool{
		if(e.type == wm_EventType::Close) return false;
		switch(state){
			case gamestate::Title:{
				if(e.type == wm_EventType::Keyboard) state = gamestate::GameStart;
				break;
			}
			case gamestate::GameStart:{
				InitGame(surface, win);
				state = gamestate::GamePlay;
				timer->Reset();
				break;
			}
			case gamestate::GamePlay:{
				GameEvent(e);
				break;
			}
			default: break;
		}
		return true;
	});
	timer->SetHandler([&](Timer &t)->bool{
		switch(state){
			case gamestate::GamePlay:{
				t.Reset();
				bool end = GameStep(surface);
				GameDraw(win, surface);
				if(end) state = gamestate::Finish;
				break;
			}
			case gamestate::Finish:{
				EndGame();
				DrawBackground(surface);
				DrawEndScreen(surface);
				win->Update();
				bt_rtc_sleep(2000);
				DrawBackground(surface);
				DrawTitle(surface);
				win->Update();
				state = gamestate::Title;
				break;
			}
			default: break;
		}
		return true;
	});
	auto eventLoop = make_shared<EventLoop>();
	eventLoop->AddWindow(win);
	MessageLoop msgLoop;
	msgLoop.AddHandler(eventLoop);
	msgLoop.AddHandler(timer);
	msgLoop.RunLoop();
    return 0;
}
