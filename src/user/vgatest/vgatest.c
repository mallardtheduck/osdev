#include <stdio.h>
#include <btos_stubs.h>
#include <video_dev.h>
#include <crt_support.h>

int main(){
    bt_filehandle fh=btos_get_handle(fileno(stdout));
    if(!fh) return -1;
    bt_vidmode original_mode;
    bt_fioctl(fh, bt_vid_ioctl_QueryMode, sizeof(original_mode), (char*)&original_mode);
    size_t modecount;
    bt_fioctl(fh, bt_vid_ioctl_GetModeCount, sizeof(modecount), (char*)&modecount);
    for(size_t i=0; i<modecount; ++i){
        bt_vidmode mode;
        bt_fioctl(fh, bt_vid_ioctl_GetMode, sizeof(i), (char*)&i);
        if(mode.bpp == 8){
            bt_fioctl(fh, bt_vid_ioctl_SetMode, sizeof(mode), (char*)&mode);
        }
    }
    bt_fioctl(fh, bt_vid_ioctl_SetMode, sizeof(original_mode), (char*)&original_mode);
    return 0;
}