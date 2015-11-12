#ifndef _WINDOWS_HPP
#define _WINDOWS_HPP

#include "window.hpp"
#include <terminal.h>
#include <memory>

uint64_t AddWindow(std::shared_ptr<Window> win);
void RemoveWindow(uint64_t id);
std::shared_ptr<Window> GetWindow(uint64_t id);
std::shared_ptr<Window> GetActiveWindow();
void DrawWindows();
void HandleInput(const bt_terminal_event &event);
void RefreshScreen(const Rect &r = Rect());
void WindowGrab(uint64_t id);
void UnGrab();

#endif