#ifndef _SLIDER_HPP
#define _SLIDER_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{
	
class Slider : public IControl{
private:
	gds::Rect rect;
	int32_t min;
	int32_t max;
	int32_t value;
	int32_t snapTo;
	
	std::function<void(int32_t)> onChange;
	
	bool update = false;
	bool focus = false;
	std::unique_ptr<gds::Surface> surf;
	std::unique_ptr<gds::Surface> bkSurf;
public:
	Slider(const gds::Rect &r, int32_t min, int32_t max, int32_t def, int32_t snapTo = 1);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &s);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	
	int32_t GetValue();
	void OnChange(const std::function<void(int32_t)> &oC);
};
	
}
}

#endif