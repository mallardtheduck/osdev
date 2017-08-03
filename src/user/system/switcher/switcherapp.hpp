#ifndef _SWITCHERAPP_HPP
#define _SWITCHERAPP_HPP

#include <ncurses/cursesapp.h>
#include "menu.hpp"

class SwitcherApp : public NCursesApplication{
public:
	SwitcherApp();
	
	int titlesize() const override;
	void title() override;	
	int run() override;
};

#endif
