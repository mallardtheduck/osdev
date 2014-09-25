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
ENUM_END
ENUM_TYPE(bt_terminal_ioctl);

#endif