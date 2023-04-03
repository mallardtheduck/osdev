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
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void SetPosition(const gds::Rect&);
	
	void SetValue(int value);
};

}
}

#endif
