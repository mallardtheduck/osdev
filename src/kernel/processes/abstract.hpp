#ifndef KERNEL_PROCESSES_ABSTRACT_HPP
#define KERNEL_PROCESSES_ABSTRACT_HPP

#include "../kernel.hpp"
#include "../utils/string.hpp"
#include <module/utils/refcountpointer.hpp>

#include <module/kernelsys/process.hpp>

void Processes_Init();
IProcessManager &GetProcessManager();

inline ProcessPointer GetProcess(bt_pid_t pid){
	auto ptr = GetProcessManager().GetByID(pid);
	if(!ptr) panic("(PROC) Process does not exist!");
	return ptr;
}

inline IProcess &CurrentProcess(){
	return GetProcessManager().CurrentProcess();
}

#endif
