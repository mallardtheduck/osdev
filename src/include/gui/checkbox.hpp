#ifndef _CHECKBOX_HPP
#define _CHECKBOX_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class Checkbox : public IValueControl<bool> {
private:
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> surf;
	std::unique_ptr<gds::Surface> bkSurf;
	
	bool value;
	gds::TextMeasurements textMeasures;
	bool update = false;
	bool focus = false;
	bool enabled = true;
public:
	Checkbox(const gds::Rect &r, const std::string &t, bool v);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	uint32_t GetFlags();
	void Enable();
	void Disable();
	bool IsEnabled();
	void SetPosition(const gds::Rect&);
	
	void SetText(const std::string &t);
	bool GetValue();
	void SetValue(bool v);
};

}
}

#endif
