#ifndef _CALC_HPP
#define _CALC_HPP

#include <memory>
#include <gds/libgds.h>

#include <gui/form.hpp>

enum class CalcMode{
	Standard, Scientific, Programmer
};

extern CalcMode CurrentMode;

std::shared_ptr<btos_api::gds::Surface> LoadPNG(const char *path);
void MakeToolbarAndMenu(std::shared_ptr<btos_api::gui::Form> form);

#endif