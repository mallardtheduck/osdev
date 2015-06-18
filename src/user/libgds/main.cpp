#include <iostream>
#include <gds/libgds.h>
#include <sstream>
#include <btos_stubs.h>
#include <cstdio>

using namespace std;

int main() {
	cout << "GDS Test Program" << endl;
	bt_vidmode vidmode;
	vidmode.width = 640;
	vidmode.height = 480;
	vidmode.bpp = 4;
	GDS_SetScreenMode(vidmode);
	GDS_SelectScreen();
	uint32_t green = GDS_GetColour(0, 255, 0);
	uint32_t red = GDS_GetColour(255, 0, 0);
	uint32_t blue = GDS_GetColour(0, 0, 255);
	uint32_t black = GDS_GetColour(0, 0, 0);
	GDS_Ellipse(300, 300, 100, 100, green, blue, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_UpdateScreen();
	uint32_t cursor = GDS_NewSurface(gds_SurfaceType::Bitmap, 20, 20);
	uint32_t cur_white = GDS_GetColour(255, 255, 255);
	GDS_Ellipse(10, 10, 20, 20, cur_white, cur_white, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_SetCursor(cursor, 10, 10);
	GDS_CursorVisibility(true);
	GDS_SelectScreen();
	for(uint32_t i = 0; i < 16; ++i) {
		GDS_Box(100, 100, 100, 100, red, i, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		GDS_UpdateScreen(99, 99, 101, 101);
		getchar();
	}
	GDS_Box(0, 0, 640, 480, black, black, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	GDS_UpdateScreen();
	uint32_t lastx = 0, lasty = 0;
	uint32_t size = 20;
	while(true) {
		for(uint32_t ypos = 0; ypos < 480; ypos+=size) {
			for(uint32_t xpos = 0; xpos < 640; xpos+=size) {
				GDS_Box(lastx, lasty, size, size, black, black, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				GDS_Box(xpos, ypos, size, size, blue, green, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
				GDS_UpdateScreen(xpos, ypos, size, size);
				GDS_UpdateScreen(lastx, lasty, size, size);
				lastx = xpos;
				lasty = ypos;
			}
		}
		char x = getchar();
		if(x == 'q') break;
	}
	return 0;
}
