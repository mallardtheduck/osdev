#ifndef _CONSOLE_BACKEND_HPP
#define _CONSOLE_BACKEND_HPP

#include "backend.hpp"
#include "module_api.h"
#include "fs_interface.h"

class console_backend : public i_backend{
private:
    static const size_t inputbuffersize=256;
    file_handle *display, *input, *pointer;
    uint64_t input_thread_id;
    uint64_t pointer_thread_id;
    uint32_t inputbuffer[inputbuffersize];
    size_t input_top, input_bottom;
    lock backend_lock;
    uint64_t active;
    bool pointer_visible;
    bt_terminal_pointer_bitmap pointer_bitmap;
    bt_terminal_pointer_info pointer_info;
    uint8_t *mouseback;

    friend void console_backend_input_thread(void *p);
    friend void console_backend_pointer_thread(void *p);

    void update_pointer(bool erase);
public:
    console_backend();

    size_t display_read(size_t bytes, char *buf);
    size_t display_write(size_t bytes, char *buf);
    size_t display_seek(size_t pos, bool relative);
    int display_ioctl(int fn, size_t bytes, char *buf);

    size_t input_read(size_t bytes, char *buf);
    size_t input_write(size_t bytes, char *buf);
    size_t input_seek(size_t pos, bool relative);
    int input_ioctl(int fn, size_t bytes, char *buf);

    bt_terminal_pointer_info pointer_read();
    void show_pointer();
    void hide_pointer();
    bool get_pointer_visibility();
    void set_pointer_bitmap(bt_terminal_pointer_bitmap bmp);
    bt_terminal_pointer_info get_pointer_info();

    bool is_active(uint64_t id);
    void set_active(uint64_t id);

    void open(uint64_t id);
    void close(uint64_t id);

    void start_switcher();

};

extern console_backend *cons_backend;

#endif