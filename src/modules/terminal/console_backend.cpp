#include "keyboard.h"
#include "console_backend.hpp"
#include "vterm.hpp"
#include "../../include/module_stubs.h"
#include "holdlock.hpp"
#include "device.hpp"

console_backend *cons_backend;
const char* video_device_name="DISPLAY_DEVICE";
const char* input_device_name="INPUT_DEVICE";

static uint64_t create_terminal(char *command) {
    uint64_t new_id=terminals->create_terminal(cons_backend);
    terminals->get(new_id)->sync(false);
    if(command){
        char old_terminal_id[128]="0";
        strncpy(old_terminal_id, getenv(terminal_var, getpid()), 128);
        char new_terminal_id[128]={0};
        i64toa(new_id, new_terminal_id, 10);
        setenv(terminal_var, new_terminal_id, 0, getpid());
        pid_t pid=spawn(command, 0, NULL);
        setenv(terminal_var, old_terminal_id, 0, getpid());
        if(!pid) terminals->get(new_id)->close();
    }
    return new_id;
}

static uint64_t switcher_term=0;

void console_backend_input_thread(void *p){
    console_backend *backend=(console_backend*)p;
    while(true){
        uint32_t key=0;
        size_t read=fread(backend->input, sizeof(key), (char*)&key);
        if(read){
            hold_lock hl(&backend->backend_lock);
            if(backend->active) {
                vterm *term=terminals->get(backend->active);
                if ((key & KeyFlags::Control) && (key & KeyCodes::Escape)==KeyCodes::Escape && !(key & KeyFlags::KeyUp)) {
                    terminals->switch_terminal(switcher_term);
                }else if (term) term->queue_input(key);
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

    input_thread_id=new_thread(&console_backend_input_thread, (void*)this);
}

void console_backend::start_switcher(){
    switcher_term=create_terminal("HDD:/BTOS/SWITCHER.ELX");
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

void console_backend::open(uint64_t /*id*/){
}

void console_backend::close(uint64_t id){
    if(is_active(id)){
        dbgpf("TERM: Active terminal closed, activating new terminal..\n");
        //TODO: Make this work with multiple backends!
        vterm *term=terminals->get(0);
        if(!term){
            uint64_t new_id=terminals->create_terminal(this);
            term=terminals->get(new_id);
        }
        dbgpf("TERM: Activating terminal %i\n", (int)term->get_id());
        term->activate();
    }
}
