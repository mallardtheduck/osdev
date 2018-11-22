#ifndef _VIDEO_DEV_H
#define _VIDEO_DEV_H

#ifndef __cplusplus
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#else
#include <cstdint>
#include <cstddef>
#endif

struct bt_vidmode{
    uint32_t id;
    uint32_t width;
    uint32_t height;
    uint32_t bpp;
    bool textmode;
    bool palette;
    uint32_t bytesPerLine;
    uint8_t rBits, rPos;
    uint8_t gBits, gPos;
    uint8_t bBits, bPos;
};

#ifndef __cplusplus
typedef struct bt_vidmode bt_vidmode;
#endif

#include <util/bt_enum.h>

ENUM_START(bt_vid_ioctl)
    ENUM_SET(bt_vid_ioctl, GetModeCount, 301),
    ENUM_SET(bt_vid_ioctl, GetMode, 302),
    ENUM_SET(bt_vid_ioctl, SetMode, 303),
    ENUM_SET(bt_vid_ioctl, QueryMode, 304),
    ENUM_SET(bt_vid_ioctl, GetPaletteEntry, 305),

    ENUM_SET(bt_vid_ioctl, GetCursorVisibility, 405),
    ENUM_SET(bt_vid_ioctl, SetCursorVisibility, 406),
    ENUM_SET(bt_vid_ioctl, SetCursorPosition, 409),

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
