#ifndef _TREEVIEW_HPP
#define _TREEVIEW_HPP

#include "icontrol.hpp"
#include "scrollbar.hpp"
#include "checkbox.hpp"

#include <functional>
#include <util/pimpl_ptr.hpp>

namespace btos_api{
namespace gui{

struct TreeViewImpl;
PIMPL_CLASS(TreeViewImpl);

class TreeViewNode{
private:
	gds::TextMeasurements measures;
	size_t level = 0;
	
	friend class TreeView;
	friend class TreeViewImpl;
public:
	size_t id;
	std::string text;
	std::vector<TreeViewNode> children;
	std::shared_ptr<gds::Surface> icon;
	std::shared_ptr<gds::Surface> openIcon;
	bool open;
	
	std::function<void(TreeViewNode&)> onOpen;
	
	TreeViewNode(size_t id, const std::string &text, const std::vector<TreeViewNode> &children = {}, std::shared_ptr<gds::Surface> icon = nullptr, std::shared_ptr<gds::Surface> openIcon = nullptr, bool open = false);
	
	TreeViewNode() = default;
	TreeViewNode(const TreeViewNode &) = default;
	TreeViewNode(TreeViewNode &&) = default;
	
	TreeViewNode& operator=(const TreeViewNode&) = default;
};

class TreeView : public IValueControl<TreeViewNode*>{
private:
	btos::pimpl_ptr<TreeViewImpl> im;
public:
	TreeView(const gds::Rect &r, bool scrollHoriz = false, size_t iconSize = 16);
	
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
	
	TreeViewNode *GetValue();
	void SetValue(TreeViewNode *node);
	
	std::vector<TreeViewNode> &Items();
	void Refresh();
	
	void SetDefaultIcon(std::shared_ptr<gds::Surface> icon);
	void SetDefaultOpenIcon(std::shared_ptr<gds::Surface> icon);
};
	
}
}

#endif