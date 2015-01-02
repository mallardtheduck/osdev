#ifndef _TERMINAL_H
#define _TERMINAL_H

#include "bt_enum.h"

ENUM_START(bt_terminal_mode)
    ENUM_SET(bt_terminal_mode, Terminal, 0),
    ENUM_SET(bt_terminal_mode, Video, 1),
    ENUM_SET(bt_terminal_mode, Keyboard, 2),
    ENUM_SET(bt_terminal_mode, Pointer, 3),
ENUM_END
ENUM_TYPE(bt_terminal_mode);

ENUM_START(bt_terminal_ioctl)
    ENUM_SET(bt_terminal_ioctl, SetMode, 261),
    ENUM_SET(bt_terminal_ioctl, GetMode, 262),
    ENUM_SET(bt_terminal_ioctl, SetInfoLine, 263),
    ENUM_SET(bt_terminal_ioctl, GetInfoLine, 264),
    ENUM_SET(bt_terminal_ioctl, SetTitle, 265),
    ENUM_SET(bt_terminal_ioctl, GetTitle, 266),
    ENUM_SET(bt_terminal_ioctl, SetEcho, 267),
    ENUM_SET(bt_terminal_ioctl, GetEcho, 268),
    ENUM_SET(bt_terminal_ioctl, ShowPointer, 269),
    ENUM_SET(bt_terminal_ioctl, HidePointer, 270),
    ENUM_SET(bt_terminal_ioctl, GetPointerVisibility, 271),
    ENUM_SET(bt_terminal_ioctl, SetPointerBitmap, 272),
    ENUM_SET(bt_terminal_ioctl, GetPointerInfo, 273),
    ENUM_SET(bt_terminal_ioctl, ReadPointerEvent, 274),
    ENUM_SET(bt_terminal_ioctl, ReadKeyEvent, 275),
    ENUM_SET(bt_terminal_ioctl, ReadEvent, 276),
    ENUM_SET(bt_terminal_ioctl, ClearEvents, 277),

    ENUM_SET(bt_terminal_ioctl, NewTerminal, 291),
    ENUM_SET(bt_terminal_ioctl, DestroyTerminal, 292),
    ENUM_SET(bt_terminal_ioctl, SwtichTerminal, 293),
ENUM_END
ENUM_TYPE(bt_terminal_ioctl);

struct bt_terminal_pointer_info{
    uint32_t x;
    uint32_t y;
    uint16_t flags;
};

#ifndef __cplusplus
typedef struct bt_terminal_pointer_info bt_terminal_pointer_info;
#endif

ENUM_START(bt_terminal_pointer_event_type)
    ENUM_SET(bt_terminal_pointer_event_type, Move, 1),
    ENUM_SET(bt_terminal_pointer_event_type, ButtonDown, 2),
    ENUM_SET(bt_terminal_pointer_event_type, ButtonUp, 1),
ENUM_END
ENUM_TYPE(bt_terminal_pointer_event_type);

struct bt_terminal_pointer_event{
    ENUM_NAME(bt_terminal_pointer_event_type) type;
    uint32_t x;
    uint32_t y;
    uint32_t button;
};

#ifndef __cplusplus
typedef struct bt_terminal_pointer_event bt_terminal_pointer_event;
#endif

ENUM_START(bt_terminal_event_type)
    ENUM_SET(bt_terminal_event_type, Pointer, 1),
    ENUM_SET(bt_terminal_event_type, Key, 2),
ENUM_END
ENUM_TYPE(bt_terminal_event_type);

struct bt_terminal_event{
    ENUM_NAME(bt_terminal_event_type) type;
    union{
        bt_terminal_pointer_event pointer;
        uint32_t key;
    };
};

#ifndef __cplusplus
typedef struct bt_terminal_event bt_terminal_event;
#endif

struct bt_terminal_pointer_bitmap{
    uint32_t w;
    uint32_t h;
    uint8_t bpp;
    uint32_t spot_x;
    uint32_t spot_y;
    uint8_t *data;
};

#ifndef __cplusplus
typedef struct bt_terminal_mouse_bitmap bt_terminal_mouse_bitmap;
#endif

#endif