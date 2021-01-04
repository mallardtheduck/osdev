#ifndef _LOAD_ELF_HPP
#define _LOAD_ELF_HPP

#include "kernel.hpp"
#include "syscalls.hpp"

namespace module_api{
	struct syscall_table;
};

class ILoadedElf{
public:
	virtual void Execute(const char *mod_params = nullptr) = 0;

	virtual ~ILoadedElf() {}
};

ILoadedElf *LoadElfModule(IFileHandle &file);
ILoadedElf *LoadElfProcess(bt_pid_t pid, IFileHandle &file);

#endif
