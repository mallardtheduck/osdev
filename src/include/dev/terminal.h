#ifndef _TERMINAL_H
#define _TERMINAL_H

#include <util/bt_enum.h>

#if defined(KERNEL) || defined(KERNEL_MODULE)
#include <btos_module.h>
#else
#include <btos.h>
#endif

#ifdef __cplusplus
using namespace btos_api;
#endif

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

ENUM_START(bt_terminal_message_type)
	ENUM_SET(bt_terminal_message_type, InputEvent, 0),
	ENUM_SET(bt_terminal_message_type, TerminalActivate, 1),
	ENUM_SET(bt_terminal_message_type, TerminalDeactivate, 2),
	ENUM_SET(bt_terminal_message_type, BackendOperation, 3),
ENUM_END
ENUM_TYPE(bt_terminal_message_type);

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

ENUM_START(bt_terminal_backend_operation_type)
	ENUM_SET(bt_terminal_backend_operation_type, DisplayRead, 0),
	ENUM_SET(bt_terminal_backend_operation_type, DisplayWrite, 1),
	ENUM_SET(bt_terminal_backend_operation_type, DisplaySeek, 2),
	ENUM_SET(bt_terminal_backend_operation_type, ShowPointer, 3),
	ENUM_SET(bt_terminal_backend_operation_type, HidePointer, 4),
	ENUM_SET(bt_terminal_backend_operation_type, GetPointerVisibility, 5),
	ENUM_SET(bt_terminal_backend_operation_type, SetPointerBitmap, 6),
	ENUM_SET(bt_terminal_backend_operation_type, GetPointerInfo, 7),
	ENUM_SET(bt_terminal_backend_operation_type, SetPointerAutohide, 8),
	ENUM_SET(bt_terminal_backend_operation_type, FreezePointer, 9),
	ENUM_SET(bt_terminal_backend_operation_type, UnfreezePointer, 10),
	ENUM_SET(bt_terminal_backend_operation_type, SetTextColours, 11),
	ENUM_SET(bt_terminal_backend_operation_type, GetTextColours, 12),
	ENUM_SET(bt_terminal_backend_operation_type, GetScreenModeCount, 13),
	ENUM_SET(bt_terminal_backend_operation_type, SetScreenMode, 14),
	ENUM_SET(bt_terminal_backend_operation_type, GetScreenMode, 15),
	ENUM_SET(bt_terminal_backend_operation_type, GetCurrentScreenMode, 16),
	ENUM_SET(bt_terminal_backend_operation_type, SetScreenScroll, 17),
	ENUM_SET(bt_terminal_backend_operation_type, GetScreenScroll, 18),
	ENUM_SET(bt_terminal_backend_operation_type, SetTextAccessMode, 19),
	ENUM_SET(bt_terminal_backend_operation_type, GetPaletteEntry, 20),
	ENUM_SET(bt_terminal_backend_operation_type, ClearScreen, 21),
	ENUM_SET(bt_terminal_backend_operation_type, RegisterGlobalShortcut, 22),
	ENUM_SET(bt_terminal_backend_operation_type, IsActive, 23),
	ENUM_SET(bt_terminal_backend_operation_type, SetActive, 24),
	ENUM_SET(bt_terminal_backend_operation_type, Open, 25),
	ENUM_SET(bt_terminal_backend_operation_type, Close, 26),
	ENUM_SET(bt_terminal_backend_operation_type, SwitchTerminal, 27),
	ENUM_SET(bt_terminal_backend_operation_type, CanCreate, 28),
	ENUM_SET(bt_terminal_backend_operation_type, Refresh, 29),
ENUM_END
ENUM_TYPE(bt_terminal_backend_operation_type);

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

struct bt_terminal_backend_operation{
	bt_handle_t handle;
	ENUM_NAME(bt_terminal_backend_operation_type) type;
	size_t datasize;
	char data[];
};
BT_STRUCT_TYPE(bt_terminal_backend_operation);

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

#ifndef NO_TERMINAL_API

ENUM_START(bt_terminal_api)
	ENUM_SET(bt_terminal_api, RegisterBackend, 0),
	ENUM_SET(bt_terminal_api, CreateTerminal, 1),
	ENUM_SET(bt_terminal_api, ReadBuffer, 2),
	ENUM_SET(bt_terminal_api, QueueEvent, 3),
	ENUM_SET(bt_terminal_api, TerminalRun, 4),
	ENUM_SET(bt_terminal_api, GetTerminalPos, 5),
	ENUM_SET(bt_terminal_api, GetTerminalTitle, 6),
ENUM_END
ENUM_TYPE(bt_terminal_api);

#if !defined(KERNEL) && !defined(KERNEL_MODULE)
#include <btos.h>

#define USE_BT_TERMINAL_API uint16_t bt_terminal_ext_id = 0
extern uint16_t bt_terminal_ext_id;

inline static void bt_terminial_init(){
	if(bt_terminal_ext_id == 0) bt_terminal_ext_id = bt_query_extension("TERMINAL");
}

inline static uint32_t bt_terminal_api_call(uint16_t fn, uint32_t b, uint32_t c, uint32_t d){
	bt_terminial_init();
	uint32_t a = (bt_terminal_ext_id << 16) + fn;
	return btos_call(a, b, c, d);
}

inline static bt_handle_t bt_terminal_create_backend(){
	return bt_terminal_api_call(ENUM_GET(bt_terminal_api, RegisterBackend), 0, 0, 0);
}

inline static bt_handle_t bt_terminal_create_terminal(bt_handle_t backend){
	return bt_terminal_api_call(ENUM_GET(bt_terminal_api, CreateTerminal), backend, 0, 0);
}

inline static void bt_terminal_read_buffer(bt_handle_t terminal, size_t size, uint8_t *buf){
	bt_terminal_api_call(ENUM_GET(bt_terminal_api, ReadBuffer), terminal, size, (uint32_t)buf);
}

inline static void bt_terminal_queue_event(bt_handle_t terminal, bt_terminal_event *event){
	bt_terminal_api_call(ENUM_GET(bt_terminal_api, QueueEvent), terminal, (uint32_t)event, 0);
}

inline static bt_pid_t bt_terminal_run(bt_handle_t terminal, const char *command){
	bt_pid_t ret;
	bt_terminal_api_call(ENUM_GET(bt_terminal_api, TerminalRun), terminal, (uint32_t)command, (uint32_t)&ret);
	return ret;
}

inline static size_t bt_terminal_get_pos(bt_handle_t terminal){
	return (size_t) bt_terminal_api_call(ENUM_GET(bt_terminal_api, GetTerminalPos), terminal, 0, 0);
}

inline static size_t bt_terminal_get_title(bt_handle_t terminal, size_t size, char *buf){
	return bt_terminal_api_call(ENUM_GET(bt_terminal_api, GetTerminalTitle), terminal, size, (uint32_t)buf);
}

#endif

#endif

#endif