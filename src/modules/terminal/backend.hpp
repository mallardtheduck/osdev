#ifndef _BACKEND_HPP
#define _BACKEND_HPP
#include "module_api.h"
#include "terminal.h"
#include "video_dev.h"

class i_backend{
public:
    virtual size_t display_read(size_t bytes, char *buf)=0;
    virtual size_t display_write(size_t bytes, char *buf)=0;
    virtual size_t display_seek(size_t pos, uint32_t flags)=0;

    virtual size_t input_read(size_t bytes, char *buf)=0;
    virtual size_t input_write(size_t bytes, char *buf)=0;
    virtual size_t input_seek(size_t pos, uint32_t flags)=0;

    virtual bt_terminal_pointer_info pointer_read()=0;
    virtual void show_pointer()=0;
    virtual void hide_pointer()=0;
    virtual bool get_pointer_visibility()=0;
    virtual void set_pointer_bitmap(bt_terminal_pointer_bitmap *bmp)=0;
    virtual bt_terminal_pointer_info get_pointer_info()=0;
	virtual void set_pointer_autohide(bool val) = 0;
	virtual void freeze_pointer()=0;
	virtual void unfreeze_pointer()=0;
	
	virtual void set_text_colours(uint8_t c) = 0;
	virtual uint8_t get_text_colours() = 0;
	virtual size_t get_screen_mode_count() = 0;
	virtual void set_screen_mode(const bt_vidmode &mode) = 0;
	virtual bt_vidmode get_screen_mode(size_t index) = 0;
	virtual bt_vidmode get_current_screen_mode() = 0;
	virtual void set_screen_scroll(bool v) = 0;
	virtual bool get_screen_scroll() = 0;
	virtual void set_text_access_mode(bt_vid_text_access_mode::Enum mode) = 0;
	virtual bt_video_palette_entry get_palette_entry(uint8_t entry) = 0;
	virtual void clear_screen() = 0;

    virtual bool is_active(uint64_t id)=0;
    virtual void set_active(uint64_t id)=0;

    virtual void open(uint64_t id)=0;
    virtual void close(uint64_t id)=0;

    virtual ~i_backend(){};
};

#endif