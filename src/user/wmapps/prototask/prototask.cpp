#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-function"

#include <SDL2_widgets.h>
#include <btos.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <deque>
#include <btos/table.hpp>
#include <dev/rtc.h>

using std::string;

static TopWin *top_win;
static TextWin *text_win;
static TextWin *freemem_win;
static TextWin *totalmem_win;

static const size_t graph_samples = 10;
static std::deque<int> mem_samples;
static std::deque<int> cpu_samples;

static uint32_t update_delay = 1000;

SDL_Color graph_background = {0, 0, 0, 255};

size_t totalmem = 0;

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
		ret << (float)size / 1024.0 << "KB";
	}else if(size < 1048576){
		ret << size / 1024 << "KB";
	}else if(size < 10485760){
		ret << (float)size / 1048576.0 << "MB";
	}else if(size < 1073741824){
		ret << size / 1048576 << "MB";
	}else{
		ret << (float)size / 1073741824.0 << "GB";
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
		text_win->add_text(ss.str().c_str(), false);
		ss.str("");
	}
	text_win->draw_blit_upd();
}

size_t get_freemem(){
	std::ifstream memfile{"INFO:/FREEMEM"};
	string line;
	std::getline(memfile, line);
	return strtoul(line.c_str(), nullptr, 10);
}

void update_freemem(){
	freemem_win->reset();
	auto freemem = get_freemem();
	auto text = "Free memory: " + formatSize(freemem);
	freemem_win->add_text(text.c_str(), true);
}

void update_totalmem(){
	totalmem_win->reset();
	std::ifstream memfile{"INFO:/TOTALMEM"};
	string line;
	std::getline(memfile, line);
	totalmem = strtoul(line.c_str(), nullptr, 10);
	auto text = "Total memory: " + formatSize(totalmem);
	totalmem_win->add_text(text.c_str(), true);
}

void draw_graph(Rect &r, const std::deque<int> &samples, SDL_Color graph_foreground){
	fill_rect(top_win->render, &r, graph_background);
	float scale = (float)r.h / 100.0;
	uint16_t bar_width = r.w / graph_samples;
	for(size_t i = 0; i < graph_samples; ++i){
		uint16_t bar_height = 0;
		if(i < samples.size()) bar_height = samples[i] * scale;
		int16_t bar_left = bar_width * i;
		int16_t bar_top = r.h - (bar_height);
		Rect bar = {(int16_t)(r.x + bar_left), (int16_t)(r.y + bar_top), bar_width, bar_height};
		fill_rect(top_win->render, &bar, graph_foreground);
	}
}

void update_memgraph(){
	auto freemem = get_freemem();
	int percent = 100 - (((float)freemem / (float)totalmem) * 100);
	mem_samples.push_back(percent);
	while(mem_samples.size() > graph_samples) mem_samples.pop_front();
	Rect graph = {350, 95, 150, 150};
	draw_graph(graph, mem_samples, {0, 255, 0, 255});
	top_win->blit_upd(&graph);
}

void update_cpugraph(){
	const int totalcpu = 128;
	int usedcpu = 0;
	std::ifstream threadsfile{"INFO:/THREADS"};
	auto threadstbl = parsecsv(threadsfile);
	std::stringstream ss;
	for(auto row : threadstbl.rows){
		auto load = strtol(row["load"].c_str(), nullptr, 10);
		auto priority = strtol(row["priority"].c_str(), nullptr, 10);
		if(priority < 0){
			usedcpu = totalcpu - load;
			break;
		}
	}
	int percent = ((float)usedcpu / (float)totalcpu) * 100;
	if(percent > 100) percent = 100;
	cpu_samples.push_back(percent);
	while(cpu_samples.size() > graph_samples) cpu_samples.pop_front();
	Rect graph = {350, 250, 150, 150};
	draw_graph(graph, cpu_samples, {255, 0, 0, 255});
	top_win->blit_upd(&graph);
}

int thread_fun(void *arg){
	while(true){
		SDL_Delay(update_delay);
		send_uev([](int) {
			update_cpugraph();
			update_memgraph();
			update_freemem();
			update_text();
		}, 0);
	}
	return 0;
}

int main(){
	top_win = new TopWin("ProtoTask", Rect(100, 100, 500, 400), 0, SDL_WINDOW_RESIZABLE, true, disp_topw, set_icon);
	text_win = new TextWin(top_win, Style(0, 0 ,5), Rect(0, 0, 350, 400), 1024, nullptr);
	totalmem_win = new TextWin(top_win, Style(0, 0 ,5), Rect(350, 0, 150, 20), 1, nullptr);
	totalmem_win->bgcol = cBackground;
	freemem_win = new TextWin(top_win, Style(0, 0 ,5), Rect(350, 20, 150, 20), 1, nullptr);
	freemem_win->bgcol = cBackground;
	auto start = bt_rtc_millis();
	update_cpugraph();
	update_memgraph();
	update_text();
	update_totalmem();
	update_freemem();
	auto end = bt_rtc_millis();
	auto diff =  end - start;
	if(diff > (update_delay / 2)){
		update_delay = ceil((double)diff / 1000.0) * 2000;
	}
	SDL_CreateThread(thread_fun, "thread_fun", 0);
	get_events();
	return 0;
}