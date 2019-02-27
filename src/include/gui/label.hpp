#ifndef _LABEL_HPP
#define _LABEL_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class Label : public IControl{
private:
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> surf;
public:
	Label(const gds::Rect &r, const std::string &t);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	
	void SetText(const std::string &t);
};

}
}

#endif
