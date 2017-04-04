#ifndef DRAWING_HPP
#define DRAWING_HPP

#include <string>
#include "rect.hpp"

void InitDrawing();

enum class WindowArea{
	Content,
	Title,
	MenuButton,
	CloseButton,
	HideButton,
	ExpandButton,
	Border,
	None
};

class TitleBar{
private:
	uint64_t gds_inactive_title = 0;
	uint64_t gds_active_title = 0;
	std::string title = "";
	uint32_t width = 0;
	WindowArea pressed = WindowArea::None;
	
public:
	uint64_t Draw(uint32_t w, const std::string &t, bool active, WindowArea p = WindowArea::None);
	
	~TitleBar();
};

void DrawBorder(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const Rect &bounds = {0, 0, INT32_MAX, INT32_MAX});
uint64_t DrawMenuItem(const std::string &text, uint32_t flags, uint64_t image, uint32_t width, bool selected);

#endif
