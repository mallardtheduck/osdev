#ifndef _LISTBOX_HPP
#define _LISTBOX_HPP

#include "icontrol.hpp"
#include "scrollbar.hpp"

namespace btos_api{
namespace gui{
	
class ListBox : public IValueControl<size_t>{
private:
	gds::Rect outerRect;
	gds::Rect rect; 
	std::unique_ptr<gds::Surface> surf;
	
	std::vector<std::string> items;
	
	size_t fontHeight;
	
	size_t itemHeight;
	size_t selectedItem = 0;
	size_t vOffset = 0;
	size_t hOffset = 0;
	
	bool update = false;
	bool hasFocus = false;
	
	std::unique_ptr<Scrollbar> hscroll;
	std::unique_ptr<Scrollbar> vscroll;
	
	bool scrollHoriz;
public:
	ListBox(const gds::Rect &r, bool scrollHoriz = false);
	
	EventResponse HandleEvent(const wm_Event&);
	void Paint(gds::Surface &surf);
	gds::Rect GetPaintRect();
	gds::Rect GetInteractRect();
	uint32_t GetSubscribed();
	void Focus();
	void Blur();
	uint32_t GetFlags();
	
	size_t GetValue();
	void SetValue(size_t idx);
	
	std::vector<std::string> &Items();
};
	
}
}

#endif