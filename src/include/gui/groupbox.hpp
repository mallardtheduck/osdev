#ifndef _GROUPBOX_HPP
#define _GROUPBOX_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class GroupBox : public IControl{
private:
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> surf;
	gds::TextMeasurements textMeasures;
	uint32_t textH;
public:
	GroupBox(const gds::Rect &r, const std::string &t);
	
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
