#ifndef _STATUSBAR_HPP
#define _STATUSBAR_HPP

#include <gui/icontrol.hpp>

namespace btos_api{
namespace gui{

class StatusBar : public IDecorativeControl{
private:
	gds::Rect rect;
	std::string text;
	std::unique_ptr<gds::Surface> surf;
	
	uint32_t height;
public:
	StatusBar(const std::string &t);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	
	void SetText(const std::string &t);
};

}
}

#endif