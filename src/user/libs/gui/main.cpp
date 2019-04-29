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

#include <wm/eventloop.hpp>
#include <util/tinyformat.hpp>
#include <cxxabi.h>

void MoreForm(btos_api::wm::EventLoop &eloop){
	auto frm = std::make_shared<btos_api::gui::Form>(gds::Rect{250, 250, 300, 500}, wm_WindowOptions::Default, "More Controls");
	auto lst = std::make_shared<btos_api::gui::ListBox>(gds::Rect{10, 10, 150, 200});
	for(auto i = 0; i < 100; ++i){
		auto label = tfm::format("Item %s", i);
		lst->Items().push_back(label);
	}
	frm->AddControls({lst});
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
		btn2->OnAction([&] {lbl2->SetText("Button 2");});
		auto txt = std::make_shared<btos_api::gui::TextBox>(gds::Rect{220, 10, 100, 20}, "An editable textbox");
		auto sld = std::make_shared<btos_api::gui::Slider>(gds::Rect{340, 10, 140, 20}, 0, 100, 50, 5);
		auto chk = std::make_shared<btos_api::gui::Checkbox>(gds::Rect{120, 55, 100, 20}, "A checkbox", true);
		auto rd1 = std::make_shared<btos_api::gui::RadioButton>(gds::Rect{220, 35, 100, 20}, "Radio 1", false);
		auto rd2 = std::make_shared<btos_api::gui::RadioButton>(gds::Rect{220, 60, 100, 20}, "Radio 2", false);
		auto rd3 = std::make_shared<btos_api::gui::RadioButton>(gds::Rect{220, 85, 100, 20}, "Radio 3", true);
		auto sch = std::make_shared<btos_api::gui::Scrollbar>(gds::Rect{340, 35, 140, 17}, 100, 1, 10, 0, true);
		auto scv = std::make_shared<btos_api::gui::Scrollbar>(gds::Rect{463, 60, 17, 140}, 100, 1, 10, 100, false);
		auto txa = std::make_shared<btos_api::gui::TextArea>(gds::Rect{10, 100, 150, 100}, "A multi-line editable text area.\nWith some lines of text.\nAnother line.\nA further line.\nAn additional line.\nAn extra line.\nA superflous line.", true);
		auto grp = std::make_shared<btos_api::gui::GroupBox>(gds::Rect{165, 110, 170, 150}, "Subformy within");
		auto tst1 = std::make_shared<btos_api::gui::TestControl>(gds::Rect{350, 110, 100, 30});
		tst1->OnEvent([] (const wm_Event &e){
			tfm::printf("Test: EventType: %s\n", e.type);
			return true;
		});
		
		btos_api::gui::RadioGroup<int> rgrp;
		rgrp.AddButton(rd1, 1);
		rgrp.AddButton(rd2, 2);
		rgrp.AddButton(rd3, 3);
		
		auto sfrm = std::make_shared<btos_api::gui::SubForm>(gds::Rect{170, 130, 150, 120});
		auto sbtn = std::make_shared<btos_api::gui::Button>(gds::Rect{10, 10, 100, 30}, "Button 3");
		sbtn->OnAction([&] {lbl2->SetText("Button 3");});
		auto tst2 = std::make_shared<btos_api::gui::TestControl>(gds::Rect{10, 50, 100, 30});
		tst2->OnEvent([] (const wm_Event &e){
			tfm::printf("Subform Test: EventType: %s\n", e.type);
			return true;
		});
		sfrm->AddControls({sbtn, tst2});
		
		auto mBtn = std::make_shared<btos_api::gui::Button>(gds::Rect{10, 260, 100, 30}, "More...");
		
		frm->AddControls({btn1, btn2, lbl1, lbl2, txt, sld, chk, rd1, rd2, rd3, sch, scv, txa, grp, sfrm, tst1, mBtn});
		frm->OnClose([]{
			tfm::printf("Form close.\n");
			return false;
		});
		
		btos_api::wm::EventLoop loop({frm});
		mBtn->OnAction([&] {MoreForm(loop);});
		loop.RunLoop();
	}catch(std::exception &e){
		int status;
		const char *typeName = abi::__cxa_demangle(typeid(e).name(), 0, 0, &status);
		std::cerr << "Exception of type: " << typeName << std::endl;
		std::cerr << "What: " << e.what() << std::endl;
	}
	return 0;
}
