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
};

}
}

#endif
