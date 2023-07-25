#ifndef _RESIZEHANDLE_HPP
#define _RESIZEHANDLE_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct ResizeHandleImpl;
PIMPL_CLASS(ResizeHandleImpl);

class ResizeHandle : public IActionControl<void>{
private:
	btos::pimpl_ptr<ResizeHandleImpl> im;	
public:
	ResizeHandle(const gds::Rect &r);

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
	
	bool GetValue();
	
	size_t GetZOrder();
};

}
}

#endif
