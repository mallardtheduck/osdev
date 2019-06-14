#ifndef _PROGRESSBAR_HPP
#define _PROGRESSBAR_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class ProgressBar : public IDecorativeControl{
private:
	gds::Rect rect;
	int value;
	std::unique_ptr<gds::Surface> surf;
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
