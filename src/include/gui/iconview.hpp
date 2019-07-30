#ifndef _ICONVIEW_HPP
#define _ICONVIEW_HPP

#include "icontrol.hpp"
#include "scrollbar.hpp"
#include "checkbox.hpp"

namespace btos_api{
namespace gui{
	
class IconView : public IValueControl<size_t>{
private:
	gds::Rect outerRect;
	gds::Rect rect; 
	std::unique_ptr<gds::Surface> surf;
	
	std::vector<std::string> items;
	std::vector<bool> multiSelection;
	
	struct DrawItem{
		std::string text;
		gds::TextMeasurements measures1;
		gds::TextMeasurements measures2;
		std::string fittedText1;
		std::string fittedText2;
		uint32_t fittedWidth;
	};
	
	std::vector<DrawItem> drawItems;
	std::shared_ptr<gds::Surface> defaultIcon;
	std::vector<std::shared_ptr<gds::Surface>> icons;
	
	size_t fontHeight;
	size_t iconSize;
	
	size_t itemWidth, itemHeight;
	size_t selectedItem = 0;
	size_t vOffset = 0;
	size_t visibleLines = 0;
	size_t visibleCols = 0;
	
	bool update = false;
	bool hasFocus = false;
	bool enabled = true;
	bool fireCurrentSelection = true;
	
	std::unique_ptr<Scrollbar> vscroll;
	
	bool multiSelect;
	
	std::function<void()> onActivate;
	std::function<void()> onInspect;
	
	void UpdateDisplayState(bool changePos = true);
	void FitTextToWidth(DrawItem &item, size_t width);
public:
	IconView(const gds::Rect &r, size_t iconSize = 32, bool multiSelect = false);
	
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
	
	void SetDefaultIcon(std::shared_ptr<gds::Surface> img);
	void SetItemIcon(size_t idx, std::shared_ptr<gds::Surface> img);
	void ClearItemIcons();
	
	void OnActivate(std::function<void()> fn);
	void OnInspect(std::function<void()> fn);
};
	
}
}

#endif