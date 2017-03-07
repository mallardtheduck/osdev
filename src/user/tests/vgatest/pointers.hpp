#ifndef _POINTERS_HPP
#define _POINTERS_HPP

#include <btos.h>
#include <dev/terminal.h>

bt_terminal_pointer_bitmap *get_pointer_bmp_16bpp();
bt_terminal_pointer_bitmap *get_pointer_bmp_24bpp();
bt_terminal_pointer_bitmap *get_pointer_bmp_32bpp();

extern bt_terminal_pointer_bitmap pointer_bmp_8bpp;
extern bt_terminal_pointer_bitmap pointer_bmp_4bpp;

#endif
