#ifndef DRAWING_HPP
#define DRAWING_HPP

#include <string>

void DrawTitleBar(uint32_t x, uint32_t y, uint32_t w, std::string title, bool active);
void DrawBorder(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

#endif