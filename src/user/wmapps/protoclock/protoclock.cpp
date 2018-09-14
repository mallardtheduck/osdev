#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-function"

#include <SDL2_widgets.h>
#include <string>
#include <fstream>

static TopWin *top_win;
static TextWin *timeMsg;

std::string text;

static std::string GetTimeString(){
	std::ifstream rtc("INFO:/RTC");
	std::string ret;
	std::getline(rtc, ret);
	return ret;
}

void set_icon(SDL_Window* window) {}

static void disp_topw() {
	fill_rect(top_win->render, 0, top_win->bgcol);
}

int thread_fun(void *arg){
	while(true){
		send_uev([](int) {
			auto ntext = GetTimeString();
			if(text != ntext){
				timeMsg->reset();
				timeMsg->add_text(text.c_str(), true);
				text = ntext;
			}
			top_win->refresh();
		}, 0);
		SDL_Delay(250);
	}
	return 0;
}

int main(){
	top_win = new TopWin("ProtoClock", Rect(100, 100, 200, 50), 0, SDL_WINDOW_RESIZABLE, true, disp_topw, set_icon);
	timeMsg = new TextWin(top_win, Style(0, 0 ,5), Rect(30, 15, 170, 20), 1, nullptr);
	timeMsg->bgcol = cBackground;
	SDL_CreateThread(thread_fun, "thread_fun", 0);
	get_events();
	return 0;
}