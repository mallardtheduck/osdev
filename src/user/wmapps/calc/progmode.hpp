#ifndef _PROGMODE_HPP
#define _PROGMODE_HPP

#include <gui/form.hpp>
#include <gui/label.hpp>
#include <gui/textbox.hpp>
#include <gui/radiobutton.hpp>
#include <gui/button.hpp>

#include <util/tinyformat.hpp>

#include "icalcmode.hpp"
#include "calc.hpp"

class ProgrammerMode : public ICalcMode{
private:
	std::shared_ptr<btos_api::gui::TextBox> output;
	std::shared_ptr<btos_api::gui::Label> curOp;
	btos_api::gds::Point pos;
	
	std::shared_ptr<btos_api::gui::Button> digit0;
	std::shared_ptr<btos_api::gui::Button> digit1;
	std::shared_ptr<btos_api::gui::Button> digit2;
	std::shared_ptr<btos_api::gui::Button> digit3;
	std::shared_ptr<btos_api::gui::Button> digit4;
	std::shared_ptr<btos_api::gui::Button> digit5;
	std::shared_ptr<btos_api::gui::Button> digit6;
	std::shared_ptr<btos_api::gui::Button> digit7;
	std::shared_ptr<btos_api::gui::Button> digit8;
	std::shared_ptr<btos_api::gui::Button> digit9;
	std::shared_ptr<btos_api::gui::Button> digitA;
	std::shared_ptr<btos_api::gui::Button> digitB;
	std::shared_ptr<btos_api::gui::Button> digitC;
	std::shared_ptr<btos_api::gui::Button> digitD;
	std::shared_ptr<btos_api::gui::Button> digitE;
	std::shared_ptr<btos_api::gui::Button> digitF;
	
	enum class OpState{
		Default, Add, Subtract, Multiply, Divide,
		LShift, RShift, And, Or, XOr, Mod, Extend,
		Equals=Default
	};
	
	OpState opState = OpState::Default;
	uint64_t curTotal, curValue;
	bool awaiting = false;
	bool curValueValid = false;
	
	enum class BaseMode{
		Dec, Hex, Bin
	};
	BaseMode lastBase = BaseMode::Dec;
	
	btos_api::gui::RadioGroup<BaseMode> baseModeGroup;
	
	enum class WidthMode{
		Bits8, Bits16, Bits32, Bits64
	};
	
	btos_api::gui::RadioGroup<WidthMode> widthModeGroup;
	
	void UpdateOp();
	uint64_t Calculate();
	void SetOutput(uint64_t val);
	
	template<char c> void HandleDigit(){
		auto text = awaiting ? "" : output->GetText();
		text += c;
		output->SetText(text);
		awaiting = false;
		curValueValid = false;
	}

	template<OpState O> void HandleOp(){
		curTotal = Calculate();
		opState = O;
		UpdateOp();
		SetOutput(curTotal);
		awaiting = true;
	}
	
	void HandleClear();
	void HandleClearEntry();
	bool HandleKeyPress(uint32_t key);
	void HandleNegate();
	void HandleNot();
	
	uint64_t GetCurrentValue();
	uint64_t GetCurrentValue(BaseMode base);
	
	void SwitchBase();
public:
	ProgrammerMode(const btos_api::gds::Point &pos);
	std::shared_ptr<btos_api::gui::Form> Show();
};

#endif