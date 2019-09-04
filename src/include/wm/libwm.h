#ifndef _LIBWM_H
#define _LIBWM_H

#include <wm/wm.h>
#include <btos.h>
#include <dev/terminal.h>
#include <dev/video_dev.h>

#ifdef __cplusplus
#include <string>
#include <vector>
extern "C"{
#endif

uint64_t WM_SelectWindow(uint64_t id);
uint64_t WM_CreateWindow(wm_WindowInfo info);
uint64_t WM_NewWindow(int32_t x, int32_t y, uint32_t options, uint32_t subscriptions, uint64_t gds_id, const char *title);
void WM_DestroyWindow();
wm_WindowInfo WM_WindowInfo();
void WM_Subscribe(uint32_t events);
void WM_Update();
void WM_UpdateRect(int32_t x, int32_t y, uint32_t w, uint32_t h);
void WM_ReplaceSurface(uint64_t gds_id);
void WM_MoveWindow(int32_t x, int32_t y);
void WM_ChangeOptions(uint32_t opts);
void WM_SetTitle(const char *title);
wm_Event WM_GetEvent();
BTOS_API_NS bt_msg_filter WM_GetEventFilter();
wm_Event WM_ParseMessage(BTOS_API_NS bt_msg_header *msg);
void WM_Sync();

uint64_t WM_SelectMenu(uint64_t id);
uint64_t WM_CreateMenu();
void WM_DestroyMenu(uint64_t id);
uint32_t WM_AddMenuItem(wm_MenuItem i);
void WM_RemoveMenuItem(uint32_t id);
void WM_ShowMenu(wm_Rect pos);
void WM_SelectWindowMenu();
void WM_SetWindowMenu();
void WM_UnSetWindowMenu();
void WM_StartResize();
void WM_StartDrag();

bt_terminal_pointer_info WM_GetPointerInfo();
bt_vidmode WM_GetScreenMode();

void WM_SetModal(uint64_t id);
void WM_ClearModal();

size_t WM_GetValidWindowIDs(uint64_t *buf, size_t size);
void WM_RaiseWindow();

#ifdef __cplusplus
}

void WM_UpdateRect(wm_Rect r);
void WM_SetTitle(const std::string title);
std::vector<uint64_t> WM_GetValidWindowIDs();
#endif

#endif
