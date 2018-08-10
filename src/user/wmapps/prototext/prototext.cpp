#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-function"

#include <SDL2_widgets.h>
#include <btos.h>
#include <iostream>
#include <fstream>

static TopWin *top_win;
static EditWin *edit_win;
static VScrollbar *edit_scr;
static Button *open_btn;
static Button *save_btn;
static TextWin *file_txt;

static int edit_lines = 0;
static int edit_offset = 0;

static std::string cur_file;

void set_icon(SDL_Window* window) {}

static void disp_topw() {
	//fill_rect(top_win->render, 0, top_win->bgcol);
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
	edit_scr=new VScrollbar(top_win,Style(0, 0, 5), Rect(490, 20, 10, 480), 1, 
		[](VScrollbar *sb) { 
			edit_offset = sb->value;
			edit_win->set_offset(edit_offset); 
		}  
	);
	open_btn = new Button(top_win, Style(0, 0, 5), Rect(0, 0, 50, 20), "Open", [](Button*){
		file_chooser([](const char* path) {
			std::ifstream file(path);
			if(file.is_open()){
				edit_win->reset();
				int cline = 0;
				while(file.good()){
					std::string line;
					std::getline(file, line);
					edit_win->set_line(cline++, true, "%s", line.c_str());
				}
				edit_win->draw();
				cur_file = path;
				file_txt->reset();
				file_txt->add_text(path, true);
			}
		});
	});
	save_btn = new Button(top_win, Style(0, 0, 5), Rect(50, 0, 50, 20), "Save", [](Button*){});
	file_txt = new TextWin(top_win, Style(0, 0 ,5), Rect(100, 0, 400, 20), 1, nullptr);
	file_txt->bgcol = cBackground;
	file_txt->add_text("Unsaved file", true);
	get_events();
	return 0;
}