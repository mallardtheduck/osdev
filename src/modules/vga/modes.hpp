#ifndef _MODES_HPP
#define _MODES_HPP

#include "vga.hpp"
#include "video_dev.h"

struct vga_mode{
	bt_vidmode vidmode;

	void (*set_mode)();
	void (*put_pixel)(uint32_t x, uint32_t y, uint8_t value);
	uint8_t (*get_pixel)(uint32_t x, uint32_t y);
};

extern vga_mode modes[];

#endif