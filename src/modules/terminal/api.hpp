#ifndef _API_HPP
#define _API_HPP

#include <extension.h>
#include "backend.hpp"

extern uapi_hanlder_fn terminal_uapi;

class user_backend : public i_backend{
	pid_t pid;
	
public:
	size_t display_read(size_t bytes, char *buf);
    size_t display_write(size_t bytes, char *buf);
    size_t display_seek(size_t pos, uint32_t flags);

    size_t input_read(size_t bytes, char *buf);
    size_t input_write(size_t bytes, char *buf);
    size_t input_seek(size_t pos, uint32_t flags);

    void show_pointer();
    void hide_pointer();
    bool get_pointer_visibility();
    void set_pointer_bitmap(bt_terminal_pointer_bitmap *bmp);
    bt_terminal_pointer_info get_pointer_info();
	void set_pointer_autohide(bool val);
	void freeze_pointer();
	void unfreeze_pointer();
	
	void set_text_colours(uint8_t c);
	uint8_t get_text_colours();
	size_t get_screen_mode_count();
	void set_screen_mode(const bt_vidmode &mode);
	bt_vidmode get_screen_mode(size_t index);
	bt_vidmode get_current_screen_mode();
	void set_screen_scroll(bool v);
	bool get_screen_scroll();
	void set_text_access_mode(bt_vid_text_access_mode::Enum mode);
	bt_video_palette_entry get_palette_entry(uint8_t entry);
	void clear_screen();
	
	void register_global_shortcut(uint16_t keycode, uint64_t termid);

    bool is_active(uint64_t id);
    void set_active(uint64_t id);

    void open(uint64_t id);
    void close(uint64_t id);
	void switch_terminal(uint64_t id);
	bool can_create();
};

#endif