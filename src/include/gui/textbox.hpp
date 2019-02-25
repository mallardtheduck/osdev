#ifndef _TEXTBOX_HPP
#define _TEXTBOX_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class TextBox : public IControl{
private:
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> surf;
	
	std::function<void()> onChange;
	std::function<bool(uint32_t)> onKeyPress;
	
	gds::TextMeasurements textMeasures;
	
	bool update = false;
	size_t textOffset = 0;
	size_t cursorPos = 0;
	bool hasFocus = false;
	int32_t textY = 0;
	
	void UpdateDisplayState();
public:
	TextBox(gds::Rect r, const std::string &t);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	
	void SetText(const std::string &t);
	std::string GetText();
	
	void OnChange(const std::function<void()> &oC);
	void OnKeyPress(const std::function<bool(uint32_t)> &oKP);
};

}
}

#endif
