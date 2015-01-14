#include <stdio.h>
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

char dbgbuf[128];
#define dbgpf(...) do{snprintf(dbgbuf, 128, __VA_ARGS__); bt_zero(dbgbuf);}while(false)

bt_vidmode original_mode;

struct screen_info{
    bt_vidmode mode;
    bt_filehandle fh;
    bt_handle mapping;
    uint8_t *buffer;
};

bt_filehandle open_device(){
    bt_filehandle stdout_fh=btos_get_handle(fileno(stdout));
    int devtype= bt_fioctl(stdout_fh, bt_ioctl::DevType, 0, NULL);
    if(devtype!=driver_types::TERMINAL){
        printf("Output device is not a terminal.\n");
        return 0;
    }
    char stdout_path[BT_MAX_PATH]={0};
    bt_getenv("STDOUT", stdout_path, BT_MAX_PATH);
    bt_filehandle dev_fh=bt_fopen(stdout_path, /*FS_Read |*/ FS_Write);
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
            scr.mode=mode;
            scr.fh=fh;
            scr.mapping=m;
            scr.buffer=buffer;
            return true;
        }
    }
    return false;
}

void screen_putpixel(uint32_t x, uint32_t y, uint32_t col, screen_info screen){
    if(x > screen.mode.width || y > screen.mode.height) return;
    size_t pixelpos=(y * screen.mode.width) + x;
    if(screen.mode.bpp == 8){
        screen.buffer[pixelpos]=(uint8_t)col;
    }else if(screen.mode.bpp==4){
        uint8_t c=(uint8_t)col;
        size_t bufpos=pixelpos/2;
        if(pixelpos % 2){
            screen.buffer[bufpos] = (uint8_t)((screen.buffer[bufpos] & 0xF0) | (0x0F & c));
        }else{
            screen.buffer[bufpos] = (uint8_t)((screen.buffer[bufpos] & 0x0F) | (0xF0 & (c << 4)));
        }
    }
}

void write_to_screen(gdImagePtr image, screen_info screen){
    for(int x=0; x<image->sx; ++x){
        for(int y=0; y<image->sy; ++y){
            int pix= gdImageGetPixel(image, x, y);
            screen_putpixel(x, y, pix, screen);
        }
    }
    bt_fflush(screen.fh);
}

int main(){
    bt_filehandle fh= open_device();
    screen_info screen;
    if(!graphics_mode(fh, 640, 480, 4, screen)){
        printf("Failed to set screen mode.\n");
        exit(-1);
    };
    gdImagePtr im=gdImageCreate(320,240);
    int bg=gdImageColorAllocate(im, 0, 0, 0);
    (void)bg;
    int fg1= gdImageColorAllocate(im, 255, 255, 255);
    int fg2= gdImageColorAllocate(im, 0, 255, 255);
    int fg3= gdImageColorAllocate(im, 255, 0, 255);
    int fg4= gdImageColorAllocate(im, 0, 255, 0);
    gdImageFilledRectangle(im, 0, 0, 319, 239, fg4);
    for(int i=0; i<320; ++i) {
        if(i) gdImageLine(im, i-1, 0, 320-i, 239, fg3);
        gdImageLine(im, i, 0, 319-i, 239, fg1);
        write_to_screen(im, screen);
    }
    getchar();
    gdImageLine(im, 0, 0, 319, 239, fg1);
    gdImageLine(im, 319, 0, 0, 239, fg1);
    gdImageFilledEllipse(im, 160, 120, 20, 20, fg2);
    write_to_screen(im, screen);
    bt_fflush(screen.fh);
    getchar();
    bt_fioctl(fh, bt_vid_ioctl::SetMode, sizeof(original_mode), (char *) &original_mode);
    return 0;
}