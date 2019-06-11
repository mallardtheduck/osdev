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
	
	btos_api::gui::RadioGroup<AngleMode> modeGroup;
	
public:
	ScientificMode(const btos_api::gds::Point &pos);
	std::shared_ptr<btos_api::gui::Form> Show();
};

#endif