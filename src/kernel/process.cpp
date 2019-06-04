#include "kernel.hpp"
#include "list.hpp"
#include "ministl.hpp"
#include "string.hpp"
#include "locks.hpp"
#include "strutil.hpp"
#include <util/asprintf.h>

static const uint32_t default_userspace_priority=100;

extern "C" void proc_run_usermode(void *stack, proc_entry entry, int argc, char **argv);

proc_process *volatile proc_current_process;
volatile pid_t proc_current_pid;
vector<proc_process*> *proc_processes;

extern lock sch_lock;
lock &proc_lock=sch_lock;
lock env_lock;

pid_t curpid=0;

static const string *blank_string;

struct proc_env_var{
	string value;
	uint8_t flags;
	proc_env_var(string v, uint8_t f) : value(v), flags(f) {}
	proc_env_var() {}
};

typedef map<string, proc_env_var> env_t;
env_t proc_copyenv(const env_t &env);

struct proc_process{
	lock ulock;
	pid_t pid;
	pid_t parent;
	env_t environment;
	string name;
	int retval;
    file_handle file;

	MM2::PageDirectory *pagedir;
	handle_t handlecounter;
    proc_status::Enum status;

    map<handle_t, bt_handle_info> handles;
	map<pid_t, int> child_returns;
	vector<string> args;

    map<pid_t, void*> msg_buffers;
    
    vector<btos_api::bt_msg_header*> msg_q;
    btos_api::bt_msg_header *cur_msg = NULL;

	proc_process() : pid(++curpid) {
		init_lock(ulock);
	}
	proc_process(proc_process *parent_proc, const string &n) : pid(++curpid), parent(parent_proc->pid),
		environment(proc_copyenv(parent_proc->environment)), name(n), pagedir(new MM2::PageDirectory),
		 handlecounter(0), status(proc_status::Starting) {
		init_lock(ulock);
    }
};

proc_process *proc_get(pid_t pid);
proc_process *proc_get_lock(pid_t pid);

char *proc_infofs(){
	bool done = false;
	size_t bufferSize = 4096;
	char *buffer;
	while(!done){
		done = true;
		buffer=(char*)malloc(bufferSize);
		snprintf(buffer, bufferSize, "# PID, path, memory, parent\n");
		size_t kmem=MM2::current_pagedir->get_kernel_used();
		{hold_lock hl(proc_lock);
			for(size_t i=0; i<proc_processes->size(); ++i){
	            proc_process *cur=(*proc_processes)[i];
				auto count = snprintf(buffer, bufferSize, "%s%i, \"%s\", %i, %i\n", buffer, (int)(cur->pid), cur->name.c_str(),
					(int)((cur->pid)?cur->pagedir->get_user_used():kmem), (int)(cur->parent));
				if((size_t)count > bufferSize){
					free(buffer);
					buffer = nullptr;
					bufferSize *= 2;
					done = false;
					break;
				}
			}
	    }
	}
    return buffer;
}

char *env_infofs(){
	char *buffer=nullptr;
	asprintf(&buffer, "# name, value, flags\n");
    {
        hold_lock hl(env_lock);
		env_t &kenv=proc_get(0)->environment;
		for(env_t::iterator i = kenv.begin(); i != kenv.end(); ++i){
			if(i->second.flags & proc_env_flags::Global){
				reasprintf_append(&buffer, "\"%s\", \"%s\", %x\n", i->first.c_str(), i->second.value.c_str(), (int) i->second.flags);
			}
		}
        for (env_t::iterator i = proc_current_process->environment.begin(); i != proc_current_process->environment.end(); ++i) {
            if (!(i->second.flags & proc_env_flags::Private)) {
                reasprintf_append(&buffer, "\"%s\", \"%s\", %x\n", i->first.c_str(), i->second.value.c_str(), (int) i->second.flags);
            }
        }
    }
	return buffer;
}

void proc_init(){
	dbgout("PROC: Init\n");
	init_lock(proc_lock);
	proc_processes=new vector<proc_process*>();
	proc_process *kproc=new proc_process();
	kproc->name="KERNEL";
	kproc->pid=0;
	curpid--;
	kproc->parent=0;
	kproc->pagedir=MM2::current_pagedir;
	kproc->status=proc_status::Running;
	proc_processes->push_back(kproc);
	proc_current_process=proc_get(0);
	proc_current_pid=0;
    for(size_t i=0; i<proc_processes->size(); ++i){
        proc_process *cur=(*proc_processes)[i];
		dbgpf("PROC: Proccess %i, '%s'\n", (int)(cur->pid), cur->name.c_str());
	}
	dbgpf("PROC: Current pid: %i\n", (int)proc_current_pid);
	infofs_register("PROCS", &proc_infofs);
	infofs_register("ENV", &env_infofs);
	blank_string=new string("");
}

proc_process *proc_get(pid_t pid){
	if(proc_current_process && pid == proc_current_pid) return proc_current_process;
	{
		hold_lock hl(proc_lock, false);
		for(size_t i=0; i<proc_processes->size(); ++i){
			proc_process *cur=(*proc_processes)[i];
			if(cur->pid==pid) return cur;
		}
		dbgpf("PROC: PID %i not found!\n", (int)pid);
		return NULL;
	}
}

proc_process *proc_get_lock(pid_t pid){
	if(proc_current_process && pid == proc_current_pid){
		take_lock_recursive(proc_current_process->ulock);
		return proc_current_process;
	}
	while(true){
		take_lock_recursive(proc_lock);
		proc_process *ret = proc_get(pid);
		if(!ret){
			release_lock(proc_lock);
			return NULL;
		}
		if(try_take_lock_recursive(ret->ulock)){
			release_lock(proc_lock);
			return ret;
		}
		release_lock(proc_lock);
		sch_yield();
	}
}

//Note: Called from scheduler. No locking, memory allocation, etc. available!
void proc_switch_sch(pid_t pid){
	//sch_setpid(pid);
	if(pid!=proc_current_pid){
		proc_process *newproc=NULL;
        for(size_t i=0; i<proc_processes->size(); ++i){
            proc_process *cur=(*proc_processes)[i];
			if(cur->pid==pid) newproc=cur;
		}
        if(!newproc) panic("(PROC) Attempt to switch to unknown process.");
		proc_current_process=newproc;
		proc_current_pid=newproc->pid;
		MM2::mm2_switch(proc_current_process->pagedir);
	}
}

bool proc_switch(pid_t pid){
	sch_setpid(pid);
	if(pid!=proc_current_pid){
		proc_process *newproc=proc_get(pid);
        if(!newproc) return false;
        if(!newproc && pid == 0) panic("(PROC) Failed to switch to PID 0!");
        {
            hold_lock hl(proc_lock, false);
            proc_current_process = newproc;
            proc_current_pid = newproc->pid;
            MM2::mm2_switch(proc_current_process->pagedir);
        }
	}
	if(proc_current_pid != pid) panic("(PROC) PID reset during switch?");
    return true;
}

pid_t proc_new(const string &name, size_t argc, char **argv, pid_t parent, file_handle *file){
	proc_process *parent_proc=proc_get(parent);
	proc_process *newproc=new proc_process(parent_proc, name);
    if(file) newproc->file=*file;
    else newproc->file.valid=false;
	newproc->args.push_back(name);
	for(size_t i=0; i<argc; ++i){
		newproc->args.push_back(argv[i]);
	}
	{	hold_lock hl(proc_lock);
		proc_processes->push_back(newproc);
	}
	return newproc->pid;
}

struct proc_threads_blockcheck_params{
	pid_t pid;
	uint64_t tid;
};

static bool proc_threads_blockcheck(void *p){
    proc_threads_blockcheck_params &params = *(proc_threads_blockcheck_params*)p;
    return sch_get_pid_threadcount(params.pid, true, params.tid) == 0;
}

void proc_end(pid_t pid) {
    if(pid==0) return;
	if(proc_get_status(pid) == proc_status::Ended) return;
	//This is not in the "right" place, but cannot be done once we have the lock.
	debug_event_notify(pid, 0, bt_debug_event::ProgramEnd);
	take_lock_exclusive(proc_lock);
	if (!proc_get(pid)){
		release_lock(proc_lock);
		return;
	}
	pid_t curpid = proc_current_pid;
	if (curpid == pid) curpid = 0;
	if (proc_get_status(pid) == proc_status::Ending) {
		dbgpf("PROC: Process %i is already ending.\n", (int) pid);
		release_lock(proc_lock);
		proc_wait(pid);
		return;
	}
	dbgpf("PROC: Ending process %i.\n", (int) pid);
	proc_set_status(proc_status::Ending, pid);
	proc_process *proc = proc_get(pid);
	if (!proc) return;
	take_lock_exclusive(proc->ulock);
	pid_t parent = proc->parent;
	release_lock(proc_lock);
	if (parent){
		proc_process *parent_proc = proc_get_lock(parent);
		if(parent_proc){
			//take_lock_exclusive(parent_proc->ulock);
			parent_proc->child_returns[pid] = proc->retval;
			release_lock(parent_proc->ulock);
		}
	}
	bool cont = true;
	while (cont) {
		cont = false;
		for (map<handle_t, bt_handle_info>::iterator i = proc->handles.rbegin(); i != proc->handles.rend(); --i) {
			if (i->second.type == kernel_handle_types::thread) {
 				uint64_t thread_id = *(uint64_t *) i->second.value;
				if (thread_id != sch_get_id()) {
					sch_abort(thread_id);
					proc_remove_thread(thread_id, pid);
					cont = true;
					break;
				}else{
					proc_remove_handle(i->first, pid);
					cont = true;
					break;
				}
			}
		}
		release_lock(proc->ulock);
		sch_yield();
		take_lock_exclusive(proc->ulock);
	}
	if(sch_get_pid_threadcount(pid, true) > 0){
		proc_threads_blockcheck_params params = {pid, sch_get_id()};
		sch_setblock(&proc_threads_blockcheck, (void *) &params);
	}
	cont = true;
	while (cont) {
		cont = false;
		for (map<handle_t, bt_handle_info>::iterator i = proc->handles.begin(); i != proc->handles.end(); ++i) {
			release_lock(proc->ulock);
			close_handle(i->second);
			take_lock_exclusive(proc->ulock);
			proc_remove_handle(i->first, pid);
			cont = true;
			break;
		}
	}
	if (proc->file.valid) fs_close(proc->file);
	proc_switch(curpid);
	for (size_t i = 0; i < proc_processes->size(); ++i) {
		proc_process *cur = (*proc_processes)[i];
		if (cur->pid == pid) {
			delete cur->pagedir;
			proc_processes->erase(i);
			release_lock(proc->ulock);
			delete cur;
			break;
		}
	}
	for (size_t i = 0; i < proc_processes->size(); ++i) {
		proc_process *cur = (*proc_processes)[i];
		if (cur->parent == pid) {
			cur->parent = parent;
		}
	}
    msg_clear(pid);
	msg_send_event(btos_api::bt_kernel_messages::ProcessEnd, (void*)&pid, sizeof(pid));
}

void proc_setenv(const pid_t pid, const string &oname, const string &value, const uint8_t flags, bool userspace){
	hold_lock hl(env_lock);
	string name=to_upper(oname);
	env_t &env=(flags & proc_env_flags::Global) ? proc_get(0)->environment : proc_get(pid)->environment;
	if(userspace && env.has_key(name) && (env[name].flags & proc_env_flags::Private || env[name].flags & proc_env_flags::ReadOnly)){
		return;
	}else{
		if(value.length()){
			env[name]=proc_env_var(value, flags);
		}else{
			env.erase(name);
		}
	}
}

void proc_setenv(const string &name, const string &value, const uint8_t flags, bool userspace){
	proc_setenv(proc_current_pid, name, value, flags, userspace);
}

const string &proc_getenv(const pid_t pid, const string &oname, bool userspace){
	hold_lock hl(env_lock);
	string name=to_upper(oname);
	env_t &kenv=proc_get(0)->environment;
	if(kenv.has_key(name) && kenv[name].flags & proc_env_flags::Global){
		if(!userspace || (kenv[name].flags & proc_env_flags::Private)==0) return kenv[name].value;
		else return *blank_string;
	}
	env_t &env=proc_get(pid)->environment;
	proc_env_var *var;
	if(env.has_key(name)) var=&env[name];
	else return *blank_string;
	if(!userspace || (var->flags & proc_env_flags::Private)==0) return var->value;
	else return *blank_string;
}

const string &proc_getenv(const string &name, bool userspace){
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
    void *stackptr;
};

void *proc_alloc_stack(size_t size){
	size_t pages=(size/MM2::MM2_Page_Size);
	uint32_t baseaddr=0-(pages*MM2::MM2_Page_Size);
	dbgpf("PROC: %i pages of stack at %x.\n", (int)pages, baseaddr);
	MM2::current_pagedir->alloc_pages_at(pages, (void*)baseaddr);
	memset((void*)baseaddr, 0, size);
	//Stack pointer starts 4 bytes below top, just in case something tries to read the top-level return address.
	return (void*)(0-sizeof(uint32_t));
}

static bool proc_start_hold_blockcheck(void *p){
	bt_pid_t &pid = *(bt_pid_t*)p;
	proc_process *proc=proc_get(pid);
	return proc && proc->status != proc_status::Held;
}

void proc_hold(){
	if(proc_get_status() == proc_status::Held){
		bt_pid_t pid = proc_current_pid;
		sch_setblock(&proc_start_hold_blockcheck, (void*)&pid);
	}
}

void proc_start(void *ptr){
	pid_t pid = ((proc_info*)ptr)->pid;
	proc_entry entry = ((proc_info*)ptr)->entry;
    void *stackptr = ((proc_info*)ptr)->stackptr;
	delete (proc_info*)ptr;
	if(!proc_switch(pid)) return;
	if(!stackptr) stackptr=proc_alloc_stack(16 * MM2::MM2_Page_Size);
    sch_set_priority(default_userspace_priority);
	//Yes, there are supposed to be two of these calls.
	sch_abortable(true);
	sch_abortable(true);
	proc_add_thread(sch_get_id());
    debug_event_notify(proc_current_pid, sch_get_id(), bt_debug_event::ThreadStart);
	if(sch_get_abortlevel()) panic("(PROC) Entering userspace with non-zero abortlevel.");
	proc_hold();
	proc_set_status(proc_status::Running);
	proc_run_usermode(stackptr, entry, 0, NULL);
}

pid_t proc_spawn(const string &path, size_t argc, char **argv, pid_t parent){
	file_handle file;
	if(!is_kvar_set("LOADER")){
		file=fs_open((char*)path.c_str(), FS_Read);
	}else{
		string loader = get_kvar("LOADER");
		dbgpf("PROC: Using program loader: %s\n", loader.c_str());
		file=fs_open((char*)loader.c_str(), FS_Read);
	}
    pid_t ret=proc_new(path, argc, argv, parent, &file);
	if(!file.valid){
        proc_end(ret);
        return 0;
    }
	loaded_elf_proc proc=elf_load_proc(ret, file);
	//fs_close(file);
	proc_info *info=new proc_info();
	info->pid=ret;
	info->entry=proc.entry;
    info->stackptr=NULL;
    debug_event_notify(ret, 0, bt_debug_event::ProgramStart);
	sch_new_thread(&proc_start, (void*)info, 8192);
	msg_send_event(btos_api::bt_kernel_messages::ProcessStart, (void*)&ret, sizeof(ret));
	return ret;
}

uint64_t proc_new_user_thread(proc_entry entry, void *param, void *stack, pid_t pid){
    proc_info *info=new proc_info();
    info->pid=pid;
    info->entry=entry;
    info->stackptr=stack;
    //TODO: parameter...
    uint64_t thread_id=sch_new_thread(&proc_start, (void*)info, 4096);
    proc_add_thread(thread_id);
    return thread_id;
}

handle_t proc_add_handle(bt_handle_info handle, pid_t pid){
    proc_process *proc=proc_get_lock(pid);
    if(!proc) return 0;
    //~ for(auto i = proc->handles.begin(); i!=proc->handles.end(); ++i){
		//~ if(i->second.value == handle.value) panic("(PROC) Duplicate handle add!");
	//~ }
    handle_t ret=++proc->handlecounter;
    while(!ret || proc->handles.has_key(ret)) ret=++proc->handlecounter;
    proc->handles[ret] = handle;
	release_lock(proc->ulock);
    return ret;
}

bt_handle_info proc_get_handle(handle_t h, pid_t pid){
    proc_process *proc=proc_get_lock(pid);
    if(!proc) return invalid_handle;
	bt_handle_info ret;
    if(proc->handles.has_key(h)) ret = proc->handles[h];
    else ret = invalid_handle;
	release_lock(proc->ulock);
	return ret;
}

void proc_remove_handle(handle_t h, pid_t pid){;
    proc_process *proc=proc_get_lock(pid);
    if(!proc) return;
    proc->handles.erase(h);
	release_lock(proc->ulock);
}

static void close_lock_handle(void *l){
    delete (lock*)l;
}

handle_t proc_add_lock(lock *l, pid_t pid){
    bt_handle_info handle=create_handle(kernel_handle_types::lock, (void*)l, &close_lock_handle);
    return proc_add_handle(handle, pid);
}

lock *proc_get_lock(handle_t h, pid_t pid){
    bt_handle_info handle=proc_get_handle(h, pid);
    if(handle.type==kernel_handle_types::lock) return (lock*)handle.value;
    else return NULL;
}

void proc_remove_lock(handle_t h, pid_t pid){
    proc_remove_handle(h, pid);
}

static void close_file_handle(void *f){
    file_handle *file=(file_handle*)f;
    fs_close(*file);
    delete file;
}

handle_t proc_add_file(file_handle *file, pid_t pid){
    bt_handle_info handle=create_handle(kernel_handle_types::file, (void*)file, &close_file_handle);
    return proc_add_handle(handle, pid);
}

file_handle *proc_get_file(handle_t h, pid_t pid){
    bt_handle_info handle=proc_get_handle(h, pid);
    if(handle.type==kernel_handle_types::file) return (file_handle*)handle.value;
    else return NULL;
}

void proc_remove_file(handle_t h, pid_t pid){
    proc_remove_handle(h, pid);
}

static void close_dir_handle(void *d){
    dir_handle *dir=(dir_handle*)d;
    fs_close_dir(*dir);
    delete dir;
}

handle_t proc_add_dir(dir_handle *dir, pid_t pid){
    bt_handle_info handle=create_handle(kernel_handle_types::directory, (void*)dir, &close_dir_handle);
    return proc_add_handle(handle, pid);
}

dir_handle *proc_get_dir(handle_t h, pid_t pid){
    bt_handle_info handle=proc_get_handle(h, pid);
    if(handle.type==kernel_handle_types::directory) return (dir_handle*)handle.value;
    else return NULL;
}

void proc_remove_dir(handle_t h, pid_t pid){
    proc_remove_handle(h, pid);
}

void proc_setreturn(int ret, pid_t pid){
    proc_process *proc=proc_get_lock(pid);
    if(!proc) return;
	if(proc && proc->status == proc_status::Running) proc->retval=ret;
	release_lock(proc->ulock);
}

bool proc_wait_blockcheck(void *p){
	pid_t &pid=*(pid_t*)p;
    for(size_t i=0; i<proc_processes->size(); ++i){
        proc_process *cur=(*proc_processes)[i];
		if(cur->pid==pid) return false;
	}
	return true;
}

int proc_wait(pid_t pid){
	while(proc_get(pid)){
		sch_setblock(&proc_wait_blockcheck, (void*)&pid);
	}
    {
        hold_lock hl(proc_lock);
        if(proc_current_process->child_returns.has_key(pid)) return proc_current_process->child_returns[pid];
        else return 0;
    }
}

size_t proc_get_argc(pid_t pid){
    proc_process *proc=proc_get_lock(pid);
    if(!proc) return 0;
	size_t ret = proc->args.size();
	release_lock(proc->ulock);
	return ret;
}

size_t proc_get_arg(size_t i, char *buf, size_t size, pid_t pid){
    proc_process *proc=proc_get_lock(pid);
    if(!proc) return 0;
	strncpy(buf, proc->args[i].c_str(), size);
	size_t ret = proc->args[i].length();
	release_lock(proc->ulock);
	return ret;
}

static void close_thread_handle(void *t){
    uint64_t thread_id=*(uint64_t*)t;
    sch_abort(thread_id);
    delete (uint64_t*)t;
}

void proc_remove_thread(uint64_t thread_id, pid_t pid){
    handle_t h=proc_get_thread_handle(thread_id, pid);
    if(h) {
        bt_handle_info handle_info=proc_get_handle(h, pid);
        proc_remove_handle(h, pid);
        delete (uint64_t*)handle_info.value;
    }
}

void proc_remove_thread_handle(handle_t h, pid_t pid){
    proc_remove_handle(h, pid);
}

handle_t proc_add_thread(uint64_t thread_id, pid_t pid){
    handle_t ret=proc_get_thread_handle(thread_id, pid);
    if(ret) return ret;
    if(proc_get_status(pid) == proc_status::Ending) return 0;
    bt_handle_info handle=create_handle(kernel_handle_types::thread, new uint64_t(thread_id), &close_thread_handle);
    return proc_add_handle(handle, pid);
}

uint64_t proc_get_thread(handle_t h, pid_t pid){
    bt_handle_info handle=proc_get_handle(h, pid);
    if(handle.type==kernel_handle_types::thread) return *(uint64_t*)handle.value;
    else return 0;
}

handle_t proc_get_thread_handle(uint64_t thread_id, pid_t pid){
    proc_process *proc=proc_get_lock(pid);
    if(!proc) return 0;
	handle_t ret = 0;
    for(map<handle_t, bt_handle_info>::iterator i=proc->handles.begin(); i!=proc->handles.end(); ++i){
        if(i->second.type==kernel_handle_types::thread){
            if(*(uint64_t*)i->second.value==thread_id) {
				ret = i->first;
				break;
			}
        }
    }
	release_lock(proc->ulock);
    return ret;
}

void proc_terminate(pid_t pid){
    dbgpf("PROC: Terminating PID: %i\n", (int)pid);
    if(pid==0) return; // panic("(PROC) Request to terminate kernel!");
    proc_setreturn(-1, pid);
    bool current=false;
    if(pid==proc_current_pid) {
        proc_switch(0);
        proc_remove_thread(sch_get_id(), pid);
        current=true;
    }
    proc_end(pid);
    if(current) sch_end_thread();
}

void proc_set_status(proc_status::Enum status, pid_t pid){
    proc_process *proc=proc_get_lock(pid);
    if(!proc) return;
    proc->status=status;
	release_lock(proc->ulock);
}
proc_status::Enum proc_get_status(pid_t pid){
    //proc_process *proc=proc_get_lock(pid);
    //if(!proc) return proc_status::DoesNotExist;
    //proc_status::Enum ret = proc->status;
    //release_lock(proc->ulock);
	//return ret;
	interrupt_lock il;
	proc_process *proc = proc_get(pid);
	if(!proc) return proc_status::DoesNotExist;
	else return proc->status;
}

void proc_free_message_buffer(pid_t topid, pid_t pid){
    proc_process *proc=proc_get_lock(pid);
    if(!proc) return;
	void *ptr=proc->msg_buffers[topid];
	proc->msg_buffers.erase(topid);
	release_lock(proc->ulock);
	if(ptr) free(ptr);
}

static bool proc_msg_blockcheck(void *p){
    btos_api::bt_msg_header header=*(btos_api::bt_msg_header*)p;
    proc_process *proc=proc_get(header.from);
    if(!proc) return false;
    return !get_lock_owner(proc->ulock) && !proc->msg_buffers.has_key(header.to);
}

extern lock msg_lock;

uint64_t proc_send_message(btos_api::bt_msg_header &header, pid_t pid) {
	if(header.flags & btos_api::bt_msg_flags::Reply){
		void *content = malloc(header.length);
		if(header.length) memcpy(content, header.content, header.length);
		header.content = content;
		return msg_send(header);
	}
	bool again=false;
	do {
		if(again) {
			sch_setblock(&proc_msg_blockcheck, (void *)&header);
		}
		again=false;
		take_lock_recursive(proc_lock);
		proc_process *proc=proc_get(pid);
		proc_process *to=proc_get(header.to);
		if(!proc || !to) {
			release_lock(proc_lock);
			return 0;
		}
		bool proc_ok = try_take_lock_recursive(proc->ulock);
		bool to_ok = try_take_lock_recursive(to->ulock);
		bool msg_ok = try_take_lock_recursive(msg_lock);
		release_lock(proc_lock);
		if (!proc_ok || !to_ok || !msg_ok || proc->msg_buffers.has_key(header.to)) {
			if(proc_ok) release_lock(proc->ulock);
			if(to_ok) release_lock(to->ulock);
			if(msg_ok) release_lock(msg_lock);
			again=true;
			sch_yield();
			continue;
		}
		if(header.content && header.length){
			proc->msg_buffers[header.to]=malloc(header.length);
			memcpy(proc->msg_buffers[header.to], header.content, header.length);
			header.content=proc->msg_buffers[header.to];
		}
		uint64_t ret = msg_send(header);
		release_lock(proc->ulock);
		release_lock(to->ulock);
		release_lock(msg_lock);
		sch_yield_to(header.to);
		return ret;
	} while(again);
	return 0;
}

static bool proc_msg_wait_blockcheck(void *p){
    pid_t pid=*(pid_t*)p;
    proc_process *proc=proc_get(pid);
    if(!proc) return false;
    return !proc->msg_buffers.size();
}

void proc_message_wait(pid_t pid){
    proc_process *proc = proc_get_lock(pid);
	if (!proc) return;
	if (!proc->msg_buffers.size()){
		release_lock(proc->ulock);
		return;
	}
	release_lock(proc->ulock);
    sch_setblock(&proc_msg_wait_blockcheck, (void *)&pid);
}

void proc_add_msg(btos_api::bt_msg_header *msg){
	proc_process *proc = proc_get_lock(msg->to);
	if (!proc) return;
	proc->msg_q.push_back(msg);
	release_lock(proc->ulock);
}

void proc_remove_msg(btos_api::bt_msg_header *msg){
	proc_process *proc = proc_get_lock(msg->to);
	if (!proc) return;
	for(size_t i = 0; i < proc->msg_q.size(); ++i){
		if(proc->msg_q[i] == msg){
			proc->msg_q.erase(i);
			break;
		}
	}
	release_lock(proc->ulock);
}

btos_api::bt_msg_header *proc_get_msg(size_t index, pid_t pid){
	proc_process *proc = proc_get_lock(pid);
	if (!proc) return NULL;
	btos_api::bt_msg_header *msg;
	if(index >= proc->msg_q.size()) msg = NULL;
	else msg = proc->msg_q[index];
	release_lock(proc->ulock);
	return msg;
}

btos_api::bt_msg_header *proc_get_msg_by_id(uint64_t id, pid_t pid){
	proc_process *proc = proc_get_lock(pid);
	if (!proc) return NULL;
	btos_api::bt_msg_header *msg = nullptr;
	for(auto &m : proc->msg_q){
		if(m->id == id){
			msg = m;
			break;
		}
	}
	release_lock(proc->ulock);
	return msg;
}

btos_api::bt_msg_header *proc_get_msg_match(btos_api::bt_msg_filter &filt, pid_t pid){
	proc_process *proc = proc_get_lock(pid);
	if (!proc) return NULL;
	btos_api::bt_msg_header *msg = nullptr;
	for(auto &m : proc->msg_q){
		if(msg_is_match(*m, filt)){
			msg = m;
			break;
		}
	}
	release_lock(proc->ulock);
	return msg;
}

btos_api::bt_msg_header *proc_get_msg_match_nolock(btos_api::bt_msg_filter &filt, pid_t pid){
	proc_process *proc = proc_get(pid);
	if (!proc) return nullptr;
	for(auto &m : proc->msg_q){
		if(msg_is_match(*m, filt)){
			return m;
		}
	}
	return nullptr;
}

btos_api::bt_msg_header *proc_get_msg_nolock(size_t index, pid_t pid){
	proc_process *proc = proc_get(pid);
	if (!proc) return NULL;
	btos_api::bt_msg_header *msg;
	if(index >= proc->msg_q.size()) msg = NULL;
	else msg = proc->msg_q[index];
	return msg;
}

btos_api::bt_msg_header *proc_get_msg_by_id(uint64_t id){
	//dbgout("PROC: p_g_m_b_i.\n");
	hold_lock hl(proc_lock);
	btos_api::bt_msg_header *ret = NULL;
	for(size_t i = 0; i < proc_processes->size(); ++i){
		proc_process *cproc = (*proc_processes)[i];
		for(size_t j = 0; j < cproc->msg_q.size(); ++j){
			if(cproc->msg_q[j]->id == id){
				ret = cproc->msg_q[j];
				break;
			}
		}
	}
	return ret;
}

void proc_set_cur_msg(btos_api::bt_msg_header *msg, pid_t pid){
	proc_process *proc = proc_get_lock(pid);
	if (!proc) return;
	proc->cur_msg = msg;
	release_lock(proc->ulock);
}

btos_api::bt_msg_header *proc_get_cur_msg(pid_t pid){
	proc_process *proc = proc_get_lock(pid);
	if (!proc) return NULL;
	btos_api::bt_msg_header *ret = proc->cur_msg;
	release_lock(proc->ulock);
	return ret;
}

void proc_set_cur_msg_nolock(btos_api::bt_msg_header *msg, pid_t pid){
	proc_process *proc = proc_get(pid);
	if (!proc) return;
	proc->cur_msg = msg;
}

