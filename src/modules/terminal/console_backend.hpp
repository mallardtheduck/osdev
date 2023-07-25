#ifndef _CONSOLE_BACKEND_HPP
#define _CONSOLE_BACKEND_HPP

#include "backend.hpp"
#include <btos_module.h>
#include <btos/fs_interface.h>
#include <util/ministl.hpp>

class console_backend : public i_backend{
private:
    IFileHandle *display, *input, *pointer;
    uint64_t input_thread_id;
    uint64_t pointer_thread_id;
	uint64_t pointer_draw_thread_id;
	bool pointer_draw_running;
    ILock *backend_lock;
    uint64_t active;
    bool pointer_visible, old_pointer_visible;
	bool autohide, frozen;
    bt_terminal_pointer_bitmap *pointer_bitmap;
    bt_terminal_pointer_info pointer_info, old_pointer_info;
    uint8_t *mouseback;
	uint32_t pointer_draw_serial, pointer_cur_serial;
	uint32_t cur_pointer_x, cur_pointer_y;
	map<uint16_t, uint64_t> global_shortcuts;
	uint32_t pointer_speed=300000;
    bt_vidmode current_mode;

    friend void console_backend_input_thread(void *p);
    friend void console_backend_pointer_thread(void *p);
	friend void console_backend_pointer_draw_thread(void *p);

    void update_pointer();
    void draw_pointer(uint32_t x, uint32_t y, bool erase);
public:
    console_backend();

    size_t display_read(size_t bytes, char *buf);
    size_t display_write(size_t bytes, const char *buf);
    size_t display_seek(size_t pos, uint32_t flags);

    size_t input_read(size_t bytes, char *buf);
    size_t input_write(size_t bytes, const char *buf);
    size_t input_seek(size_t pos, uint32_t flags);

    void show_pointer();
    void hide_pointer();
    bool get_pointer_visibility();
    void set_pointer_bitmap(bt_terminal_pointer_bitmap *bmp);
    bt_terminal_pointer_info get_pointer_info();
	void set_pointer_autohide(bool val);
	void freeze_pointer();
	void unfreeze_pointer();
	uint32_t get_pointer_speed();
	void set_pointer_speed(uint32_t speed);
	
	size_t get_screen_mode_count();
	void set_screen_mode(const bt_vidmode &mode);
	bt_vidmode get_screen_mode(size_t index);
	bt_vidmode get_current_screen_mode();
	bt_video_palette_entry get_palette_entry(uint8_t entry);
	void clear_screen();
	void set_cursor_position(size_t pos);
	
	void register_global_shortcut(uint16_t keycode, uint64_t termid);

    bool is_active(uint64_t id);
    void set_active(uint64_t id);

    void open(uint64_t id);
    void close(uint64_t id);
	void switch_terminal(uint64_t id);
	bool can_create();
	void refresh();

    const char *desc();
};

extern console_backend *cons_backend;

void draw_graphics_pointer(IFileHandle *file, uint32_t x, uint32_t y, bt_terminal_pointer_bitmap *bitmap, uint8_t *data = nullptr);
uint8_t *get_graphics_pointer_background(IFileHandle *file, uint32_t x, uint32_t y, bt_terminal_pointer_bitmap *bitmap);

#endif