#ifndef _TREEVIEW_HPP
#define _TREEVIEW_HPP

#include "icontrol.hpp"
#include "scrollbar.hpp"
#include "checkbox.hpp"

#include <functional>

namespace btos_api{
namespace gui{

class TreeViewNode{
private:
	gds::TextMeasurements measures;
	size_t level = 0;
	
	friend class TreeView;
public:
	size_t id;
	std::string text;
	std::vector<TreeViewNode> children;
	std::shared_ptr<gds::Surface> icon;
	std::shared_ptr<gds::Surface> openIcon;
	bool open;
	
	std::function<void(TreeViewNode&)> onOpen;
	
	TreeViewNode(size_t id, const std::string &text, const std::vector<TreeViewNode> &children = {}, std::shared_ptr<gds::Surface> icon = nullptr, std::shared_ptr<gds::Surface> openIcon = nullptr, bool open = false);
	
	TreeViewNode(const TreeViewNode &) = default;
	TreeViewNode(TreeViewNode &&) = default;
	
	TreeViewNode& operator=(const TreeViewNode&) = default;
};

class TreeView : public IValueControl<TreeViewNode*>{
private:
	gds::Rect outerRect;
	gds::Rect rect; 
	std::unique_ptr<gds::Surface> surf;
	
	std::vector<TreeViewNode> items;
	std::shared_ptr<gds::Surface> defaultIcon;
	std::shared_ptr<gds::Surface> defaultOpenIcon;
	
	size_t fontHeight;
	size_t iconSize;
	
	TreeViewNode *selectedItem = nullptr;
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
	void ForEachShown(const std::function<void(TreeViewNode&)> &fn);
	enum class MovePos{
		Offset, First, Last
	};
	void SelectionMove(int offset, MovePos pos = MovePos::Offset);
	void SelectByChar(char c);
	TreeViewNode *GetNodeByPos(uint32_t yPos);
	void ToggleNodeOpen(TreeViewNode &node);
	std::shared_ptr<gds::Surface> GetNodeIcon(const TreeViewNode &node);
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