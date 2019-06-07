#ifndef _STDMODE_HPP
#define _STDMODE_HPP

#include <gui/form.hpp>
#include <gui/label.hpp>
#include <gui/textbox.hpp>

#include <util/tinyformat.hpp>

class StandardMode{
private:
	std::shared_ptr<btos_api::gui::TextBox> output;
	std::shared_ptr<btos_api::gui::Label> curOp;
	std::shared_ptr<btos_api::wm::Menu> menu;
	
	enum class OpState{
		Default, Add, Subtract, Multiply, Divide, Equals=Default
	};
	
	OpState opState;
	double curTotal;
	bool awaiting = false;
	
	void UpdateOp();
	double Calculate();
	
	template<int N> void HandleDigit(){
		auto text = awaiting ? "" : output->GetText();
		text += (char)('0' + N);
		output->SetText(text);
		awaiting = false;
	}
	
	void HandleDecimal();

	template<OpState O> void HandleOp(){
		curTotal = Calculate();
		opState = O;
		UpdateOp();
		output->SetText(tfm::format("%s", curTotal));
		awaiting = true;
	}
	
	void HandleClear();
	void HandleClearEntry();
	void HandleSqrt();
	void HandlePercent();
	bool HandleKeyPress(uint32_t key);
	
public:
	void Show();
};

#endif