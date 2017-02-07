#ifndef _DEBUG_EXT_HPP
#define _DEBUG_EXT_HPP

#include "kernel.hpp"
#include <ext/debug.h>

void init_debug_extension();
void debug_event_notify(pid_t pid, uint64_t thread, bt_debug_event::Enum event, bt_exception::Enum error=bt_exception::NoError);

#endif //_DEBUG_EXT_HPP
