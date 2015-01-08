#include <stdio.h>
#include <btos_stubs.h>
#include <video_dev.h>
#include <crt_support.h>
#include <stdlib.h>

int main(){
    bt_filehandle fh=btos_get_handle(fileno(stdout));
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
            bt_closehandle(m);
            free(buffer);
        }
    }
    bt_fioctl(fh, bt_vid_ioctl_SetMode, sizeof(original_mode), (char*)&original_mode);
    return 0;
}