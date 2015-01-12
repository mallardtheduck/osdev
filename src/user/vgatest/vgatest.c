#include <stdio.h>
#include <btos_stubs.h>
#include <video_dev.h>
#include <crt_support.h>
#include <terminal.h>
#include <stdlib.h>
#include <ioctl.h>
#include <drivers.h>

#include "../../../other/art/BTOS-bootscreen-mono.xbm"

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
    return dev_fh;
}

void load_btos_bootscreen(uint8_t *buffer){
    size_t pixpos=0;
    for(size_t x=0; x<640; ++x){
        for(size_t y=0; y<480; ++y){
            size_t byte=pixpos/8;
            size_t bit=7-(pixpos-(byte*8));
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
            pixpos++;
        }
    }
}

int main(){
    bt_filehandle fh=open_device();
    if(!fh) return -1;
    bt_vidmode original_mode;
    bt_fioctl(fh, bt_vid_ioctl_QueryMode, sizeof(original_mode), (char*)&original_mode);
    enum bt_terminal_mode terminal_mode=bt_terminal_mode_Video;
    bt_fioctl(fh, bt_terminal_ioctl_SetMode, sizeof(terminal_mode), (char*)&terminal_mode);
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
            bt_closehandle(m);
            free(buffer);
        }
    }
    bt_fioctl(fh, bt_vid_ioctl_SetMode, sizeof(original_mode), (char*)&original_mode);
    return 0;
}