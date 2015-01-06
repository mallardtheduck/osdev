#ifndef _OPS_HPP
#define _OPS_HPP

#include "vga.hpp"

template<typename T> static T max(T a, T b){ return (a>b)?a:b; }

struct vga_instance;

size_t text_read(vga_instance *inst, size_t bytes, char *buf);
size_t text_write(vga_instance *inst, size_t bytes, char *buf);
size_t text_seek(vga_instance *inst, size_t pos, bool relative);
int text_ioctl(vga_instance *inst, int fn, size_t bytes, char *buf);

#endif
