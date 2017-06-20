#ifndef _WINDOWS_HPP
#define _WINDOWS_HPP

#include "window.hpp"
#include <dev/terminal.h>
#include <memory>

class Window;

void InitWindws();

uint64_t AddWindow(std::shared_ptr<Window> win);
void RemoveWindow(uint64_t id);
std::shared_ptr<Window> GetWindow(uint64_t id);
std::shared_ptr<Window> GetActiveWindow();
void DrawWindows(const Rect &r = Rect(), uint64_t above = 0, bool ignoreGrab = false);
void DrawWindows(const std::vector<Rect> &v);
void HandleInput(const bt_terminal_event &event);
void RefreshScreen(Rect r = Rect());
void RefreshScreen(const std::vector<Rect> &v);
void DrawAndRefreshWindows(const Rect &r = Rect(), uint64_t above = 0);
void DrawAndRefreshWindows(const std::vector<Rect> &v);
void WindowGrab(uint64_t id);
void UnGrab();
void BringToFront(std::shared_ptr<Window> win);

#endif
