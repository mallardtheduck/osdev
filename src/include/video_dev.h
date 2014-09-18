#ifndef _VIDEO_DEV_H
#define _VIDEO_DEV_H

#ifndef __cplusplus
#include <stdbool.h>
#endif

struct bt_vidmode{
    uint32_t id;
    uint32_t width;
    uint32_t height;
    uint32_t bpp;
    bool textmode;
    bool palette;
};

#ifndef __cplusplus
typedef struct bt_vidmode bt_vidmode;
#endif

#include "bt_enum.h"

ENUM_START(bt_vid_ioctl)
    ENUM_SET(bt_vid_ioctl, GetModeCount, 301),
    ENUM_SET(bt_vid_ioctl, GetMode, 302),
    ENUM_SET(bt_vid_ioctl, SetMode, 303),
    ENUM_SET(bt_vid_ioctl, QueryMode, 304),

    ENUM_SET(bt_vid_ioctl, SetTextFGColour, 401),
    ENUM_SET(bt_vid_ioctl, SetTextBGColour, 402),
    ENUM_SET(bt_vid_ioctl, SetTextColours, 403),
    ENUM_SET(bt_vid_ioctl, GetTextFGColour, 404),
    ENUM_SET(bt_vid_ioctl, GetTextBGColour, 405),
    ENUM_SET(bt_vid_ioctl, GetTextColours, 406),
ENUM_END
ENUM_TYPE(bt_vid_ioctl);

#endif