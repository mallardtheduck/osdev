#include <btos.h>
#include <iostream>
#include <gds/libgds.h>
#include <cstdio>
#include <crt_support.h>
#include <sstream>
#include "windows.hpp"
#include "window.hpp"
#include "service.hpp"
#include "drawing.hpp"
#include "metrics.hpp"
#include "config.hpp"

using namespace std;

static void set_env(const string &name, const string &value) {
	bt_setenv(name.c_str(), value.c_str(), 0);
}

void InitCursor(){
	uint32_t cursor = GDS_NewSurface(gds_SurfaceType::Bitmap, 12, 21);
	uint32_t cur_black = GDS_GetColour(0, 0, 0);
	uint32_t cur_transp = GDS_GetColour(0, 0, 0, 255);
	uint32_t cur_white = GDS_GetColour(255, 255, 255);
	gds_Point cur_points[] = {{0, 0}, {0, 13}, {3, 10}, {6, 15}, {8, 15}, {8, 14}, {6, 9}, {10, 9}, {1, 0}};
	GDS_Box(0, 0, 12, 21, cur_transp, cur_transp, 0, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_Polygon(9, cur_points, true, cur_black, cur_white, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_SetCursor(cursor, 1, 1);
	GDS_CursorVisibility(true);
}

/*shared_ptr<Window> CreateTestWin(string title, uint32_t x, uint32_t y, uint32_t w, uint32_t h){
	uint64_t surface = GDS_NewSurface(gds_SurfaceType::Bitmap, w, h);
	GDS_Box(0, 0, w, h, GDS_GetColour(0, 0, 0), GDS_GetColour(255, 255, 255), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_Line(0, 0, w, h, GDS_GetColour(0, 0, 0));
	GDS_Line(0, h, w, 0, GDS_GetColour(0, 0, 0));
	shared_ptr<Window> win(new Window(surface));
	win->SetPosition(Point(x, y));
	win->SetTitle(title);
	AddWindow(win);
	win->SetVisible(true);
	return win;
}*/

int main(int argc, char **argv){
    cout << "BT/OS WM" << endl;
    ParseConfig(ConfigFilePath);
	bt_pid pid = bt_getpid();
	char pid_str[64] = {0};
	snprintf(pid_str, 64, "%i", pid);
	set_env("WM_PID", pid_str);
	if(argc > 1) {
		int s_argc = 0;
		char **s_argv = NULL;
		if(argc > 2) {
			s_argc = argc - 2;
			s_argv = &argv[2];
		}
		char elxpath[BT_MAX_PATH];
		btos_path_parse(argv[1], elxpath, BT_MAX_PATH);
		bt_pid_t root_pid = 0;
		root_pid = bt_spawn(elxpath, s_argc, s_argv);
		if(root_pid) {
			try {
				bt_vidmode vidmode;
				vidmode.width = GetMetric(ScreenWidth);
				vidmode.height = GetMetric(ScreenHeight);
				vidmode.bpp = GetMetric(ScreenBpp);
				InitDrawing();
				GDS_SetScreenMode(vidmode);
				InitWindws();
				InitCursor();
				DrawWindows();
				RefreshScreen();
				/*shared_ptr<Window> win1 = CreateTestWin("Window 1", 50, 50, 200, 100);
				win1->SetZOrder(10);
				shared_ptr<Window> win2 = CreateTestWin("Window 2", 100, 100, 250, 150);
				win2->SetZOrder(20);
				shared_ptr<Window> win3 = CreateTestWin("Window 3", 300, 200, 300, 250);
				win3->SetZOrder(30);*/
				Service(root_pid);
			} catch(exception &e) {
				cout << "Exception: " << e.what() << endl;
				stringstream ss;
				ss << "WM: Exception: " << e.what() << endl;
				bt_zero(ss.str().c_str());
				
			}
		} else {
			cout << "Could not load " << argv[1] << endl;
		}
	} else {
		cout << "Usage: " << argv[0] << " command-line." << endl;
	}
    return 0;
}
