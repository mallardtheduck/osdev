#include <gd.h>
#include <btos_stubs.h>
#include <video_dev.h>
#include <crt_support.h>
#include <ioctl.h>
#include <drivers.h>
#include <terminal.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <gdfonts.h>

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

bool graphics_mode(bt_filehandle fh, uint32_t w, uint32_t h, uint8_t bpp, screen_info &scr){
    bt_fioctl(fh, bt_vid_ioctl::QueryMode, sizeof(original_mode), (char*)&original_mode);
    size_t modecount=bt_fioctl(fh, bt_vid_ioctl::GetModeCount, 0, NULL);
    bt_vidmode mode;
    for(size_t i=0; i<modecount; ++i) {
        mode.id=i;
        bt_fioctl(fh, bt_vid_ioctl::GetMode, sizeof(mode), (char *) &mode);
        if(!mode.textmode && mode.width==w && mode.height==h && mode.bpp==bpp){
            bt_fioctl(fh, bt_vid_ioctl::SetMode, sizeof(mode), (char *) &mode);
            bt_fseek(fh, 0, false);
            size_t buffersize = (mode.width * mode.height);
            if (mode.bpp == 4) buffersize /= 2;
            uint8_t *buffer=new uint8_t[buffersize]();
            memset(buffer, 0, buffersize);
            bt_handle m=bt_mmap(fh, 0, (char*)buffer, buffersize);
            uint8_t *backbuffer=new uint8_t[buffersize]();
            memset(backbuffer, 0, buffersize);
            scr.mode=mode;
            scr.fh=fh;
            scr.mapping=m;
            scr.buffer=buffer;
            scr.backbuffer=backbuffer;
            scr.bufsize=buffersize;
            scr.image=gdImageCreate(mode.width, mode.height);
            for(size_t p=0; p<256; ++p){
                size_t idx=(p % (1 << mode.bpp));
                bt_video_palette_entry entry;
                entry.index=idx;
                bt_fioctl(fh, bt_vid_ioctl::GetPaletteEntry, sizeof(entry), (char*)&entry);
                int c=gdImageColorAllocate(scr.image, entry.r, entry.g, entry.b);
                dbgpf("GDS: Colour %i: (%i, %i, %i) [%i]\n", c, entry.r, entry.g, entry.b, (int)idx);
            }
            return true;
        }
    }
    return false;
}

void screen_putpixel(uint32_t x, uint32_t y, uint32_t col, screen_info screen, bool backbuffer=false){
    if(x > screen.mode.width || y > screen.mode.height) return;
    uint8_t *buffer=screen.buffer;
    if(backbuffer) buffer=screen.backbuffer;
    if(!buffer) return;
    size_t pixelpos=(y * screen.mode.width) + x;
    if(screen.mode.bpp == 8){
        buffer[pixelpos]=(uint8_t)col;
    }else if(screen.mode.bpp==4){
        uint8_t c=(uint8_t)col;
        size_t bufpos=pixelpos/2;
        if(pixelpos % 2){
            buffer[bufpos] = (uint8_t)((buffer[bufpos] & 0xF0) | (0x0F & c));
        }else{
            buffer[bufpos] = (uint8_t)((buffer[bufpos] & 0x0F) | (0xF0 & (c << 4)));
        }
    }
}

uint8_t screen_getpixel(uint32_t x, uint32_t y, screen_info screen, bool backbuffer=false){
    if(x > screen.mode.width || y > screen.mode.height) return 0;
    uint8_t *buffer=screen.buffer;
    if(backbuffer) buffer=screen.backbuffer;
    if(!buffer) return 0;
    size_t pixelpos=(y * screen.mode.width) + x;
    if(screen.mode.bpp == 8){
        return buffer[pixelpos];
    }else if(screen.mode.bpp==4){
        uint8_t c=0;
        size_t bufpos=pixelpos/2;
        if(pixelpos % 2){
            c = (uint8_t)(buffer[bufpos] & 0x0F);
        }else{
            c = (uint8_t)((buffer[bufpos] >> 4) & 0x0F);
        }
        return c;
    }
    return 0;
}

void write_to_screen(gdImagePtr image, uint32_t xpos, uint32_t ypos, screen_info screen){
    for(int x=0; x<image->sx; ++x){
        for(int y=0; y<image->sy; ++y){
            int pix= gdImageGetPixel(image, x, y);
            if(screen_getpixel(x+xpos, y+ypos, screen, true) != pix) {
                screen_putpixel(x + xpos, y + ypos, pix, screen);
                screen_putpixel(x + xpos, y + ypos, pix, screen, true);
            }
        }
    }
    bt_fflush(screen.fh);
}

void exp_write_screen(gdImagePtr image, int dx, int dy, int dw, int dh, screen_info screen){
    bt_fioctl(screen.fh, bt_terminal_ioctl::HidePointer, 0, NULL);
    const size_t max_run=1024;
    uint8_t runbuf[max_run];
    size_t cur_run=0;
    size_t run_start=0;
    for(size_t i=0; i<screen.bufsize; ++i){
        size_t pixidx=i*2;
        int y=(int)(pixidx/screen.mode.width);
        int x=(int)(pixidx-(y*screen.mode.width));
        if(x+1 < dx || x > dx+dw || y < dy || y > dy+dh) continue;
        uint8_t lpxl=(uint8_t) gdImageGetPixel(image, x, y);
        uint8_t hpxl=(uint8_t) gdImageGetPixel(image, x+1, y);
        uint8_t slpx=screen_getpixel(x, y, screen, true);
        uint8_t shpx=screen_getpixel(x+1, y, screen, true);
        if(hpxl != shpx || lpxl != slpx) {
            uint8_t value=(uint8_t)((hpxl & 0x0F) | ((lpxl << 4) & 0xF0));
            if(cur_run+1 > max_run) {
                runbuf[cur_run] = value;
                cur_run++;
                if(!run_start) run_start=i;
            }else{
                bt_fseek(screen.fh, run_start, false);
                bt_fwrite(screen.fh, cur_run, (char*)&runbuf);
                cur_run=0;
                run_start=i;
                runbuf[cur_run] = value;
                cur_run++;
            }
            screen_putpixel(x, y, lpxl, screen, true);
            screen_putpixel(x+1, y, hpxl, screen, true);
        }else if(cur_run){
            bt_fseek(screen.fh, run_start, false);
            bt_fwrite(screen.fh, cur_run, (char*)&runbuf);
            cur_run=0;
            run_start=0;
        }
    }
    if(cur_run){
        bt_fseek(screen.fh, run_start, false);
        bt_fwrite(screen.fh, cur_run, (char*)&runbuf);
    }
    bt_fioctl(screen.fh, bt_terminal_ioctl::ShowPointer, 0, NULL);
}

int main(){
    bt_filehandle fh= open_device();
    screen_info screen;
    if(!graphics_mode(fh, 640, 480, 4, screen)){
        printf("Failed to set screen mode.\n");
        exit(-1);
    };
    bt_fioctl(fh, bt_terminal_ioctl::SetPointerBitmap, sizeof(pointer_bmp_4bpp)+pointer_bmp_4bpp.datasize, (char*)&pointer_bmp_4bpp);
    bt_fioctl(fh, bt_terminal_ioctl::ShowPointer, 0, NULL);
    gdImagePtr im=screen.image;
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
    write_to_screen(im, 0, 0, screen);
    getchar();
    gdImageFilledRectangle(im, 0, 0, 639, 479, bg);
    write_to_screen(im, 0, 0, screen);
    int bcol= gdImageColorClosest(im, 0, 0, 255);
    int xpos=0; int ypos=0;
    int xmov=5; int ymov=5;
    int lxps=0; int lyps=0;
    const int size=30;
    for(int i=0; i<10000; ++i){
        gdImageFilledRectangle(im, xpos, ypos, xpos+size, ypos+size, bcol);
        gdImageFilledEllipse(im, xpos+(size/2), ypos+(size/2), size/3, size/3, fg3);
        //write_to_screen(im, 0, 0, screen);
        exp_write_screen(im, lxps, lyps, size, size, screen);
        exp_write_screen(im, xpos, ypos, size, size, screen);
        (void)lyps; (void)lxps;
        gdImageFilledRectangle(im, xpos, ypos, xpos+size, ypos+size, bg);
        lxps=xpos;
        lyps=ypos;
        xpos+=xmov;
        ypos+=ymov;
        if(xpos < 0 || xpos > 640-size) xmov*=-1;
        if(ypos < 0 || ypos > 480-size) ymov*=-1;
    }
    bt_fioctl(fh, bt_terminal_ioctl::HidePointer, 0, NULL);
    getchar();
    bt_fioctl(fh, bt_vid_ioctl::SetMode, sizeof(original_mode), (char *) &original_mode);
    return 0;
}