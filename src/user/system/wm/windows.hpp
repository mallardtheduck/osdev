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
void DrawWindows(const gds::Rect &r = gds::Rect(), uint64_t above = 0, bool ignoreGrab = false);
void DrawWindows(const std::vector<gds::Rect> &v, uint64_t above = 0);
void HandleInput(const bt_terminal_event &event);
void RefreshScreen(gds::Rect r = gds::Rect());
void RefreshScreen(const std::vector<gds::Rect> &v);
void DrawAndRefreshWindows(const gds::Rect &r = gds::Rect(), uint64_t above = 0);
void DrawAndRefreshWindows(const std::vector<gds::Rect> &v);
void WindowGrab(uint64_t id);
void UnGrab();
void BringToFront(std::shared_ptr<Window> win);

#endif
