#include "mouse.h"
#include "keyboard.h"
#include "console_backend.hpp"
#include "vterm.hpp"
#include "module_stubs.h"
#include "holdlock.hpp"
#include "device.hpp"

console_backend *cons_backend;
const char* video_device_name="DISPLAY_DEVICE";
const char* input_device_name="INPUT_DEVICE";
const char* pointer_device_name="POINTER_DEVICE";

const uint32_t pointer_speed=500000;

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
    thread_priority(2);
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
void console_backend_pointer_thread(void *p){
    console_backend *backend=(console_backend*)p;
    thread_priority(2);
    while(true){
        bt_mouse_packet packet;
        size_t read=fread(backend->pointer, sizeof(packet), (char*)&packet);
        if(read){
            hold_lock hl(&backend->backend_lock);
            backend->update_pointer(true);
            uint32_t oldx=backend->pointer_info.x;
            backend->pointer_info.x+=(packet.x_motion * pointer_speed);
            if(packet.x_motion > 0 && backend->pointer_info.x < oldx) backend->pointer_info.x=0xFFFFFFFF;
            if(packet.x_motion < 0 && backend->pointer_info.x > oldx) backend->pointer_info.x=0;
            uint32_t oldy=backend->pointer_info.y;
            backend->pointer_info.y+=(packet.y_motion * pointer_speed);
            if(packet.y_motion > 0 && backend->pointer_info.y < oldy) backend->pointer_info.y=0xFFFFFFFF;
            if(packet.y_motion < 0 && backend->pointer_info.y > oldy) backend->pointer_info.y=0;
            backend->pointer_info.flags=packet.flags;
            backend->update_pointer(false);
        }
    }
}

void console_backend::update_pointer(bool erase) {
    if(pointer_visible){
        hold_lock hl(&backend_lock, false);
        bt_vidmode mode;
        fioctl(display, bt_vid_ioctl::QueryMode, sizeof(mode), (char*)&mode);
        uint32_t xscale=(0xFFFFFFFF/(mode.width-1));
        uint32_t yscale=(0xFFFFFFFF/(mode.height-1));
        uint32_t x=(pointer_info.x/xscale);
        uint32_t y=(pointer_info.y/yscale);
        if(mode.textmode){
            y=(mode.height-1)-y;
            size_t pos=(((y * mode.width) + x) * 2) + 1;
            size_t cpos=fseek(display, 0, true);
            bt_vid_text_access_mode::Enum omode=(bt_vid_text_access_mode::Enum) fioctl(display, bt_vid_ioctl::GetTextAccessMode, 0, NULL);
            bt_vid_text_access_mode::Enum nmode=bt_vid_text_access_mode::Raw;
            fioctl(display, bt_vid_ioctl::SetTextAccessMode, sizeof(nmode), (char*)&nmode);
            fseek(display, pos, false);
            if(erase) {
                if(mouseback) {
                    fwrite(display, 1, (char*)mouseback);
                }
            } else {
                if(mouseback) delete mouseback;
                mouseback=new uint8_t();
                fread(display, 1, (char*)mouseback);
                fseek(display, pos, false);
                uint8_t cursor=*mouseback ^ 0xFF;
                fwrite(display, 1, (char*)&cursor);
            }
            fioctl(display, bt_vid_ioctl::SetTextAccessMode, sizeof(omode), (char*)&omode);
            fseek(display, cpos, false);
        }
    }
}

console_backend::console_backend() {
    init_lock(&backend_lock);
    input_top=1;
    input_bottom=0;
    pointer_visible=false;
    pointer_bitmap.h=0; pointer_bitmap.w=0; pointer_bitmap.bpp=0; pointer_bitmap.data=NULL;
    pointer_info.x=0; pointer_info.y=0; pointer_info.flags=0;
    mouseback=NULL;

    char video_device_path[BT_MAX_PATH]="DEV:/";
    char input_device_path[BT_MAX_PATH]="DEV:/";
    char pointer_device_path[BT_MAX_PATH]="DEV:/";

    strncpy(video_device_path+5, (char*)getenv((char*)video_device_name, 0), BT_MAX_PATH-5);
    strncpy(input_device_path+5, (char*)getenv((char*)input_device_name, 0), BT_MAX_PATH-5);
    strncpy(pointer_device_path+5, (char*)getenv((char*)pointer_device_name, 0), BT_MAX_PATH-5);

    display=fopen(video_device_path, (fs_mode_flags)(FS_Read | FS_Write));
    input=fopen(input_device_path, (fs_mode_flags)(FS_Read));
    pointer=fopen(pointer_device_path, (fs_mode_flags)(FS_Read));

    input_thread_id=new_thread(&console_backend_input_thread, (void*)this);
    pointer_thread_id=new_thread(&console_backend_pointer_thread, (void*)this);
}

void console_backend::start_switcher(){
    switcher_term=create_terminal("HDD:/BTOS/SWITCHER.ELX");
}

size_t console_backend::display_read(size_t bytes, char *buf) {
    update_pointer(true);
    size_t ret=fread(display, bytes, buf);
    update_pointer(false);
    return ret;
}

size_t console_backend::display_write(size_t bytes, char *buf) {
    update_pointer(true);
    size_t ret=fwrite(display, bytes, buf);
    update_pointer(false);
    return ret;
}

size_t console_backend::display_seek(size_t pos, bool relative) {
    return fseek(display, pos, relative);
}

int console_backend::display_ioctl(int fn, size_t bytes, char *buf) {
    update_pointer(true);
    int ret=fioctl(display, fn, bytes, buf);
    update_pointer(false);
    return ret;
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

bt_terminal_pointer_info console_backend::pointer_read(){
    bt_terminal_pointer_info ret;
    return ret;
}

void console_backend::show_pointer() {
    fioctl(pointer, bt_mouse_ioctl::ClearBuffer, 0, NULL);
    pointer_visible=true;
    update_pointer(false);
}

void console_backend::hide_pointer() {
    update_pointer(true);
    pointer_visible=false;
}

bool console_backend::get_pointer_visibility() {
    return pointer_visible;
}

void console_backend::set_pointer_bitmap(bt_terminal_pointer_bitmap /*bmp*/) {

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
