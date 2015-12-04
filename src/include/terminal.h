#ifndef _TERMINAL_H
#define _TERMINAL_H

#include "bt_enum.h"

ENUM_START(bt_terminal_mode)
    ENUM_SET(bt_terminal_mode, Terminal, 0),
    ENUM_SET(bt_terminal_mode, Video, 1),
ENUM_END
ENUM_TYPE(bt_terminal_mode);

ENUM_START(bt_terminal_ioctl)
    ENUM_SET(bt_terminal_ioctl, SetTerminalMode, 261),
    ENUM_SET(bt_terminal_ioctl, GetTerminalMode, 262),
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
	ENUM_SET(bt_terminal_ioctl, StartEventMode, 274),
	ENUM_SET(bt_terminal_ioctl, EndEventMode, 275),
	ENUM_SET(bt_terminal_ioctl, SetEventMode, 276),
	ENUM_SET(bt_terminal_ioctl, PointerAutoHide, 278),
	ENUM_SET(bt_terminal_ioctl, PointerFreeze, 279),
	ENUM_SET(bt_terminal_ioctl, PointerUnfreeze, 280),

    ENUM_SET(bt_terminal_ioctl, NewTerminal, 291),
    ENUM_SET(bt_terminal_ioctl, SwtichTerminal, 293),
	ENUM_SET(bt_terminal_ioctl, RegisterGlobalShortcut, 294),
	
	ENUM_SET(bt_terminal_ioctl, ClearScreen, 501),
	ENUM_SET(bt_terminal_ioctl, GetScreenModeCount, 301),
	ENUM_SET(bt_terminal_ioctl, GetScreenMode, 302),
	ENUM_SET(bt_terminal_ioctl, SetScreenMode, 303),
	ENUM_SET(bt_terminal_ioctl, QueryScreenMode, 304),
	ENUM_SET(bt_terminal_ioctl, GetPaletteEntry, 305),
	ENUM_SET(bt_terminal_ioctl, SetTextColours, 401),
	ENUM_SET(bt_terminal_ioctl, GetTextColours, 402),
	ENUM_SET(bt_terminal_ioctl, GetScrolling, 403),
	ENUM_SET(bt_terminal_ioctl, SetScrolling, 404),
ENUM_END
ENUM_TYPE(bt_terminal_ioctl);

ENUM_START(bt_terminal_event_mode)
	ENUM_SET(bt_terminal_event_mode, None, 0),
	ENUM_SET(bt_terminal_event_mode, Keyboard, 1),
	ENUM_SET(bt_terminal_event_mode, Pointer, 2),
	ENUM_SET(bt_terminal_event_mode, Both, 3),
ENUM_END
ENUM_TYPE(bt_terminal_event_mode);

struct bt_terminal_pointer_info{
    uint32_t x;
    uint32_t y;
    uint16_t flags;
};

#ifndef __cplusplus
typedef struct bt_terminal_pointer_info bt_terminal_pointer_info;
#endif

ENUM_START(bt_terminal_pointer_event_type)
    ENUM_SET(bt_terminal_pointer_event_type, None, 0),
    ENUM_SET(bt_terminal_pointer_event_type, Move, 1),
    ENUM_SET(bt_terminal_pointer_event_type, ButtonDown, 2),
    ENUM_SET(bt_terminal_pointer_event_type, ButtonUp, 3),
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
    uint32_t transparent;
    uint32_t spot_x;
    uint32_t spot_y;
    size_t datasize;
    uint8_t data[];
};

#ifndef __cplusplus
typedef struct bt_terminal_pointer_bitmap bt_terminal_pointer_bitmap;
#endif

#endif