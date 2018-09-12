#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-function"

#include <SDL2_widgets.h>
#include <btos.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <btos/table.hpp>

using std::string;

static TopWin *top_win;
static TextWin *text_win;

void set_icon(SDL_Window* window) {}

static void disp_topw() {
	fill_rect(top_win->render, 0, top_win->bgcol);
}

string formatSize(size_t size){
	std::stringstream ret;
	ret << std::fixed;
	ret.precision(1);
	if(size < 1024){
		ret << size << " bytes";
	}else if (size < 10240){
		ret << (float)size / 1024.0 << " KB";
	}else if(size < 1048576){
		ret << size / 1024 << " KB";
	}else if(size < 10485760){
		ret << (float)size / 1048576.0 << " MB";
	}else{
		ret << size / 1048576 << " MB";	
		
	}
	return ret.str();
}

void update_text(){
	text_win->reset();
	std::ifstream procsfile{"INFO:/PROCS"};
	auto procstbl = parsecsv(procsfile);
	std::stringstream ss;
	for(auto row : procstbl.rows){
		auto size = strtoul(row["memory"].c_str(), nullptr, 10);
		auto sizeFmt = formatSize(size);
		ss <<  row["PID"] << ": " << row["path"] << " (" << sizeFmt << ")";
		text_win->add_text(ss.str().c_str(), true);
		ss.str("");
	}
}

int main(){
	top_win = new TopWin("ProtoTask", Rect(100, 100, 500, 400), 0, SDL_WINDOW_RESIZABLE, true, disp_topw, set_icon);
	text_win = new TextWin(top_win, Style(0, 0 ,5), Rect(0, 0, 350, 400), 1024, nullptr);
	update_text();
	get_events();
	return 0;
}