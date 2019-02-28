#ifndef _CHECKBOX_HPP
#define _CHECKBOX_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class Checkbox : public IControl{
private:
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> surf;
	std::unique_ptr<gds::Surface> bkSurf;
	
	bool value;
	gds::TextMeasurements textMeasures;
	bool update = false;
	bool focus = false;
	
	std::function<void(bool)> onChange;
public:
	Checkbox(const gds::Rect &r, const std::string &t, bool v);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	
	void SetText(const std::string &t);
	bool GetValue();
	
	void OnChange(const std::function<void(bool)> &oC);
};

}
}

#endif
