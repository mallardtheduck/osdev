#ifndef _PROCESS_HPP
#define _PROCESS_HPP

#include "kernel.hpp"
#include "string.hpp"

typedef uint64_t pid_t;

namespace proc_env_flags{
	enum {
		Global		= (1<<0), //Use PID 0 (kernel) value instead
		ReadOnly	= (1<<1), //Not changeable by user-mode code
		Private		= (1<<2), //Not visible to user-mode code
		NoInherit	= (1<<3), //Do not copy from parent to child
	};
}

struct proc_process;
class string;

extern proc_process *proc_current_process;
extern pid_t proc_current_pid;

void proc_init();
void proc_switch(proc_process *newproc);
proc_process *proc_get(pid_t pid);

void proc_setenv(const pid_t pid, const string &name, const string &value, const uint8_t flags=0);
void proc_setenv(const string &name, const string &value, const uint8_t flags=0);
string proc_getenv(const pid_t pid, const string &name);
string proc_getenv(const string &name);

#endif