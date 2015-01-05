#ifndef _MOUSE_H
#define _MOUSE_H

#include <stddef.h>
#include <stdint.h>
#include "bt_enum.h"

struct bt_mouse_packet{
	uint16_t flags;
	int16_t x_motion;
	int16_t y_motion;
};

#ifndef __cplusplus
typedef struct bt_mouse_packet bt_mouse_packet;
#endif

ENUM_START(MouseFlags)
ENUM_SET(MouseFlags, Button1, 1 << 0),
ENUM_SET(MouseFlags, Button2, 1 << 1),
ENUM_SET(MouseFlags, Button3, 1 << 2),
ENUM_SET(MouseFlags, Button4, 1 << 3),
ENUM_SET(MouseFlags, Button5, 1 << 4),
ENUM_SET(MouseFlags, ScrollXUp, 1 << 5),
ENUM_SET(MouseFlags, ScrollXDown, 1 << 6),
ENUM_SET(MouseFlags, ScrollYUp, 1 << 7),
ENUM_SET(MouseFlags, ScrollYDown, 1 << 8),
ENUM_SET(MouseFlags, Valid, 1 << 15),
ENUM_END
ENUM_TYPE(MouseFlags);

ENUM_START(bt_mouse_ioctl)
ENUM_SET(bt_mouse_ioctl, ClearBuffer, 300),
ENUM_END
ENUM_TYPE(bt_mouse_ioctl);

#endif