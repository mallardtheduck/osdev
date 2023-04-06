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
	
	EventResponse HandleEvent(const wm_Event&) override;
	void Paint(gds::Surface &s) override;
	gds::Rect GetPaintRect() override;
	gds::Rect GetInteractRect() override;
	uint32_t GetSubscribed() override;
	void Focus() override;
	void Blur() override;
	uint32_t GetFlags() override;
	void Enable() override;
	void Disable() override;
	bool IsEnabled() override;
	void SetPosition(const gds::Rect&) override;
	
	int32_t GetValue() override;
};
	
}
}

#endif
