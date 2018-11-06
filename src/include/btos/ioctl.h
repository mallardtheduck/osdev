#ifndef _IOCTL_H
#define _IOCTL_H

#include "../util/bt_enum.h"

ENUM_START(bt_ioctl)
ENUM_SET(bt_ioctl, DevType, 1),
ENUM_SET(bt_ioctl, DevDesc, 2),
ENUM_SET(bt_ioctl, BlockSize, 3),
ENUM_END
ENUM_TYPE(bt_ioctl);

#endif
