#include <stdio.h>
#include <btos_stubs.h>
#include <video_dev.h>
#include <crt_support.h>
#include <terminal.h>
#include <stdlib.h>
#include <ioctl.h>
#include <drivers.h>

#include "../../../other/art/BTOS-bootscreen-mono.xbm"

bt_terminal_pointer_bitmap pointer_bmp_8bpp={
    .w=11,
    .h=11,
    .bpp=8,
    .transparent=0,
    .spot_x=5,
    .spot_y=5,
    .datasize=(11*11),
    .data = {
        0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x10, 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x10, 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x10, 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x10, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x10,
        0x10, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x10,
        0x00, 0x00, 0x00, 0x00, 0x10, 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x10, 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x10, 0x0F, 0x10, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
    }
};

bt_terminal_pointer_bitmap pointer_bmp_4bpp={
        .w=11,
        .h=11,
        .bpp=4,
        .transparent=0xE,
        .spot_x=5,
        .spot_y=5,
        .datasize=((11*11)/2) + 1,
        .data = {
            0xEE, 0xEE, 0x00, 0x0E, 0xEE, 0xEE,
            0xEE, 0xE0, 0xF0, 0xEE, 0xEE,
            0xEE, 0xEE, 0x0F, 0x0E, 0xEE, 0xEE,
            0xEE, 0xE0, 0xF0, 0xEE, 0xEE,
            0x00, 0x00, 0x0F, 0x00, 0x00, 0x00,
            0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
            0x00, 0x00, 0x0F, 0x00, 0x00, 0x0E,
            0xEE, 0xE0, 0xF0, 0xEE, 0xEE,
            0xEE, 0xEE, 0x0F, 0x0E, 0xEE, 0xEE,
            0xEE, 0xE0, 0xF0, 0xEE, 0xEE,
            0xEE, 0xEE, 0x00, 0x0E, 0xEE, 0xEE
        }
};

bt_filehandle open_device(){
    bt_filehandle stdout_fh=btos_get_handle(fileno(stdout));
    int devtype= bt_fioctl(stdout_fh, bt_ioctl_DevType, 0, NULL);
    if(devtype!=TERMINAL){
        printf("Output device is not a terminal.\n");
        return 0;
    }
    char stdout_path[BT_MAX_PATH]={0};
    bt_getenv("STDOUT", stdout_path, BT_MAX_PATH);
    bt_filehandle dev_fh=bt_fopen(stdout_path, FS_Read | FS_Write);
    bt_terminal_mode terminal_mode=bt_terminal_mode_Video;
    bt_fioctl(dev_fh, bt_terminal_ioctl_SetMode, sizeof(terminal_mode), (char*)&terminal_mode);
    return dev_fh;
}

void load_btos_bootscreen(uint8_t *buffer){
    for(size_t pixpos=0; pixpos<(640*480); ++pixpos){
        size_t byte=pixpos >> 3;
        size_t bit=pixpos & 7;
        size_t bufpos=pixpos/2;
        uint8_t imask=1 << bit;
        bool value=!(BTOS_bootscreen_mono_bits[byte] & imask);
        if(pixpos % 2){
            if(value) {
                buffer[bufpos] |= 0x0F;
            }else{
                buffer[bufpos] &= 0xF0;
            }
        }else{
            if(value) {
                buffer[bufpos] |= 0xF0;
            }else{
                buffer[bufpos] &= 0x0F;
            }
        }
    }
}

int main(){
    bt_filehandle fh=open_device();
    if(!fh) return -1;
    bt_vidmode original_mode;
    bt_fioctl(fh, bt_vid_ioctl_QueryMode, sizeof(original_mode), (char*)&original_mode);
    size_t modecount=bt_fioctl(fh, bt_vid_ioctl_GetModeCount, 0, NULL);
    bt_vidmode mode;
    for(size_t i=0; i<modecount; ++i) {
        mode.id = i;
        bt_fioctl(fh, bt_vid_ioctl_GetMode, sizeof(mode), (char *) &mode);
        if (!mode.textmode) {
            bt_fioctl(fh, bt_vid_ioctl_SetMode, sizeof(mode), (char *) &mode);
            bt_fseek(fh, 0, false);
            size_t buffersize = (mode.width * mode.height);
            if (mode.bpp == 4) buffersize /= 2;
            for (size_t i = 0; i < buffersize; ++i) {
                uint32_t y=i/mode.width;
                if(mode.bpp==4) y/=2;
                uint8_t col = y % (1 << mode.bpp);
                if(mode.bpp==4) col |= col << 4;
                bt_fwrite(fh, 1, (char *) &col);
            }
            getchar();
        }
    }
    for(size_t i=0; i<modecount; ++i) {
        mode.id = i;
        bt_fioctl(fh, bt_vid_ioctl_GetMode, sizeof(mode), (char *) &mode);
        if (!mode.textmode) {
            bt_fioctl(fh, bt_vid_ioctl_SetMode, sizeof(mode), (char *) &mode);
            bt_fseek(fh, 0, false);
            size_t buffersize = (mode.width * mode.height);
            if (mode.bpp == 4) buffersize /= 2;
            uint8_t *buffer=malloc(buffersize);
            if(!buffer){
                bt_fioctl(fh, bt_vid_ioctl_SetMode, sizeof(original_mode), (char*)&original_mode);
                printf("Could not allocate buffer for memory-mapping!\n");
                return 0;
            }
            bt_handle m= bt_mmap(fh, 0, (char*)buffer, buffersize);
            for (size_t i = 0; i < buffersize; ++i) {
                uint32_t y=i/mode.width;
                if(mode.bpp==4) y/=2;
                uint8_t col = y % (1 << mode.bpp);
                if(mode.bpp==4) col |= col << 4;
                buffer[i]=col;
            }
            bt_fflush(fh);
            getchar();
            if(mode.width==640 && mode.height==480 && mode.bpp==4){
                load_btos_bootscreen(buffer);
                bt_fflush(fh);
                getchar();
            }
            if(mode.bpp == 8){
                bt_fioctl(fh, bt_terminal_ioctl_SetPointerBitmap, sizeof(pointer_bmp_8bpp)+pointer_bmp_8bpp.datasize, (char*)&pointer_bmp_8bpp);
                bt_fioctl(fh, bt_terminal_ioctl_ShowPointer, 0, NULL);
                getchar();
                bt_fioctl(fh, bt_terminal_ioctl_HidePointer, 0, NULL);
            }
            if(mode.bpp == 4){
                bt_fioctl(fh, bt_terminal_ioctl_SetPointerBitmap, sizeof(pointer_bmp_8bpp)+pointer_bmp_4bpp.datasize, (char*)&pointer_bmp_4bpp);
                bt_fioctl(fh, bt_terminal_ioctl_ShowPointer, 0, NULL);
                getchar();
                bt_fioctl(fh, bt_terminal_ioctl_HidePointer, 0, NULL);
            }
            bt_closehandle(m);
            free(buffer);
        }
    }
    bt_fioctl(fh, bt_vid_ioctl_SetMode, sizeof(original_mode), (char*)&original_mode);
    for(size_t i=0; i<256; ++i){
        bt_video_palette_entry entry;
        entry.index=i;
        bt_fioctl(fh, bt_vid_ioctl_GetPaletteEntry, sizeof(entry), (char*)&entry);
        printf("Palette entry %i: (%i, %i, %i)\n", (int)entry.index, entry.r, entry.g, entry.b);
        if(!((i + 1) % (original_mode.height - 1))) getchar();
    }
    return 0;
}