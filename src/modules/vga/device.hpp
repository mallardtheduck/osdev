#ifndef _DEVICE_HPP
#define _DEVICE_HPP

#include "video_dev.h"

struct vga_instance{
    size_t pos;
    bt_vid_text_access_mode::Enum mode;
};

void init_device();

#endif