#include <iostream>
#include <typeinfo>
#include <exception>

#include <gui/form.hpp>
#include <gui/button.hpp>
#include <gui/label.hpp>
#include <gui/textbox.hpp>
#include <gui/slider.hpp>
#include <gui/checkbox.hpp>
#include <gui/radiobutton.hpp>
#include <gui/scrollbar.hpp>
#include <gui/textarea.hpp>
#include <gui/subform.hpp>
#include <gui/groupbox.hpp>
#include <gui/testcontrol.hpp>
#include <gui/listbox.hpp>
#include <gui/detaillist.hpp>
#include <gui/image.hpp>
#include <gui/imagebutton.hpp>
#include <gui/iconview.hpp>
#include <gui/treeview.hpp>
#include <gui/toolbar.hpp>
#include <gui/statusbar.hpp>
#include <gui/tabs.hpp>

#include <wm/eventloop.hpp>
#include <util/tinyformat.hpp>
#include <cxxabi.h>

#include <gds/libgds.h>
#include <btos/resc.h>
#include <unistd.h>
#include "guitest_resc.tar.h"

std::shared_ptr<gds::Surface> load_png_resc(const char *path){
	auto r = btos_api::resc::Resc_LocalOpen(guitest_resc_data, guitest_resc_size);
	auto fd = btos_api::resc::Resc_OpenResc(r, path);
	auto ret = GDS_LoadPNG(fd);
	close(fd);
	btos_api::resc::Resc_Close(r);
	return std::make_shared<gds::Surface>(std::move(gds::Surface::Wrap(ret, true)));
}

void MoreForm(btos_api::wm::EventLoop &eloop){
	auto frm = std::make_shared<btos_api::gui::Form>(gds::Rect{200, 50, 600, 500}, wm_WindowOptions::Default, "More Controls");
	auto lst = std::make_shared<btos_api::gui::ListBox>(gds::Rect{10, 10, 150, 200}, true);
	auto lst2 = std::make_shared<btos_api::gui::ListBox>(gds::Rect{240, 10, 150, 200}, false, true);
	auto tst = std::make_shared<btos_api::gui::TestControl>(gds::Rect{170, 10, 50, 50});
	auto dls = std::make_shared<btos_api::gui::DetailList>(gds::Rect{10, 220, 280, 200}, std::vector<std::string>{"Col 1", "Col 2", "Col 3"}, true, 16, true);
	auto icv = std::make_shared<btos_api::gui::IconView>(gds::Rect{300, 220, 280, 200}, 32, false);
	auto png = load_png_resc("logo.png");
	auto img = std::make_shared<btos_api::gui::Image>(gds::Rect{10, 430, 170, 60}, png);
	auto png2 = load_png_resc("button_img.png");
	auto igb = std::make_shared<btos_api::gui::ImageButton>(gds::Rect{190, 430, 50, 50}, png2);
	auto trv = std::make_shared<btos_api::gui::TreeView>(gds::Rect{400, 10, 150, 200}, true);
	tst->OnEvent([] (const wm_Event &e){
		tfm::printf("More Test: EventType: %s\n", e.type);
		return true;
	});
	
	for(auto i = 0; i < 100; ++i){
		auto label = tfm::format("Item %s", i);
		lst->Items().push_back(label);
		lst2->Items().push_back(label);
	}
	lst->Items().push_back("A much, much longer item name...");
	lst->Refresh();
	lst2->Items().push_back("A much, much longer item name...");
	lst2->Refresh();
	
	for(auto i = 0; i < 100; ++i){
		auto label = tfm::format("Item %s", i);
		dls->Items().push_back({label, "Detail 1", "Detail 2"});
	}
	dls->Items().push_back({"A longer item", "Some extra detail", "Another string of superflous detail text"});
	dls->ColumnWidths() = {70, 150, 200};
	dls->Refresh();
	auto icon = load_png_resc("list_icon.png");
	dls->SetItemIcon(dls->Items().size() - 1, icon);
	auto dicon = load_png_resc("list_default.png");
	dls->SetDefaultIcon(dicon);
	
	auto icvdicon = load_png_resc("icon_default.png");
	icv->SetDefaultIcon(icvdicon);
	for(auto i = 0; i < 100; ++i){
		auto label = tfm::format("Item %s", i);
		icv->Items().push_back(label);
	}
	icv->Refresh();
	
	btos_api::gui::TreeViewNode root{0, "Root 1"};
	root.open = true;
	root.children = {
		{1, "Child 1"},
		{2, "Child 2"},
		{3, "Child 3"},
		{4, "Child 4"}
	};
	trv->Items().push_back(root);
	btos_api::gui::TreeViewNode root2{5, "Root 2"};
	root2.icon = load_png_resc("folder.png");
	root2.openIcon = load_png_resc("folder_open.png");
	root2.children = {
		{6, "Child 1"},
		{7, "Child 2"},
		{8, "Child 3"},
		{9, "Child 4"}
	};
	root2.children[2].children = {
		{10, "Child 1"},
		{11, "Child 2"},
		{12, "Child 3"},
		{13, "Child 4"}
	};
	root2.children[2].children[3].onOpen = [](btos_api::gui::TreeViewNode &n){
		n.children.clear();
		for(size_t i = 0; i < 20; ++i){
			auto text = tfm::format("Gen Child %s", i);
			n.children.push_back({100 + i, text});
		}
	};
	trv->Items().push_back(root2);
	trv->Refresh();
	
	frm->AddControls({lst, lst2, tst, dls, img, igb, icv, trv});
	eloop.AddWindow(frm);
}

void EvenMoreForm(btos_api::wm::EventLoop &eloop){
	auto frm = std::make_shared<btos_api::gui::Form>(gds::Rect{100, 100, 400, 300}, wm_WindowOptions::Default, "Even More Controls");
	auto tbar = std::make_shared<btos_api::gui::Toolbar>();
	
	auto tb1icon = load_png_resc("tb1_icon.png");
	auto tb3icon = load_png_resc("tb3_icon.png");
	auto tb1 = std::make_shared<btos_api::gui::ToolbarButton>(tb1icon);
	auto tb2 = std::make_shared<btos_api::gui::ToolbarButton>(nullptr, "Test");
	auto tb3 = std::make_shared<btos_api::gui::ToolbarButton>(tb3icon, "Label");
	tbar->Controls().push_back(tb1);
	tbar->Controls().push_back(tb2);
	tbar->Controls().push_back(std::make_shared<btos_api::gui::ToolbarSpacer>());
	tbar->Controls().push_back(tb3);
	tbar->Refresh();
	
	auto tabs = std::make_shared<btos_api::gui::Tabs>(gds::Rect{10, 40, 380, 230});
	auto t1c = std::make_shared<btos_api::gui::Label>(tabs->GetContentRect(), "Tab 1 content");
	tabs->TabItems().push_back({"Tab 1", t1c});
	auto t2c = std::make_shared<btos_api::gui::Label>(tabs->GetContentRect(), "Tab 2 content");
	tabs->TabItems().push_back({"Tab 2", t2c});
	auto t3c = std::make_shared<btos_api::gui::Label>(tabs->GetContentRect(), "Tab 3 content");
	tabs->TabItems().push_back({"Tab 3", t3c});
	auto ttc = std::make_shared<btos_api::gui::TestControl>(tabs->GetContentRect());
	tabs->TabItems().push_back({"Test Tab", ttc});
	tabs->Refresh();
	
	auto sbar = std::make_shared<btos_api::gui::StatusBar>("Status text.");
	tb3->OnAction([=](){
		sbar->SetText("New status.");
	});
	
	frm->AddControls({tbar, sbar, tabs});
	
	eloop.AddWindow(frm);
}

int main(){
	try{
		auto frm = std::make_shared<btos_api::gui::Form>(gds::Rect{200, 200, 500, 300}, wm_WindowOptions::Default, "GUI Controls Test");
		auto lbl1 = std::make_shared<btos_api::gui::Label>(gds::Rect{120, 10, 100, 20}, "A Label");
		auto lbl2 = std::make_shared<btos_api::gui::Label>(gds::Rect{120, 30, 100, 20}, "Nothing");
		auto btn1 = std::make_shared<btos_api::gui::Button>(gds::Rect{10, 10, 100, 30}, "Button 1");
		btn1->OnAction([&] {lbl2->SetText("Button 1");});
		auto btn2 = std::make_shared<btos_api::gui::Button>(gds::Rect{10, 50, 100, 30}, "Button 2");
		btn2->OnAction([&] {
			lbl2->SetText("Button 2");
			if(btn1->IsEnabled()){
				btn1->Disable();
			}else{
				btn1->Enable();
			}
		});
		auto txt = std::make_shared<btos_api::gui::TextBox>(gds::Rect{220, 10, 100, 20}, "An editable textbox");
		auto sld = std::make_shared<btos_api::gui::Slider>(gds::Rect{340, 10, 140, 20}, 0, 100, 50, 5);
		auto chk = std::make_shared<btos_api::gui::Checkbox>(gds::Rect{120, 55, 100, 20}, "A checkbox", true);
		auto rd1 = std::make_shared<btos_api::gui::RadioButton>(gds::Rect{220, 35, 100, 20}, "Radio 1", false);
		auto rd2 = std::make_shared<btos_api::gui::RadioButton>(gds::Rect{220, 60, 100, 20}, "Radio 2", false);
		auto rd3 = std::make_shared<btos_api::gui::RadioButton>(gds::Rect{220, 85, 100, 20}, "Radio 3", true);
		auto sch = std::make_shared<btos_api::gui::Scrollbar>(gds::Rect{340, 35, 140, 17}, 100, 1, 10, 0, true);
		auto scv = std::make_shared<btos_api::gui::Scrollbar>(gds::Rect{463, 60, 17, 140}, 100, 1, 10, 100, false);
		auto txa = std::make_shared<btos_api::gui::TextArea>(gds::Rect{10, 100, 150, 100}, "A multi-line editable text area.\nWith some lines of text.\nAnother line.\nA further line.\nAn additional line.\nAn extra line.\nA superflous line.", true);
		auto grp = std::make_shared<btos_api::gui::GroupBox>(gds::Rect{165, 110, 170, 110}, "Subformy within");
		auto tst1 = std::make_shared<btos_api::gui::TestControl>(gds::Rect{350, 110, 100, 30});
		tst1->OnEvent([] (const wm_Event &e){
			tfm::printf("Test: EventType: %s\n", e.type);
			return true;
		});
		
		btos_api::gui::RadioGroup<int> rgrp;
		rgrp.AddButton(rd1, 1);
		rgrp.AddButton(rd2, 2);
		rgrp.AddButton(rd3, 3);
		
		auto sfrm = std::make_shared<btos_api::gui::SubForm>(gds::Rect{170, 130, 150, 80});
		auto sbtn = std::make_shared<btos_api::gui::Button>(gds::Rect{10, 10, 100, 30}, "Button 3");
		sbtn->OnAction([&] {lbl2->SetText("Button 3");});
		auto tst2 = std::make_shared<btos_api::gui::TestControl>(gds::Rect{10, 50, 100, 30});
		tst2->OnEvent([] (const wm_Event &e){
			tfm::printf("Subform Test: EventType: %s\n", e.type);
			return true;
		});
		sfrm->AddControls({sbtn, tst2});
		
		auto mBtn = std::make_shared<btos_api::gui::Button>(gds::Rect{10, 260, 100, 30}, "More...");
		auto m2Btn = std::make_shared<btos_api::gui::Button>(gds::Rect{120, 260, 100, 30}, "Even more...");
		
		frm->AddControls({btn1, btn2, lbl1, lbl2, txt, sld, chk, rd1, rd2, rd3, sch, scv, txa, grp, sfrm, tst1, mBtn, m2Btn});
		frm->OnClose([]{
			tfm::printf("Form close.\n");
			return false;
		});
		
		btos_api::wm::EventLoop loop({frm});
		mBtn->OnAction([&] {MoreForm(loop);});
		m2Btn->OnAction([&] {EvenMoreForm(loop);});
		loop.RunLoop();
	}catch(std::exception &e){
		int status;
		const char *typeName = abi::__cxa_demangle(typeid(e).name(), 0, 0, &status);
		std::cerr << "Exception of type: " << typeName << std::endl;
		std::cerr << "What: " << e.what() << std::endl;
	}
	return 0;
}
