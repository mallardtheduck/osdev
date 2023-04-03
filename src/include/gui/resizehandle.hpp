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
	
	bool GetValue();
	
	size_t GetZOrder();
};

}
}

#endif
