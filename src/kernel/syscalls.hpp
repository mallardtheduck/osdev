#ifndef _SYSCALLS_HPP
#define _SYSCALLS_HPP

#include "kernel.hpp"

namespace module_api{
	#include <module_api.h>
}

typedef int (*syscall_vector)(int, void*);

int module_syscall(int, void*);
int user_syscall(int, void*);

#endif
