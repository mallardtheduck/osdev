#ifndef _LIBWM_H
#define _LIBWM_H

#include <wm/wm.h>

#ifdef __cplusplus
#include <string>
extern "C"{
#endif

uint64_t WM_SelectWindow(uint64_t id);
uint64_t WM_CreateWindow(wm_WindowInfo info);
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

#ifdef __cplusplus
}

void WM_UpdateRect(wm_Rect r);
void WM_SetTitle(const std::string title);
#endif

#endif