#ifndef _STATUSBAR_HPP
#define _STATUSBAR_HPP

#include <gui/icontrol.hpp>
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

class StatusBarImpl;
PIMPL_CLASS(StatusBarImpl);

class StatusBar : public IDecorativeControl{
private:
	btos::pimpl_ptr<StatusBarImpl> im;
public:
	StatusBar(const std::string &t);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void SetPosition(const gds::Rect&) {}
	
	void SetText(const std::string &t);
};

}
}

#endif