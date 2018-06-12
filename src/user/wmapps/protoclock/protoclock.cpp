#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-function"

#include <SDL2_widgets.h>
#include <string>
#include <fstream>

static TopWin *top_win;
static Message *timeMsg;

static std::string GetTimeString(){
	std::ifstream rtc("INFO:/RTC");
	std::string ret;
	std::getline(rtc, ret);
	return ret;
}

void set_icon(SDL_Window* window) {}

static void disp_topw() {
	fill_rect(top_win->render, 0, top_win->bgcol);
	auto t = GetTimeString();
	timeMsg->label = t.c_str();
	timeMsg->draw_label();
}

int thread_fun(void *arg){
	while(true){
		send_uev([](int) {
			disp_topw();
			top_win->refresh();
		}, 0);
		SDL_Delay(250);
	}
	return 0;
}

int main(){
	top_win = new TopWin("ProtoClock", Rect(100, 100, 200, 50), 0, SDL_WINDOW_RESIZABLE, true, disp_topw, set_icon);
	timeMsg = new Message(top_win, 2, "1999-99-99 99:99:99", Point(30, 15));
	SDL_CreateThread(thread_fun, "thread_fun", 0);
	get_events();
	return 0;
}