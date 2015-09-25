#include <stdio.h>
#include <btos_stubs.h>
#include <terminal.h>
#include <video_dev.h>
#include <string.h>
#include <stdbool.h>

bt_handle btos_get_handle(int fd);
bool btos_path_parse(const char *opath, char *buffer, size_t size);

int main(int argc, char **argv){
    if(argc < 2 && argv[1]){
        printf("Change terminal configuration.\n");
        printf("Usage: %s command [params...]\n", argv[0]);
        return 1;
    }
    bt_filehandle fh=btos_get_handle(fileno(stdout));
    if(!fh) return -1;
    if(strcmp(argv[1], "title")==0) {
        bt_fioctl(fh, bt_terminal_ioctl_SetTitle, strlen(argv[2]), argv[2]);
    }else if(strcmp(argv[1], "echo")==0 && argc == 3) {
        if(strcmp(argv[2], "on")==0) {
            bool val = true;
            bt_fioctl(fh, bt_terminal_ioctl_SetEcho, 1, (char*)&val);
        }else if(strcmp(argv[2], "off")==0){
            bool val = false;
            bt_fioctl(fh, bt_terminal_ioctl_SetEcho, 1, (char*)&val);
        }else return 1;
    }else if(strcmp(argv[1], "clear")==0) {
        bt_fioctl(fh, bt_vid_ioctl_ClearScreen, 0, NULL);
    }else if(strcmp(argv[1], "new")==0){
        char runpath[BT_MAX_PATH]="";
        if(argc < 3){
            bt_getenv("SHELL", runpath, BT_MAX_PATH);
        }else{
            btos_path_parse(argv[2], runpath, BT_MAX_PATH);
        }
        bt_fioctl(fh, bt_terminal_ioctl_NewTerminal, BT_MAX_PATH, runpath);
    }else if(strcmp(argv[1], "switch")==0  && argc == 3){
        uint64_t id=0;
        sscanf(argv[2], "%i", (int*)&id);
        bt_fioctl(fh, bt_terminal_ioctl_SwtichTerminal, sizeof(id), (char*)&id);
    }else if(strcmp(argv[1], "pointer")==0 && argc == 3){
        if(strcmp(argv[2], "on")==0){
            bt_fioctl(fh, bt_terminal_ioctl_ShowPointer, 0, NULL);
        }else if(strcmp(argv[2], "off")==0){
            bt_fioctl(fh, bt_terminal_ioctl_HidePointer, 0, NULL);
        }
    }else if(strcmp(argv[1], "pointer")==0 && argc == 2){
        bt_terminal_pointer_info info;
        bt_fioctl(fh, bt_terminal_ioctl_GetPointerInfo, sizeof(info), (char*)&info);
        printf("Pointer: (%i, %i) Flags: %x\n", info.x, info.y, info.flags);
    }else if(strcmp(argv[1], "event")==0) {
        
    }else if(strcmp(argv[1], "modes")==0){
        size_t modecount= bt_fioctl(fh, bt_vid_ioctl_GetModeCount, 0, NULL);
        for(size_t i=0; i<modecount; ++i){
            bt_vidmode mode;
            mode.id=i;
            bt_fioctl(fh, bt_vid_ioctl_GetMode, sizeof(mode), (char*)&mode);
            printf("Mode %i: ID: %i %ix%i %ibpp %s.\n", (int)i, mode.id, mode.width, mode.height, mode.bpp, mode.textmode?"text":"graphics");
        }
    }else if(strcmp(argv[1], "reset")==0){
        size_t modecount= bt_fioctl(fh, bt_vid_ioctl_GetModeCount, 0, NULL);
        for(size_t i=0; i<modecount; ++i) {
            bt_vidmode mode;
            mode.id=i;
            bt_fioctl(fh, bt_vid_ioctl_GetMode, sizeof(mode), (char*)&mode);
            if(mode.textmode){
                bt_fioctl(fh, bt_vid_ioctl_SetMode, sizeof(mode), (char*)&mode);
                break;
            }
        }
    }else{
        printf("Unknown option '%s'\n", argv[1]);
    }
    return 0;
}