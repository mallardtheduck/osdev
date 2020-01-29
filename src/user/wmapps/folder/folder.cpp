#define BTOS_NO_USING

#include "folder.hpp"

#include <gui/shell/foldericonview.hpp>
#include <gui/shell/foldertreeview.hpp>
#include <gui/shell/folderdetailsview.hpp>

#include <gui/form.hpp>
#include <gui/toolbar.hpp>
#include <gui/statusbar.hpp>
#include <gui/messagebox.hpp>
#include <gui/inputbox.hpp>
#include <gui/actionmanager.hpp>

#include <wm/eventloop.hpp>
#include <wm/menu.hpp>

#include <gui/shell/utils.hpp>

#include <btos/directory.hpp>
#include <btos/clipboard.hpp>

#include <stack>

#include <util/tinyformat.hpp>

namespace gds = btos_api::gds;
namespace gui = btos_api::gui;
namespace sh = btos_api::gui::shell;
namespace wm = btos_api::wm;
namespace clip = btos_api::clipboard;

enum class ViewMode{
	Icons, Details
};

static const uint32_t formWidth = 500;
static const uint32_t formHeight = 320;
static const uint32_t toolbarHeight = 32;
static const uint32_t statusbarHeight = 18;
static const uint32_t treeWidth = 150;

static const uint32_t margin = 1;
static const uint32_t contentHeight = formHeight - toolbarHeight - statusbarHeight - (2 * margin);

int main(int argc, char **argv){
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
	
	std::shared_ptr<gui::ToolbarButton> backBtn;
	std::shared_ptr<gui::ToolbarButton> fwdBtn;
	std::shared_ptr<gui::ToolbarButton> upBtn;
	std::shared_ptr<gui::ToolbarButton> iconsBtn;
	std::shared_ptr<gui::ToolbarButton> detailsBtn;
	
	auto form = std::make_shared<gui::Form>(gds::Rect{50, 50, 500, 320}, gui::FormOptions::ClosedSizable, sh::PathItemTitle(curPath));
	
	auto toolbar = std::make_shared<gui::Toolbar>();
	
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
			form->MoveControl(tree, {margin, margin + toolbarHeight, treeWidth, newContentHeight});
			if(size.w > treeWidth - (3 * margin)){
				form->MoveControl(icons, {treeWidth + (2 * margin), margin + toolbarHeight, size.w - treeWidth - (3 * margin), newContentHeight});
				form->MoveControl(details, {treeWidth + (2 * margin), margin + toolbarHeight, size.w - treeWidth - (3 * margin), newContentHeight});
			}
		}else if(size.w > (2 * margin)){
			form->MoveControl(icons, {margin, margin + toolbarHeight, size.w - (2 * margin), newContentHeight});
			form->MoveControl(details, {margin, margin + toolbarHeight, size.w - (2 * margin), newContentHeight});
		}
	};
	
	form->OnResize(updateSize);
	
	auto updateStatusbar = [&](const std::string &path){
		std::string text;
		auto stat = btos_api::bt_stat(path.c_str());
		if(stat.valid && stat.type == FS_Directory){
			btos_api::Directory d(path.c_str(), FS_Read);
			size_t count = 0;
			for(const auto &i : d){ 
				++count;
				(void)i;
			}
			text = tfm::format("%s - %s items", path, count);
		}else if(stat.valid){
			text = tfm::format("%s - %s", path, sh::FormatSize(stat.size));
		}else if(path != ""){
			text = tfm::format("%s - ERROR!", path);
		}
		statusbar->SetText(text);
	};
	
	auto navigateTo = [&](const std::string &path, bool keep){
		if(path != curPath){
			if(keep){
				history.push(curPath);
				future = {};
			}
			icons->SetPath(path);
			icons->SetValue(0);
			details->SetPath(path);
			details->SetValue(0);
			tree->SetSelectedPath(path);
			updateStatusbar(path);
			curPath = path;
			form->SetTitle(sh::PathItemTitle(path));
			updateMenus();
			if(history.empty()) backBtn->Disable();
			else backBtn->Enable();
			if(future.empty()) fwdBtn->Disable();
			else fwdBtn->Enable();
			if(curPath.empty()) upBtn->Disable();
			else upBtn->Enable();
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
	
	auto iconView = [&]{
		curView = ViewMode::Icons;
		form->RemoveControl(details);
		form->AddControl(icons);
		iconsBtn->Disable();
		detailsBtn->Enable();
		updateMenus();
	};
	
	auto detailsView = [&]{
		curView = ViewMode::Details;
		form->RemoveControl(icons);
		form->AddControl(details);
		detailsBtn->Disable();
		iconsBtn->Enable();
		updateMenus();
	};
	
	tree->OnChange([&](gui::TreeViewNode*){
		auto path = tree->GetSelectedPath();
		navigateTo(path, true);
	});
	
	auto launch = [&](const std::string &path){
		auto pid = sh::Launch(path);
		if(!pid){
			gui::MessageBox msg(tfm::format("Cannot launch this item."), "Error", LoadIcon("icons/error_32.png"));
			msg.Show(form.get());
		}
	};
	
	icons->OnActivate([&]{
		auto entry = icons->GetSelectedEntry();
		if(entry.valid && entry.type == FS_Directory){
			auto path = sh::CombinePath({icons->GetPath(), entry.filename});
			navigateTo(path, true);
		}else if(entry.valid && entry.type == FS_File){
			auto path = sh::CombinePath(curPath, entry.filename);
			launch(path);
		}
	});
	
	icons->OnChange([&](size_t){
		auto path = sh::CombinePath(curPath, icons->GetSelectedEntry().filename);
		updateStatusbar(path);
	});
	
	details->OnActivate([&]{
		auto entry = details->GetSelectedEntry();
		if(entry.valid && entry.type == FS_Directory){
			auto path = sh::CombinePath({details->GetPath(), entry.filename});
			navigateTo(path, true);
		}else if(entry.valid && entry.type == FS_File){
			auto path = sh::CombinePath(curPath, entry.filename);
			launch(path);
		}
	});
	
	details->OnChange([&](size_t){
		auto path = sh::CombinePath(curPath, details->GetSelectedEntry().filename);
		updateStatusbar(path);
	});
	
	auto goBack = [&]{
		if(!history.empty()){
			auto path = history.top();
			history.pop();
			future.push(curPath);
			navigateTo(path, false);
		}
	};
	
	auto goFwd = [&]{
		if(!future.empty()){
			auto path = future.top();
			future.pop();
			history.push(curPath);
			navigateTo(path, false);
		}
	};
	
	auto goUp = [&]{
		if(!curPath.empty()){
			auto parts = sh::SplitPath(curPath);
			parts.pop_back();
			auto path = sh::CombinePath(parts);
			navigateTo(path, true);
		}
	};
	
	auto newWindow = [&]{
		if(argc) btos_api::bt_spawn(argv[0], 0, nullptr);
	};
	
	auto newFolder = [&]{
		if(curPath != ""){
			gui::InputBox dlg("Enter new folder name:", "New Folder...");
			auto name = dlg.Show(form.get());
			if(!name.empty()){
				auto fullpath = sh::CombinePath(curPath, name);
				btos_api::bt_handle_t dh = btos_api::bt_dopen(fullpath.c_str(), FS_Read | FS_Create);
				if(dh){
					btos_api::bt_dclose(dh);
					navigateTo(fullpath, true);
				}else{
					gui::MessageBox msg(tfm::format("Error creating folder."), "Error", LoadIcon("icons/error_32.png"));
					msg.Show(form.get());
				}
			}
		}else{
			gui::MessageBox msg(tfm::format("Cannot create folder here."), "Error", LoadIcon("icons/error_32.png"));
			msg.Show(form.get());	
		}
	};
	
	auto about = [&]{
		gui::MessageBox("BT/OS Folder View", "About", LoadIcon("icons/folder_32.png")).Show(form.get());
	};
	
	const std::string copyClipType = "vnd.btos/filecopy";
	const std::string moveClipType = "vnd.btos/filecut";
	
	auto paste = [&]{
		auto header = clip::GetContentHeader(clip::Clipboard::Primary);
		if(header.type == copyClipType || header.type == moveClipType){
			auto data = clip::Paste(clip::Clipboard::Primary, header.id);
			if(!data.empty()){
				auto paths = clip::RPCDeserialize<std::vector<std::string>>(data);
				std::string question;
				if(header.type == copyClipType) question = "Copy %s file(s)?";
				else question = "Move %s file(s)?";
				auto confirm = gui::MessageBox(tfm::format(question.c_str(), paths.size()), "Confirm", LoadIcon("icons/question_32.png"), {"Yes", "No"}).Show(form.get());
				if(confirm == 0){
					for(auto &p : paths){
						auto parts = sh::SplitPath(p);
						auto dest = sh::CombinePath(curPath, parts.back());
						CopyMove(p, dest, (header.type == moveClipType), form.get());
						
					}
					if(header.type == moveClipType) clip::Clear(clip::Clipboard::Primary, header.id);
					icons->Update();
					details->Update();
				}
			}
		}
	};
	
	auto copyCut = [&](const std::string &type){
		bt_directory_entry entry;
		if(curView == ViewMode::Icons){
			entry = icons->GetSelectedEntry();
		}else{
			entry = details->GetSelectedEntry();
		}
		auto path = sh::CombinePath({curPath, entry.filename});
		std::vector<std::string> paths;
		paths.push_back(path);
		clip::CopyCut(clip::Clipboard::Primary, type, clip::RPCSerialize(paths));
	};
	
	auto copy = [&]{
		copyCut(copyClipType);
	};
	
	auto cut = [&]{
		copyCut(moveClipType);
	};
	
	auto deleteFile = [&]{
		bt_directory_entry entry;
		if(curView == ViewMode::Icons){
			entry = icons->GetSelectedEntry();
		}else{
			entry = details->GetSelectedEntry();
		}
		auto path = sh::CombinePath({curPath, entry.filename});
		bool confirmed = false;
		if(entry.type == FS_Directory){
			auto btn = gui::MessageBox("Delete this folder and its entire contents?", "Confirm", LoadIcon("icons/question_32.png"), {"Yes", "No"}).Show(form.get());
			confirmed = (btn == 0);
		}else if(entry.type == FS_File){
			auto btn = gui::MessageBox("Delete this file?", "Confirm", LoadIcon("icons/question_32.png"), {"Yes", "No"}).Show(form.get());
			confirmed = (btn == 0);
		}else{
			gui::MessageBox("Cannot delete this item.", "Delete", LoadIcon("icons/error_32.png")).Show(form.get());
		}
		if(confirmed){
			if(entry.type == FS_File){
				auto fh = btos_api::bt_fopen(path.c_str(), FS_Read | FS_Delete);
				if(fh) btos_api::bt_fclose(fh);
			}else if(entry.type == FS_Directory){
				std::stack<std::string> dirs;
				std::stack<std::string> emptyDirs;
				dirs.push(path);
				while(!dirs.empty()){
					auto curDir = dirs.top();
					dirs.pop();
					btos_api::Directory d(curDir.c_str(), FS_Read);
					for(auto e : d){
						if(e.type == FS_File){
							auto filePath = sh::CombinePath(curDir, e.filename);
							auto fh = btos_api::bt_fopen(filePath.c_str(), FS_Read | FS_Delete);
							if(fh) btos_api::bt_fclose(fh);
						}else if(e.type == FS_Directory){
							auto dirPath = sh::CombinePath(curDir, e.filename);
							dirs.push(dirPath);
						}else{
							auto itemPath = sh::CombinePath(curDir, e.filename);
							gui::MessageBox(tfm::format("Cannot delete: %s", itemPath), "Delete", LoadIcon("icons/error_32.png")).Show(form.get());
							icons->Update();
							details->Update();
							return;
						}
					}
					emptyDirs.push(curDir);
				}
				while(!emptyDirs.empty()){
					auto dh = btos_api::bt_dopen(emptyDirs.top().c_str(), FS_Read | FS_Delete);
					if(dh) btos_api::bt_dclose(dh);
					emptyDirs.pop();
				}
			}
			icons->Update();
			details->Update();
		}
	};
	
	gui::ActionManager am;
	am.Add("newWindow", "New window...", LoadIcon("icons/window_new_16.png"), newWindow);
	am.Add("toggleTree", "Toggle tree", LoadIcon("icons/view_tree_16.png"), toggleTree);
	am.Add("iconView", "Icon view", LoadIcon("icons/view_icon_16.png"), iconView);
	am.Add("detailsView", "Details view", LoadIcon("icons/view_detailed_16.png"), detailsView);
	am.Add("goUp", "Up a level", LoadIcon("icons/up_16.png"), goUp);
	am.Add("goBack", "Back", LoadIcon("icons/back_16.png"), goBack);
	am.Add("goFwd", "Forward", LoadIcon("icons/forward_16.png"), goFwd);
	am.Add("newFolder", "New folder...", LoadIcon("icons/new_folder_16.png"), newFolder);
	am.Add("editPaste", "Paste", LoadIcon("icons/editpaste_16.png"), paste);
	am.Add("editCopy", "Copy", LoadIcon("icons/editcopy_16.png"), copy);
	am.Add("editCut", "Cut", LoadIcon("icons/editcut_16.png"), cut);
	am.Add("delete", "Delete", LoadIcon("icons/editdelete_16.png"), deleteFile);
	am.Add("about", "About...", LoadIcon("icons/folder_16.png"), about);
	
	auto newWinBtn = am.GetToolbarButton("newWindow");
	auto treeBtn = am.GetToolbarButton("toggleTree");
	iconsBtn = am.GetToolbarButton("iconView");
	detailsBtn = am.GetToolbarButton("detailsView");
	auto spc1 = std::make_shared<gui::ToolbarSpacer>();
	upBtn = am.GetToolbarButton("goUp");
	backBtn = am.GetToolbarButton("goBack");
	fwdBtn = am.GetToolbarButton("goFwd");
	auto spc2 = std::make_shared<gui::ToolbarSpacer>();
	auto newFolderBtn = am.GetToolbarButton("newFolder");
	auto editPasteBtn = am.GetToolbarButton("editPaste");
	auto editCopyBtn = am.GetToolbarButton("editCopy");
	auto editCutBtn = am.GetToolbarButton("editCut");
	auto deleteBtn = am.GetToolbarButton("delete");
	
	toolbar->Controls() = {newWinBtn, treeBtn, iconsBtn, detailsBtn, spc1, upBtn, backBtn, fwdBtn, spc2, 
		newFolderBtn, editPasteBtn, editCopyBtn, editCutBtn, deleteBtn};
	toolbar->Refresh();
	
	iconsBtn->Disable();
	upBtn->Disable();
	backBtn->Disable();
	fwdBtn->Disable();
	
	auto menuHandler = [&](int action) -> bool{
		am.MenuHandler(action);
		return true;
	};
	
	wm::EventLoop loop;
	
	updateMenus = [&]{
		if(viewMenu) loop.RemoveMenu(viewMenu->GetID());
		viewMenu = std::make_shared<wm::Menu>();
		viewMenu->AddItem(am.GetMenuItem("toggleTree"));
		viewMenu->AddItem(wm::MenuItem(0, "", wm_MenuItemFlags::Separator));
		auto iconsItem = am.GetMenuItem("iconView");
		iconsItem.flags = curView == ViewMode::Icons ? wm_MenuItemFlags::Disabled : wm_MenuItemFlags::Default;
		viewMenu->AddItem(iconsItem);
		auto detailsItem = am.GetMenuItem("detailsView");
		detailsItem.flags = curView == ViewMode::Details ? wm_MenuItemFlags::Disabled : wm_MenuItemFlags::Default;
		viewMenu->AddItem(detailsItem);
		viewMenu->SetEventHandler(menuHandler);
		loop.AddMenu(viewMenu);
		
		if(navMenu) loop.RemoveMenu(navMenu->GetID());
		navMenu = std::make_shared<wm::Menu>();
		auto backItem = am.GetMenuItem("goBack");
		backItem.flags = history.empty() ? wm_MenuItemFlags::Disabled : wm_MenuItemFlags::Default;
		navMenu->AddItem(backItem);
		auto forwardItem = am.GetMenuItem("goFwd");
		forwardItem.flags = future.empty() ? wm_MenuItemFlags::Disabled : wm_MenuItemFlags::Default;
		navMenu->AddItem(forwardItem);
		auto upItem = am.GetMenuItem("goUp");
		upItem.flags = curPath.empty() ? wm_MenuItemFlags::Disabled : wm_MenuItemFlags::Default;
		navMenu->AddItem(upItem);
		navMenu->SetEventHandler(menuHandler);
		loop.AddMenu(navMenu);
		
		if(editMenu) loop.RemoveMenu(editMenu->GetID());
		editMenu = std::make_shared<wm::Menu>();
		editMenu->AddItem(am.GetMenuItem("editPaste"));
		editMenu->AddItem(am.GetMenuItem("editCopy"));
		editMenu->AddItem(am.GetMenuItem("editCut"));
		editMenu->AddItem(am.GetMenuItem("delete"));
		editMenu->SetEventHandler(menuHandler);
		loop.AddMenu(editMenu);
		
		if(menu) loop.RemoveMenu(menu->GetID());
		menu = std::make_shared<wm::Menu>();
		menu->AddItem(am.GetMenuItem("newWindow"));
		menu->AddItem(am.GetMenuItem("newFolder"));
		menu->AddItem(wm::MenuItem(0, "View", wm_MenuItemFlags::ChildMenu, nullptr, viewMenu.get()));
		menu->AddItem(wm::MenuItem(0, "Navigate", wm_MenuItemFlags::ChildMenu, nullptr, navMenu.get()));
		menu->AddItem(wm::MenuItem(0, "Edit", wm_MenuItemFlags::ChildMenu, nullptr, editMenu.get()));
		menu->AddItem(wm::MenuItem(0, "", wm_MenuItemFlags::Separator));
		menu->AddItem(am.GetMenuItem("about"));
		
		menu->SetEventHandler(menuHandler);
		loop.AddMenu(menu);
		
		form->SetMenu(*menu);
	};
	
	updateMenus();
	
	loop.AddWindow(form);
	form->Open();
	loop.RunLoop();

	return 0;
}