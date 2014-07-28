#include "kernel.hpp"
#include "list.hpp"
#include "ministl.hpp"
#include "string.hpp"

proc_process *proc_current_process;
pid_t proc_current_pid;
list<proc_process> proc_processes;

pid_t curpid=0;

struct proc_env_var{
	string value;
	uint8_t flags;
	proc_env_var(string v, uint8_t f) : value(v), flags(f) {}
	proc_env_var() {}
};

typedef map<string, proc_env_var> env_t;
env_t proc_copyenv(const env_t &env);

struct proc_process{
	pid_t pid;
	pid_t parent;
	env_t environment;
	string name;
	vmm_pagedir *pagedir;
	proc_process() : pid(++curpid) {}
	proc_process(proc_process *parent_proc, const string &n) : pid(++curpid), parent(parent_proc->pid),
		environment(proc_copyenv(parent_proc->environment)), name(n), pagedir(vmm_newpagedir()) {}
};

proc_process *proc_get(pid_t pid);

list<proc_process> *processes;

void proc_init(){
	dbgout("PROC: Init.\n");
	processes=new list<proc_process>();
	proc_process kproc;
	kproc.name="KERNEL";
	kproc.pid=0;
	kproc.parent=0;
	kproc.pagedir=vmm_cur_pagedir;
	processes->add(kproc);
	proc_current_process=proc_get(0);
	proc_current_pid=0;
	for(list<proc_process>::iterator i=processes->begin(); i; ++i){
		dbgpf("PROC: Proccess %i, '%s'\n", (int)i->pid, i->name.c_str());
	}
	dbgpf("PROC: Current pid: %i\n", (int)proc_current_pid);
}

proc_process *proc_get(pid_t pid){
	for(list<proc_process>::iterator i=processes->begin(); i; ++i){
		if(i->pid==pid) return i;
	}
	return NULL;
}

//Note: Called from scheduler. No locking, memory allocation, etc. available!
void proc_switch(pid_t pid){
	if(pid!=proc_current_pid){
		proc_process *newproc=proc_get(pid);
		proc_current_process=newproc;
		proc_current_pid=newproc->pid;
		vmm_switch(proc_current_process->pagedir);
	}
}

pid_t proc_new(const string &name, pid_t parent){
	proc_process *parent_proc=proc_get(parent);
	proc_process newproc(parent_proc, name);
	processes->add(newproc);
	return newproc.pid;
}

void proc_end(pid_t pid){
	pid_t parent=proc_get(pid)->parent;
	for(list<proc_process>::iterator i=processes->begin(); i; ++i){
		if(i->pid==pid){
			vmm_deletepagedir(i->pagedir);
			processes->remove(i);
			break;
		}
	}
	for(list<proc_process>::iterator i=processes->begin(); i; ++i){
		if(i->parent==pid){
			i->parent=parent;
		}
	}
}

void proc_setenv(const pid_t pid, const string &name, const string &value, const uint8_t flags, bool userspace){
	env_t &env=(flags & proc_env_flags::Global) ? proc_get(0)->environment : proc_get(pid)->environment;
	if(userspace && env.has_key(name) && (env[name].flags & proc_env_flags::Private || env[name].flags & proc_env_flags::ReadOnly)){
		return;
	}else{
		env[name]=proc_env_var(value, flags);
	}
}

void proc_setenv(const string &name, const string &value, const uint8_t flags, bool userspace){
	proc_setenv(proc_current_pid, name, value, flags, userspace);
}

string proc_getenv(const pid_t pid, const string &name, bool userspace){
	env_t &kenv=proc_get(0)->environment;
	if(kenv.has_key(name) && kenv[name].flags & proc_env_flags::Global){
		if(!userspace || (kenv[name].flags & proc_env_flags::Private)==0) return kenv[name].value;
		else return "";
	}
	proc_env_var var=proc_get(pid)->environment[name];
	if(!userspace || (var.flags & proc_env_flags::Private)==0) return var.value;
	else return "";
}

string proc_getenv(const string &name, bool userspace){
	return proc_getenv(proc_current_pid, name, userspace);
}

env_t proc_copyenv(const env_t &env){
	env_t ret;
	for(env_t::const_iterator i=env.cbegin(); i!=env.cend(); ++i){
		if((i->second.flags & proc_env_flags::NoInherit)==0 && (i->second.flags & proc_env_flags::Global)==0) ret.insert(*i);
	}
	return ret;
}

pid_t proc_spawn(const string &path, const string &params, pid_t parent){
	pid_t ret=proc_new(path, parent);
	file_handle file=fs_open((char*)path.c_str());
	elf_load_proc(ret, file);
	fs_close(file);
	//start process thread...
	return ret;
}