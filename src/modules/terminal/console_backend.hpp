#ifndef _CONSOLE_BACKEND_HPP
#define _CONSOLE_BACKEND_HPP

#include "backend.hpp"
#include "module_api.h"
#include "fs_interface.h"

class console_backend : public i_backend{
private:
    file_handle *display, *input, *pointer;
    uint64_t input_thread_id;
    uint64_t pointer_thread_id;
	uint64_t pointer_draw_thread_id;
	bool pointer_draw_running;
    lock backend_lock;
    uint64_t active;
    bool pointer_visible, old_pointer_visible;
	bool autohide, frozen;
    bt_terminal_pointer_bitmap *pointer_bitmap;
    bt_terminal_pointer_info pointer_info, old_pointer_info;
    uint8_t *mouseback;
	uint32_t pointer_draw_serial, pointer_cur_serial;
	uint32_t cur_pointer_x, cur_pointer_y;

    friend void console_backend_input_thread(void *p);
    friend void console_backend_pointer_thread(void *p);
	friend void console_backend_pointer_draw_thread(void *p);

    void update_pointer();
    void draw_pointer(uint32_t x, uint32_t y, bool erase);
public:
    console_backend();

    size_t display_read(size_t bytes, char *buf);
    size_t display_write(size_t bytes, char *buf);
    size_t display_seek(size_t pos, uint32_t flags);
    int display_ioctl(int fn, size_t bytes, char *buf);

    size_t input_read(size_t bytes, char *buf);
    size_t input_write(size_t bytes, char *buf);
    size_t input_seek(size_t pos, uint32_t flags);
    int input_ioctl(int fn, size_t bytes, char *buf);

    bt_terminal_pointer_info pointer_read();
    void show_pointer();
    void hide_pointer();
    bool get_pointer_visibility();
    void set_pointer_bitmap(bt_terminal_pointer_bitmap *bmp);
    bt_terminal_pointer_info get_pointer_info();
	void set_pointer_autohide(bool val);
	virtual void freeze_pointer();
	virtual void unfreeze_pointer();

    bool is_active(uint64_t id);
    void set_active(uint64_t id);

    void open(uint64_t id);
    void close(uint64_t id);

    void start_switcher();

};

extern console_backend *cons_backend;

void draw_graphics_pointer(file_handle *file, uint32_t x, uint32_t y, bt_terminal_pointer_bitmap *bitmap, uint8_t *data=NULL);
uint8_t *get_graphics_pointer_background(file_handle *file, uint32_t x, uint32_t y, bt_terminal_pointer_bitmap *bitmap);

#endif