#define BTOS_NO_USING

#include <gui/form.hpp>
#include <gui/label.hpp>
#include <gui/button.hpp>
#include <gui/imagebutton.hpp>

#include <gui/shell/utils.hpp>

#include <wm/eventloop.hpp>

namespace gui = btos_api::gui;
namespace wm = btos_api::wm;
namespace gds = btos_api::gds;
namespace sh = gui::shell;

static const uint32_t baseFormWidth = 71;
static const uint32_t formHeight = 64;
static const uint32_t appBtnSize = 64;
static const uint32_t margin = 5;

int main(){
	uint32_t formWidth = baseFormWidth + (3 * appBtnSize);
	
	auto form = std::make_shared<gui::Form>(gds::Rect{0, 0, formWidth, formHeight}, wm_WindowOptions::NoTitle | wm_WindowOptions::Unlisted, "Launcher");
	auto timeLbl = std::make_shared<gui::Label>(gds::Rect{5, 5, 61, 21}, "12:34 PM");
	auto exitBtn = std::make_shared<gui::Button>(gds::Rect{5, 31, 28, 28}, "X");
	auto runBtn = std::make_shared<gui::Button>(gds::Rect{38, 31, 28, 28}, "R");
	
	auto app1Btn = std::make_shared<gui::ImageButton>(gds::Rect{baseFormWidth + margin, 5, 54, 54}, sh::GetPathIcon("HDD:/GUI/APPVIEW.ELX", 32));
	auto app2Btn = std::make_shared<gui::ImageButton>(gds::Rect{baseFormWidth + appBtnSize + margin, 5, 54, 54}, sh::GetPathIcon("HDD:/GUI/FOLDER.ELX", 32));
	auto app3Btn = std::make_shared<gui::ImageButton>(gds::Rect{baseFormWidth + (2 * appBtnSize) + margin, 5, 54, 54}, sh::GetPathIcon("HDD:/BTOS/BIN/TERMWIN.ELX", 32));
	
	form->AddControls({timeLbl, exitBtn, runBtn, app1Btn, app2Btn, app3Btn});
	
	auto mode = form->GetScreenMode();
	int32_t formX = (mode.width - formWidth) / 2;
	int32_t formY = mode.height - formHeight;
	
	form->SetPosition({formX, formY});
	
	wm::EventLoop loop;
	loop.AddWindow(form);
	form->Show();
	loop.RunLoop();
	
	return 0;
}