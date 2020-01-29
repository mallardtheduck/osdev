#ifndef _ICALCMODE_HPP
#define _ICALCMODE_HPP

#include <memory>
#include <gui/form.hpp>

class ICalcMode{
public:
	virtual std::shared_ptr<btos_api::gui::Form> Show() = 0;
	
	virtual std::string GetValue() = 0;
	virtual void SetValue(const std::string &) = 0;

	virtual ~ICalcMode() {}
};

#endif