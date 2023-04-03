#ifndef _TABS_HPP
#define _TABS_HPP

#include "icontrol.hpp"
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct Tab{
private:
	gds::TextMeasurements labelMeasures = gds::TextMeasurements();
	friend class Tabs;
public:
	std::string label;
	std::shared_ptr<IControl> content;
	
	Tab(const std::string &l, std::shared_ptr<IControl> c) : label(l), content(c) {}
	
	Tab() = default;
	Tab(const Tab&) = default;
	Tab(Tab&&) = default;
};

struct TabsImpl;
PIMPL_CLASS(TabsImpl);

class Tabs : public IActionControl<void>{
private:
	friend struct TabsImpl;
	btos::pimpl_ptr<TabsImpl> im;
public:
	Tabs(const gds::Rect &r);

	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &s);
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
	
	void OnBind();
	
	std::vector<Tab> &TabItems();
	void Refresh();
	
	gds::Rect GetContentRect();
};

}
}

#endif
