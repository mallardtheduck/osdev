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
};

}
}

#endif
