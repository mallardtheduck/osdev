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

	EventResponse HandleEvent(const wm_Event&) override;
	void Paint(gds::Surface &surf) override;
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
	
	void Paint(const std::vector<gds::Rect> &rects) override;
};
	
}
}

#endif
