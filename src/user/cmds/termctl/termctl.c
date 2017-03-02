#include <stdio.h>
#include <btos.h>
#include <dev/terminal.h>
#include <dev/video_dev.h>
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
        bt_fioctl(fh, bt_terminal_ioctl_ClearScreen, 0, NULL);
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
		bt_fioctl(fh, bt_terminal_ioctl_StartEventMode, 0, NULL);
		bt_terminal_event_mode emode = bt_terminal_event_mode_Both;
		bt_fioctl(fh, bt_terminal_ioctl_SetEventMode, sizeof(emode), (void*)&emode);
		bt_msg_filter filter;
		filter.flags = bt_msg_filter_flags_Source;
		filter.source = bt_query_extension("TERMINAL");
		bt_msg_header hdr = bt_recv_filtered(filter);
		bt_terminal_event event;
		bt_msg_content(&hdr, (void*)&event, sizeof(event));
		bt_msg_ack(&hdr);
		if (event.type == bt_terminal_event_type_Key) {
		printf("Keyboard event: %x\n", event.key);
        } else if (event.type == bt_terminal_event_type_Pointer) {
            char *type = NULL;
            if (event.pointer.type == bt_terminal_pointer_event_type_ButtonDown) type = "Button Down";
            if (event.pointer.type == bt_terminal_pointer_event_type_ButtonUp) type = "Button Up";
            if (event.pointer.type == bt_terminal_pointer_event_type_Move) type = "Move";
            printf("Pointer event: '%s' (%i, %i) %i\n", type, event.pointer.x, event.pointer.y, event.pointer.button);
        } else {
            printf("Unknown terminal event type: %x\n", event.type);
        }
    }else if(strcmp(argv[1], "modes")==0){
        size_t modecount= bt_fioctl(fh, bt_terminal_ioctl_GetScreenModeCount, 0, NULL);
        for(size_t i=0; i<modecount; ++i){
            bt_vidmode mode;
            mode.id=i;
            bt_fioctl(fh, bt_terminal_ioctl_GetScreenMode, sizeof(mode), (char*)&mode);
            printf("Mode %i: ID: %i %ix%i %ibpp %s.\n", (int)i, mode.id, mode.width, mode.height, mode.bpp, mode.textmode?"text":"graphics");
        }
        bt_vidmode cmode;
        bt_fioctl(fh, bt_terminal_ioctl_QueryScreenMode, sizeof(cmode), (char*)&cmode);
        printf("Current mode: ID: %i %ix%i %ibpp %s.\n", cmode.id, cmode.width, cmode.height, cmode.bpp, cmode.textmode?"text":"graphics");
    }else if(strcmp(argv[1], "reset")==0){
        size_t modecount= bt_fioctl(fh, bt_terminal_ioctl_GetScreenModeCount, 0, NULL);
        for(size_t i=0; i<modecount; ++i) {
            bt_vidmode mode;
            mode.id=i;
            bt_fioctl(fh, bt_terminal_ioctl_GetScreenMode, sizeof(mode), (char*)&mode);
            if(mode.textmode){
                bt_fioctl(fh, bt_terminal_ioctl_SetScreenMode, sizeof(mode), (char*)&mode);
                break;
            }
        }
    }else{
        printf("Unknown option '%s'\n", argv[1]);
    }
    return 0;
}
