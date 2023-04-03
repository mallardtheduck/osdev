#ifndef _SLIDER_HPP
#define _SLIDER_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct SliderImpl;
PIMPL_CLASS(SliderImpl);
	
class Slider : public IValueControl<int32_t>{
private:
	btos::pimpl_ptr<SliderImpl> im;
public:
	Slider(const gds::Rect &r, int32_t min, int32_t max, int32_t def, int32_t snapTo = 1);
	
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
	void SetPosition(const gds::Rect&);
	
	int32_t GetValue();
};
	
}
}

#endif
