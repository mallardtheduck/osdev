#ifndef _DEVICE_HPP
#define _DEVICE_HPP

#include <dev/video_dev.h>

struct vga_instance{
    size_t pos;
};

void init_hwpnp();

#endif
