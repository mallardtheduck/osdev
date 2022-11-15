#ifndef KERNEL_PROCESSES_ABSTRACT_HPP
#define KERNEL_PROCESSES_ABSTRACT_HPP

#include "../kernel.hpp"
#include "../utils/string.hpp"
#include <module/utils/refcountpointer.hpp>

#include <module/kernelsys/process.hpp>

void Processes_Init();
IProcessManager &GetProcessManager();

bool Processes_Ready();

inline ProcessPointer GetProcess(bt_pid_t pid){
	auto ptr = GetProcessManager().GetByID(pid);
	return ptr;
}

inline IProcess &CurrentProcess(){
	return GetProcessManager().CurrentProcess();
}

#endif
