#ifndef _LISTBOX_HPP
#define _LISTBOX_HPP

#include "icontrol.hpp"
#include "scrollbar.hpp"
#include "checkbox.hpp"

#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{
	
struct ListBoxImpl;
PIMPL_CLASS(ListBoxImpl);

class ListBox : public IValueControl<size_t>{
private:
	btos::pimpl_ptr<ListBoxImpl> im;
public:
	ListBox(const gds::Rect &r, bool scrollHoriz = false, bool multiSelect = false);
	
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
	
	size_t GetValue() override;
	void SetValue(size_t idx);
	std::vector<bool> &MulitSelections();
	
	std::vector<std::string> &Items();
	void Refresh();
};
	
}
}

#endif