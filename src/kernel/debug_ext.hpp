#ifndef _DEBUG_EXT_HPP
#define _DEBUG_EXT_HPP

#include "kernel.hpp"
#include <ext/debug.h>

void init_debug_extension();
void debug_event_notify(bt_pid_t pid, uint64_t thread, bt_debug_event::Enum event, bt_exception::Enum error=bt_exception::NoError);
void debug_getdrstate(uint32_t *buffer);
void debug_setdrstate(const uint32_t *buffer);
void debug_setbreaks(bool state);

static const size_t Debug_DRStateSize = 6;

#endif //_DEBUG_EXT_HPP
