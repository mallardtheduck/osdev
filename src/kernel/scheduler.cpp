#include "kernel.hpp"
#include "ministl.hpp"
#include "locks.hpp"

extern char _start, _end;
const uint32_t default_priority=10;
const uint32_t modifier_limit=128;
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
	sch_thread_status::Enum status;
	uint32_t magic;
	void *stackptr;
	void *stackbase;
	isr_regs *usercontext;
	sch_start *start;
	uint32_t priority;
	uint32_t dynpriority;
	uint32_t modifier;
	uint64_t ext_id;
	pid_t pid;
	sch_blockcheck blockcheck;
	void *bc_param;
	uint32_t eip;
	int abortlevel;
    bool user_abort;
	sch_thread *next;
	uint32_t sch_cycle;
	thread_msg_status::Enum msgstatus;
	uint8_t fpu_xmm_data[512];
};

vector<sch_thread*> *threads;
sch_thread *current_thread;
uint64_t current_thread_id;
sch_thread *reaper_thread;
sch_thread *prescheduler_thread;
uint64_t cur_ext_id;
sch_thread *idle_thread;
uint64_t sch_zero=0;
bool sch_deferred=false;

void thread_reaper(void*);
void sch_threadtest();
void sch_idlethread(void*);
void sch_prescheduler_thread(void*);
static sch_thread *sch_get(uint64_t ext_id);

lock sch_lock;
bool sch_inited=false;
static const uint32_t cstart=5;
static uint32_t counter=cstart;

char *sch_threads_infofs(){
	char *buffer=(char*)malloc(4096);
	memset(buffer, 0, 4096);
	sprintf(buffer, "# ID, PID, priority, addr, status, alevel, load\n");
	{hold_lock hl(sch_lock);
		for(size_t i=0; i<threads->size(); ++i){
			sch_thread *t=(*threads)[i];
			sprintf(&buffer[strlen(buffer)],"%i, %i, %i, %x, %i, %i, %i\n", (int)t->ext_id, (int)t->pid, t->priority, t->eip,
				(int)t->status, t->abortlevel, t->modifier);
		}
    }
    return buffer;
}

void sch_init(){
	dbgout("SCH: Init\n");
	init_lock(sch_lock);
    uint16_t value=0x7FFF;
    dbgpf("SCH: Value: %i\n", (int)value);
	outb(0x43, 0x36);
	outb(0x40, value & 0xFF);
	outb(0x40, (value >> 8) & 0xFF);
	threads=new vector<sch_thread*>();
	sch_stack=(char*)malloc(4096)+4096;
	sch_thread *mainthread=new sch_thread();
	mainthread->status = sch_thread_status::Runnable;
	mainthread->priority=default_priority;
	mainthread->dynpriority=0;
	mainthread->modifier=0;
	mainthread->magic=0xF00D;
	mainthread->pid=proc_current_pid;
	mainthread->blockcheck=NULL;
	mainthread->bc_param=NULL;
	mainthread->abortlevel=2;
	mainthread->pid=0;
	mainthread->sch_cycle=0;
	mainthread->msgstatus=thread_msg_status::Normal;
	memcpy(mainthread->fpu_xmm_data, default_fpu_xmm_data, 512);
	current_thread_id=mainthread->ext_id=++cur_ext_id;
	threads->push_back(mainthread);
	current_thread=(*threads)[threads->size()-1];
	uint64_t idle_thread_id=sch_new_thread(&sch_idlethread, NULL, 1024);
	idle_thread=sch_get(idle_thread_id);
	uint64_t reaper_thread_id=sch_new_thread(&thread_reaper, NULL, 4096);
	reaper_thread=sch_get(reaper_thread_id);
	uint64_t prescheduler_id=sch_new_thread(&sch_prescheduler_thread, NULL, 1024);
	prescheduler_thread=sch_get(prescheduler_id);
	current_thread->next=prescheduler_thread;
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
	current_thread->priority=priority;
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
	sch_set_priority(0xFFFFFFFF);
	while(true)asm volatile("hlt");
}

extern "C" void sch_wrapper(){
    uint64_t ext_id;
    sch_start *start;
    {
        hold_lock hl(sch_lock);
        start = current_thread->start;
        ext_id=(int)current_thread->ext_id;
    }
	dbgpf("SCH: Starting new thread %x (%i) at %x (param %x) [%x].\n", current_thread, (int)ext_id, start->ptr, start->param, start);
    void (*entry)(void*) = start->ptr;
    void *param = start->param;
    free(start);
	entry(param);
	sch_end_thread();
}

uint64_t sch_new_thread(void (*ptr)(void*), void *param, size_t stack_size){
	sch_thread *newthread=new sch_thread();
	sch_start *start=(sch_start*)malloc(sizeof(sch_start));
	start->ptr=ptr;
	start->param=param;
	uint32_t stack=(uint32_t)malloc(stack_size);
	newthread->stackptr=(void*)stack;
	stack+=stack_size;
	stack-=4;
	*(uint32_t*)stack=(uint32_t)&sch_wrapper;
	newthread->stackbase=(void*)stack;
	newthread->stack.ss=0x10;
	newthread->stack.esp=stack;
	newthread->start=start;
	newthread->status = sch_thread_status::Runnable;
	newthread->magic=0xBABE;
	newthread->priority=default_priority;
	newthread->dynpriority=0;
	newthread->modifier=0;
	newthread->blockcheck=NULL;
	newthread->bc_param=NULL;
	newthread->abortlevel=2;
	newthread->pid=0;
    newthread->user_abort=false;
	newthread->next=NULL;
	newthread->sch_cycle=0;
	newthread->msgstatus=thread_msg_status::Normal;
	memcpy(newthread->fpu_xmm_data, default_fpu_xmm_data, 512);
    take_lock_exclusive(sch_lock);
	newthread->ext_id=++cur_ext_id;
	threads->push_back(newthread);
	release_lock(sch_lock);
	return newthread->ext_id;
}

void thread_reaper(void*){
    sch_set_priority(1);
	while(true){
		bool changed=true;
		while(changed){
			hold_lock lck(sch_lock);
			changed=false;
			for(size_t i=0; i<threads->size(); ++i){
				if((*threads)[i]->status == sch_thread_status::Ending){
					sch_thread *ptr=(*threads)[i];
					uint64_t id=(*threads)[i]->ext_id;
                    void *stackptr=(*threads)[i]->stackptr;
					threads->erase(i);
                    release_lock(sch_lock);
                    free(stackptr);
					delete ptr;
                    take_lock_exclusive(sch_lock);
					changed=true;
					dbgpf("SCH: Reaped %i (%i) [%x].\n", i, (uint32_t)id, stackptr);
					break;
				}
			}
		}
		sch_block();
	}
}

void sch_end_thread(){
    proc_remove_thread(sch_get_id(), current_thread->pid);
    take_lock_exclusive(sch_lock);
	current_thread->status = sch_thread_status::Ending;
	reaper_thread->status = sch_thread_status::Runnable;
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

static bool sch_find_thread(sch_thread *&torun, uint32_t cycle){
	static uint32_t lcycle=0;
	//Find runnable threads and minimum dynamic priority
	int nrunnables=0;
	uint32_t min=0xFFFFFFFF;
	for(size_t i=0; i<threads->size(); ++i){
		sch_thread *ithread = (*threads)[i];
		//Priority 0xFFFFFFFF == "idle", only run when nothing else is available.
		if(!ithread->priority==0xFFFFFFFF) ithread->dynpriority=0xFFFFFFFF;
	    if(lcycle != cycle && ithread->status == sch_thread_status::Blocked && ithread->blockcheck!=NULL){
	        if(ithread->blockcheck(ithread->bc_param)) ithread->status = sch_thread_status::Runnable;
	    }
		if(ithread->status == sch_thread_status::Runnable){
			if(!ithread->priority) panic("(SCH) Thread priority 0 is not allowed.\n");
			nrunnables++;
			if(ithread->dynpriority < min) min=ithread->dynpriority;
		}
	}
	lcycle=cycle;

	//If there are no runnable threads, halt. Hopefully an interrupt will awaken one soon...
	if(nrunnables==0){
		return false;
	}
	
	//Subtract minimum dynamic priority from all threads. If there is now a thread with dynamic priority 0
	//that isn't the current thread, record it
	bool foundtorun=false;
	for(size_t i=0; i<(*threads).size(); ++i){
		sch_thread *ithread = (*threads)[i];
		if(ithread->status == sch_thread_status::Runnable){
			if(ithread->dynpriority) ithread->dynpriority-=min;
			if(ithread!=current_thread && ithread->dynpriority==0){
				foundtorun=true;
				torun=ithread;
			}
			else if(ithread->modifier) --ithread->modifier;
		}else if(ithread->modifier) --ithread->modifier;
	}
	if(foundtorun){
		if(torun->modifier < modifier_limit) ++torun->modifier;
		return true;
	}else{
		torun=current_thread;
		if(torun->modifier < modifier_limit) ++torun->modifier;
		return true;
	}
}

extern "C" sch_stackinfo *sch_schedule(uint32_t ss, uint32_t esp){
	if(!are_interrupts_enabled()) panic("(SCH) Interrupts disabled in scheduler!\n");
	if(get_lock_owner(sch_lock)!=current_thread_id) panic("(SCH) Bad scheduler locking detected!\n");
	
	//Save current thread's state
	current_thread->stack.ss=ss;
	current_thread->stack.esp=esp;

	//Get next thread
	sch_thread *torun=current_thread->next;

	//Clear old thread's next value, to prevent accidents
	current_thread->next=NULL;
	//If the thread exists, but isn't runnable (made non-runnable since last preschedule), skip it
	if(torun && torun->status != sch_thread_status::Runnable) torun=torun->next;
	//If there is no next, run the prescheduler instead
	if(!torun) torun=prescheduler_thread;
	save_fpu_xmm_data(current_thread->fpu_xmm_data);
	current_thread=torun;
	curstack=current_thread->stack;
	if(!torun->ext_id) panic("(SCH) Thread with no ID?");
	lock_transfer(sch_lock, torun->ext_id);
	current_thread_id=torun->ext_id;
	proc_switch_sch(current_thread->pid);
	gdt_set_kernel_stack(current_thread->stackbase);
	fpu_switch();
	sch_deferred=false;
	return &curstack;
}

extern "C" uint32_t sch_dolock(){
    if(!are_interrupts_enabled()) enable_interrupts();//panic("(SCH) Attempt to yield while interrupts are disabled!");
	if(!try_take_lock_exclusive(sch_lock)){
		//dbgout("SCH: Scheduler run while locked!\n");
		return 0;
	}
	return 1;
}

extern "C" void sch_unlock(){
	release_lock(sch_lock);
}

void sch_isr(int irq, isr_regs *regs){
    irq_ack(irq);
	if(try_take_lock_exclusive(sch_lock)){
        counter--;
        if(!counter) {
            counter=cstart;
            sch_abortable(true);
			current_thread->eip = regs->eip;
            release_lock(sch_lock);
            enable_interrupts();
            sch_yield();
            disable_interrupts();
            sch_abortable(false);
        }else{
            release_lock(sch_lock);
        }
	}
}

const uint64_t &sch_get_id(){
	if(!sch_inited) return sch_zero;
	return current_thread_id;
}

void sch_set_priority(uint32_t pri){
	current_thread->priority=pri;
}

void sch_block(){
	current_thread->status=sch_thread_status::Blocked;
	sch_yield();
}

void sch_unblock(uint64_t ext_id){
	hold_lock hl(sch_lock);
	for(size_t i=0; i<threads->size(); ++i){
		if((*threads)[i]->ext_id==ext_id){
			if((*threads)[i]->status == sch_thread_status::Blocked) (*threads)[i]->status=sch_thread_status::Runnable;
			break;
		}
	}
}

bool sch_active(){
	return sch_inited;
}

void sch_setpid(pid_t pid){
	current_thread->pid=pid;
}

void sch_setblock(sch_blockcheck check, void *param){
	if(check(param)) return;
	current_thread->blockcheck=check;
	current_thread->bc_param=param;
	bool changeabort = false;
	if(sch_get_abortlevel()){
		changeabort = true;
		sch_abortable(true);
	}
    sch_block();
    sch_clearblock();
    if(changeabort) sch_abortable(false);
}

void sch_clearblock(){
	current_thread->blockcheck=NULL;
	current_thread->bc_param=NULL;
}

bool sch_wait_blockcheck(void *p){
	uint64_t &ext_id=*(uint64_t*)p;
	for(size_t i=0; i<threads->size(); ++i){
		if((*threads)[i]->ext_id==ext_id){
			return false;
		}
	}
	return true;
}

void sch_wait(uint64_t ext_id){
    take_lock_exclusive(sch_lock);
	for(size_t i=0; i<threads->size(); ++i){
		if((*threads)[i]->ext_id==ext_id){
            release_lock(sch_lock);
			sch_setblock(sch_wait_blockcheck, (void*)&ext_id);
            take_lock_exclusive(sch_lock);
			break;
		}
	}
    release_lock(sch_lock);
}

extern "C" void sch_update_eip(uint32_t eip){
	current_thread->eip=eip;
}

uint32_t sch_get_eip(bool lock){
	return current_thread->eip;
}

void sch_abortable(bool abortable, uint64_t ext_id){
	sch_thread *thread = current_thread;
	if(ext_id != current_thread_id){;
		for(size_t i=0; i<threads->size(); ++i){
			if((*threads)[i]->ext_id==ext_id){
				thread = (*threads)[i];
				break;
			}
		}
	}
    int alevel;
	if(abortable) alevel = atomic_decrement(thread->abortlevel);
	else alevel = atomic_increment(thread->abortlevel);
	if(alevel < 0){
		thread->abortlevel=0;
	}
}

bool sch_abort_blockcheck(void *p){
	uint64_t &ext_id=*(uint64_t*)p;
	for(size_t i=0; i<threads->size(); ++i){
		if((*threads)[i]->ext_id==ext_id){
			return (*threads)[i]->abortlevel > 0;
		}
	}
	return true;
}

void sch_abort(uint64_t ext_id){
	if(ext_id == sch_get_id()) panic("(SCH) Thread attempting to abort itself!");
	bool tryagain=true;
	while(tryagain){
        take_lock_recursive(sch_lock);
		bool found=false;
		for(size_t i=0; i<threads->size(); ++i){
			if((*threads)[i]->ext_id==ext_id){
				found=true;
				if(!(*threads)[i]->abortlevel){
					(*threads)[i]->status=sch_thread_status::Ending;
					reaper_thread->status=sch_thread_status::Runnable;
					tryagain=false;
				}else{
                    (*threads)[i]->user_abort=true;
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

bool sch_can_lock(){
    if(!try_take_lock_exclusive(sch_lock)) {
		sch_deferred=true;
		return false;
	}
    release_lock(sch_lock);
	sch_deferred=false;
    return true;
}

bool sch_user_abort(){
    return current_thread->user_abort;
}

void sch_prescheduler_thread(void*){
	current_thread->status=sch_thread_status::Special;
	uint32_t cycle=0;
	while(true){
		cycle++;
		take_lock_exclusive(sch_lock);
		sch_thread *current=current_thread;
		sch_thread *next=NULL;
		uint32_t count=0;
		while(sch_find_thread(next, cycle)){
			if(next->sch_cycle==cycle || (count && next==idle_thread)){
				break;
			}
			current->next=next;
			current=current->next;
			if(current->modifier < modifier_limit) ++current->modifier;
			//Prevent overflow of dynamic priority...
			if(current->priority + current->modifier >= current->priority){
				current->dynpriority=current->priority + current->modifier;
			}else{
				current->dynpriority=0xFFFFFFFF;
			}
			current->sch_cycle=cycle;
			count++;
		}
		release_lock(sch_lock);
		sch_yield();
	}
}

static sch_thread *sch_get(uint64_t ext_id){
	if(ext_id == current_thread->ext_id) return current_thread;
	{
		hold_lock hl(sch_lock, false);
		for(size_t i=0; i<threads->size(); ++i){
			if((*threads)[i]->ext_id==ext_id) return (*threads)[i];
		}
		return NULL;
	}
}

void sch_set_msgstaus(thread_msg_status::Enum status, uint64_t ext_id){
	if(ext_id == current_thread_id){
		current_thread->msgstatus=status;
	}else{
		hold_lock hl(sch_lock);
		sch_get(ext_id)->msgstatus = status;
	}
}

thread_msg_status::Enum sch_get_msgstatus(uint64_t ext_id){
	if(ext_id == current_thread_id){
		return current_thread->msgstatus;
	}else{
		hold_lock hl(sch_lock);
		return sch_get(ext_id)->msgstatus;
	}
}


void sch_deferred_yield(){
	if(sch_deferred) sch_yield();
}

uint8_t *sch_get_fpu_xmm_data(){
	return current_thread->fpu_xmm_data;
}

size_t sch_get_pid_threadcount(pid_t pid){
	take_lock_recursive(sch_lock);
	size_t ret=0;
	for(size_t i=0; i<threads->size(); ++i){
		if((*threads)[i]->pid == pid) ++ret;
	}
	release_lock(sch_lock);
	return ret;
}

void sch_debug_stop(pid_t pid){
	hold_lock hl(sch_lock);	
	for(size_t i=0; i<threads->size(); ++i){
		sch_thread *c = (*threads)[i];
		if(c->pid == pid){
			if(c->status == sch_thread_status::Runnable){
				c->status = sch_thread_status::DebugStopped;
			}else if(c->status == sch_thread_status::Blocked){
				c->status = sch_thread_status::DebugBlocked;
			}
		}
	}
}

void sch_debug_resume(pid_t pid){
	hold_lock hl(sch_lock);	
	for(size_t i=0; i<threads->size(); ++i){
		sch_thread *c = (*threads)[i];
		if(c->pid == pid){
			if(c->status == sch_thread_status::DebugStopped){
				c->status = sch_thread_status::Runnable;
			}else if(c->status == sch_thread_status::DebugBlocked){
				c->status = sch_thread_status::Blocked;
			}
		}
	}
}

void sch_update_usercontext(isr_regs *uc, uint64_t ext_id){
	if(ext_id == current_thread_id){
		current_thread->usercontext = uc;
	}else{
		hold_lock hl(sch_lock);
		sch_get(ext_id)->usercontext = uc;
	}

}

void *sch_get_usercontext(uint64_t ext_id){
	if(ext_id == current_thread_id){
		return current_thread->usercontext;
	}else{
		hold_lock hl(sch_lock);
		return sch_get(ext_id)->usercontext;
	}
}

int sch_get_abortlevel(){
	return current_thread->abortlevel;
}