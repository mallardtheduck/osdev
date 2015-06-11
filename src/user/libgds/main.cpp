#include <iostream>
#include <gds/libgds.h>

using namespace std;

int main(){
    cout << "GDS Test Program" << endl;
	bt_vidmode vidmode;
	vidmode.width = 640; vidmode.height = 480; vidmode.bpp = 4;
	GDS_SetScreenMode(vidmode);
	GDS_SelectScreen();
	uint32_t green = GDS_GetColour(0, 255, 0);
	gds_DrawingOp op;
	op.type = gds_DrawingOpType::Dot;
	op.Dot.x = 100; op.Dot.y = 100;
	op.Common.lineStyle = gds_LineStyle::Default;
	op.Common.lineColour.type = gds_ColourType::Indexed;
	op.Common.lineColour.indexedColour = green;
	GDS_AddDrawingOp(op);
	GDS_UpdateScreen(0, 0, 0, 0);
	while(true);
    return 0;
}