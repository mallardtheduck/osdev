#ifndef _SCROLLBAR_HPP
#define _SCROLLBAR_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class Scrollbar : public IControl{
private:
	gds::Rect rect;
	
	uint32_t lines, step, page, value;
	bool horiz;
	bool focus = false;
	bool update = false;
	
	bool topBtnDown = false;
	bool btmBtnDown = false;
	bool grabbed = false;
	
	std::shared_ptr<gds::Surface> surf;
	std::shared_ptr<gds::Surface> bkSurf;
	
	std::function<void(uint32_t)> onChange;
public:
	Scrollbar(const gds::Rect &r, uint32_t lines, uint32_t step, uint32_t page, uint32_t value, bool horiz = false);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	
	void OnChange(const std::function<void(uint32_t)> &oC);
};

}
}

#endif