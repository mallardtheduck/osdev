#ifndef _BUTTON_HPP
#define _BUTTON_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class Button : public IActionControl<void>{
private:
	bool down = false;
	bool focus = false;
	bool enabled = true;
	bool paintDown;
	bool paintFocus;

	gds::Rect rect;
	std::string label;
	
	std::unique_ptr<gds::Surface> surf;
	std::unique_ptr<gds::Surface> bkSurf;
	gds::TextMeasurements labelMeasures;
	
public:
	Button(const gds::Rect &r, const std::string &l);

	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &s);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	uint32_t GetFlags();
	void Enable();
	void Disable();
	bool IsEnabled();
};

}
}

#endif
