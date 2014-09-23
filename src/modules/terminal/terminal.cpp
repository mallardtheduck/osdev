#include "module_stubs.h"
#include "fs_interface.h"
#include "terminal.hpp"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

char video_device_path[BT_MAX_PATH];
char input_device_path[BT_MAX_PATH];
file_handle *video_device_handle;
file_handle *input_device_handle;

const char* video_device_name="DISPLAY_DEVICE";
const char* input_device_name="INPUT_DEVICE";

#pragma GCC diagnostic ignored "-Wunused-parameter"

void init();

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
    init();
    return 0;
}

void init(){
    dbgpf("TERM: %s %s\n", video_device_name, (char*)getenv((char*)video_device_name, 0));
    dbgpf("TERM: %s %s\n", input_device_name, (char*)getenv((char*)input_device_name, 0));
    strncpy(video_device_path, (char*)getenv((char*)video_device_name, 0), BT_MAX_PATH);
    strncpy(video_device_path, (char*)getenv((char*)video_device_name, 0), BT_MAX_PATH);

    video_device_handle=fopen(video_device_path, (fs_mode_flags)(FS_Read | FS_Write));
    input_device_handle=fopen(input_device_path, (fs_mode_flags)(FS_Read | FS_Write));
}