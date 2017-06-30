#ifndef _TERMINAL_IOCTL_H
#define _TERMINAL_IOCTL_H

#include <btos.h>
#include <dev/terminal.h>
#include <dev/video_dev.h>

NS_BEGIN(btos_api)

EXTERN_C void bt_term_handle(bt_handle_t handle);
EXTERN_C void bt_term_stdout();

EXTERN_C void bt_term_SetTerminalMode(ENUM_NAME(bt_terminal_mode) mode);
EXTERN_C ENUM_NAME(bt_terminal_mode) bt_term_GetTerminalMode();
EXTERN_C void bt_term_SetInfoLine(bool state);
EXTERN_C bool bt_term_GetInfoLine();
EXTERN_C void bt_term_SetTitle(const char *title);
EXTERN_C size_t bt_term_GetTitle(char *title, size_t size);
EXTERN_C void bt_term_SetEcho(bool state);
EXTERN_C bool bt_term_GetEcho();
EXTERN_C void bt_term_ShowPointer();
EXTERN_C void bt_term_HidePointer();
EXTERN_C bool bt_term_GetPointerVisibility();
EXTERN_C void bt_term_SetPointerBitmap(bt_terminal_pointer_bitmap *bitmap);
EXTERN_C bt_terminal_pointer_info bt_term_GetPointerInfo();
EXTERN_C void bt_term_StartEventMode();
EXTERN_C void bt_term_EndEventMode();
EXTERN_C void bt_term_SetEventMode(ENUM_NAME(bt_terminal_event_mode) mode);
EXTERN_C void bt_term_PointerAutoHide(bool state);
EXTERN_C void bt_term_PointerFreeze();
EXTERN_C void bt_term_PointerUnfreeze();
EXTERN_C uint32_t bt_term_GetPointerSpeed();
EXTERN_C void bt_term_SetPointerSpeed(uint32_t speed);

EXTERN_C void bt_term_NewTerminal(const char *cmd);
EXTERN_C void bt_term_SwitchTerminal(uint32_t id);
EXTERN_C void bt_term_RegisterGlobalShortcut(uint16_t keycode);

EXTERN_C void bt_term_ClearScreen();
EXTERN_C size_t bt_term_GetScreenModeCount();
EXTERN_C bt_vidmode bt_term_GetScreenMode(size_t id);
EXTERN_C void bt_term_SetScreenMode(bt_vidmode mode);
EXTERN_C bt_vidmode bt_term_QueryScreenMode();
EXTERN_C bt_video_palette_entry bt_term_GetPaletteEntry(size_t idx);
EXTERN_C void bt_term_SetTextColours(uint8_t c);
EXTERN_C uint8_t bt_term_GetTextColours();
EXTERN_C bool bt_term_GetScrolling();
EXTERN_C void bt_term_SetScrolling(bool s);

NS_END


#endif
