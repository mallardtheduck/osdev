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
	
	EventResponse HandleEvent(const wm_Event&) override;
	void Paint(gds::Surface &surf) override;
	gds::Rect GetPaintRect() override;
	gds::Rect GetInteractRect() override;
	uint32_t GetSubscribed() override;
	void SetPosition(const gds::Rect&) {}
	
	void SetText(const std::string &t);
};

}
}

#endif