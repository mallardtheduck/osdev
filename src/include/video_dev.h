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

ENUM_START(bt_vid_text_access_mode)
    ENUM_SET(bt_vid_text_access_mode, Simple, 0),
    ENUM_SET(bt_vid_text_access_mode, Raw, 1),
ENUM_END

ENUM_START(bt_vid_ioctl)
    ENUM_SET(bt_vid_ioctl, GetModeCount, 301),
    ENUM_SET(bt_vid_ioctl, GetMode, 302),
    ENUM_SET(bt_vid_ioctl, SetMode, 303),
    ENUM_SET(bt_vid_ioctl, QueryMode, 304),
    ENUM_SET(bt_vid_ioctl, GetPaletteEntry, 305),

    ENUM_SET(bt_vid_ioctl, SetTextColours, 401),
    ENUM_SET(bt_vid_ioctl, GetTextColours, 402),
    ENUM_SET(bt_vid_ioctl, GetScrolling, 403),
    ENUM_SET(bt_vid_ioctl, SetScrolling, 404),
    ENUM_SET(bt_vid_ioctl, GetCursorVisibility, 405),
    ENUM_SET(bt_vid_ioctl, SetCursorVisibility, 406),
    ENUM_SET(bt_vid_ioctl, SetTextAccessMode, 407),
    ENUM_SET(bt_vid_ioctl, GetTextAccessMode, 408),

    ENUM_SET(bt_vid_ioctl, ClearScreen, 501),
ENUM_END
ENUM_TYPE(bt_vid_ioctl);

struct bt_video_palette_entry{
    size_t index;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

#ifndef __cplusplus
typedef struct bt_video_palette_entry bt_video_palette_entry;
#endif

#endif