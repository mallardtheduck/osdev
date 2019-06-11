#define BTOS_NO_USING

#include "scimode.hpp"
#include <gui/button.hpp>

namespace gds = btos_api::gds;
namespace gui = btos_api::gui;

ScientificMode::ScientificMode(const gds::Point &p) : pos(p) {}

std::shared_ptr<gui::Form> ScientificMode::Show(){
	auto form = std::make_shared<gui::Form>(gds::Rect{pos.x, pos.y, 510, 237}, gui::FormOptions::Fixed, "Calculator");
	MakeToolbarAndMenu(form);
	
	output = std::make_shared<gui::TextBox>(gds::Rect{10, 42, 380, 25});
	//output->OnKeyPress(std::bind(&StandardMode::HandleKeyPress, this, _1));
	
	auto opDivide = std::make_shared<gui::Button>(gds::Rect{170, 77, 30, 30}, "\xC3\xB7");
	//opDivide->OnAction(std::bind(&StandardMode::HandleOp<OpState::Divide>, this));
	auto opMultiply = std::make_shared<gui::Button>(gds::Rect{170, 117, 30, 30}, "\xC3\x97");
	//opMultiply->OnAction(std::bind(&StandardMode::HandleOp<OpState::Multiply>, this));
	auto opSubtract = std::make_shared<gui::Button>(gds::Rect{170, 157, 30, 30}, "-");
	//opSubtract->OnAction(std::bind(&StandardMode::HandleOp<OpState::Subtract>, this));
	auto opAdd = std::make_shared<gui::Button>(gds::Rect{170, 197, 30, 30}, "+");
	//opAdd->OnAction(std::bind(&StandardMode::HandleOp<OpState::Add>, this));
	
	auto clear = std::make_shared<gui::Button>(gds::Rect{10, 77, 30, 30}, "C");
	//clear->OnAction(std::bind(&StandardMode::HandleClear, this));
	auto clearEntry = std::make_shared<gui::Button>(gds::Rect{10, 117, 30, 30}, "CE");
	//clearEntry->OnAction(std::bind(&StandardMode::HandleClearEntry, this));
	auto opEquals = std::make_shared<gui::Button>(gds::Rect{10, 157, 30, 70}, "=");
	//opEquals->OnAction(std::bind(&StandardMode::HandleOp<OpState::Equals>, this));
	
	auto digit7 = std::make_shared<gui::Button>(gds::Rect{50, 77, 30, 30}, "7");
	//digit7->OnAction(std::bind(&StandardMode::HandleDigit<7>, this));
	auto digit8 = std::make_shared<gui::Button>(gds::Rect{90, 77, 30, 30}, "8");
	//digit8->OnAction(std::bind(&StandardMode::HandleDigit<8>, this));
	auto digit9 = std::make_shared<gui::Button>(gds::Rect{130, 77, 30, 30}, "9");
	//digit9->OnAction(std::bind(&StandardMode::HandleDigit<9>, this));
	
	auto digit4 = std::make_shared<gui::Button>(gds::Rect{50, 117, 30, 30}, "4");
	//digit4->OnAction(std::bind(&StandardMode::HandleDigit<4>, this));
	auto digit5 = std::make_shared<gui::Button>(gds::Rect{90, 117, 30, 30}, "5");
	//digit5->OnAction(std::bind(&StandardMode::HandleDigit<5>, this));
	auto digit6 = std::make_shared<gui::Button>(gds::Rect{130, 117, 30, 30}, "6");
	//digit6->OnAction(std::bind(&StandardMode::HandleDigit<6>, this));
	
	auto digit1 = std::make_shared<gui::Button>(gds::Rect{50, 157, 30, 30}, "1");
	//digit1->OnAction(std::bind(&StandardMode::HandleDigit<1>, this));
	auto digit2 = std::make_shared<gui::Button>(gds::Rect{90, 157, 30, 30}, "2");
	//digit2->OnAction(std::bind(&StandardMode::HandleDigit<2>, this));
	auto digit3 = std::make_shared<gui::Button>(gds::Rect{130, 157, 30, 30}, "3");
	//digit3->OnAction(std::bind(&StandardMode::HandleDigit<3>, this));
	
	auto digit0 = std::make_shared<gui::Button>(gds::Rect{50, 197, 30, 30}, "0");
	//digit0->OnAction(std::bind(&StandardMode::HandleDigit<0>, this));
	auto decimal = std::make_shared<gui::Button>(gds::Rect{90, 197, 30, 30}, ".");
	//decimal->OnAction(std::bind(&StandardMode::HandleDecimal, this));
	auto opExp = std::make_shared<gui::Button>(gds::Rect{130, 197, 30, 30}, "EXP");
	
	auto opLog = std::make_shared<gui::Button>(gds::Rect{210, 77, 50, 30}, "log");
	auto opLn = std::make_shared<gui::Button>(gds::Rect{270, 77, 50, 30}, "ln");
	auto opLog2 = std::make_shared<gui::Button>(gds::Rect{330, 77, 50, 30}, "log\xE2\x82\x82");
	auto opE = std::make_shared<gui::Button>(gds::Rect{390, 77, 50, 30}, "e");
	auto opPower = std::make_shared<gui::Button>(gds::Rect{450, 77, 50, 30}, "x^");
	
	auto opSin = std::make_shared<gui::Button>(gds::Rect{210, 117, 50, 30}, "sin");
	auto opCos = std::make_shared<gui::Button>(gds::Rect{270, 117, 50, 30}, "cos");
	auto opTan = std::make_shared<gui::Button>(gds::Rect{330, 117, 50, 30}, "tan");
	auto opPi = std::make_shared<gui::Button>(gds::Rect{390, 117, 50, 30}, "\xCF\x80");
	auto opFact = std::make_shared<gui::Button>(gds::Rect{450, 117, 50, 30}, "!");
	
	auto opASin = std::make_shared<gui::Button>(gds::Rect{210, 157, 50, 30}, "asin");
	auto opACos = std::make_shared<gui::Button>(gds::Rect{270, 157, 50, 30}, "acos");
	auto opATan = std::make_shared<gui::Button>(gds::Rect{330, 157, 50, 30}, "atan");
	auto opInv = std::make_shared<gui::Button>(gds::Rect{390, 157, 50, 30}, "\xC2\xB9\xE2\x81\x84x");
	auto opNeg = std::make_shared<gui::Button>(gds::Rect{450, 157, 50, 30}, "\xC2\xB1");
	
	auto opOpenParen = std::make_shared<gui::Button>(gds::Rect{210, 197, 50, 30}, "(");
	auto opCloseParen = std::make_shared<gui::Button>(gds::Rect{270, 197, 50, 30}, ")");
	auto opSqrt = std::make_shared<gui::Button>(gds::Rect{330, 197, 50, 30}, "\xE2\x88\x9A");
	auto opNRoot = std::make_shared<gui::Button>(gds::Rect{390, 197, 50, 30}, "n\xE2\x88\x9A");
	auto opSquared = std::make_shared<gui::Button>(gds::Rect{450, 197, 50, 30}, "x\xC2\xB2");
	
	auto modeDeg = std::make_shared<gui::RadioButton>(gds::Rect{455, 40, 42, 25}, "DEG", true);
	auto modeRad = std::make_shared<gui::RadioButton>(gds::Rect{400, 40, 42, 25}, "RAD", false);
	modeGroup.AddButton(modeDeg, AngleMode::Degrees);
	modeGroup.AddButton(modeRad, AngleMode::Radians);
	
	form->AddControls({
		output, modeDeg, modeRad,
		opDivide, opMultiply, opSubtract, opAdd,
		clear, clearEntry, opEquals,
		digit7, digit8, digit9,
		digit4, digit5, digit6,
		digit1, digit2, digit3,
		digit0, decimal, opExp,
		opLog, opLn, opLog2, opE, opPower,
		opSin, opCos, opTan, opPi, opFact,
		opASin, opACos, opATan, opInv, opNeg,
		opOpenParen, opCloseParen, opSqrt, opNRoot, opSquared
	});
	form->SetFocus(output);
	return form;
}