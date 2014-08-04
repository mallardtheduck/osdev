#include "kernel.hpp"
#include "list.hpp"
#include "ministl.hpp"
#include "string.hpp"
#include "locks.hpp"

extern "C" void proc_run_usermode(void *stack, proc_entry entry, int argc, char **argv);

proc_process *proc_current_process;
pid_t proc_current_pid;
list<proc_process> *proc_processes;

lock proc_lock;
lock env_lock;

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
	handle_t handlecounter;
	map<handle_t, lock*> locks;
	map<handle_t, file_handle*> files;
	map<handle_t, dir_handle*> dirs;
	map<handle_t, uint64_t> threads;

	proc_process() : pid(++curpid) {}
	proc_process(proc_process *parent_proc, const string &n) : pid(++curpid), parent(parent_proc->pid),
		environment(proc_copyenv(parent_proc->environment)), name(n), pagedir(vmm_newpagedir()),
		 handlecounter(0) {}
};

proc_process *proc_get(pid_t pid);

void proc_init(){
	dbgout("PROC: Init\n");
	init_lock(proc_lock);
	proc_processes=new list<proc_process>();
	proc_process kproc;
	kproc.name="KERNEL";
	kproc.pid=0;
	kproc.parent=0;
	kproc.pagedir=vmm_cur_pagedir;
	proc_processes->add(kproc);
	proc_current_process=proc_get(0);
	proc_current_pid=0;
	for(list<proc_process>::iterator i=proc_processes->begin(); i; ++i){
		dbgpf("PROC: Proccess %i, '%s'\n", (int)i->pid, i->name.c_str());
	}
	dbgpf("PROC: Current pid: %i\n", (int)proc_current_pid);
}

proc_process *proc_get(pid_t pid){
	hold_lock hl(proc_lock);
	for(list<proc_process>::iterator i=proc_processes->begin(); i; ++i){
		if(i->pid==pid) return i;
	}
	return NULL;
}

//Note: Called from scheduler. No locking, memory allocation, etc. available!
void proc_switch(pid_t pid, bool setthread){
	if(setthread) sch_setpid(pid);
	if(pid!=proc_current_pid){
		dbgpf("PROC: Switching process. Old PID: %i, new PID: %i\n", (int)proc_current_pid, (int)pid);
		proc_process *newproc=proc_get(pid);
		proc_current_process=newproc;
		proc_current_pid=newproc->pid;
		vmm_switch(proc_current_process->pagedir);
	}
}

pid_t proc_new(const string &name, pid_t parent){
	proc_process *parent_proc=proc_get(parent);
	proc_process newproc(parent_proc, name);
	{	hold_lock hl(proc_lock);
		proc_processes->add(newproc);
	}
	return newproc.pid;
}

void proc_end(pid_t pid){
	dbgpf("PROC: Ending process %i.\n", (int)pid);
	proc_process *proc=proc_get(pid);
	pid_t parent=proc->parent;
	for(map<handle_t, lock*>::iterator i=proc->locks.begin(); i!=proc->locks.end(); ++i){
		delete i->second;
	}
	{hold_lock hl(proc_lock);
		for(list<proc_process>::iterator i=proc_processes->begin(); i; ++i){
			if(i->pid==pid){
				vmm_deletepagedir(i->pagedir);
				proc_processes->remove(i);
				break;
			}
		}
		for(list<proc_process>::iterator i=proc_processes->begin(); i; ++i){
			if(i->parent==pid){
				i->parent=parent;
			}
		}
	}
}

void proc_setenv(const pid_t pid, const string &name, const string &value, const uint8_t flags, bool userspace){
	hold_lock hl(env_lock);
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
	hold_lock hl(env_lock);
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
	hold_lock hl(env_lock);
	for(env_t::const_iterator i=env.cbegin(); i!=env.cend(); ++i){
		if((i->second.flags & proc_env_flags::NoInherit)==0 && (i->second.flags & proc_env_flags::Global)==0) ret.insert(*i);
	}
	return ret;
}

struct proc_info{
	pid_t pid;
	proc_entry entry;
	/*params*/
};

void proc_start(void *ptr){
	pid_t pid = ((proc_info*)ptr)->pid;
	proc_entry entry = ((proc_info*)ptr)->entry;
	delete (proc_info*)ptr;
	proc_switch(pid);
	void *stack=vmm_alloc(4, false);
	stack=(void*)((size_t)stack+4*VMM_PAGE_SIZE);
	stack=(void*)((size_t)stack-sizeof(uint32_t));
	dbgpf("PROC: Usermode stack: %x\n", stack);
	proc_run_usermode(stack, entry, 0, NULL);
}

pid_t proc_spawn(const string &path, const string &params, pid_t parent){
	pid_t ret=proc_new(path, parent);
	file_handle file=fs_open((char*)path.c_str());
	loaded_elf_proc proc=elf_load_proc(ret, file);
	fs_close(file);
	proc_info *info=new proc_info();
	info->pid=ret;
	info->entry=proc.entry;
	sch_new_thread(&proc_start, (void*)info);
	return ret;
}

handle_t proc_add_lock(lock *l, pid_t pid){
	proc_process *proc=proc_get(pid);
	handle_t ret=++proc->handlecounter;
	proc->locks[ret] = l;
	return ret;
}

lock *proc_get_lock(handle_t h, pid_t pid){
	proc_process *proc=proc_get(pid);
	return proc->locks[h];
}

void proc_remove_lock(handle_t h, pid_t pid){
	proc_process *proc=proc_get(pid);
	proc->locks.erase(h);
}

handle_t proc_add_file(file_handle *file, pid_t pid){
	proc_process *proc=proc_get(pid);
    handle_t ret=++proc->handlecounter;
    proc->files[ret] = file;
    return ret;
}

file_handle *proc_get_file(handle_t h, pid_t pid){
    proc_process *proc=proc_get(pid);
    return proc->files[h];
}

void proc_remove_file(handle_t h, pid_t pid){
	proc_process *proc=proc_get(pid);
	proc->files.erase(h);
}

handle_t proc_add_dir(dir_handle *dir, pid_t pid){
	proc_process *proc=proc_get(pid);
    handle_t ret=++proc->handlecounter;
    proc->dirs[ret] = dir;
    return ret;
}

dir_handle *proc_get_dir(handle_t h, pid_t pid){
    proc_process *proc=proc_get(pid);
    return proc->dirs[h];
}

void proc_remove_dir(handle_t h, pid_t pid){
	proc_process *proc=proc_get(pid);
	proc->dirs.erase(h);
}