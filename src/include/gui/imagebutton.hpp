#ifndef _IMAGEBUTTON_HPP
#define _IMAGEBUTTON_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class ImageButton : public IActionControl<void>{
private:
	bool down = false;
	bool focus = false;
	bool enabled = true;
	bool paintDown;
	bool paintFocus;

	gds::Rect rect;
	
	std::unique_ptr<gds::Surface> surf;
	std::unique_ptr<gds::Surface> bkSurf;
	std::shared_ptr<gds::Surface> img;
	gds_SurfaceInfo info;
	
public:
	ImageButton(const gds::Rect &r, std::shared_ptr<gds::Surface> img);

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
};

}
}

#endif
