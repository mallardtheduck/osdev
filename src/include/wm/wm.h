#ifndef _WM_H
#define _WM_H

#include "../bt_enum.h"

#ifdef __cplusplus
	#include <cstdint>
	#include <cstddef>
#else
	#include <stdint.h>
	#include <stddef.h>
#endif

ENUM_START(wm_WindowOptions)
	ENUM_SET(wm_WindowOptions, NoFrame, 	1 << 0),
	ENUM_SET(wm_WindowOptions, NoMenu, 		1 << 1),
	ENUM_SET(wm_WindowOptions, NoMaximize, 	1 << 2),
	ENUM_SET(wm_WindowOptions, NoMinimize,	1 << 3),
	ENUM_SET(wm_WindowOptions, NoClose, 	1 << 4),
	ENUM_SET(wm_WindowOptions, Resizable, 	1 << 5),
	ENUM_SET(wm_WindowOptions, ToolWindow, 	1 << 6),
ENUM_END
ENUM_TYPE(wm_WindowOptions)

#endif