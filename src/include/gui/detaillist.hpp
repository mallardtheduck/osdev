#ifndef _DETAILLIST_HPP
#define _DETAILLIST_HPP

#include "icontrol.hpp"
#include "scrollbar.hpp"

#include<util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{
	
struct DetailListImpl;
PIMPL_CLASS(DetailListImpl);

class DetailList : public IValueControl<size_t>{
private:
	btos::pimpl_ptr<DetailListImpl> im;
public:
	DetailList(const gds::Rect &r, const std::vector<std::string> &cols, bool scrollHoriz = false, size_t iconsize = 0, bool multiSelect = false);
	
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
	
	std::vector<std::vector<std::string>> &Items();
	std::vector<std::string> &Columns();
	std::vector<uint32_t> &ColumnWidths();
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