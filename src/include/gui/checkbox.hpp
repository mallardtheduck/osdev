#ifndef _CHECKBOX_HPP
#define _CHECKBOX_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct CheckboxImpl;
PIMPL_CLASS(CheckboxImpl);

class Checkbox : public IValueControl<bool> {
private:
	btos::pimpl_ptr<CheckboxImpl> impl;
public:
	Checkbox(const gds::Rect &r, const std::string &t, bool v);
	
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
	
	void SetText(const std::string &t);
	bool GetValue() override;
	void SetValue(bool v);
};

}
}

#endif
