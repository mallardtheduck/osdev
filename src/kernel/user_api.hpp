#ifndef _USER_API_HPP
#define _USER_API_HPP

#include "kernel.hpp"

void userapi_init();
bool is_safe_ptr(uint32_t ptr, size_t size, bt_pid_t pid = CurrentProcess().ID());
bool is_safe_string(uint32_t ptr, bt_pid_t pid = CurrentProcess().ID());

#endif