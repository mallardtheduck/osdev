#ifndef _API_HPP
#define _API_HPP

#include <btos_module.h>
#include "backend.hpp"

void terminal_uapi_fn(uint16_t fn, ICPUState &state);

class user_backend : public i_backend{
	bt_pid_t pid;
	bt_handle_t handle_id;
	uint64_t active_id;
	
public:
	user_backend(bt_pid_t p);
	void set_handlde_id(bt_handle_t h);

	size_t display_read(size_t bytes, char *buf);
    size_t display_write(size_t bytes, const char *buf);
    size_t display_seek(size_t pos, uint32_t flags);

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

#endif