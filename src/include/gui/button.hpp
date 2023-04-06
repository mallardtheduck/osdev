#ifndef _BUTTON_HPP
#define _BUTTON_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct ButtonImpl;
PIMPL_CLASS(ButtonImpl);

class Button : public IActionControl<void>{
private:
	btos::pimpl_ptr<ButtonImpl> impl;
public:
	Button(const gds::Rect &r, const std::string &l);

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
};

}
}

#endif
