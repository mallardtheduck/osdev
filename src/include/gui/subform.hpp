#ifndef _SUBFORM_HPP
#define _SUBFORM_HPP

#include "container.hpp"
#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class SubForm : public Container, public IControl{
private:
	gds::Rect rect;
	std::unique_ptr<gds::Surface> surf;
	
	uint32_t subs;
	std::vector<gds::Rect> updateRects;
	
	gds::Surface &GetSurface();
	gds::Rect GetBoundingRect();
	
	void Update(const gds::Rect &r);
	void Update();
	void SetSubscribed(uint32_t subs);
public:
	SubForm(const gds::Rect &r);

	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	uint32_t GetFlags();
	
	void Paint(const std::vector<gds::Rect> &rects);
};
	
}
}

#endif
