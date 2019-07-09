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

TreeViewNode::TreeViewNode(size_t i, const std::string &t, const std::vector<TreeViewNode> &c, std::shared_ptr<gds::Surface> ic, std::shared_ptr<gds::Surface> oI, bool o):
measures(), id(i), text(t), children(c), icon(ic), openIcon(oI), open(o)
{}

TreeView::TreeView(const gds::Rect &r, bool sH, size_t iS) : 
	outerRect(r), 
	rect(sH ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h}),
	iconSize(iS), scrollHoriz(sH)
	{
	auto info = fonts::GetTreeViewFont().Info();
	fontHeight = (info.maxH * fonts::GetTreeViewTextSize()) / info.scale;
	if(fontHeight < iconSize) fontHeight = iconSize;
	
	vscroll.reset(new Scrollbar({outerRect.x + (int32_t)outerRect.w - scrollbarSize, outerRect.y, scrollbarSize, outerRect.h - (scrollHoriz ? scrollbarSize : 0)}, 1, 1, 1, 1, false));
	
	vscroll->OnChange([this] (uint32_t v) {
		if(v != vOffset) update = true;
		vOffset = v;
	});
	
	if(scrollHoriz){
		hscroll.reset(new Scrollbar({outerRect.x, outerRect.y + (int32_t)outerRect.h - scrollbarSize, outerRect.w - scrollbarSize, scrollbarSize}, 1, 1, 1, 1, true));
		
		hscroll->OnChange([this] (uint32_t v) {
			if(v != hOffset) update = true;
			hOffset = v;
		});
	}
	
	UpdateDisplayState();
}

void TreeView::UpdateDisplayState(bool changePos){
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
		if(maxTextW > rect.w - 2){
			hscroll->Enable();
		 	hscroll->SetLines(maxTextW - (rect.w - 2));
		 	hscroll->SetPage(rect.w - 2);
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

void TreeView::ForEachShown(const std::function<void(TreeViewNode&)> &fn){
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

void TreeView::SelectionMove(int offset, MovePos pos){
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

std::shared_ptr<gds::Surface> TreeView::GetNodeIcon(const TreeViewNode &node){
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

void TreeView::SelectByChar(char c){
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

TreeViewNode *TreeView::GetNodeByPos(uint32_t yPos){
	TreeViewNode *node = nullptr;
	size_t i = 0;
	ForEachShown([&](TreeViewNode &cItem){
		if(i >= vOffset && i < vOffset + visibleItems + 1){
			uint32_t itemY = (i - vOffset) * fontHeight;
			if(itemY <= yPos) node = &cItem;
		}
		++i;
	});
	return node;
}

void TreeView::ToggleNodeOpen(TreeViewNode &node){
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
			SelectionMove(1);
			update = true;
			handled = true;
			UpdateDisplayState();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::UpArrow)){
			SelectionMove(-1);
			update = true;
			handled = true;
			UpdateDisplayState();
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageUp)){
			SelectionMove(-visibleItems);
			update = true;
			UpdateDisplayState();
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::PageDown)){
			SelectionMove(visibleItems);
			update = true;
			UpdateDisplayState();
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::Home)){
			SelectionMove(0, MovePos::First);
			update = true;
			UpdateDisplayState();
			handled = true;
		}else if(code == (KeyFlags::NonASCII | KeyCodes::End)){
			SelectionMove(0, MovePos::Last);
			update = true;
			UpdateDisplayState();
			handled = true;
		}else if(!(code & KeyFlags::NonASCII)){
			char c = KB_char(e.Key.code);
			if(c == ' ' || c == '\n'){
				ToggleNodeOpen(*selectedItem);
			}else{
				c = std::tolower(c);
				SelectByChar(c);
			}
			update = true;
			handled = true;
			UpdateDisplayState();
		}
	}else if(e.type & wm_PointerEvents){
		if(InRect(e.Pointer.x, e.Pointer.y, rect)){
			if(e.type == wm_EventType::PointerButtonUp){
				auto node = GetNodeByPos(e.Pointer.y - outerRect.y);
				if(node){
					selectedItem = node;
					auto ptrX = (e.Pointer.x - outerRect.x) + hOffset;
					if(ptrX > node->level * iconSize && ptrX < (node->level + 1) * iconSize){
						ToggleNodeOpen(*node);
					}
					update = true;
				}
				handled = true;
				UpdateDisplayState();
			}
		}else if(hscroll && hscroll->IsEnabled() && InRect(e.Pointer.x, e.Pointer.y, hscroll->GetInteractRect()) && (e.type & hscroll->GetSubscribed())){
			auto ret = hscroll->HandleEvent(e);
			update = ret.IsFinishedProcessing();
			handled = handled || update;
		}else if(vscroll && vscroll->IsEnabled() && InRect(e.Pointer.x, e.Pointer.y, vscroll->GetInteractRect()) && (e.type & vscroll->GetSubscribed())){
			auto ret = vscroll->HandleEvent(e);
			update = ret.IsFinishedProcessing();
			handled = handled || update;
		}
	}
	if(update) IControl::Paint(outerRect);
	return {handled};
}

void TreeView::Paint(gds::Surface &s){
	if(update || !surf){
		if(!surf) surf.reset(new gds::Surface(gds_SurfaceType::Vector, rect.w, rect.h, 100, gds_ColourType::True));
		UpdateDisplayState(false);
		
		uint32_t inW = rect.w - 1;
		uint32_t inH = rect.h - 1;
		
		auto bkgCol = colours::GetBackground().Fix(*surf);
		auto txtCol = colours::GetTreeViewText().Fix(*surf);
		auto border = colours::GetBorder().Fix(*surf);
		auto selCol = colours::GetSelection().Fix(*surf);
		
		auto topLeft = colours::GetTreeViewLowLight().Fix(*surf);
		auto bottomRight = colours::GetTreeViewHiLight().Fix(*surf);
		surf->Clear();
		surf->BeginQueue();
		surf->Box({0, 0, rect.w, rect.h}, bkgCol, bkgCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
		size_t i = 0;
		ForEachShown([&](TreeViewNode &cItem){
			if(i >= vOffset && i < vOffset + visibleItems + 1){
				int32_t iconX = (cItem.level * iconSize) - hOffset;
				int32_t iconY = (i - vOffset) * fontHeight;
				int32_t textX = iconX + iconSize;
				int32_t textY = iconY + std::max<int32_t>(((fontHeight + cItem.measures.h) / 2), 0);
				
				if(&cItem == selectedItem){
					auto selFocus = colours::GetSelectionFocus().Fix(*surf);
					int32_t selY = fontHeight * (i - vOffset);
					if(hasFocus){
						surf->Box({1, selY, inW, fontHeight}, selCol, selCol, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
					}
					surf->Box({1, selY, inW, fontHeight}, selFocus, selFocus, 1, gds_LineStyle::Solid);
				}
				
				auto icon = GetNodeIcon(cItem);
				surf->Blit(*icon, {0, 0, iconSize, iconSize}, {iconX, iconY, iconSize, iconSize});
				surf->Text({textX, textY}, cItem.text, fonts::GetTreeViewFont(), fonts::GetTreeViewTextSize(), txtCol);
			}
			++i;
		});
		drawing::Border(*surf, {0, 0, inW, inH}, border);
		drawing::BevelBox(*surf, {1, 1, inW - 2, inH - 2}, topLeft, bottomRight);
		
		surf->CommitQueue();
		update = false;
	}
	s.Blit(*surf, {0, 0, rect.w, rect.h}, rect);

	if(hscroll) hscroll->Paint(s);
	if(vscroll) vscroll->Paint(s);
	
	if(!enabled){
		auto cast = colours::GetDisabledCast().Fix(s);
		s.Box(outerRect, cast, cast, 1, gds_LineStyle::Solid, gds_FillStyle::Filled);
	}
}

gds::Rect TreeView::GetPaintRect(){
	return outerRect;
}

gds::Rect TreeView::GetInteractRect(){
	return outerRect;
}

uint32_t TreeView::GetSubscribed(){
	auto ret = wm_KeyboardEvents | wm_EventType::PointerButtonUp | wm_EventType::PointerButtonDown;
	if(hscroll) ret |= hscroll->GetSubscribed();
	if(vscroll) ret |= vscroll->GetSubscribed();
	return ret;
}

void TreeView::Focus(){
	if(!hasFocus){
		update = true;
		hasFocus = true;
		IControl::Paint(outerRect);
	}
}

void TreeView::Blur(){
	if(hasFocus){
		update = true;
		hasFocus = false;
		IControl::Paint(outerRect);
	}
}

uint32_t TreeView::GetFlags(){
	return 0;
}

void TreeView::Enable(){
	if(!enabled){
		enabled = true;
		IControl::Paint(rect);
	}
}

void TreeView::Disable(){
	if(enabled){
		enabled = false;
		IControl::Paint(rect);
	}
}

bool TreeView::IsEnabled(){
	return enabled;
}

void TreeView::SetPosition(const gds::Rect &r){
	outerRect = r;
	rect = scrollHoriz ? gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h - scrollbarSize} : gds::Rect{r.x, r.y, r.w - scrollbarSize, r.h};
	if(vscroll) vscroll->SetPosition({outerRect.x + (int32_t)outerRect.w - scrollbarSize, outerRect.y, scrollbarSize, outerRect.h - (scrollHoriz ? scrollbarSize : 0)});
	if(hscroll) hscroll->SetPosition({outerRect.x, outerRect.y + (int32_t)outerRect.h - scrollbarSize, outerRect.w - scrollbarSize, scrollbarSize});
	update = true;
	surf.reset();
}

TreeViewNode *TreeView::GetValue(){
	return selectedItem;
}

void TreeView::SetValue(TreeViewNode *node){
	if(selectedItem == node) return;
	selectedItem = node;
	update = true;
}

std::vector<TreeViewNode> &TreeView::Items(){
	return items;
}

void TreeView::Refresh(){
	update = true;
	IControl::Paint(outerRect);
}

}
}