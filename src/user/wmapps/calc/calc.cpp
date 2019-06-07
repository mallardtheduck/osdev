#define BTOS_NO_USING

#include <gui/form.hpp>
#include <gui/button.hpp>
#include <gui/textbox.hpp>
#include <gui/toolbar.hpp>
#include <gui/label.hpp>

#include <wm/eventloop.hpp>
#include <dev/keyboard.h>

#include "calc_resc.tar.h"

#include <gds/libgds.h>
#include <btos/resc.h>
#include <unistd.h>

#include <cstdlib>
#include <exception>
#include <util/tinyformat.hpp>

namespace gui = btos_api::gui;
namespace resc = btos_api::resc;
namespace gds = btos_api::gds;

resc::RescHandle rsc;

std::shared_ptr<gui::TextBox> output;
std::shared_ptr<gui::Label> curOp;

enum class OpState{
	Default, Add, Subtract, Multiply, Divide, Equals=Default
};

OpState opState;
double curTotal;
bool awaiting = false;

std::shared_ptr<gds::Surface> LoadPNG(const char *path){
	auto fd = resc::Resc_OpenResc(rsc, path);
	auto ret = GDS_LoadPNG(fd);
	close(fd);
	return std::make_shared<gds::Surface>(std::move(gds::Surface::Wrap(ret, true)));
}

void UpdateOp(){
	switch(opState){
		case OpState::Default:
			curOp->SetText("=");
			break;
		case OpState::Add:
			curOp->SetText("+");
			break;
		case OpState::Subtract:
			curOp->SetText("-");
			break;
		case OpState::Multiply:
			curOp->SetText("\xC3\x97");
			break;
		case OpState::Divide:
			curOp->SetText("\xC3\xB7");
			break;
	}
}

double Calculate(){
	auto curValue = strtod(output->GetText().c_str(), nullptr);
	switch(opState){
		case OpState::Default:
			return curValue;
		case OpState::Add:
			return curTotal + curValue;
		case OpState::Subtract:
			return curTotal - curValue;
		case OpState::Multiply:
			return curTotal * curValue;
		case OpState::Divide:
			return curTotal / curValue;
	}
	throw std::exception();
}

template<int N> void HandleDigit(){
	auto text = awaiting ? "" : output->GetText();
	text += (char)('0' + N);
	output->SetText(text);
	awaiting = false;
}

void HandleDecimal(){
	auto text = awaiting ? "" : output->GetText();
	if(text.find('.') == std::string::npos){
		text += '.';
		output->SetText(text);
		awaiting = false;
	}else if(text == ""){
		output->SetText("0.");
		awaiting = false;
	}
}

template<OpState O> void HandleOp(){
	curTotal = Calculate();
	opState = O;
	UpdateOp();
	output->SetText(tfm::format("%s", curTotal));
	awaiting = true;
}

void HandleClear(){
	opState = OpState::Default;
	UpdateOp();
	curTotal = 0;
	output->SetText("");
}

void HandleClearEntry(){
	output->SetText("");
	awaiting = true;
}

void HandleSqrt(){
	auto curValue = strtod(output->GetText().c_str(), nullptr);
	curTotal = sqrt(curValue);
	output->SetText(tfm::format("%s", curTotal));
	opState = OpState::Default;
	UpdateOp();
}

void HandlePercent(){
	auto curValue = strtod(output->GetText().c_str(), nullptr);
	curValue = curTotal * (curValue / 100.0);
	output->SetText(tfm::format("%s", curValue));
	awaiting = true;
}

bool HandleKeyPress(uint32_t key){
	if(!(key & KeyFlags::NonASCII)){
		char c = KB_char(key);
		c = tolower(c);
		switch(c){
			case '0':
				HandleDigit<0>();
				break;
			case '1':
				HandleDigit<1>();
				break;
			case '2':
				HandleDigit<2>();
				break;
			case '3':
				HandleDigit<3>();
				break;
			case '4':
				HandleDigit<4>();
				break;
			case '5':
				HandleDigit<5>();
				break;
			case '6':
				HandleDigit<6>();
				break;
			case '7':
				HandleDigit<7>();
				break;
			case '8':
				HandleDigit<8>();
				break;
			case '9':
				HandleDigit<9>();
				break;
			case '.':
				HandleDecimal();
				break;
			
			case '+':
				HandleOp<OpState::Add>();
				break;
			case '-':
				HandleOp<OpState::Subtract>();
				break;
			case '*':
				HandleOp<OpState::Multiply>();
				break;
			case '/':
				HandleOp<OpState::Divide>();
				break;
			case '=':
			case '\n':
				HandleOp<OpState::Equals>();
				break;
			
			case 'r':
			case 's':
				HandleSqrt();
				break;
			case '%':
			case 'p':
				HandlePercent();
				break;
			
			
			case 'c':
				HandleClear();
				break;
			case 'e':
			case 0x08:
				HandleClearEntry();
				break;
		}
	}
	return true;
}

int main(){
	rsc = resc::Resc_LocalOpen(calc_resc_data, calc_resc_size);
	
	auto form = std::make_shared<gui::Form>(gds::Rect{100, 100, 210, 232}, gui::FormOptions::Fixed, "Calculator");
	
	auto toolbar = std::make_shared<gui::Toolbar>();
	auto tbModeStd = std::make_shared<gui::ToolbarButton>(LoadPNG("calc_standard.png"));
	tbModeStd->Disable();
	auto tbModeSci = std::make_shared<gui::ToolbarButton>(LoadPNG("calc_scientific.png"));
	auto tbModeProg = std::make_shared<gui::ToolbarButton>(LoadPNG("calc_programmer.png"));
	auto tbSpacer = std::make_shared<gui::ToolbarSpacer>();
	auto tbCopy = std::make_shared<gui::ToolbarButton>(LoadPNG("editcopy.png"));
	auto tbPaste = std::make_shared<gui::ToolbarButton>(LoadPNG("editpaste.png"));
	toolbar->Controls().insert(toolbar->Controls().end(), {tbModeStd, tbModeSci, tbModeProg, tbSpacer, tbCopy, tbPaste});
	toolbar->Refresh();
	
	curOp = std::make_shared<gui::Label>(gds::Rect{180, 42, 20, 20}, "=");
	output = std::make_shared<gui::TextBox>(gds::Rect{10, 42, 160, 20});
	output->OnKeyPress(HandleKeyPress);
	
	auto opDivide = std::make_shared<gui::Button>(gds::Rect{170, 72, 30, 30}, "\xC3\xB7");
	opDivide->OnAction(HandleOp<OpState::Divide>);
	auto opMultiply = std::make_shared<gui::Button>(gds::Rect{170, 112, 30, 30}, "\xC3\x97");
	opMultiply->OnAction(HandleOp<OpState::Multiply>);
	auto opSubtract = std::make_shared<gui::Button>(gds::Rect{170, 152, 30, 30}, "-");
	opSubtract->OnAction(HandleOp<OpState::Subtract>);
	auto opAdd = std::make_shared<gui::Button>(gds::Rect{170, 192, 30, 30}, "+");
	opAdd->OnAction(HandleOp<OpState::Add>);
	
	auto clear = std::make_shared<gui::Button>(gds::Rect{10, 72, 30, 30}, "C");
	clear->OnAction(HandleClear);
	auto clearEntry = std::make_shared<gui::Button>(gds::Rect{10, 112, 30, 30}, "CE");
	clearEntry->OnAction(HandleClearEntry);
	auto opSqrt = std::make_shared<gui::Button>(gds::Rect{10, 152, 30, 30}, "\xE2\x88\x9A");
	opSqrt->OnAction(HandleSqrt);
	auto opPercent = std::make_shared<gui::Button>(gds::Rect{10, 192, 30, 30}, "%");
	opPercent->OnAction(HandlePercent);
	
	auto digit7 = std::make_shared<gui::Button>(gds::Rect{50, 72, 30, 30}, "7");
	digit7->OnAction(HandleDigit<7>);
	auto digit8 = std::make_shared<gui::Button>(gds::Rect{90, 72, 30, 30}, "8");
	digit8->OnAction(HandleDigit<8>);
	auto digit9 = std::make_shared<gui::Button>(gds::Rect{130, 72, 30, 30}, "9");
	digit9->OnAction(HandleDigit<9>);
	
	auto digit4 = std::make_shared<gui::Button>(gds::Rect{50, 112, 30, 30}, "4");
	digit4->OnAction(HandleDigit<4>);
	auto digit5 = std::make_shared<gui::Button>(gds::Rect{90, 112, 30, 30}, "5");
	digit5->OnAction(HandleDigit<5>);
	auto digit6 = std::make_shared<gui::Button>(gds::Rect{130, 112, 30, 30}, "6");
	digit6->OnAction(HandleDigit<6>);
	
	auto digit1 = std::make_shared<gui::Button>(gds::Rect{50, 152, 30, 30}, "1");
	digit1->OnAction(HandleDigit<1>);
	auto digit2 = std::make_shared<gui::Button>(gds::Rect{90, 152, 30, 30}, "2");
	digit2->OnAction(HandleDigit<2>);
	auto digit3 = std::make_shared<gui::Button>(gds::Rect{130, 152, 30, 30}, "3");
	digit3->OnAction(HandleDigit<3>);
	
	auto digit0 = std::make_shared<gui::Button>(gds::Rect{50, 192, 30, 30}, "0");
	digit0->OnAction(HandleDigit<0>);
	auto decimal = std::make_shared<gui::Button>(gds::Rect{90, 192, 30, 30}, ".");
	decimal->OnAction(HandleDecimal);
	auto opEquals = std::make_shared<gui::Button>(gds::Rect{130, 192, 30, 30}, "=");
	opEquals->OnAction(HandleOp<OpState::Equals>);
	
	form->AddControls({
		toolbar, output, curOp, 
		opDivide, opMultiply, opSubtract, opAdd,
		clear, clearEntry, opSqrt, opPercent,
		digit7, digit8, digit9,
		digit4, digit5, digit6,
		digit1, digit2, digit3,
		digit0, decimal, opEquals,
	});
	form->SetFocus(output);
	
	btos_api::wm::EventLoop loop({form});
	loop.RunLoop();
	
	resc::Resc_Close(rsc);
	return 0;
}