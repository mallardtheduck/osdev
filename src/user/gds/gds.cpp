#include "gds.hpp"
#include "screen.hpp"
#include "drawingop.hpp"

char dbgbuf[128];
#define dbgpf(...) do{snprintf(dbgbuf, 128, __VA_ARGS__); bt_zero(dbgbuf);}while(false)

bt_vidmode original_mode;

struct screen_info{
    bt_vidmode mode;
    bt_filehandle fh;
    bt_handle mapping;
    size_t bufsize;
    uint8_t *buffer;
    uint8_t *backbuffer;
    gdImagePtr image;
};

extern bt_terminal_pointer_bitmap pointer_bmp_4bpp;


bt_filehandle open_device(){
    bt_filehandle stdout_fh=btos_get_handle(fileno(stdout));
    int devtype= bt_fioctl(stdout_fh, bt_ioctl::DevType, 0, NULL);
    if(devtype!=driver_types::TERMINAL){
        printf("Output device is not a terminal.\n");
        return 0;
    }
    char stdout_path[BT_MAX_PATH]={0};
    bt_getenv("STDOUT", stdout_path, BT_MAX_PATH);
    bt_filehandle dev_fh=bt_fopen(stdout_path, FS_Read | FS_Write);
    bt_terminal_mode::Enum terminal_mode=bt_terminal_mode::Video;
    bt_fioctl(dev_fh, bt_terminal_ioctl::SetMode, sizeof(terminal_mode), (char*)&terminal_mode);
    return dev_fh;
}

int main(){
	Screen screen;
	screen.SetMode(640, 480, 4);
    DrawingOp op1;
    op1.type = DrawingOpType::Line;
    op1.Line.x1 = 100;
    op1.Line.y1 = 100;
    op1.Line.x2 = 300;
    op1.Line.y2 = 300;
    op1.Common.lineIndexedColour = 255;
    screen.AddOperation(op1);
	GD::Image *cursor=new GD::Image(10, 10, false);
	int cursor_transparent=cursor->ColorResolve(255, 0, 255, 0);
	cursor->ColorTransparent(cursor_transparent);
	int cursor_white=cursor->ColorResolve(255, 255, 255);
	int cursor_black=cursor->ColorResolve(0, 0, 0, 255);
	cursor->FilledRectangle(0, 0, 9, 9, cursor_transparent);
	cursor->Line(0, 0, 9, 9, cursor_white);
	cursor->Line(0, 9, 9, 0, cursor_white);
	cursor->Line(5, 0, 5, 9, cursor_black);
	cursor->Line(0, 5, 9, 5, cursor_black);
	screen.SetCursorImage(*cursor, 5, 5);
	screen.ShowCursor();
	delete cursor;
	GD::Image *imageobj=screen.GetImage();
	gdImagePtr im;
	if(imageobj) im=const_cast<gdImagePtr>(imageobj->GetPtr());
	else return 0;
    int bg= gdImageColorClosest(im, 0, 0, 0);
    (void)bg;
    int fg1= gdImageColorClosest(im, 255, 255, 255);
    int fg2= gdImageColorClosest(im, 0, 255, 255);
    int fg3= gdImageColorClosest(im, 0, 255, 0);
    int fg4= gdImageColorClosest(im, 255, 0, 0);
    gdImageFilledRectangle(im, 0, 0, 639, 479, fg4);
    for(int i=0; i<640; ++i) {
        if(i) gdImageLine(im, i-1, 0, 640-i, 479, fg3);
        gdImageLine(im, i, 0, 639-i, 479, fg1);
    }
    gdImageLine(im, 0, 0, 639, 479, fg1);
    gdImageLine(im, 639, 0, 0, 479, fg1);
    gdImageFilledEllipse(im, 320, 240, 50, 50, fg2);
    gdFontPtr font=gdFontGetSmall();
    gdImageString(im, font, 297, 232, (u_char *)"GDS TEST", bg);
    screen.UpdateScreen();
	getchar();
    gdImageFilledRectangle(im, 0, 0, 639, 479, bg);
	screen.UpdateScreen();
    int bcol= gdImageColorClosest(im, 0, 0, 255);
    int xpos=0; int ypos=0;
    int xmov=5; int ymov=5;
    int lxps=0; int lyps=0;
    const int size=30;
    for(int i=0; i<10000; ++i){
        gdImageFilledRectangle(im, xpos, ypos, xpos+size, ypos+size, bcol);
        gdImageFilledEllipse(im, xpos+(size/2), ypos+(size/2), size/3, size/3, fg3);
		screen.UpdateScreen(lxps>0?lxps:0, lyps>0?lyps:0, size, size);
		screen.UpdateScreen(xpos>0?xpos:0, ypos>0?ypos:0, size, size);
        (void)lyps; (void)lxps;
        gdImageFilledRectangle(im, xpos, ypos, xpos+size, ypos+size, bg);
        lxps=xpos;
        lyps=ypos;
        xpos+=xmov;
        ypos+=ymov;
        if(xpos < 0 || xpos > 640-size) xmov*=-1;
        if(ypos < 0 || ypos > 480-size) ymov*=-1;
    }
    return 0;
}