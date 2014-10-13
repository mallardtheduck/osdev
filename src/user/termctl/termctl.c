#include <stdio.h>
#include <btos_stubs.h>
#include <terminal.h>
#include <string.h>

int main(int argc, char **argv){
    if(argc < 2){
        printf("Sets the terminal title.\n");
        printf("Usage: %s title\n", argv[0]);
        return 1;
    }
    char path[BT_MAX_PATH]="";
    if(!bt_getenv("STDOUT", path, BT_MAX_PATH)) return -1;
    bt_filehandle fh= bt_fopen(path, FS_Write);
    if(!fh) return -1;
    bt_fioctl(fh, bt_terminal_ioctl_SetTitle, strlen(argv[1]), argv[1]);
    return 0;
}