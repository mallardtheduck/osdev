#ifndef _WM_H
#define _WM_H

#include "../bt_enum.h"

#ifdef __cplusplus
	#include <cstdint>
	#include <cstddef>
	static const size_t WM_TITLE_MAX = 255;
#else
	#include <stdint.h>
	#include <stddef.h>
	#define WM_TITLE_MAX 255;
#endif

ENUM_START(wm_WindowOptions)
	ENUM_SET(wm_WindowOptions, Visible, 	1 << 0),
	ENUM_SET(wm_WindowOptions, NoFrame, 	1 << 1),
	ENUM_SET(wm_WindowOptions, NoMenu, 		1 << 2),
	ENUM_SET(wm_WindowOptions, NoExpand, 	1 << 3),
	ENUM_SET(wm_WindowOptions, NoHide,		1 << 4),
	ENUM_SET(wm_WindowOptions, NoClose, 	1 << 5),
	ENUM_SET(wm_WindowOptions, Resizable, 	1 << 6),
	ENUM_SET(wm_WindowOptions, ToolWindow, 	1 << 7),
ENUM_END
ENUM_TYPE(wm_WindowOptions)

ENUM_START(wm_EventType)
	ENUM_SET(wm_EventType, PointerMove, 		1 << 0),
	ENUM_SET(wm_EventType, PointerButtonDown, 	1 << 1),
	ENUM_SET(wm_EventType, PointerButtonUp,		1 << 2),
	ENUM_SET(wm_EventType, KeyDown,				1 << 3),
	ENUM_SET(wm_EventType, KeyUp,				1 << 4),
	ENUM_SET(wm_EventType, Click,				1 << 5),
	ENUM_SET(wm_EventType, DoubleClick,			1 << 6),
	ENUM_SET(wm_EventType, KeyPress, 			1 << 7),
	ENUM_SET(wm_EventType, Close,				1 << 8),
	ENUM_SET(wm_EventType, Hide,				1 << 9),
	ENUM_SET(wm_EventType, Expand,				1 << 10),
	ENUM_SET(wm_EventType, MenuSelection,		1 << 11),
ENUM_END
ENUM_TYPE(wm_EventType)

struct wm_WindowInfo{
	int32_t x, y;
	ENUM_NAME(wm_WindowOptions) options;
	uint64_t gds_id;
	char title[WM_TITLE_MAX];
};
BT_STRUCT_TYPE(wm_WindowInfo);

struct wm_Event{
	ENUM_NAME(wm_EventType) type;
	uint64_t window_id;
	union{
		struct{
			uint32_t x, y;
			uint32_t button;
		} Pointer;
		struct{
			uint32_t code;
		} Key;
		struct{
			uint64_t id;
		} Menu;
	};
};

ENUM_START(wm_RequestType)
	ENUM_SET(wm_RequestType, SelectWindow, 		1),
	ENUM_SET(wm_RequestType, CreateWindow, 		2),
	ENUM_SET(wm_RequestType, DestroyWindow,		3),
	ENUM_SET(wm_RequestType, WindowInfo, 		4),
	ENUM_SET(wm_RequestType, Subscribe, 		5),
	ENUM_SET(wm_RequestType, Update, 			6),
	ENUM_SET(wm_RequestType, ReplaceSurface,	7),
	ENUM_SET(wm_RequestType, MoveWindow, 		8),
	ENUM_SET(wm_RequestType, ChangeFlags, 		9),
	ENUM_SET(wm_RequestType, SetTitle,			10),
ENUM_END
ENUM_TYPE(wm_RequestType)

#endif