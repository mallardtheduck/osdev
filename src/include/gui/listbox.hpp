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
	
	size_t GetValue();
	void SetValue(size_t idx);
	std::vector<bool> &MulitSelections();
	
	std::vector<std::string> &Items();
	void Refresh();
};
	
}
}

#endif