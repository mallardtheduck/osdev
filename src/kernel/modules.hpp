#ifndef _MODULES_HPP
#define _MODULES_HPP

#include "kernel.hpp"

void init_modules();
void load_module(const char *path, char *params=NULL);

#endif
