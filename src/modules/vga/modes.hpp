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

extern const size_t vga_mode_count;
extern vga_mode modes[];

struct vga_palette_entry{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

extern vga_palette_entry vga_palette[256];

#endif