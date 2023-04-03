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
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void SetPosition(const gds::Rect&);
	
	void SetText(const std::string &t);
};

}
}

#endif
