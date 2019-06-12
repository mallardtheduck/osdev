#ifndef _SCIMODE_HPP
#define _SCIMODE_HPP

#include <gui/form.hpp>
#include <gui/textbox.hpp>
#include <gui/radiobutton.hpp>

#include "icalcmode.hpp"
#include "calc.hpp"

class ScientificMode : public ICalcMode{
private:
	std::shared_ptr<btos_api::gui::TextBox> output;
	btos_api::gds::Point pos;
	
	enum class AngleMode{
		Degrees, Radians
	};
	
	std::function<void()> MakeHandler(const std::string &str);
	bool HandleKeyPress(uint32_t key);
	void HandleClear();
	void Calculate();
	double Evaluate(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);
	double EvalFunc(const std::string &func, double param);
	
	btos_api::gui::RadioGroup<AngleMode> modeGroup;
	
	double ans = 0.0;
	bool awaiting = false;
public:
	ScientificMode(const btos_api::gds::Point &pos);
	std::shared_ptr<btos_api::gui::Form> Show();
};

#endif