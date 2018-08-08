#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-function"

#include <SDL2_widgets.h>

static TopWin *top_win;
static EditWin *edit_win;
static VScrollbar *edit_scr;

void set_icon(SDL_Window* window) {}

static void disp_topw() {
	fill_rect(top_win->render, 0, top_win->bgcol);
	//edit_win->draw();
}

int main(){
	top_win = new TopWin("ProtoText", Rect(100, 100, 500, 500), 0, SDL_WINDOW_RESIZABLE, true, disp_topw, set_icon);
	edit_win = new EditWin(top_win, Rect(0, 20, 490, 480), nullptr, [](int ctrl_key,int key) {});
	edit_scr=new VScrollbar(top_win,Style(0,0,5), Rect(490, 20, 10, 480), 200, [](VScrollbar *sb) { edit_win->set_offset(sb->value); }
  );
	get_events();
	return 0;
}