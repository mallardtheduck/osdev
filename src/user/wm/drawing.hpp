#ifndef DRAWING_HPP
#define DRAWING_HPP

#include <string>
#include "window.hpp"

void DrawTitleBar(uint32_t x, uint32_t y, uint32_t w, std::string title, bool active, WindowArea pressed = WindowArea::None);
void DrawBorder(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

#endif