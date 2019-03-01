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

#include <wm/eventloop.hpp>

#include <cxxabi.h>

int main(){
	try{
		auto frm = std::make_shared<btos_api::gui::Form>(gds::Rect{200, 200, 500, 300}, wm_WindowOptions::Default, "GUI Controls Test");
		auto btn1 = std::make_shared<btos_api::gui::Button>(gds::Rect{10, 10, 100, 30}, "Button 1", [] {std::cout << "Button 1 pressed." << std::endl;});
		auto btn2 = std::make_shared<btos_api::gui::Button>(gds::Rect{10, 50, 100, 30}, "Button 2", [] {std::cout << "Button 2 pressed." << std::endl;});
		auto lbl = std::make_shared<btos_api::gui::Label>(gds::Rect{120, 10, 100, 20}, "A Label");
		auto txt = std::make_shared<btos_api::gui::TextBox>(gds::Rect{220, 10, 100, 20}, "An editable textbox");
		auto sld = std::make_shared<btos_api::gui::Slider>(gds::Rect{340, 10, 140, 20}, 0, 100, 50, 5);
		auto chk = std::make_shared<btos_api::gui::Checkbox>(gds::Rect{120, 30, 100, 20}, "A checkbox", true);
		auto rd1 = std::make_shared<btos_api::gui::RadioButton>(gds::Rect{220, 35, 100, 20}, "Radio 1", false);
		auto rd2 = std::make_shared<btos_api::gui::RadioButton>(gds::Rect{220, 60, 100, 20}, "Radio 2", false);
		auto rd3 = std::make_shared<btos_api::gui::RadioButton>(gds::Rect{220, 85, 100, 20}, "Radio 3", true);
		auto sch = std::make_shared<btos_api::gui::Scrollbar>(gds::Rect{340, 35, 140, 17}, 100, 5, 10, 0, true);
		auto scv = std::make_shared<btos_api::gui::Scrollbar>(gds::Rect{463, 60, 17, 140}, 100, 5, 10, 100, false);
		
		btos_api::gui::RadioGroup<int> rgrp;
		rgrp.AddButton(rd1, 1);
		rgrp.AddButton(rd2, 2);
		rgrp.AddButton(rd3, 3);
		
		frm->AddControls({btn1, btn2, lbl, txt, sld, chk, rd1, rd2, rd3, sch, scv});
		
		btos_api::wm::EventLoop loop({frm});
		loop.RunLoop();
	}catch(std::exception &e){
		int status;
		const char *typeName = abi::__cxa_demangle(typeid(e).name(), 0, 0, &status);
		std::cerr << "Exception of type: " << typeName << std::endl;
		std::cerr << "What: " << e.what() << std::endl;
	}
	return 0;
}
