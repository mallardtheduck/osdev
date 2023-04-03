#ifndef _IMAGE_HPP
#define _IMAGE_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct ImageImpl;
PIMPL_CLASS(ImageImpl);

class Image : public IDecorativeControl{
private:
	btos::pimpl_ptr<ImageImpl> im;
public:
	Image(const gds::Rect &r, std::shared_ptr<gds::Surface> img);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void SetPosition(const gds::Rect&);
};

}
}

#endif
