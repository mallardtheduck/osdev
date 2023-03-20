#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-function"

#include <SDL2_widgets.h>
#include <btos.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <deque>
#include <map>
#include <btos/table.hpp>
#include <dev/rtc.h>

using std::string;
using namespace btos_api;

static TopWin *top_win;
static TextWin *text_win;
static TextWin *freemem_win;
static TextWin *totalmem_win;
static TextWin *totalcpu_win;

static const size_t graph_samples = 10;
static std::deque<int> mem_samples;
static std::deque<int> cpu_samples;

static size_t draw_count = 0;
static size_t drawn = 0;

struct proc_info{
	bt_pid_t pid;
	string name;
	size_t threads;
	size_t memory;
	int load;
};

std::map<bt_pid_t, proc_info> procs_info;

const int totalcpu = 128;
int usedcpu = 0;
size_t totalmem = 0;
int totalload = 0;

static uint32_t update_delay = 1000;

SDL_Color graph_background = {0, 0, 0, 255};

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
	std::stringstream ss;
	for(auto proc : procs_info){
		auto sizeFmt = formatSize(proc.second.memory);
		int load = (((float)proc.second.load / (float)totalload) * 100.0) * ((float)usedcpu / (float)totalcpu);
		ss << proc.second.pid << ": " << proc.second.name << " (" << sizeFmt << " ";
		ss << proc.second.threads << "T " << load << "%)";
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

void update_totalcpu(){
	totalcpu_win->reset();
	std::stringstream ss;
	int percent = ((float)usedcpu / (float)totalcpu) * 100;
	ss << "CPU usage: " << percent << "%";
	totalcpu_win->add_text(ss.str().c_str(), true);
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
	if(drawn >= draw_count){
		draw_graph(graph, mem_samples, {0, 255, 0, 255});
		top_win->blit_upd(&graph);
	}
}

void update_cpugraph(){
	int percent = ((float)usedcpu / (float)totalcpu) * 100;
	cpu_samples.push_back(percent);
	while(cpu_samples.size() > graph_samples) cpu_samples.pop_front();
	Rect graph = {350, 250, 150, 150};
	if(drawn >= draw_count){
		draw_graph(graph, cpu_samples, {255, 0, 0, 255});
		top_win->blit_upd(&graph);
	}
}

void get_proc_info(){
	std::ifstream procsfile{"INFO:/PROCS"};
	auto procstbl = parsecsv(procsfile);
	procs_info.clear();
	for(auto proc : procstbl.rows){
		proc_info info;
		info.pid = strtoul(proc["PID"].c_str(), nullptr, 10);
		info.name = proc["path"];
		info.memory = strtoul(proc["memory"].c_str(), nullptr, 10);
		info.threads = 0;
		info.load = 0;
		procs_info[info.pid] = info;
	}
	
	totalload = 0;
	usedcpu = 0;
	std::ifstream threadsfile{"INFO:/THREADS"};
	auto threadstbl = parsecsv(threadsfile);
	for(auto thread : threadstbl.rows){
		auto load = strtol(thread["load"].c_str(), nullptr, 10);
		if(thread["name"] != "IDLE"){
			auto pid = strtoul(thread["PID"].c_str(), nullptr, 10);
			totalload += load;
			auto proc = procs_info.find(pid);
			if(proc != procs_info.end()){
				proc->second.load += load;
				++proc->second.threads;
			}
		}else{
			usedcpu = totalcpu - load;
		}
	}
}

int thread_fun(void *arg){
	while(true){
		SDL_Delay(update_delay);
		send_uev([](int) {
			++drawn;
			get_proc_info();
			update_cpugraph();
			update_memgraph();
			update_freemem();
			update_totalcpu();
			if(drawn >= draw_count) update_text();
		}, 0);
		++draw_count;
		if(draw_count == 0) drawn = 0;
	}
	return 0;
}

int main(){
	top_win = new TopWin("ProtoTask", Rect(100, 100, 500, 400), 0, SDL_WINDOW_RESIZABLE, true, disp_topw, set_icon);
	text_win = new TextWin(top_win, Style(0, 0 ,5), Rect(0, 0, 350, 400), 128, nullptr);
	totalmem_win = new TextWin(top_win, Style(0, 0 ,5), Rect(350, 0, 150, 20), 1, nullptr);
	totalmem_win->bgcol = cBackground;
	freemem_win = new TextWin(top_win, Style(0, 0 ,5), Rect(350, 20, 150, 20), 1, nullptr);
	freemem_win->bgcol = cBackground;
	totalcpu_win = new TextWin(top_win, Style(0, 0 ,5), Rect(350, 40, 150, 20), 1, nullptr);
	totalcpu_win->bgcol = cBackground;
	auto start = bt_rtc_millis();
	get_proc_info();
	update_cpugraph();
	update_memgraph();
	update_text();
	update_totalmem();
	update_freemem();
	update_totalcpu();
	auto end = bt_rtc_millis();
	auto diff =  end - start;
	if(diff > (update_delay / 2)){
		update_delay = ceil((double)diff / 1000.0) * 2000;
	}
	SDL_CreateThread(thread_fun, "thread_fun", 0);
	get_events();
	return 0;
}