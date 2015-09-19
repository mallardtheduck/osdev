#include <iostream>
#include <gds/libgds.h>
#include <cstdio>
#include "window.hpp"

using namespace std;

int main(){
    cout << "BT/OS WM" << endl;
	bt_vidmode vidmode;
	vidmode.width = 640;
	vidmode.height = 480;
	vidmode.bpp = 4;
	GDS_SetScreenMode(vidmode);
	GDS_SelectScreen();
	uint64_t surface = GDS_NewSurface(gds_SurfaceType::Bitmap, 200, 100);
	Window win(surface);
	win.Draw();
	GDS_UpdateScreen();
	getchar();
    return 0;
}