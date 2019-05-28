#ifndef _DETAILLIST_HPP
#define _DETAILLIST_HPP

#include "icontrol.hpp"
#include "scrollbar.hpp"

namespace btos_api{
namespace gui{
	
class DetailList : public IValueControl<size_t>{
private:
	gds::Rect outerRect;
	gds::Rect rect; 
	std::unique_ptr<gds::Surface> surf;
	
	std::vector<std::vector<std::string>> items;
	std::vector<std::shared_ptr<gds::Surface>> icons;
	std::vector<std::string> cols;
	
	struct DrawItem{
		std::string text;
		gds::TextMeasurements measures;
		std::string fittedText;
		uint32_t fittedWidth;
	};
	
	std::vector<std::vector<DrawItem>> drawItems;
	std::vector<uint32_t> colWidths;
	std::vector<DrawItem> colItems;
	
	std::shared_ptr<gds::Surface> defaultIcon;
	
	size_t fontHeight;
	
	size_t itemHeight;
	size_t selectedItem = 0;
	size_t vOffset = 0;
	size_t hOffset = 0;
	size_t visibleItems = 0;
	size_t iconsize = 0;
	
	bool update = false;
	bool hasFocus = false;
	bool enabled = true;
	
	std::unique_ptr<Scrollbar> hscroll;
	std::unique_ptr<Scrollbar> vscroll;
	
	bool scrollHoriz;
	
	void UpdateDisplayState(bool changePos = true);
	void CalculateColumnWidths();
	std::string FitTextToCol(DrawItem &item, size_t colIndex);
public:
	DetailList(const gds::Rect &r, const std::vector<std::string> &cols, bool scrollHoriz = false, size_t iconsize = 0);
	
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
	
	size_t GetValue();
	void SetValue(size_t idx);
	
	std::vector<std::vector<std::string>> &Items();
	std::vector<std::string> &Columns();
	std::vector<uint32_t> &ColumnWidths();
	void Refresh();
	
	void SetDefaultIcon(std::shared_ptr<gds::Surface> img);
	void SetItemIcon(size_t idx, std::shared_ptr<gds::Surface> img);
	void ClearItemIcons();
};
	
}
}

#endif