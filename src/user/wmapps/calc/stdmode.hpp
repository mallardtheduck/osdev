#ifndef _STDMODE_HPP
#define _STDMODE_HPP

#include <gui/form.hpp>
#include <gui/label.hpp>
#include <gui/textbox.hpp>

#include <util/tinyformat.hpp>

#include "icalcmode.hpp"
#include "calc.hpp"

class StandardMode : public ICalcMode{
private:
	std::shared_ptr<btos_api::gui::TextBox> output;
	std::shared_ptr<btos_api::gui::Label> curOp;
	btos_api::gds::Point pos;
	
	enum class OpState{
		Default, Add, Subtract, Multiply, Divide, Equals=Default
	};
	
	OpState opState = OpState::Default;
	double curTotal, curValue;
	bool awaiting = false;
	bool curValueValid = false;
	
	void UpdateOp();
	double Calculate();
	
	template<int N> void HandleDigit(){
		auto text = awaiting ? "" : output->GetText();
		text += (char)('0' + N);
		output->SetText(text);
		awaiting = false;
		curValueValid = false;
	}

	template<OpState O> void HandleOp(){
		curTotal = Calculate();
		opState = O;
		UpdateOp();
		output->SetText(tfm::format("%s", curTotal));
		awaiting = true;
	}
	
	void HandleDecimal();
	void HandleClear();
	void HandleClearEntry();
	void HandleSqrt();
	void HandlePercent();
	bool HandleKeyPress(uint32_t key);
	
	double GetCurrentValue();
	
public:
	StandardMode(const btos_api::gds::Point &pos);
	std::shared_ptr<btos_api::gui::Form> Show();
};

#endif