#ifndef DRAWING_HPP
#define DRAWING_HPP

#include <string>
#include <gds/surface.hpp>
#include <memory>
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
	std::shared_ptr<gds::Surface> gds_inactive_title;
	std::shared_ptr<gds::Surface> gds_active_title = 0;
	std::string title = "";
	uint32_t width = 0;
	WindowArea pressed = WindowArea::None;
	uint32_t window_options = 0;
	
public:
	std::shared_ptr<gds::Surface> Draw(uint32_t w, const std::string &t, bool active, uint32_t options, WindowArea p = WindowArea::None);
	
	~TitleBar();
};

void DrawBorder(gds::Surface &surf, const gds::Rect &r, const gds::Rect &bounds = {0, 0, INT32_MAX, INT32_MAX});
gds::Surface DrawMenuItem(const std::string &text, uint32_t flags, const gds::Surface *image, uint32_t width, bool selected);

#endif
