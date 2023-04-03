#ifndef _IMAGEBUTTON_HPP
#define _IMAGEBUTTON_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct ImageButtonImpl;
PIMPL_CLASS(ImageButtonImpl);

class ImageButton : public IActionControl<void>{
private:
	btos::pimpl_ptr<ImageButtonImpl> im;	
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
