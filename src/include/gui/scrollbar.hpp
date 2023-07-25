#ifndef _SCROLLBAR_HPP
#define _SCROLLBAR_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct ScrollbarImpl;
PIMPL_CLASS(ScrollbarImpl);

class Scrollbar : public IValueControl<uint32_t>{
private:
	btos::pimpl_ptr<ScrollbarImpl> im;
public:
	Scrollbar(const gds::Rect &r, uint32_t lines, uint32_t step, uint32_t page, uint32_t value, bool horiz = false);
	
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
	
	void SetLines(uint32_t l);
	void SetStep(uint32_t s);
	void SetPage(uint32_t p);
	void SetValue(uint32_t v);
	uint32_t GetValue() override;
	
	void Refresh();
};

}
}

#endif
