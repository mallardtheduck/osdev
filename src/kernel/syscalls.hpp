#ifndef _SYSCALLS_HPP
#define _SYSCALLS_HPP

#include "kernel.hpp"

namespace module_api{
	#include <module/module_api.h>
}

extern module_api::syscall_table MODULE_SYSCALL_TABLE;

#endif
