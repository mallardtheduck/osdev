#define BTOS_NO_USING
#include "appview.hpp"

#include <gui/form.hpp>
#include <gui/toolbar.hpp>
#include <gui/statusbar.hpp>
#include <gui/iconview.hpp>
#include <gui/treeview.hpp>
#include <gui/messagebox.hpp>
#include <gui/actionmanager.hpp>

#include <wm/eventloop.hpp>
#include <wm/menu.hpp>

#include <gui/shell/utils.hpp>

#include <util/tinyformat.hpp>

namespace gds = btos_api::gds;
namespace gui = btos_api::gui;
namespace sh = btos_api::gui::shell;
namespace wm = btos_api::wm;

static const uint32_t formWidth = 500;
static const uint32_t formHeight = 320;
static const uint32_t toolbarHeight = 32;
static const uint32_t statusbarHeight = 18;
static const uint32_t treeWidth = 150;

static const uint32_t margin = 1;
static const uint32_t contentHeight = formHeight - toolbarHeight - statusbarHeight - (2 * margin);

int main(){
	bool onHome = true;
	bool treeVisible = true;
	auto curWidth = formWidth;
	auto curHeight = formHeight;
	
	std::vector<App> apps;
	std::vector<Category> cats;
	
	auto form = std::make_shared<gui::Form>(gds::Rect{70, 70, 500, 320}, gui::FormOptions::ClosedSizable, "Applications");
	
	auto toolbar = std::make_shared<gui::Toolbar>();
	auto tree = std::make_shared<gui::TreeView>(gds::Rect{margin, margin + toolbarHeight, treeWidth, contentHeight});
	auto icons = std::make_shared<gui::IconView>(gds::Rect{treeWidth + (2 * margin), margin + toolbarHeight, formWidth - treeWidth - (3 * margin), contentHeight});
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
			}
		}else if(size.w > (2 * margin)){
			form->MoveControl(icons, {margin, margin + toolbarHeight, size.w - (2 * margin), newContentHeight});
		}
	};
	
	form->OnResize(updateSize);
	
	auto toggleTree = [&]{
		treeVisible = !treeVisible;
		if(treeVisible){
			form->AddControl(tree);
		}else{
			form->RemoveControl(tree);
		}
		updateSize({0, 0, curWidth, curHeight});
	};
	
	auto getCatName = [](const Category &cat) -> std::string {
		if(cat.name.empty()) return "(Uncategorised)";
		else return cat.name;
	};
	
	auto updateTree = [&]{
		auto &items = tree->Items();
		items.clear();
		cats = GetCategories();
		for(size_t i = 0; i < cats.size(); ++i){
			auto &cat = cats[i];
			auto name = getCatName(cat);
			auto node = gui::TreeViewNode(i, name, {}, cat.icon16);
			items.push_back(node);
		}
		tree->Refresh();
	};
	
	updateTree();
	
	auto homeView = [&]{
		auto &items = icons->Items();
		items.clear();
		cats = GetCategories();
		for(size_t i = 0; i < cats.size(); ++i){
			auto &cat = cats[i];
			items.push_back(getCatName(cat));
			icons->SetItemIcon(i, cat.icon32);
		}
		icons->Refresh();
		statusbar->SetText("(Home)");
		onHome = true;
	};
	
	homeView();
	
	auto showCat = [&](const Category &cat){
		apps = GetApps(cat.name);
		auto &items = icons->Items();
		items.clear();
		for(size_t i = 0; i < apps.size(); ++i){
			auto &app = apps[i];
			items.push_back(app.description);
			icons->SetItemIcon(i, app.icon32);
		}
		icons->Refresh();
		statusbar->SetText(getCatName(cat));
		auto treeVal = tree->GetValue();
		if(treeVal && cats[treeVal->id].name != cat.name){
			for(auto &i : tree->Items()){
				if(cats[i.id].name == cat.name){
					tree->SetValue(&i);
					break;
				}
			}
		}
		onHome = false;
	};
	
	tree->OnChange([&](gui::TreeViewNode *node){
		if(node){
			auto &cat = cats[node->id];
			showCat(cat);
		}
	});
	
	icons->OnActivate([&]{
		auto idx = icons->GetValue();
		if(onHome){
			auto &cat = cats[idx];
			showCat(cat);
		}else{
			auto &app = apps[idx];
			btos_api::bt_spawn(app.path.c_str(), 0, nullptr);
		}
	});

	
	auto about = [&]{
		gui::MessageBox("BT/OS Application View", "About", LoadIcon("icons/appview_32.png")).Show(form.get());
	};
	
	
	gui::ActionManager am;
	am.Add("about", "About...", LoadIcon("icons/appview_16.png"), about);
	am.Add("home", "Home", LoadIcon("icons/home_16.png"), homeView);
	am.Add("toggleTree", "Toggle tree", LoadIcon("icons/view_tree_16.png"), toggleTree);
	
	toolbar->Controls() = {
		am.GetToolbarButton("home"),
		am.GetToolbarButton("toggleTree")
	};
	toolbar->Refresh();
	
	auto menuHandler = [&](int action) -> bool{
		am.MenuHandler(action);
		return true;
	};
	
	auto menu = std::make_shared<wm::Menu>();
	menu->AddItem(am.GetMenuItem("home"));
	menu->AddItem(am.GetMenuItem("toggleTree"));
	menu->AddItem(wm::MenuItem(0, "", wm_MenuItemFlags::Separator));
	menu->AddItem(am.GetMenuItem("about"));
	
	menu->SetEventHandler(menuHandler);
	form->SetMenu(*menu);
	
	wm::EventLoop loop;
	loop.AddWindow(form);
	loop.AddMenu(menu);
	form->Open();
	loop.RunLoop();

	return 0;
}