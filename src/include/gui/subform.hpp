#ifndef _SUBFORM_HPP
#define _SUBFORM_HPP

#include "container.hpp"
#include "icontrol.hpp"

namespace btos_api{
namespace gui{

struct SubFormImpl;
PIMPL_CLASS(SubFormImpl);

class SubForm : public Container, public IControl{
private:
	btos::pimpl_ptr<SubFormImpl> im;
	
	gds::Surface &GetSurface() override;
	gds::Rect GetBoundingRect() override;

	void Update(const gds::Rect &r) override;
	void Update() override;
	void SetSubscribed(uint32_t subs) override;
	bool OnLastControlFocus(bool reverse) override;
public:
	SubForm(const gds::Rect &r);

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
	
	void Paint(const std::vector<gds::Rect> &rects);
};
	
}
}

#endif
