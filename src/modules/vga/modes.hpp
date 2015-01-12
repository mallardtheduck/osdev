#ifndef _MODES_HPP
#define _MODES_HPP

#include "vga.hpp"
#include "video_dev.h"

struct vga_mode{
	bt_vidmode vidmode;

	void (*set_mode)();
	void (*put_pixel)(uint32_t x, uint32_t y, uint8_t value);
	uint8_t (*get_pixel)(uint32_t x, uint32_t y);
	void (*write_pixels)(uint32_t startpos, size_t count, uint8_t *data);
	void (*read_pixels)(uint32_t startpos, size_t count, uint8_t *data);
};

extern const size_t vga_mode_count;
extern vga_mode *vga_modes[];
extern vga_mode *current_mode;

struct vga_palette_entry{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

void init_modes();

#endif