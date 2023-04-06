#ifndef _GROUPBOX_HPP
#define _GROUPBOX_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct GroupBoxImpl;
PIMPL_CLASS(GroupBoxImpl);

class GroupBox : public IDecorativeControl{
private:
	btos::pimpl_ptr<GroupBoxImpl> im;
public:
	GroupBox(const gds::Rect &r, const std::string &t);
	
	EventResponse HandleEvent(const wm_Event&) override;
	void Paint(gds::Surface &surf) override;
	gds::Rect GetPaintRect() override;
	gds::Rect GetInteractRect() override;
	uint32_t GetSubscribed() override;
	void SetPosition(const gds::Rect&) override;
	
	void SetText(const std::string &t);
};

}
}

#endif
