#include <iostream>

#include <gui/form.hpp>
#include <gui/button.hpp>
#include <gui/label.hpp>
#include <gui/textbox.hpp>
#include <wm/eventloop.hpp>

int main(){
	auto frm = std::make_shared<btos_api::gui::Form>(gds::Rect{200, 200, 500, 300}, wm_WindowOptions::Default, "GUI Controls Test");
	auto btn = std::make_shared<btos_api::gui::Button>(gds::Rect{10, 10, 100, 30}, "A Button", [] {std::cout << "Button pressed." << std::endl;});
	auto lbl = std::make_shared<btos_api::gui::Label>(gds::Rect{120, 10, 100, 20}, "A Label");
	auto txt = std::make_shared<btos_api::gui::TextBox>(gds::Rect{220, 10, 100, 20}, "An editable textbox");
	
	frm->AddControls({btn, lbl, txt});
	
	btos_api::wm::EventLoop loop({frm});
	loop.RunLoop();
	return 0;
}
