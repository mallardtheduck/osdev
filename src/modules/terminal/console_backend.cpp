#include "console_backend.hpp"
#include "vterm.hpp"
#include "../../include/module_stubs.h"
#include "holdlock.hpp"

console_backend *cons_backend;
const char* video_device_name="DISPLAY_DEVICE";
const char* input_device_name="INPUT_DEVICE";

void console_backend_input_thread(void *p){
    console_backend *backend=(console_backend*)p;
    while(true){
        uint32_t key=0;
        size_t read=fread(backend->input, sizeof(key), (char*)&key);
        if(read){
            hold_lock hl(&backend->backend_lock);
            if(backend->input_top!=backend->input_bottom){
                backend->inputbuffer[backend->input_top]=key;
                backend->input_top++;
                if(backend->input_top == console_backend::inputbuffersize) backend->input_top=0;
            }
        }
    }
}

console_backend::console_backend() {
    init_lock(&backend_lock);
    input_top=1;
    input_bottom=0;

    char video_device_path[BT_MAX_PATH]="DEV:/";
    char input_device_path[BT_MAX_PATH]="DEV:/";

    strncpy(video_device_path+5, (char*)getenv((char*)video_device_name, 0), BT_MAX_PATH-5);
    strncpy(input_device_path+5, (char*)getenv((char*)input_device_name, 0), BT_MAX_PATH-5);

    display=fopen(video_device_path, (fs_mode_flags)(FS_Read | FS_Write));
    input=fopen(input_device_path, (fs_mode_flags)(FS_Read | FS_Read));

    //input_thread_id=new_thread(&console_backend_input_thread, (void*)this);
}

size_t console_backend::display_read(size_t bytes, char *buf) {
    return fread(display, bytes, buf);
}

size_t console_backend::display_write(size_t bytes, char *buf) {
    return fwrite(display, bytes, buf);
}

size_t console_backend::display_seek(size_t pos, bool relative) {
    return fseek(display, pos, relative);
}

int console_backend::display_ioctl(int fn, size_t bytes, char *buf) {
    return fioctl(display, fn, bytes, buf);
}

size_t console_backend::input_read(size_t bytes, char *buf) {
    return fread(input, bytes, buf);
}

size_t console_backend::input_write(size_t bytes, char *buf) {
    return fwrite(input, bytes, buf);
}

size_t console_backend::input_seek(size_t pos, bool relative) {
    return fseek(input, pos, relative);
}

int console_backend::input_ioctl(int fn, size_t bytes, char *buf) {
    return fioctl(input, fn, bytes, buf);
}

bool console_backend::is_active(uint64_t id) {
    return active==id;
}

void console_backend::set_active(uint64_t id) {
    active=id;
}
