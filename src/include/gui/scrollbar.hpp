#ifndef _SCROLLBAR_HPP
#define _SCROLLBAR_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class Scrollbar : public IValueControl<uint32_t>{
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
public:
	Scrollbar(const gds::Rect &r, uint32_t lines, uint32_t step, uint32_t page, uint32_t value, bool horiz = false);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	uint32_t GetFlags();
	
	void SetLines(uint32_t l);
	void SetStep(uint32_t s);
	void SetPage(uint32_t p);
	void SetValue(uint32_t v);
	uint32_t GetValue();
};

}
}

#endif
