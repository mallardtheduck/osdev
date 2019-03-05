#ifndef _TEXTAREA_HPP
#define _TEXTAREA_HPP

#include "icontrol.hpp"
#include "scrollbar.hpp"

namespace btos_api{
namespace gui{

class TextArea : public IControl{
private:
	gds::Rect rect;
	std::unique_ptr<gds::Surface> surf;
	
	std::function<void(const std::string &)> onChange;
	std::function<bool(uint32_t)> onKeyPress;
	
	struct Line{
		std::string text;
		gds::TextMeasurements textMeasures;
	};
	
	size_t fontHeight;
	
	std::vector<Line> lines;
	
	size_t cursorLine = 0;
	size_t lineOffset = 0;
	
	size_t textOffset = 0;
	uint32_t textOffsetPxls = 0;
	size_t cursorPos = 0;
	uint32_t cursorPosPxls = 0;
	
	bool update = false;
	bool hasFocus = false;
	
	std::unique_ptr<Scrollbar> hscroll;
	std::unique_ptr<Scrollbar> vscroll;
	
	void UpdateDisplayState();
	size_t MapPosToLine(uint32_t pxlPos, const Line &line);
public:
	TextArea(const gds::Rect &r, const std::string &t);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	
	void SetText(const std::string &t);
	std::string GetText();
	
	void OnChange(const std::function<void(const std::string &)> &oC);
	void OnKeyPress(const std::function<bool(uint32_t)> &oKP);
};

}
}

#endif
