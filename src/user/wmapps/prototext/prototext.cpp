#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-function"

#include <SDL2_widgets.h>

static TopWin *top_win;
static EditWin *edit_win;

void set_icon(SDL_Window* window) {}

static void disp_topw() {
	fill_rect(top_win->render, 0, top_win->bgcol);
	//edit_win->draw();
}

int main(){
	top_win = new TopWin("ProtoText", Rect(100, 100, 500, 500), 0, SDL_WINDOW_RESIZABLE, true, disp_topw, set_icon);
	edit_win = new EditWin(top_win, Rect(0, 0, 500, 500), "", [](int ctrl_key,int key) {});
	get_events();
	return 0;
}