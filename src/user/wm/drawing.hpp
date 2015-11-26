#ifndef DRAWING_HPP
#define DRAWING_HPP

#include <string>
#include "window.hpp"

uint64_t DrawTitleBar(uint32_t w, std::string title, bool active, WindowArea pressed = WindowArea::None);
void DrawBorder(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const Rect &bounds = {0, 0, INT32_MAX, INT32_MAX});

#endif