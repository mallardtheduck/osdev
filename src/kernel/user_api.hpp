#ifndef _USER_API_HPP
#define _USER_API_HPP

#include "kernel.hpp"

void userapi_init();
bool is_safe_ptr(uint32_t ptr);

#endif