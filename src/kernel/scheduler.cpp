#include "kernel.hpp"
#include "ministl.hpp"
#include "locks.hpp"

extern char _start, _end;
const uint32_t default_priority=10;
void *sch_stack;

struct sch_start{
	void (*ptr)(void*);
	void *param;
};

struct sch_stackinfo{
	uint32_t ss;
	uint32_t esp;
} __attribute__((packed));

sch_stackinfo curstack;

struct sch_thread{
	sch_stackinfo stack;
	bool runnable;
	uint32_t magic;
	void *stackptr;
	void *stackbase;
	bool to_be_deleted;
	sch_start *start;
	uint32_t priority;
	uint32_t dynpriority;
	uint64_t ext_id;
	pid_t pid;
	sch_blockcheck blockcheck;
	void *bc_param;
	uint32_t eip;
	bool abortable;
	int abortlevel;
};

vector<sch_thread> *threads;
size_t current_thread;
uint64_t current_thread_id;
size_t reaper_thread;
uint64_t cur_ext_id;
size_t idle_thread;

void thread_reaper(void*);
void sch_threadtest();
void sch_idlethread(void*);

lock sch_lock;
bool sch_inited=false;

char *sch_threads_infofs(){
	char *buffer=(char*)malloc(4096);
	memset(buffer, 0, 4096);
	sprintf(buffer, "# ID, PID, priority, addr, run, alevel\n");
	{hold_lock hl(sch_lock);
		for(size_t i=0; i<threads->size(); ++i){
			sch_thread *t=&(*threads)[i];
			sprintf(&buffer[strlen(buffer)],"%i, %i, %i, %x, %i, %i\n", (int)t->ext_id, (int)t->pid, t->priority, t->eip,
				(bool)t->runnable, t->abortlevel);
		}
    }
    return buffer;
}

void sch_init(){
	dbgout("SCH: Init\n");
	init_lock(sch_lock);
	outb(0x43, 0x36);
	outb(0x40, 39000 & 0xFF);
	outb(0x40, (39000 >> 8) & 0xFF);
	threads=new vector<sch_thread>();
	sch_stack=(char*)malloc(4096)+4096;
	sch_thread mainthread;
	mainthread.runnable=true;
	mainthread.to_be_deleted=false;
	mainthread.priority=default_priority;
	mainthread.dynpriority=0;
	mainthread.magic=0xF00D;
	mainthread.pid=proc_current_pid;
	mainthread.blockcheck=NULL;
	mainthread.bc_param=NULL;
	mainthread.abortlevel=1;
	mainthread.abortable=false;
	mainthread.pid=0;
	current_thread_id=mainthread.ext_id=++cur_ext_id;
	threads->push_back(mainthread);
	current_thread=threads->size()-1;
	sch_new_thread(&sch_idlethread, NULL, 1024);
	reaper_thread=sch_new_thread(&thread_reaper, NULL, 4096);
	for(size_t i=0; i<(*threads).size(); ++i){
		if((*threads)[i].ext_id==reaper_thread){
			reaper_thread=i;
			break;
		}
	}
	//sch_threadtest();
	irq_handle(0, &sch_isr);
	sch_inited=true;
	IRQ_clear_mask(0);
	dbgout("SCH: Init complete.\n");
	infofs_register("THREADS", &sch_threads_infofs);
}

void test_priority(void *params){
	uint32_t *p=(uint32_t*)params;
	char c=(char)(p[0]);
	uint32_t priority=p[1];
	(*threads)[current_thread].priority=priority;
	free(params);
	while(true){
		printf("%c", c);
		sch_yield();
	}
}

void sch_threadtest(){
	uint32_t* p1=(uint32_t*)malloc(sizeof(uint32_t)*2);
	p1[0]='.';
	p1[1]=200;
	sch_new_thread(&test_priority, (void*)p1);
	uint32_t* p2=(uint32_t*)malloc(sizeof(uint32_t)*2);
	p2[0]='!';
	p2[1]=400;
	sch_new_thread(&test_priority, (void*)p2);
}

void sch_idlethread(void*){
	idle_thread=current_thread_id;
	sch_set_priority(0xFFFFFFFF);
	while(true)asm volatile("hlt");
}

extern "C" void sch_wrapper(){
	sch_start *start=(*threads)[current_thread].start;
	dbgpf("SCH: Starting new thread %i (%i) at %x (param %x) [%x].\n", current_thread, (int)(*threads)[current_thread].ext_id, start->ptr, start->param, start);
	start->ptr(start->param);
	free(start);
	sch_end_thread();
}

uint64_t sch_new_thread(void (*ptr)(void*), void *param, size_t stack_size){
	sch_thread newthread;
	sch_start *start=(sch_start*)malloc(sizeof(sch_start));
	start->ptr=ptr;
	start->param=param;
	uint32_t stack=(uint32_t)malloc(stack_size);
	newthread.stackptr=(void*)stack;
	stack+=stack_size;
	stack-=4;
	*(uint32_t*)stack=(uint32_t)&sch_wrapper;
	newthread.stackbase=(void*)stack;
	newthread.stack.ss=0x10;
	newthread.stack.esp=stack;
	newthread.start=start;
	newthread.runnable=true;
	newthread.to_be_deleted=false;
	newthread.magic=0xBABE;
	newthread.priority=default_priority;
	newthread.dynpriority=0;
	newthread.blockcheck=NULL;
	newthread.bc_param=NULL;
	newthread.abortlevel=1;
	newthread.abortable=false;
	newthread.pid=0;
	take_lock(sch_lock);
	newthread.ext_id=++cur_ext_id;
	threads->push_back(newthread);
	release_lock(sch_lock);
	return newthread.ext_id;
}

void thread_reaper(void*){
	while(true){
		bool changed=true;
		while(changed){
			hold_lock lck(sch_lock);
			changed=false;
			for(size_t i=0; i<threads->size(); ++i){
				if((*threads)[i].to_be_deleted){
					uint64_t id=(*threads)[i].ext_id;
					release_lock(sch_lock);
					free((*threads)[i].stackptr);
					take_lock(sch_lock);
					threads->erase(i);
					changed=true;
					dbgpf("SCH: Reaped %i (%i).\n", i, (uint32_t)id);
					break;
				}
			}
		}
		sch_block();
	}
}

void sch_end_thread(){
	take_lock(sch_lock);
	(*threads)[current_thread].runnable=false;
	(*threads)[current_thread].to_be_deleted=true;
	(*threads)[reaper_thread].runnable=true;
	release_lock(sch_lock);
	sch_yield();
	panic("SCH: Attempt to run to_be_deleted thread!");
}

inline void out_regs(const irq_regs &ctx){
	dbgpf("SCH: INTERRUPT %x\n", ctx.int_no);
	dbgpf("EAX: %x EBX: %x ECX: %x EDX: %x\n", ctx.eax, ctx.ebx, ctx.ecx, ctx.edx);
	dbgpf("EDI: %x ESI: %x EBP: %x ESP: %x\n", ctx.edi, ctx.esi, ctx.ebp, ctx.esp);
	dbgpf("EIP: %x CS: %x SS: %x\n", ctx.eip, ctx.cs, ctx.ss);
	dbgpf("EFLAGS: %x ORESP: %x\n", ctx.eflags, ctx.useresp);
}

bool sch_find_thread(size_t &torun){
	//Reset dyanmic priority of idle thread (ensures it only runs when nothing else is available)
	(*threads)[idle_thread].dynpriority=(*threads)[idle_thread].priority;
	//Find runnable threads and minimum dynamic priority
	int nrunnables=0;
	uint32_t min=0xFFFFFFFF;
	for(size_t i=0; i<threads->size(); ++i){
	    if(!(*threads)[i].runnable && (*threads)[i].blockcheck!=NULL){
	        (*threads)[i].runnable=(*threads)[i].blockcheck((*threads)[i].bc_param);
	        if((*threads)[i].runnable) dbgpf("SCH: Thread %i is now runnable.\n", i);
	    }
		if((*threads)[i].runnable){
			if(!(*threads)[i].priority) panic("(SCH) Thread priority 0 is not allowed.\n");
			nrunnables++;
			if((*threads)[i].dynpriority < min) min=(*threads)[i].dynpriority;
		}
	}

	//If there are no runnable threads, halt. Hopefully an interrupt will awaken one soon...
	if(nrunnables==0){
		return false;
	}
	
	//Subtract minimum dynamic priority from all threads. If there is now a thread with dynamic priority 0
	//that isn't the current thread, record it
	bool foundtorun=false;
	for(size_t i=0; i<(*threads).size(); ++i){
		if((*threads)[i].runnable){
			if((*threads)[i].dynpriority) (*threads)[i].dynpriority-=min;
			if(i!=current_thread && (*threads)[i].dynpriority==0){
				foundtorun=true;
				torun=i;
			}
		}
	}
	if(foundtorun){
		return true;
	}else{
		torun=current_thread;
		return true;
	}
}

extern "C" sch_stackinfo *sch_schedule(uint32_t ss, uint32_t esp){
	if(!are_interrupts_enabled()) panic("(SCH) Interrupts disabled in scheduler!\n");
	if(sch_lock!=current_thread_id) panic("(SCH) Bad scheduler locking detected!\n");
	
	//Save current thread's state
	(*threads)[current_thread].stack.ss=ss;
	(*threads)[current_thread].stack.esp=esp;

	size_t torun;
	//If we found a thread to run, run it
	if(sch_find_thread(torun)){
		(*threads)[torun].dynpriority=(*threads)[torun].priority;
		current_thread=torun;
		current_thread_id=(*threads)[torun].ext_id;
		curstack=(*threads)[current_thread].stack;
		sch_lock=current_thread_id;
		proc_switch_sch((*threads)[current_thread].pid, false);
		gdt_set_kernel_stack((*threads)[current_thread].stackbase);
		return &curstack;		
	}else{
		//Nothing to run?
		panic("(SCH) No runnable threads (idle thread not runnable?)!\n:");
	}
	release_lock(sch_lock);
	return &curstack;
}

extern "C" uint32_t sch_dolock(){
	if(!try_take_lock(sch_lock)){
		dbgout("SCH: Scheduler run while locked!\n");
		return 0;
	}
	return 1;
}

extern "C" void sch_unlock(){
	release_lock(sch_lock);
}

void sch_isr(int, isr_regs *regs){
	sch_abortable(true);
	(*threads)[current_thread].eip=regs->eip;
    enable_interrupts();
	if(try_take_lock(sch_lock)){
		release_lock(sch_lock);
		sch_yield();
	}
	sch_abortable(false);
}

const uint64_t &sch_get_id(){
	if(!sch_inited) current_thread_id=0;
	return current_thread_id;
}

void sch_set_priority(uint32_t pri){
	hold_lock hl(sch_lock);
	(*threads)[current_thread].priority=pri;
}

void sch_block(){
	take_lock(sch_lock);
	(*threads)[current_thread].runnable=false;
	release_lock(sch_lock);
	sch_yield();
}

void sch_unblock(uint64_t ext_id){
	hold_lock hl(sch_lock);
	for(size_t i=0; i<threads->size(); ++i){
		if((*threads)[i].ext_id==ext_id && !(*threads)[i].to_be_deleted){
			dbgpf("SCH: Unblocked %i.\n", (uint32_t)ext_id);
			(*threads)[i].runnable=true;
			break;
		}
	}
}

bool sch_active(){
	return sch_inited;
}

void sch_setpid(pid_t pid){
	hold_lock hl(sch_lock);
	(*threads)[current_thread].pid=pid;
}

void sch_setblock(sch_blockcheck check, void *param){
    { hold_lock hl(sch_lock);
        (*threads)[current_thread].blockcheck=check;
        (*threads)[current_thread].bc_param=param;
    }
    sch_block();
    sch_clearblock();
}

void sch_clearblock(){
	hold_lock hl(sch_lock);
	(*threads)[current_thread].blockcheck=NULL;
	(*threads)[current_thread].bc_param=NULL;
}

bool sch_wait_blockcheck(void *p){
	uint64_t &ext_id=*(uint64_t*)p;
	for(size_t i=0; i<threads->size(); ++i){
		if((*threads)[i].ext_id==ext_id){
			return false;
		}
	}
	return true;
}

void sch_wait(uint64_t ext_id){
	for(size_t i=0; i<threads->size(); ++i){
		if((*threads)[i].ext_id==ext_id){
			sch_setblock(sch_wait_blockcheck, (void*)&ext_id);
			break;
		}
	}
}

extern "C" void sch_update_eip(uint32_t eip){
	(*threads)[current_thread].eip=eip;
}

void sch_abortable(bool abortable){
	//hold_lock hl(sch_lock);
	(*threads)[current_thread].abortlevel+=abortable? -1 : 1;
	if((*threads)[current_thread].abortlevel<=0){
		(*threads)[current_thread].abortlevel=0;
		(*threads)[current_thread].abortable=true;
		dbgpf("SCH: Thread %i now abortable.\n", (int)current_thread_id);
	}else{
		(*threads)[current_thread].abortable=false;
	}
}

bool sch_abort_blockcheck(void *p){
	uint64_t &ext_id=*(uint64_t*)p;
	for(size_t i=0; i<threads->size(); ++i){
		if((*threads)[i].ext_id==ext_id){
			return (*threads)[i].abortable;
		}
	}
	return true;
}

void sch_abort(uint64_t ext_id){
	bool tryagain=true;
	while(tryagain){
		take_lock(sch_lock);
		bool found=false;
		for(size_t i=0; i<threads->size(); ++i){
			if((*threads)[i].ext_id==ext_id){
				found=true;
				if((*threads)[i].abortable){
					(*threads)[i].runnable=false;
					(*threads)[i].to_be_deleted=true;
					(*threads)[reaper_thread].runnable=true;
					tryagain=false;
				}
			}
		}
		release_lock(sch_lock);
		if(!found) tryagain=false;
		if(tryagain){
			sch_setblock(&sch_abort_blockcheck, (void*)&ext_id);
		}
	}
}