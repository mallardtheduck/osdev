#ifndef _PROGRESSBAR_HPP
#define _PROGRESSBAR_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct ProgressBarImpl;
PIMPL_CLASS(ProgressBarImpl);

class ProgressBar : public IDecorativeControl{
private:
	btos::pimpl_ptr<ProgressBarImpl> im;
public:
	ProgressBar(const gds::Rect &r, int value);
	
	EventResponse HandleEvent(const wm_Event&) override;
	void Paint(gds::Surface &surf) override;
	gds::Rect GetPaintRect() override;
	gds::Rect GetInteractRect() override;
	uint32_t GetSubscribed() override;
	void SetPosition(const gds::Rect&) override;
	
	void SetValue(int value);
};

}
}

#endif
