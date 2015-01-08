#include <stdio.h>
#include <btos_stubs.h>
#include <video_dev.h>
#include <crt_support.h>

int main(){
    bt_filehandle fh=btos_get_handle(fileno(stdout));
    if(!fh) return -1;
    bt_vidmode original_mode;
    bt_fioctl(fh, bt_vid_ioctl_QueryMode, sizeof(original_mode), (char*)&original_mode);
    size_t modecount=bt_fioctl(fh, bt_vid_ioctl_GetModeCount, 0, NULL);
    bt_vidmode mode;
    for(size_t i=0; i<modecount; ++i){
        mode.id=i;
        bt_fioctl(fh, bt_vid_ioctl_GetMode, sizeof(mode), (char*)&mode);
        if(mode.bpp == 8){
            printf("Mode %i set.\n", (int)i);
            bt_fioctl(fh, bt_vid_ioctl_SetMode, sizeof(mode), (char*)&mode);
            break;
        }
    }
    bt_fseek(fh, 0, false);
    for(size_t x=0; x<mode.width; ++x){
        for(size_t y=0; y<mode.height; ++y){
            uint8_t col=x;
            bt_fwrite(fh, 1, (char*)&col);
        }
    }
    getchar();
    bt_fioctl(fh, bt_vid_ioctl_SetMode, sizeof(original_mode), (char*)&original_mode);
    return 0;
}