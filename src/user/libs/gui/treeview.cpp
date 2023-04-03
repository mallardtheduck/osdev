#include <gui/treeview.hpp>
#include <gui/defaults.hpp>
#include <gui/drawing.hpp>
#include <dev/keyboard.h>

#include <cctype>
#include <algorithm>
#include <stack>
#include <functional>

namespace btos_api{
namespace gui{
	
const auto scrollbarSize = 17;

struct TreeViewImpl{
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
};
PIMPL_IMPL(TreeViewImpl);

TreeViewNode::TreeViewNode(size_t i, const std::string &t, const std::vector<TreeViewNode> &c, std::shared_ptr<gds::Surface> ic, std::shared_ptr<gds::Surface> oI, bool o):
measures(), id(i), text(t), children(c), icon(ic), openIcon(oI), open(o)
{}

TreeView::TreeView(const gds::Rect &r, bool sH, size_t iS) : im(new TreeViewImpl()){
	im->outerRect = r; 
	im->rect = sH ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h};
	im->iconSize = iS; im->scrollHoriz = sH;
	auto info = fonts::GetTreeViewFont().Info();
	im->fontHeight = (info.maxH * fonts::GetTreeViewTextSize()) / info.scale;
	if(im->fontHeight < im->iconSize) im->fontHeight = im->iconSize;
	
	im->vscroll.reset(new Scrollbar({im->outerRect.x + (int32_t)im->outerRect.w - scrollbarSize, im->outerRect.y, scrollbarSize, im->outerRect.h - (im->scrollHoriz ? scrollbarSize : 0)}, 1, 1, 1, 1, false));
	
	im->vscroll->OnChange([this] (uint32_t v) {
		if(v != im->vOffset) im->update = true;
		im->vOffset = v;
	});
	
	if(im->scrollHoriz){
		im->hscroll.reset(new Scrollbar({im->outerRect.x, im->outerRect.y + (int32_t)im->outerRect.h - scrollbarSize, im->outerRect.w - scrollbarSize, scrollbarSize}, 1, 1, 1, 1, true));
		
		im->hscroll->OnChange([this] (uint32_t v) {
			if(v != im->hOffset) im->update = true;
			im->hOffset = v;
		});
	}
	
	im->UpdateDisplayState();
}

void TreeViewImpl::UpdateDisplayState(bool changePos){
	visibleItems = rect.h / fontHeight;
	
	uint32_t maxTextW = 0;
	int32_t shownItems = 0;
	bool selectionFound = false;
	ForEachShown([&](TreeViewNode &node){
		if(!node.measures.w){
			node.measures = surf->MeasureText(node.text, fonts::GetTreeViewFont(), fonts::GetTreeViewTextSize());
		}
		auto totalW = node.measures.w + ((node.level + 1) * iconSize);
		if(totalW > maxTextW) maxTextW = totalW;
		if(selectedItem == &node) selectionFound = true;
		++shownItems;
	});
	if(!selectionFound && !items.empty()) selectedItem = &items.front();
	
	if(vscroll){
		if(visibleItems < (uint32_t)shownItems){
			vscroll->Enable();
			vscroll->SetLines(std::max<int32_t>(shownItems - visibleItems, 1));
			vscroll->SetPage(visibleItems);
			vscroll->SetValue(vOffset);
		}else{
			vscroll->Disable();
			vscroll->SetLines(1);
			vscroll->SetPage(1);
			vscroll->SetValue(0);
			vOffset = 0;
		}
	}
	
	if(hscroll){
		if(maxTextW > rect.w - 1){
			hscroll->Enable();
		 	hscroll->SetLines(maxTextW - (rect.w - 1));
		 	hscroll->SetPage(rect.w - 1);
		 	hscroll->SetValue(hOffset);
		 	hscroll->SetStep(fonts::GetTreeViewTextSize() / 2);
		}else{
			hscroll->Disable();
			hscroll->SetLines(1);
			hscroll->SetPage(1);
			hscroll->SetValue(0);
			hOffset = 0;
		}
	}
	
	if(changePos){
		size_t vIndex = 0;
		ForEachShown([&](TreeViewNode &node){
			if(&node == selectedItem){
				if(vIndex < vOffset) vOffset = vIndex;
				if(vIndex >= vOffset + (visibleItems - 1)) vOffset = std::max<int32_t>(0, (int32_t)(vIndex - (visibleItems - 1)));
				auto totalW = node.measures.w + ((node.level + 1) * iconSize);
				if(totalW > rect.w || node.level * iconSize < hOffset) hOffset = node.level * iconSize;
				if(hOffset > maxTextW - (rect.w - 2)) hOffset = maxTextW - (rect.w - 2);
			}
			++vIndex;
		});
	}
}

void TreeViewImpl::ForEachShown(const std::function<void(TreeViewNode&)> &fn){
	std::stack<TreeViewNode *> nodes;
	std::for_each(items.rbegin(), items.rend(), [&](TreeViewNode &n){
		n.level = 0;
		nodes.push(&n);
	});
	while(!nodes.empty()){
		auto &node = *nodes.top();
		fn(node);
		nodes.pop();
		if(node.open){
			std::for_each(node.children.rbegin(), node.children.rend(), [&](TreeViewNode &n){
				n.level = node.level + 1;
				nodes.push(&n);
			});	
		}
	}
}

void TreeViewImpl::SelectionMove(int offset, MovePos pos){
	std::vector<TreeViewNode*> nodes;
	size_t selectedIndex;
	ForEachShown([&](TreeViewNode &n){
		nodes.push_back(&n);
		if(&n == selectedItem) selectedIndex = nodes.size() - 1;
	});
	if(pos == MovePos::Offset){
		if((int32_t)selectedIndex + offset < 0) selectedIndex = 0;
		else if(selectedIndex + offset > nodes.size() - 1) selectedIndex = nodes.size() - 1;
		else selectedIndex += offset;
		selectedItem = nodes[selectedIndex];
	}else if(pos == MovePos::First){
		selectedItem = nodes.front();
	}else if(pos == MovePos::Last){
		selectedItem = nodes.back();
	}
}

std::shared_ptr<gds::Surface> TreeViewImpl::GetNodeIcon(const TreeViewNode &node){
	if(node.open){
		if(node.openIcon) return node.openIcon;
		else if(node.icon) return node.icon;
		else return icons::GetTreeViewDefaultOpen();
	}else{
		if(node.icon) return node.icon;
		else if(!node.children.empty() || node.onOpen) return icons::GetTreeViewDefaultChildren();
		else return icons::GetTreeViewDefaultNoChildren();
	}
}

void TreeViewImpl::SelectByChar(char c){
	TreeViewNode *first = nullptr;
	TreeViewNode *newSel = nullptr;
	bool foundSelection = false;
	ForEachShown([&](TreeViewNode &n){
		if(!newSel && !n.text.empty() && tolower(n.text.front()) == c){
			if(!first) first = &n;
			if(foundSelection) newSel = &n;
		}
		if(&n == selectedItem) foundSelection = true;
	});
	if(newSel) selectedItem = newSel;
	else if(first) selectedItem = first;
}

TreeViewNode *TreeViewImpl::GetNodeByPos(uint32_t yPos){
	TreeViewNode *node = nullptr;
	size_t i = 0;
	ForEachShown([&](TreeViewNode &cItem){
		if(i >= vOffset && i < vOffset + visibleItems + 1){
			uint32_t itemY = ((i - vOffset) * fontHeight) + 1;
			if(itemY <= yPos && itemY + fontHeight > yPos) node = &cItem;
		}
		++i;
	});
	return node;
}

void TreeViewImpl::ToggleNodeOpen(TreeViewNode &node){
	if(node.open) node.open = false;
	else{
		if(node.onOpen) node.onOpen(node);
		if(!node.children.empty()) node.open = true;
	}
}

EventResponse TreeView::HandleEvent(const wm_Event &e){
	bool handled = false;
	if(e.type == wm_EventType::Keyboard && !(e.Key.code & KeyFlags::KeyUp)){
		uint16_t code = KB_code(e.Key.code);
		if(code == (KeyFlags::NonASCII | KeyCodes::DownArrow)){
			im->SelectionMove(1);
			im->update = true;
			handled = true;
			im->UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::UpArrow)){
			im->SelectionMove(-1);
			im->update = true;
			handled = true;
			im->UpdateDisplayState();
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp)){
			im->SelectionMove(-im->visibleItems);
			im->update = true;
			im->UpdateDisplayState();
			handled = true;
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown)){
			im->SelectionMove(im->visibleItems);
			im->update = true;
			im->UpdateDisplayState();
			handled = true;
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::Home)){
			im->SelectionMove(0, TreeViewImpl::MovePos::First);
			im->update = true;
			im->UpdateDisplayState();
			handled = true;
			RaiseChangeEvent();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::End)){
			im->SelectionMove(0, TreeViewImpl::MovePos::Last);
			im->update = true;
			im->UpdateDisplayState();
			handled = true;
			RaiseChangeEvent();
		}else if(!(code & KeyFlags::NonASCII)){
			char c = KB_char(e.Key.code);
			if(c == ' ' || c == '\n'){
				im->ToggleNodeOpen(*im->selectedItem);
			}else{
				c = std::tolower(c);
				im->SelectByChar(c);
				RaiseChangeEvent();
			}
			im->update = true;
			handled = true;
			im->UpdateDisplayState();
		}
	}else if(e.type & wm_PointerEvents){
		if(InRect(e.Pointer.x, e.Pointer.y, im->rect)){
			if(e.type == wm_EventType::PointerButtonUp){
				auto node = im->GetNodeByPos(e.Pointer.y - im->outerRect.y);
				if(node){
					im->selectedItem = node;
					auto ptrX = (e.Pointer.x - im->outerRect.x) + im->hOffset;
					if(ptrX > node->level * im->iconSize && ptrX < (node->level + 1) * im->iconSize){
						im->ToggleNodeOpen(*node);
					}
					im->update = true;
					RaiseChangeEvent();
				}
				handled = true;
				im->UpdateDisplayState();
			}
		}else if(im->hscroll && im->hscroll->IsEnabled() && InRect(e.Pointer.x, e.Pointer.y, im->hscroll->GetInteractRect()) && (e.type & im->hscroll->GetSubscribed())){
			auto ret = im->hscroll->HandleEvent(e);
			im->update = ret.IsFinishedProcessing();
			handled = handled || im->update;
		}else if(im->vscroll && im->vscroll->IsEnabled() && InRect(e.Pointer.x, e.Pointer.y, im->vscroll->GetInteractRect()) && (e.type & im->vscroll->GetSubscribed())){
			auto ret = im->vscroll->HandleEvent(e);
			im->update = ret.IsFinishedProcessing();
			handled = handled || im->update;
		}
	}
	if(im->update) IControl::Paint(im->outerRect);
	return {handled};
}

void TreeView::Paint(gds::Surface &s){
	if(im->update || !im->surf){
		if(!im->surf) im->surf.reset(new gds::Surface(gds_SurfaceType::Vector, im->rect.w, im->rect.h, 100, gds_ColourType::True));
		im->UpdateDisplayState(false);
		
		uint32_t inW = im->rect.w - 1;
		uint32_t inH = im->rect.h - 1;
		
		auto bkgCol = colours::GetBackground().Fix(*im->surf);
		auto txtCol = colours::GetTreeViewText().Fix(*im->surf);
		auto border = colours::GetBorder().Fix(*im->surf);
		auto selCol = colours::GetSelection().Fix(*im->surf);
		
		auto topLeft = colours::GetTreeViewLowLight().Fix(*im->surf);
		auto bottomRight = colours::GetTreeViewHiLight().Fix(*im->surf);
		im->surf->Clear();
		im->surf->BeginQueue();
		im->surf->Box(im->rect.AtZero(), bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		size_t i = 0;
		im->ForEachShown([&](TreeViewNode &cItem){
			if(i >= im->vOffset && i < im->vOffset + im->visibleItems + 1){
				int32_t iconX = ((cItem.level * im->iconSize) - im->hOffset) + 1;
				int32_t iconY = ((i - im->vOffset) * im->fontHeight) + 1;
				int32_t textX = iconX + im->iconSize;
				int32_t textY = iconY + std::max<int32_t>(((im->fontHeight + cItem.measures.h) / 2), 0);
				
				if(&cItem == im->selectedItem){
					auto selFocus = colours::GetSelectionFocus().Fix(*im->surf);
					int32_t selY = (im->fontHeight * (i - im->vOffset)) + 1;
					if(im->hasFocus){
						im->surf->Box({1, selY, inW, im->fontHeight}, selCol, selCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
					}
					im->surf->Box({1, selY, inW, im->fontHeight}, selFocus, selFocus, 1, gds_LineStyle::Solid);
				}
				
				auto icon = im->GetNodeIcon(cItem);
				im->surf->Blit(*icon, {0, 0, im->iconSize, im->iconSize}, {iconX, iconY, im->iconSize, im->iconSize});
				im->surf->Text({textX, textY}, cItem.text, fonts::GetTreeViewFont(), fonts::GetTreeViewTextSize(), txtCol);
			}
			++i;
		});
		drawing::Border(*im->surf, {0, 0, inW, inH}, border);
		drawing::BevelBox(*im->surf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);
		
		im->surf->CommitQueue();
		im->update = false;
	}
	s.Blit(*im->surf, im->rect.AtZero(), im->rect);

	if(im->hscroll) im->hscroll->Paint(s);
	if(im->vscroll) im->vscroll->Paint(s);
	
	if(!im->enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(im->outerRect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect TreeView::GetPaintRect(){
	return im->outerRect;
}

gds::Rect TreeView::GetInteractRect(){
	return im->outerRect;
}

uint32_t TreeView::GetSubscribed(){
	auto ret = wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown;
	if(im->hscroll) ret |= im->hscroll->GetSubscribed();
	if(im->vscroll) ret |= im->vscroll->GetSubscribed();
	return ret;
}

void TreeView::Focus(){
	if(!im->hasFocus){
		im->update = true;
		im->hasFocus = true;
		IControl::Paint(im->outerRect);
	}
}

void TreeView::Blur(){
	if(im->hasFocus){
		im->update = true;
		im->hasFocus = false;
		IControl::Paint(im->outerRect);
	}
}

uint32_t TreeView::GetFlags(){
	return 0;
}

void TreeView::Enable(){
	if(!im->enabled){
		im->enabled = true;
		IControl::Paint(im->rect);
	}
}

void TreeView::Disable(){
	if(im->enabled){
		im->enabled = false;
		IControl::Paint(im->rect);
	}
}

bool TreeView::IsEnabled(){
	return im->enabled;
}

void TreeView::SetPosition(const gds::Rect &r){
	im->outerRect = r;
	im->rect = im->scrollHoriz ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h};
	if(im->vscroll) im->vscroll->SetPosition({im->outerRect.x + (int32_t)im->outerRect.w - scrollbarSize, im->outerRect.y, scrollbarSize, im->outerRect.h - (im->scrollHoriz ? scrollbarSize : 0)});
	if(im->hscroll) im->hscroll->SetPosition({im->outerRect.x, im->outerRect.y + (int32_t)im->outerRect.h - scrollbarSize, im->outerRect.w - scrollbarSize, scrollbarSize});
	im->update = true;
	im->surf.reset();
}

TreeViewNode *TreeView::GetValue(){
	return im->selectedItem;
}

void TreeView::SetValue(TreeViewNode *node){
	if(im->selectedItem == node) return;
	im->selectedItem = node;
	im->update = true;
	im->UpdateDisplayState(true);
}

std::vector<TreeViewNode> &TreeView::Items(){
	return im->items;
}

void TreeView::Refresh(){
	im->update = true;
	IControl::Paint(im->outerRect);
}

}
}