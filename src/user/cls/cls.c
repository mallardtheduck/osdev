#include <stdio.h>
#include <string.h>
#include <btos_stubs.h>
#include <video_dev.h>

bt_handle btos_get_handle(int fd);

int main(){
    bt_filehandle fh=btos_get_handle(fileno(stdout));
    if(!fh){
        char outdev[BT_MAX_PATH]="";
        strcpy(outdev, "DEV:/");
        size_t result=bt_getenv("DISPLAY_DEVICE", outdev+5, BT_MAX_PATH-5);
        if(!result) return -1;
        fh=bt_fopen(outdev, FS_Write);
    }
    bt_fioctl(fh, bt_vid_ioctl_ClearScreen, 0, NULL);
    return 0;
}