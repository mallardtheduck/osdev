#ifndef _LISTBOX_HPP
#define _LISTBOX_HPP

#include "icontrol.hpp"
#include "scrollbar.hpp"
#include "checkbox.hpp"

namespace btos_api{
namespace gui{
	
class ListBox : public IValueControl<size_t>{
private:
	gds::Rect outerRect;
	gds::Rect rect; 
	std::unique_ptr<gds::Surface> surf;
	
	std::vector<std::string> items;
	std::vector<bool> multiSelection;
	
	struct DrawItem{
		std::string text;
		gds::TextMeasurements measures;
	};
	
	std::vector<DrawItem> drawItems;
	
	size_t fontHeight;
	
	size_t selectedItem = 0;
	size_t vOffset = 0;
	size_t hOffset = 0;
	size_t visibleItems = 0;
	
	bool update = false;
	bool hasFocus = false;
	bool enabled = true;
	
	std::unique_ptr<Scrollbar> hscroll;
	std::unique_ptr<Scrollbar> vscroll;
	
	bool scrollHoriz;
	bool multiSelect;
	
	void UpdateDisplayState(bool changePos = true);
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