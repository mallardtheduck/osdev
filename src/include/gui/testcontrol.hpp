#ifndef _TESTCONTROL_HPP
#define _TESTCONTROL_HPP

#include "icontrol.hpp"

namespace btos_api{
namespace gui{

class TestControl : public IControl{
private:
	gds::Rect rect;
	
	std::function<bool(const wm_Event&)> onEvent;
public:
	TestControl(const gds::Rect &r);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	uint32_t GetFlags();
	void Enable();
	void Disable();
	bool IsEnabled();
	void SetPosition(const gds::Rect&);
	
	void OnEvent(const std::function<bool(const wm_Event&)> &oE);
};

}
}

#endif
