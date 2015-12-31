#include <stdio.h>
#include <btos.h>
#include <dev/terminal.h>

bt_handle btos_get_handle(int fd);

int main(){
    bt_filehandle fh=btos_get_handle(fileno(stdout));
    if(fh) bt_fioctl(fh, bt_terminal_ioctl_ClearScreen, 0, NULL);
    return 0;
}