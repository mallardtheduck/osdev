#include "process.hpp"
#include "list.hpp"
#include "ministl.hpp"
#include "string.hpp"

proc_process *proc_current_process;
pid_t proc_current_pid;
list<proc_process> proc_processes;

struct proc_env_var{
	string value;
	uint8_t flags;
	proc_env_var(string v, uint8_t f) : value(v), flags(f) {}
	proc_env_var() {}
};

struct proc_process{
	pid_t pid;
	map<string, proc_env_var> environment;
};

list<proc_process> *processes;

void proc_init(){
	dbgout("PROC: Init.\n");
	proc_current_process=new proc_process();
	proc_current_pid=0;
}

void proc_switch(proc_process *newproc){
	processes=new list<proc_process>();
	proc_current_process=newproc;
	proc_current_pid=newproc->pid;
}

proc_process *proc_get(pid_t pid){
	for(list<proc_process>::iterator i=processes->begin(); i; ++i){
		if(i->pid==pid) return i;
	}
	return NULL;
}
void proc_setenv(const pid_t pid, const string &name, const string &value, const uint8_t flags){
	proc_get(pid)->environment[name]=proc_env_var(value, flags);
}
void proc_setenv(const string &name, const string &value, const uint8_t flags){
	proc_setenv(proc_current_pid, name, value, flags);
}
string proc_getenv(const pid_t pid, const string &name){
	proc_env_var var=proc_get(pid)->environment[name];
	if(var.flags & proc_env_flags::Global){
		var=proc_get(0)->environment[name];
	}
	return var.value;
}
string proc_getenv(const string &name){
	return proc_getenv(proc_current_pid, name);
}
