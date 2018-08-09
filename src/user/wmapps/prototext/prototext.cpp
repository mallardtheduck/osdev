#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-function"

#include <SDL2_widgets.h>

static TopWin *top_win;
static EditWin *edit_win;
static VScrollbar *edit_scr;

static int edit_lines = 0;
static int edit_offset = 0;

void set_icon(SDL_Window* window) {}

static void disp_topw() {
	fill_rect(top_win->render, 0, top_win->bgcol);
}

int main(){
	top_win = new TopWin("ProtoText", Rect(100, 100, 500, 500), 0, SDL_WINDOW_RESIZABLE, true, disp_topw, set_icon);
	edit_win = new EditWin(top_win, Rect(0, 20, 490, 480), nullptr, 
		[](int ctrl_key, int key) {
			int lines = 0;
			int ypos = 0;
			edit_win->get_info(nullptr, &lines, &ypos, nullptr, nullptr);
			if(lines != edit_lines){
				edit_scr->set_range((lines + 1) * TDIST);
				edit_lines = lines;
				edit_scr->set_ypos(edit_offset);
			}
			if(ypos * TDIST > edit_offset + 480){
				edit_offset = ((ypos + 1) * TDIST) - 480;
				edit_win->set_offset(edit_offset);
				edit_scr->set_ypos(edit_offset);
			}
			if(ypos * TDIST < edit_offset){
				edit_offset = ypos * TDIST;
				edit_win->set_offset(edit_offset);
				edit_scr->set_ypos(edit_offset);
			}
		}
	);
	edit_scr=new VScrollbar(top_win,Style(0,0,5), Rect(490, 20, 10, 480), 1, 
		[](VScrollbar *sb) { 
			edit_offset = sb->value;
			edit_win->set_offset(edit_offset); 
		}  
	);
	get_events();
	return 0;
}