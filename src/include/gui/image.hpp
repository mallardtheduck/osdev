#ifndef _IMAGE_HPP
#define _IMAGE_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class Image : public IDecorativeControl{
private:
	gds::Rect rect;
	std::unique_ptr<gds::Surface> surf;
	std::shared_ptr<gds::Surface> img;
public:
	Image(const gds::Rect &r, std::shared_ptr<gds::Surface> img);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
};

}
}

#endif
