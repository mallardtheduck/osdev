#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-function"

#include <SDL2_widgets.h>
#include <btos.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

static TopWin *top_win;
static EditWin *edit_win;
static VScrollbar *edit_scr;
static Button *open_btn;
static Button *save_btn;
static TextWin *file_txt;

static BgrWin *save_dlg;
static TextWin *save_folder;
static DialogWin *save_file_name;
static Button *save_choose_dir;
static Button *save_ok_btn;
static Button *save_cancel_btn;

static int edit_lines = 0;
static int edit_offset = 0;

static std::string cur_file = "Unsaved file";
static std::string cur_path;

void set_icon(SDL_Window* window) {}

static void disp_topw() {
	//fill_rect(top_win->render, 0, top_win->bgcol);
}

static void update_scrollbar(){
	int lines = 0;
	int ypos = 0;
	edit_win->get_info(nullptr, &lines, &ypos, nullptr, nullptr);
	if(ypos < 0) ypos = 0;
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

static void open_file(const char *path){
	std::ifstream file(path);
	if(file.is_open()){
		int lines = 0;
		edit_win->get_info(nullptr, &lines, nullptr, nullptr, nullptr);
		for(int i = 0; i < lines; ++i){
			edit_win->set_line(i, true, "");
		}
		edit_win->reset();
		int cline = 0;
		while(file.good()){
			std::string line;
			std::getline(file, line);
			edit_win->set_line(cline++, true, "%s", line.c_str());
		}
		update_scrollbar();
		cur_file = path;
		char buf[BT_MAX_PATH] = {0};
		cur_path = getcwd(buf, BT_MAX_PATH);
		file_txt->reset();
		file_txt->add_text(path, true);
	}
}

static void init_save_dlg();

static void save_file(){
	save_dlg->show();
	save_dlg->keep_on_top();
	save_dlg->draw_blit_recur();
	top_win->refresh(&save_dlg->tw_area);
	save_folder->reset();
	save_folder->add_text(cur_path.c_str(), true);
	save_file_name->dialog_def(cur_file.c_str(), [](const char *fname,int){
		cur_file = fname;
		std::string fullpath = cur_path + "/" + cur_file;
		std::ofstream file(fullpath);
		if(file.is_open()){
			int lines = 0;
			edit_win->get_info(nullptr, &lines, nullptr, nullptr, nullptr);
			for(int i = 0; i < lines; ++i){
				file << edit_win->get_line(i) << std::endl;
			}
			file_txt->reset();
			file_txt->add_text(cur_file.c_str(), true);
		}else{
			alert("File could not be saved!");
		}
		save_dlg->hide();
	}, 0);
}

static void init_save_dlg(){
	save_dlg = new BgrWin(0, Rect(0, 0, 300, 135), 0, [](BgrWin*){
		//save_dlg->clear();
		fill_rect(save_dlg->render, 0, save_dlg->bgcol);
	}, mwin::down, mwin::move, mwin::up, cBackground);
	save_folder = new TextWin(save_dlg, Style(0, 0, 5), Rect(5, 20, 290, 20), 1, "Folder");
	save_choose_dir = new Button(save_dlg, Style(0, 0, 5), Rect(5, 45, 70, 20), "Browse...", [](Button*){
		working_dir([](const char *dir_name){
			cur_path = dir_name;
			save_folder->reset();
			save_folder->add_text(cur_path.c_str(), true);
		});
	});
	save_file_name = new DialogWin(save_dlg, Rect(5, 70, 290, 25));
	save_file_name->dialog_label("File name");
	save_ok_btn = new Button(save_dlg, Style(0, 0, 5), Rect(5, 110, 50, 20), "OK", [](Button*){
		save_file_name->dok();
	});
	save_cancel_btn = new Button(save_dlg, Style(0, 0, 5), Rect(60, 110, 50, 20), "Cancel", [](Button*){
		save_dlg->hide();
	});
	save_dlg->hide();
}

int main(){
	top_win = new TopWin("ProtoText", Rect(100, 100, 500, 500), 0, SDL_WINDOW_RESIZABLE, true, disp_topw, set_icon);
	edit_win = new EditWin(top_win, Rect(0, 20, 490, 480), nullptr, 
		[](int ctrl_key, int key) {
			update_scrollbar();
		}
	);
	edit_scr=new VScrollbar(top_win,Style(0, 0, 5), Rect(490, 20, 10, 480), 1, 
		[](VScrollbar *sb) { 
			edit_offset = sb->value;
			edit_win->set_offset(edit_offset); 
		}  
	);
	open_btn = new Button(top_win, Style(0, 0, 5), Rect(0, 0, 50, 20), "Open", [](Button*){
		file_chooser([](const char *path) {
			open_file(path);
		});
	});
	save_btn = new Button(top_win, Style(0, 0, 5), Rect(50, 0, 50, 20), "Save", [](Button*){
		save_file();
	});
	file_txt = new TextWin(top_win, Style(0, 0 ,5), Rect(100, 0, 400, 20), 1, nullptr);
	file_txt->bgcol = cBackground;
	file_txt->add_text(cur_file.c_str(), true);
	char buf[BT_MAX_PATH] = {0};
	cur_path = getcwd(buf, BT_MAX_PATH);
	init_save_dlg();
	get_events();
	return 0;
}