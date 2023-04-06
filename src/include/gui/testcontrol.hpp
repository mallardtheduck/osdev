#ifndef _TESTCONTROL_HPP
#define _TESTCONTROL_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct TestControlImpl;
PIMPL_CLASS(TestControlImpl);

class TestControl : public IControl{
private:
	btos::pimpl_ptr<TestControlImpl> im;
public:
	TestControl(const gds::Rect &r);
	
	EventResponse HandleEvent(const wm_Event&) override;
	void Paint(gds::Surface &surf) override;
	gds::Rect GetPaintRect() override;
	gds::Rect GetInteractRect() override;
	uint32_t GetSubscribed() override;
	void Focus() override;
	void Blur() override;
	uint32_t GetFlags() override;
	void Enable() override;
	void Disable() override;
	bool IsEnabled() override;
	void SetPosition(const gds::Rect&) override;
	
	void OnEvent(const std::function<bool(const wm_Event&)> &oE);
};

}
}

#endif
