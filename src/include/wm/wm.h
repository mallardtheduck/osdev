#ifndef _WM_H
#define _WM_H

#include <util/bt_enum.h>

#ifdef __cplusplus
	#include <cstdint>
	#include <cstddef>
	static const size_t WM_TITLE_MAX = 255;
	static const size_t WM_MENUTEXT_MAX = 255;
#else
	#include <stdint.h>
	#include <stddef.h>
	#define WM_TITLE_MAX 255
	#define WM_MENUTEXT_MAX 255
#endif

ENUM_START(wm_WindowOptions)
	ENUM_SET(wm_WindowOptions, Visible, 			1 << 0),
	ENUM_SET(wm_WindowOptions, NoTitle, 			1 << 1),
	ENUM_SET(wm_WindowOptions, NoFrame,	(1 << 1) | (1 << 2)),
	ENUM_SET(wm_WindowOptions, NoMenu, 				1 << 3),
	ENUM_SET(wm_WindowOptions, NoExpand, 			1 << 4),
	ENUM_SET(wm_WindowOptions, NoHide,				1 << 5),
	ENUM_SET(wm_WindowOptions, NoClose, 			1 << 6),
	ENUM_SET(wm_WindowOptions, Resizable, 			1 << 7),
	ENUM_SET(wm_WindowOptions, ToolWindow, 			1 << 8),
	ENUM_SET(wm_WindowOptions, EnableTransparency, 	1 << 9),
	ENUM_SET(wm_WindowOptions, Unlisted,			1 << 10),
	ENUM_SET(wm_WindowOptions, Default,				(1 << 0)),
ENUM_END
ENUM_TYPE(wm_WindowOptions);

ENUM_START(wm_EventType)
	ENUM_SET(wm_EventType, None,				0),
	ENUM_SET(wm_EventType, PointerMove, 		1 << 0),
	ENUM_SET(wm_EventType, PointerButtonDown, 	1 << 1),
	ENUM_SET(wm_EventType, PointerButtonUp,		1 << 2),
	ENUM_SET(wm_EventType, PointerEnter,		1 << 3),
	ENUM_SET(wm_EventType, PointerLeave,		1 << 4),
	ENUM_SET(wm_EventType, KeyDown,				1 << 5),
	ENUM_SET(wm_EventType, KeyUp,				1 << 6),
	ENUM_SET(wm_EventType, Click,				1 << 7),
	ENUM_SET(wm_EventType, DoubleClick,			1 << 8),
	ENUM_SET(wm_EventType, Keyboard, 			1 << 9),
	ENUM_SET(wm_EventType, Close,				1 << 10),
	ENUM_SET(wm_EventType, Hide,				1 << 11),
	ENUM_SET(wm_EventType, Expand,				1 << 12),
	ENUM_SET(wm_EventType, MenuSelection,		1 << 13),
ENUM_END
ENUM_TYPE(wm_EventType);

static const int wm_KeyboardEvents = ENUM_GET(wm_EventType, KeyDown) | ENUM_GET(wm_EventType, KeyUp) 
	| ENUM_GET(wm_EventType, Keyboard);
static const int wm_PointerEvents = ENUM_GET(wm_EventType, PointerMove) | ENUM_GET(wm_EventType, PointerButtonDown) 
	| ENUM_GET(wm_EventType, PointerButtonUp) | ENUM_GET(wm_EventType, PointerEnter) | ENUM_GET(wm_EventType, PointerLeave)
	| ENUM_GET(wm_EventType, Click) | ENUM_GET(wm_EventType, DoubleClick);
static const int wm_FrameEvents = ENUM_GET(wm_EventType, Close) | ENUM_GET(wm_EventType, Hide) | ENUM_GET(wm_EventType, Expand)
	 | ENUM_GET(wm_EventType, MenuSelection);

struct wm_WindowInfo{
	int32_t x, y;
	uint32_t options;
	uint32_t subscriptions;
	uint64_t gds_id;
	char title[WM_TITLE_MAX+1];
};
BT_STRUCT_TYPE(wm_WindowInfo);

struct wm_Rect{
	int32_t x, y;
	uint32_t w, h;
};
BT_STRUCT_TYPE(wm_Rect);

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
			uint64_t menu_id;
			uint32_t action;
		} Menu;
	};
};
BT_STRUCT_TYPE(wm_Event);

ENUM_START(wm_RequestType)
	ENUM_SET(wm_RequestType, SelectWindow, 		1),
	ENUM_SET(wm_RequestType, CreateWindow, 		2),
	ENUM_SET(wm_RequestType, DestroyWindow,		3),
	ENUM_SET(wm_RequestType, WindowInfo, 		4),
	ENUM_SET(wm_RequestType, Subscribe, 		5),
	ENUM_SET(wm_RequestType, Update, 			6),
	ENUM_SET(wm_RequestType, UpdateRect,		7),
	ENUM_SET(wm_RequestType, ReplaceSurface,	8),
	ENUM_SET(wm_RequestType, MoveWindow, 		9),
	ENUM_SET(wm_RequestType, ChangeOptions,		10),
	ENUM_SET(wm_RequestType, SetTitle,			11),
	ENUM_SET(wm_RequestType, Sync,				12),
	
	ENUM_SET(wm_RequestType, SelectMenu,		20),
	ENUM_SET(wm_RequestType, CreateMenu,		21),
	ENUM_SET(wm_RequestType, DestroyMenu,		22),
	ENUM_SET(wm_RequestType, AddMenuItem,		23),
	ENUM_SET(wm_RequestType, RemoveMenuItem,	24),
	ENUM_SET(wm_RequestType, ReOrderMenu,		25),
	ENUM_SET(wm_RequestType, MenuInfo,			26),
	ENUM_SET(wm_RequestType, ShowMenu,			27),
	ENUM_SET(wm_RequestType, SelectWindowMenu,	28),
	ENUM_SET(wm_RequestType, SetWindowMenu,		29),
	ENUM_SET(wm_RequestType, UnSetWindowMenu,	30),
ENUM_END
ENUM_TYPE(wm_RequestType);

ENUM_START(wm_MessageType)
	ENUM_SET(wm_MessageType, Event,				1),
ENUM_END
ENUM_TYPE(wm_MessageType);

ENUM_START(wm_MenuItemFlags)
	ENUM_SET(wm_MenuItemFlags, Default, 	0),
	ENUM_SET(wm_MenuItemFlags, Seperator, 	(1 << 0)),
	ENUM_SET(wm_MenuItemFlags, Disabled, 	(1 << 1)),
	ENUM_SET(wm_MenuItemFlags, ChildMenu, 	(1 << 2)),
	ENUM_SET(wm_MenuItemFlags, ImageRight, 	(1 << 3)),
	ENUM_SET(wm_MenuItemFlags, ImageOnly, 	(1 << 4)),
ENUM_END
ENUM_TYPE(wm_MenuItemFlags);

struct wm_MenuItem{
	uint32_t actionID;
	char text[WM_MENUTEXT_MAX+1];
	uint32_t flags;
	uint64_t image;
	uint64_t childMenu;
};
BT_STRUCT_TYPE(wm_MenuItem);

#endif
