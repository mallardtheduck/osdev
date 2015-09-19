#include <iostream>
#include <gds/libgds.h>
#include <cstdio>
#include "window.hpp"

using namespace std;

void InitCursor(){
	uint32_t cursor = GDS_NewSurface(gds_SurfaceType::Bitmap, 12, 21);
	uint32_t cur_black = GDS_GetColour(0, 0, 0);
	uint32_t cur_transp = GDS_GetColour(0, 0, 0, 255);
	uint32_t cur_white = GDS_GetColour(255, 255, 255);
	gds_Point cur_points[] = {{0, 0}, {0, 13}, {3, 10}, {6, 15}, {8, 15}, {8, 14}, {6, 9}, {10, 9}, {1, 0}};
	GDS_Box(0, 0, 11, 20, cur_transp, cur_transp, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_Polygon(9, cur_points, true, cur_black, cur_white, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_SetCursor(cursor, 1, 1);
	GDS_CursorVisibility(true);
}

int main(){
    cout << "BT/OS WM" << endl;
	bt_vidmode vidmode;
	vidmode.width = 640;
	vidmode.height = 480;
	vidmode.bpp = 4;
	GDS_SetScreenMode(vidmode);
	InitCursor();
	GDS_SelectScreen();
	uint64_t surface = GDS_NewSurface(gds_SurfaceType::Bitmap, 400, 250);
	GDS_Box(0, 0, 400, 250, GDS_GetColour(0, 0, 0), GDS_GetColour(255, 255, 255), 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	Window win(surface);
	win.SetPosition(100, 100);
	win.SetTitle("Window 1");
	win.Draw();
	GDS_UpdateScreen();
	getchar();
    return 0;
}