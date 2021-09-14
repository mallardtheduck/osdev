#ifndef _LOAD_ELF_HPP
#define _LOAD_ELF_HPP

#include "kernel.hpp"
#include "syscalls.hpp"

namespace module_api{
	struct syscall_table;
};

class ILoadedElf : private nonmovable{
public:
	virtual void Execute(const char *mod_params = nullptr) = 0;
	virtual ProcessEntryPoint GetEntryPoint() = 0;

	virtual uint32_t GetType(){
		return kernel_handle_types::elf;
	};

	virtual intptr_t GetBaseAddress() = 0;

	virtual ~ILoadedElf() {}
};

ILoadedElf *LoadElfModule(IFileHandle &file);
ILoadedElf *LoadElfProcess(bt_pid_t pid, IFileHandle &file);

#endif
