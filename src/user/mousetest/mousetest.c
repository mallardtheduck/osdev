#include <stdio.h>
#include <mouse.h>
#include <btos_stubs.h>

int main(){
    bt_filehandle fh= bt_fopen("DEV:/MOUSE0", FS_Read);
    bt_fioctl(fh, bt_mouse_ioctl_ClearBuffer, 0, NULL);
    while(1){
        bt_mouse_packet packet;
        bt_fread(fh, sizeof(bt_mouse_packet), (char*)&packet);
        printf("Flags: %x, X: %i, Y: %i\n", packet.flags, packet.x_motion, packet.y_motion);
    }
    return 0;
}