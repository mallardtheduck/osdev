#ifndef _USER_API_HPP
#define _USER_API_HPP

#include "kernel.hpp"

void userapi_init();
bool is_safe_ptr(uint32_t ptr, size_t size, pid_t pid = proc_current_pid);
bool is_safe_string(uint32_t ptr, pid_t pid = proc_current_pid);

#endif