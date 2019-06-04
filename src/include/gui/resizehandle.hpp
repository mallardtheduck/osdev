#ifndef _RESIZEHANDLE_HPP
#define _RESIZEHANDLE_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class ResizeHandle : public IActionControl<void>{
private:
	bool down = false;
	bool enabled = true;
	bool paintDown;

	gds::Rect rect;
	
	std::unique_ptr<gds::Surface> surf;
	std::unique_ptr<gds::Surface> bkSurf;
	gds_SurfaceInfo info;
	
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
	
	bool GetValue();
	
	size_t GetZOrder();
};

}
}

#endif
