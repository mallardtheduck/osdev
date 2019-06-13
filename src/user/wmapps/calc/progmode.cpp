#define BTOS_NO_USING

#include "progmode.hpp"
#include "calc.hpp"

#include <dev/keyboard.h>

#include <cstdlib>
#include <exception>

namespace gui = btos_api::gui;
namespace gds = btos_api::gds;
namespace wm = btos_api::wm;

void ProgrammerMode::SetOutput(uint64_t val){
	std::string fmt;
	switch(baseModeGroup.GetValue()){
		case BaseMode::Dec:
			fmt = "%d";
			break;
		case BaseMode::Hex:
			fmt = "%X";
			break;
		case BaseMode::Bin:
			fmt = "%x";
			break;
	}
	std::string text;
	switch(widthModeGroup.GetValue()){
		case WidthMode::Bits8:
			text = tfm::format(fmt.c_str(), (uint8_t)val);
			break;
		case WidthMode::Bits16:
			text = tfm::format(fmt.c_str(), (uint16_t)val);
			break;
		case WidthMode::Bits32:
			text = tfm::format(fmt.c_str(), (uint32_t)val);
			break;
		case WidthMode::Bits64:
			text = tfm::format(fmt.c_str(), (uint64_t)val);
			break;
	}
	if(baseModeGroup.GetValue() == BaseMode::Bin){
		std::stringstream binText;
		for(auto c : text){
			switch(c){
				case '0':
					binText << "0000";
					break;
				case '1':
					binText << "0001";
					break;
				case '2':
					binText << "0010";
					break;
				case '3':
					binText << "0011";
					break;
				case '4':
					binText << "0100";
					break;
				case '5':
					binText << "0101";
					break;
				case '6':
					binText << "0110";
					break;
				case '7':
					binText << "0111";
					break;
				case '8':
					binText << "1000";
					break;
				case '9':
					binText << "1001";
					break;
				case 'a':
					binText << "1010";
					break;
				case 'b':
					binText << "1011";
					break;
				case 'c':
					binText << "1100";
					break;
				case 'd':
					binText << "1101";
					break;
				case 'e':
					binText << "1110";
					break;
				case 'f':
					binText << "1111";
					break;
			}
		}
		text = binText.str();
	}
	output->SetText(text);
}

void ProgrammerMode::UpdateOp(){
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
		case OpState::LShift:
			curOp->SetText("<<");
			break;
		case OpState::RShift:
			curOp->SetText(">>");
			break;
		case OpState::And:
			curOp->SetText("&");
			break;
		case OpState::Or:
			curOp->SetText("|");
			break;
		case OpState::XOr:
			curOp->SetText("^");
			break;
		case OpState::Mod:
			curOp->SetText("%");
			break;
		case OpState::Extend:
			curOp->SetText("Ex");
			break;
	}
}

uint64_t ProgrammerMode::Calculate(){
	auto value = GetCurrentValue();
	uint64_t ret = -1;
	switch(opState){
		case OpState::Default:
			ret = value;
			break;
		case OpState::Add:
			ret = curTotal + value;
			break;
		case OpState::Subtract:
			ret = curTotal - value;
			break;
		case OpState::Multiply:
			ret = curTotal * value;
			break;
		case OpState::Divide:
			ret = curTotal / value;
			break;
		case OpState::LShift:
			ret = curTotal << value;
			break;
		case OpState::RShift:
			ret = curTotal >> value;
			break;
		case OpState::And:
			ret = curTotal & value;
			break;
		case OpState::Or:
			ret = curTotal | value;
			break;
		case OpState::XOr:
			ret = curTotal ^ value;
			break;
		case OpState::Mod:
			ret = curTotal % value;
			break;
		case OpState::Extend:{
			bool val = (curTotal >> value) & 1;
			uint64_t mask = val ? UINT64_MAX : 0;
			if(value > 64) ret = mask;
			mask = (mask >> value) << value;
			ret = curTotal | mask;
			break;
		}
		default:
			throw std::exception();
	}
	curValue = ret;
	curValueValid = true;
	return ret;
}

void ProgrammerMode::HandleClear(){
	opState = OpState::Default;
	UpdateOp();
	curTotal = 0;
	output->SetText("");
	curValueValid = false;
}

void ProgrammerMode::HandleClearEntry(){
	output->SetText("");
	awaiting = true;
	curValueValid = false;
}

bool ProgrammerMode::HandleKeyPress(uint32_t key){
	if(!(key & KeyFlags::NonASCII)){
		char c = KB_char(key);
		c = toupper(c);
		switch(c){
			case '0':
				HandleDigit<'0'>();
				break;
			case '1':
				HandleDigit<'1'>();
				break;
			case '2':
				if(baseModeGroup.GetValue() == BaseMode::Dec || baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'2'>();
				break;
			case '3':
				if(baseModeGroup.GetValue() == BaseMode::Dec || baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'3'>();
				break;
			case '4':
				if(baseModeGroup.GetValue() == BaseMode::Dec || baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'4'>();
				break;
			case '5':
				if(baseModeGroup.GetValue() == BaseMode::Dec || baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'5'>();
				break;
			case '6':
				if(baseModeGroup.GetValue() == BaseMode::Dec || baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'6'>();
				break;
			case '7':
				if(baseModeGroup.GetValue() == BaseMode::Dec || baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'7'>();
				break;
			case '8':
				if(baseModeGroup.GetValue() == BaseMode::Dec || baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'8'>();
				break;
			case '9':
				if(baseModeGroup.GetValue() == BaseMode::Dec || baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'9'>();
				break;
			case 'A':
				if(baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'A'>();
				break;
			case 'B':
				if(baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'B'>();
				break;
			case 'C':
				if(baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'C'>();
				break;
			case 'D':
				if(baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'D'>();
				break;
			case 'E':
				if(baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'E'>();
				break;
			case 'F':
				if(baseModeGroup.GetValue() == BaseMode::Hex) HandleDigit<'F'>();
				break;
			
			case '#':
				HandleNegate();
				break;
			case '~':
				HandleNot();
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
			case '<':
				HandleOp<OpState::LShift>();
				break;
			case '>':
				HandleOp<OpState::RShift>();
				break;
			case '&':
				HandleOp<OpState::And>();
				break;
			case '|':
				HandleOp<OpState::Or>();
				break;
			case '^':
				HandleOp<OpState::XOr>();
				break;
			case '%':
				HandleOp<OpState::Mod>();
				break;
			case 'X':
				HandleOp<OpState::Extend>();
				break;
			case '=':
			case '\n':
				HandleOp<OpState::Equals>();
				break;
			case 0x08:
				HandleClearEntry();
				break;
		}
	}else if(KB_code(key) == (KeyFlags::NonASCII | KeyCodes::Delete)){
		HandleClear();
	}
	return true;
}

void ProgrammerMode::HandleNegate(){
	curTotal = GetCurrentValue() * -1;
	SetOutput(curTotal);
	opState = OpState::Default;
	curValue = curTotal;
	curValueValid = true;
	UpdateOp();
}

void ProgrammerMode::HandleNot(){
	curTotal = ~GetCurrentValue();
	SetOutput(curTotal);
	opState = OpState::Default;
	curValue = curTotal;
	curValueValid = true;
	UpdateOp();
}

uint64_t ProgrammerMode::GetCurrentValue(){
	return GetCurrentValue(baseModeGroup.GetValue());
}

uint64_t ProgrammerMode::GetCurrentValue(BaseMode baseMode){
	int base = 0;
	switch(baseMode){
		case BaseMode::Dec:
			base = 10;
			break;
		case BaseMode::Hex:
			base = 16;
			break;
		case BaseMode::Bin:
			base = 2;
			break;
	}
	if(curValueValid) return curValue;
	else return strtoull(output->GetText().c_str(), nullptr, base);
}

void ProgrammerMode::SwitchBase(){
	auto val = GetCurrentValue(lastBase);
	SetOutput(val);
	awaiting = true;
	digit0->Enable();
	digit1->Enable();
	if(baseModeGroup.GetValue() == BaseMode::Bin){
		digit2->Disable();
		digit3->Disable();
		digit4->Disable();
		digit5->Disable();
		digit6->Disable();
		digit7->Disable();
		digit8->Disable();
		digit9->Disable();
		digitA->Disable();
		digitB->Disable();
		digitC->Disable();
		digitD->Disable();
		digitE->Disable();
		digitF->Disable();
	}else if(baseModeGroup.GetValue() == BaseMode::Dec){
		digit2->Enable();
		digit3->Enable();
		digit4->Enable();
		digit5->Enable();
		digit6->Enable();
		digit7->Enable();
		digit8->Enable();
		digit9->Enable();
		digitA->Disable();
		digitB->Disable();
		digitC->Disable();
		digitD->Disable();
		digitE->Disable();
		digitF->Disable();
	}else if(baseModeGroup.GetValue() == BaseMode::Hex){
		digit2->Enable();
		digit3->Enable();
		digit4->Enable();
		digit5->Enable();
		digit6->Enable();
		digit7->Enable();
		digit8->Enable();
		digit9->Enable();
		digitA->Enable();
		digitB->Enable();
		digitC->Enable();
		digitD->Enable();
		digitE->Enable();
		digitF->Enable();
	}
	lastBase = baseModeGroup.GetValue();
}

ProgrammerMode::ProgrammerMode(const gds::Point &p) : pos(p) {}

std::shared_ptr<gui::Form> ProgrammerMode::Show(){
	using namespace std::placeholders;
	
	auto form = std::make_shared<gui::Form>(gds::Rect{pos.x, pos.y, 360, 277}, gui::FormOptions::Fixed, "Calculator");
	
	MakeToolbarAndMenu(form);
	
	curOp = std::make_shared<gui::Label>(gds::Rect{330, 42, 20, 25}, "=");
	output = std::make_shared<gui::TextBox>(gds::Rect{10, 42, 310, 25});
	output->OnKeyPress(std::bind(&ProgrammerMode::HandleKeyPress, this, _1));
	
	auto opDivide = std::make_shared<gui::Button>(gds::Rect{170, 77, 30, 30}, "\xC3\xB7");
	opDivide->OnAction(std::bind(&ProgrammerMode::HandleOp<OpState::Divide>, this));
	auto opMultiply = std::make_shared<gui::Button>(gds::Rect{170, 117, 30, 30}, "\xC3\x97");
	opMultiply->OnAction(std::bind(&ProgrammerMode::HandleOp<OpState::Multiply>, this));
	auto opSubtract = std::make_shared<gui::Button>(gds::Rect{170, 157, 30, 30}, "-");
	opSubtract->OnAction(std::bind(&ProgrammerMode::HandleOp<OpState::Subtract>, this));
	auto opAdd = std::make_shared<gui::Button>(gds::Rect{170, 197, 30, 30}, "+");
	opAdd->OnAction(std::bind(&ProgrammerMode::HandleOp<OpState::Add>, this));
	
	auto clear = std::make_shared<gui::Button>(gds::Rect{10, 77, 30, 30}, "C");
	clear->OnAction(std::bind(&ProgrammerMode::HandleClear, this));
	auto clearEntry = std::make_shared<gui::Button>(gds::Rect{10, 117, 30, 30}, "CE");
	clearEntry->OnAction(std::bind(&ProgrammerMode::HandleClearEntry, this));
	auto opEquals = std::make_shared<gui::Button>(gds::Rect{10, 157, 30, 110}, "=");
	opEquals->OnAction(std::bind(&ProgrammerMode::HandleOp<OpState::Equals>, this));
	
	digit7 = std::make_shared<gui::Button>(gds::Rect{50, 77, 30, 30}, "7");
	digit7->OnAction(std::bind(&ProgrammerMode::HandleDigit<'7'>, this));
	digit8 = std::make_shared<gui::Button>(gds::Rect{90, 77, 30, 30}, "8");
	digit8->OnAction(std::bind(&ProgrammerMode::HandleDigit<'8'>, this));
	digit9 = std::make_shared<gui::Button>(gds::Rect{130, 77, 30, 30}, "9");
	digit9->OnAction(std::bind(&ProgrammerMode::HandleDigit<'9'>, this));
	
	digit4 = std::make_shared<gui::Button>(gds::Rect{50, 117, 30, 30}, "4");
	digit4->OnAction(std::bind(&ProgrammerMode::HandleDigit<'4'>, this));
	digit5 = std::make_shared<gui::Button>(gds::Rect{90, 117, 30, 30}, "5");
	digit5->OnAction(std::bind(&ProgrammerMode::HandleDigit<'5'>, this));
	digit6 = std::make_shared<gui::Button>(gds::Rect{130, 117, 30, 30}, "6");
	digit6->OnAction(std::bind(&ProgrammerMode::HandleDigit<'6'>, this));
	
	digit1 = std::make_shared<gui::Button>(gds::Rect{50, 157, 30, 30}, "1");
	digit1->OnAction(std::bind(&ProgrammerMode::HandleDigit<'1'>, this));
	digit2 = std::make_shared<gui::Button>(gds::Rect{90, 157, 30, 30}, "2");
	digit2->OnAction(std::bind(&ProgrammerMode::HandleDigit<'2'>, this));
	digit3 = std::make_shared<gui::Button>(gds::Rect{130, 157, 30, 30}, "3");
	digit3->OnAction(std::bind(&ProgrammerMode::HandleDigit<'3'>, this));
	
	digit0 = std::make_shared<gui::Button>(gds::Rect{50, 197, 30, 30}, "0");
	digit0->OnAction(std::bind(&ProgrammerMode::HandleDigit<'0'>, this));
	digitA = std::make_shared<gui::Button>(gds::Rect{90, 197, 30, 30}, "A");
	digitA->OnAction(std::bind(&ProgrammerMode::HandleDigit<'A'>, this));
	digitB = std::make_shared<gui::Button>(gds::Rect{130, 197, 30, 30}, "B");
	digitB->OnAction(std::bind(&ProgrammerMode::HandleDigit<'B'>, this));
	
	digitC = std::make_shared<gui::Button>(gds::Rect{50, 237, 30, 30}, "C");
	digitC->OnAction(std::bind(&ProgrammerMode::HandleDigit<'C'>, this));
	digitD = std::make_shared<gui::Button>(gds::Rect{90, 237, 30, 30}, "D");
	digitD->OnAction(std::bind(&ProgrammerMode::HandleDigit<'D'>, this));
	digitE = std::make_shared<gui::Button>(gds::Rect{130, 237, 30, 30}, "E");
	digitE->OnAction(std::bind(&ProgrammerMode::HandleDigit<'E'>, this));
	digitF = std::make_shared<gui::Button>(gds::Rect{170, 237, 30, 30}, "F");
	digitF->OnAction(std::bind(&ProgrammerMode::HandleDigit<'F'>, this));
	
	auto modeDec = std::make_shared<gui::RadioButton>(gds::Rect{210, 77, 40, 30}, "DEC", true);
	baseModeGroup.AddButton(modeDec, BaseMode::Dec);
	auto modeHex = std::make_shared<gui::RadioButton>(gds::Rect{260, 77, 40, 30}, "HEX", false);
	baseModeGroup.AddButton(modeHex, BaseMode::Hex);
	auto modeBin = std::make_shared<gui::RadioButton>(gds::Rect{310, 77, 40, 30}, "BIN", false);
	baseModeGroup.AddButton(modeBin, BaseMode::Bin);
	
	baseModeGroup.OnChange([&](BaseMode){
		SwitchBase();
	});
	
	auto mode8 = std::make_shared<gui::RadioButton>(gds::Rect{210, 117, 30, 30}, "8", false);
	widthModeGroup.AddButton(mode8, WidthMode::Bits8);
	auto mode16 = std::make_shared<gui::RadioButton>(gds::Rect{245, 117, 30, 30}, "16", false);
	widthModeGroup.AddButton(mode16, WidthMode::Bits16);
	auto mode32 = std::make_shared<gui::RadioButton>(gds::Rect{280, 117, 30, 30}, "32", false);
	widthModeGroup.AddButton(mode32, WidthMode::Bits32);
	auto mode64 = std::make_shared<gui::RadioButton>(gds::Rect{315, 117, 35, 30}, "64", true);
	widthModeGroup.AddButton(mode64, WidthMode::Bits64);
	
	auto opLShift = std::make_shared<gui::Button>(gds::Rect{210, 157, 40, 30}, "<<");
	opLShift->OnAction(std::bind(&ProgrammerMode::HandleOp<OpState::LShift>, this));
	auto opRShift = std::make_shared<gui::Button>(gds::Rect{260, 157, 40, 30}, ">>");
	opRShift->OnAction(std::bind(&ProgrammerMode::HandleOp<OpState::RShift>, this));
	auto opNeg = std::make_shared<gui::Button>(gds::Rect{310, 157, 40, 30}, "\xC2\xB1");
	opNeg->OnAction(std::bind(&ProgrammerMode::HandleNegate, this));
	
	auto opAnd = std::make_shared<gui::Button>(gds::Rect{210, 197, 40, 30}, "&");
	opAnd->OnAction(std::bind(&ProgrammerMode::HandleOp<OpState::And>, this));
	auto opOr = std::make_shared<gui::Button>(gds::Rect{260, 197, 40, 30}, "|");
	opOr->OnAction(std::bind(&ProgrammerMode::HandleOp<OpState::Or>, this));
	auto opMod = std::make_shared<gui::Button>(gds::Rect{310, 197, 40, 30}, "%");
	opMod->OnAction(std::bind(&ProgrammerMode::HandleOp<OpState::Mod>, this));
	
	auto opXOr = std::make_shared<gui::Button>(gds::Rect{210, 237, 40, 30}, "^");
	opXOr->OnAction(std::bind(&ProgrammerMode::HandleOp<OpState::XOr>, this));
	auto opNot = std::make_shared<gui::Button>(gds::Rect{260, 237, 40, 30}, "~");
	opNot->OnAction(std::bind(&ProgrammerMode::HandleNot, this));
	auto opExt = std::make_shared<gui::Button>(gds::Rect{310, 237, 40, 30}, "Ext");
	opExt->OnAction(std::bind(&ProgrammerMode::HandleOp<OpState::Extend>, this));
	
	SwitchBase();
	
	form->AddControls({
		output, curOp, 
		opDivide, opMultiply, opSubtract, opAdd,
		clear, clearEntry, opEquals,
		digit7, digit8, digit9,
		digit4, digit5, digit6,
		digit1, digit2, digit3,
		digit0, digitA, digitB,
		digitC, digitD, digitE, digitF,
		modeDec, modeHex, modeBin,
		mode8, mode16, mode32, mode64,
		opLShift, opRShift, opNeg,
		opAnd, opOr, opMod,
		opXOr, opNot, opExt,
	});
	form->SetFocus(output);
	
	return form;
}