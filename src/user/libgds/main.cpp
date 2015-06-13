#include <iostream>
#include <gds/libgds.h>
#include <sstream>
#include <btos_stubs.h>
#include <cstdio>

using namespace std;

int main(){
    cout << "GDS Test Program" << endl;
	bt_vidmode vidmode;
	vidmode.width = 640; vidmode.height = 480; vidmode.bpp = 4;
	GDS_SetScreenMode(vidmode);
	GDS_SelectScreen();
	uint32_t green = GDS_GetColour(0, 255, 0);
	uint32_t red = GDS_GetColour(255, 0, 0);
	uint32_t blue = GDS_GetColour(0, 0, 255);
	stringstream ss1;
	ss1 << "GDSTEST: " << green << " , " << red << " , " << blue << endl;
	bt_zero(ss1.str().c_str());
	gds_DrawingOp op;
	op.type = gds_DrawingOpType::Box;
	op.Box.x = 100; op.Box.y = 100;
	op.Box.w = 100; op.Box.h = 100;
	for(uint32_t i = 0; i < 255; ++i){
		op.Common.lineStyle = gds_LineStyle::Default;
		op.Common.lineColour = red;
		op.Common.fillColour = i;
		GDS_AddDrawingOp(op);
		GDS_UpdateScreen(99, 99, 101, 101);
		getchar();
	}
	getchar();
    return 0;
}