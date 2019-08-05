#define BTOS_NO_USING

#include "folder.hpp"

#include <gui/shell/foldericonview.hpp>
#include <gui/shell/foldertreeview.hpp>
#include <gui/shell/folderdetailsview.hpp>

#include <gui/form.hpp>
#include <gui/toolbar.hpp>
#include <gui/statusbar.hpp>
#include <gui/messagebox.hpp>

#include <wm/eventloop.hpp>
#include <wm/menu.hpp>

#include <gui/shell/utils.hpp>

#include <stack>

#include <util/tinyformat.hpp>

namespace gds = btos_api::gds;
namespace gui = btos_api::gui;
namespace sh = btos_api::gui::shell;
namespace wm = btos_api::wm;

enum class ViewMode{
	Icons, Details
};

static const uint32_t formWidth = 500;
static const uint32_t formHeight = 320;
static const uint32_t toolbarHeight = 32;
static const uint32_t statusbarHeight = 20;
static const uint32_t treeWidth = 150;

static const uint32_t margin = 5;
static const uint32_t contentHeight = formHeight - toolbarHeight - statusbarHeight - (2 * margin);

int main(){
	std::string curPath;
	bool treeVisible = true;
	ViewMode curView = ViewMode::Icons;
	auto curWidth = formWidth;
	auto curHeight = formHeight;
	std::stack<std::string> history;
	std::stack<std::string> future;
	
	std::shared_ptr<wm::Menu> menu;
	std::shared_ptr<wm::Menu> viewMenu;
	std::shared_ptr<wm::Menu> navMenu;
	std::shared_ptr<wm::Menu> editMenu;
	std::function<void()> updateMenus;
	
	auto form = std::make_shared<gui::Form>(gds::Rect{50, 50, 500, 320}, gui::FormOptions::ClosedSizable, sh::PathItemTitle(curPath));
	
	auto toolbar = std::make_shared<gui::Toolbar>();
	auto newWinBtn = std::make_shared<gui::ToolbarButton>(LoadIcon("icons/window_new_16.png"));
	auto treeBtn = std::make_shared<gui::ToolbarButton>(LoadIcon("icons/view_tree_16.png"));
	auto iconsBtn = std::make_shared<gui::ToolbarButton>(LoadIcon("icons/view_icon_16.png"));
	auto detailsBtn = std::make_shared<gui::ToolbarButton>(LoadIcon("icons/view_detailed_16.png"));
	auto spc1 = std::make_shared<gui::ToolbarSpacer>();
	auto backBtn = std::make_shared<gui::ToolbarButton>(LoadIcon("icons/back_16.png"));
	auto fwdBtn = std::make_shared<gui::ToolbarButton>(LoadIcon("icons/forward_16.png"));
	auto upBtn = std::make_shared<gui::ToolbarButton>(LoadIcon("icons/up_16.png"));
	auto spc2 = std::make_shared<gui::ToolbarSpacer>();
	auto newFolderBtn = std::make_shared<gui::ToolbarButton>(LoadIcon("icons/new_folder_16.png"));
	auto editPasteBtn = std::make_shared<gui::ToolbarButton>(LoadIcon("icons/editpaste_16.png"));
	auto editCopyBtn = std::make_shared<gui::ToolbarButton>(LoadIcon("icons/editcopy_16.png"));
	auto editCutBtn = std::make_shared<gui::ToolbarButton>(LoadIcon("icons/editcut_16.png"));
	auto deleteBtn = std::make_shared<gui::ToolbarButton>(LoadIcon("icons/editdelete_16.png"));
	
	toolbar->Controls() = {newWinBtn, treeBtn, iconsBtn, detailsBtn, spc1, backBtn, fwdBtn, upBtn, spc2, 
		newFolderBtn, editPasteBtn, editCopyBtn, editCutBtn, deleteBtn};
	toolbar->Refresh();
	
	iconsBtn->Disable();
	
	auto tree = std::make_shared<sh::FolderTreeView>(gds::Rect{margin, margin + toolbarHeight, treeWidth, contentHeight}, "");
	auto icons = std::make_shared<sh::FolderIconView>(gds::Rect{treeWidth + (2 * margin), margin + toolbarHeight, formWidth - treeWidth - (3 * margin), contentHeight}, "");
	auto details = std::make_shared<sh::FolderDetailsView>(gds::Rect{treeWidth + (2 * margin), margin + toolbarHeight, formWidth - treeWidth - (3 * margin), contentHeight}, "");
	
	auto statusbar = std::make_shared<btos_api::gui::StatusBar>("");
	
	form->AddControls({toolbar, tree, icons, statusbar});
	
	auto updateSize = [&](const gds::Rect &size){
		curWidth = size.w;
		curHeight = size.h;
		if(size.h < toolbarHeight + statusbarHeight + (2 * margin)) return;
		uint32_t newContentHeight = size.h - toolbarHeight - statusbarHeight - (2 * margin);
		if(treeVisible){
			tree->SetPosition({margin, margin + toolbarHeight, treeWidth, newContentHeight});
			if(size.w > treeWidth - (3 * margin)){
				icons->SetPosition({treeWidth + (2 * margin), margin + toolbarHeight, size.w - treeWidth - (3 * margin), newContentHeight});
				details->SetPosition({treeWidth + (2 * margin), margin + toolbarHeight, size.w - treeWidth - (3 * margin), newContentHeight});
			}
		}else if(size.w > (2 * margin)){
			icons->SetPosition({margin, margin + toolbarHeight, size.w - (2 * margin), newContentHeight});
			details->SetPosition({margin, margin + toolbarHeight, size.w - (2 * margin), newContentHeight});
		}
	};
	
	auto navigateTo = [&](const std::string &path, bool keep){
		if(path != details->GetPath()){
			if(keep){
				history.push(details->GetPath());
				backBtn->Enable();
				future = {};
			}
			icons->SetPath(path);
			icons->SetValue(0);
			details->SetPath(path);
			details->SetValue(0);
			tree->SetSelectedPath(path);
			statusbar->SetText(path);
			form->SetTitle(sh::PathItemTitle(path));
			curPath = path;
			updateMenus();
		}
	};
	
	auto toggleTree = [&]{
		treeVisible = !treeVisible;
		if(treeVisible){
			form->AddControl(tree);
		}else{
			form->RemoveControl(tree);
		}
		updateSize({0, 0, curWidth, curHeight});
	};
	
	treeBtn->OnAction(toggleTree);
	
	auto iconView = [&]{
		curView = ViewMode::Icons;
		form->RemoveControl(details);
		form->AddControl(icons);
		iconsBtn->Disable();
		detailsBtn->Enable();
		updateMenus();
	};
	
	iconsBtn->OnAction(iconView);
	
	auto detailsView = [&]{
		curView = ViewMode::Details;
		form->RemoveControl(icons);
		form->AddControl(details);
		detailsBtn->Disable();
		iconsBtn->Enable();
		updateMenus();
	};
	
	detailsBtn->OnAction(detailsView);
	
	tree->OnChange([&](gui::TreeViewNode*){
		auto path = tree->GetSelectedPath();
		navigateTo(path, true);
	});
	
	icons->OnActivate([&]{
		auto entry = icons->GetSelectedEntry();
		if(entry.valid && entry.type == FS_Directory){
			auto path = sh::CombinePath({icons->GetPath(), entry.filename});
			navigateTo(path, true);
		}
	});
	
	details->OnActivate([&]{
		auto entry = details->GetSelectedEntry();
		if(entry.valid && entry.type == FS_Directory){
			auto path = sh::CombinePath({details->GetPath(), entry.filename});
			navigateTo(path, true);
		}
	});
	
	form->OnResize(updateSize);
	
	auto menuHandler = [&](int action) -> bool{
		switch(action){
			case 1:
				//new window
				break;
			case 2:
				//new folder
				break;
			case 3:
				gui::MessageBox("BT/OS Folder View", "About", LoadIcon("icons/folder_32.png")).Show(form.get());
				break;
				
			case 11:
				toggleTree();
				break;
			case 12:
				iconView();
				break;
			case 13:
				detailsView();
				break;
			
			case 21:
				//back
				break;
			case 22:
				//forward
				break;
			case 23:
				//up
				break;
			
			case 31:
				//paste
				break;
			case 32:
				//copy
				break;
			case 33:
				//cut
				break;
			case 34:
				//delete
				break;
		}
		return true;
	};
	
	wm::EventLoop loop;
	
	updateMenus = [&]{
		if(viewMenu) loop.RemoveMenu(viewMenu->GetID());
		viewMenu = std::make_shared<wm::Menu>();
		viewMenu->AddItem(wm::MenuItem(11, "Toggle tree", wm_MenuItemFlags::Default, LoadIcon("icons/view_tree_16.png").get()));
		viewMenu->AddItem(wm::MenuItem(0, "", wm_MenuItemFlags::Separator));
		auto iconFlags = curView == ViewMode::Icons ? wm_MenuItemFlags::Disabled : wm_MenuItemFlags::Default;
		viewMenu->AddItem(wm::MenuItem(12, "Icon view",iconFlags, LoadIcon("icons/view_icon_16.png").get()));
		auto detailFlags = curView == ViewMode::Details ? wm_MenuItemFlags::Disabled : wm_MenuItemFlags::Default;
		viewMenu->AddItem(wm::MenuItem(13, "Detail view", detailFlags, LoadIcon("icons/view_detailed_16.png").get()));
		viewMenu->SetEventHandler(menuHandler);
		loop.AddMenu(viewMenu);
		
		if(navMenu) loop.RemoveMenu(navMenu->GetID());
		navMenu = std::make_shared<wm::Menu>();
		auto backFlags = history.empty() ? wm_MenuItemFlags::Disabled : wm_MenuItemFlags::Default;
		navMenu->AddItem(wm::MenuItem(21, "Back", backFlags, LoadIcon("icons/back_16.png").get()));
		auto forwardFlags = future.empty() ? wm_MenuItemFlags::Disabled : wm_MenuItemFlags::Default;
		navMenu->AddItem(wm::MenuItem(22, "Forward", forwardFlags, LoadIcon("icons/forward_16.png").get()));
		auto upFlags = curPath.empty() ? wm_MenuItemFlags::Disabled : wm_MenuItemFlags::Default;
		navMenu->AddItem(wm::MenuItem(23, "Up a level", upFlags, LoadIcon("icons/up_16.png").get()));
		navMenu->SetEventHandler(menuHandler);
		loop.AddMenu(navMenu);
		
		if(editMenu) loop.RemoveMenu(editMenu->GetID());
		editMenu = std::make_shared<wm::Menu>();
		editMenu->AddItem(wm::MenuItem(31, "Paste", wm_MenuItemFlags::Default, LoadIcon("icons/editpaste_16.png").get()));
		editMenu->AddItem(wm::MenuItem(32, "Copy", wm_MenuItemFlags::Default, LoadIcon("icons/editcopy_16.png").get()));
		editMenu->AddItem(wm::MenuItem(33, "Cut", wm_MenuItemFlags::Default, LoadIcon("icons/editcut_16.png").get()));
		editMenu->AddItem(wm::MenuItem(34, "Delete", wm_MenuItemFlags::Default, LoadIcon("icons/editdelete_16.png").get()));
		editMenu->SetEventHandler(menuHandler);
		loop.AddMenu(editMenu);
		
		if(menu) loop.RemoveMenu(menu->GetID());
		menu = std::make_shared<wm::Menu>();
		menu->AddItem(wm::MenuItem(1, "New window", wm_MenuItemFlags::Default, LoadIcon("icons/window_new_16.png").get()));
		menu->AddItem(wm::MenuItem(2, "New folder...", wm_MenuItemFlags::Default, LoadIcon("icons/new_folder_16.png").get()));
		menu->AddItem(wm::MenuItem(0, "View", wm_MenuItemFlags::ChildMenu, nullptr, viewMenu.get()));
		menu->AddItem(wm::MenuItem(0, "Navigate", wm_MenuItemFlags::ChildMenu, nullptr, navMenu.get()));
		menu->AddItem(wm::MenuItem(0, "Edit", wm_MenuItemFlags::ChildMenu, nullptr, editMenu.get()));
		menu->AddItem(wm::MenuItem(0, "", wm_MenuItemFlags::Separator));
		menu->AddItem(wm::MenuItem(3, "About...", wm_MenuItemFlags::Default, LoadIcon("icons/folder_16.png").get()));
		menu->SetEventHandler(menuHandler);
		loop.AddMenu(menu);
		
		form->SetMenu(*menu);
	};
	
	updateMenus();
	
	loop.AddWindow(form);
	form->Show();
	loop.RunLoop();

	return 0;
}