#ifndef _DEVICE_HPP
#define _DEVICE_HPP

#include <dev/video_dev.h>

struct vga_instance{
    size_t pos;
    bt_vid_text_access_mode::Enum mode;
};

extern drv_driver vga_device;

void init_device();

#endif
