#include "kernel.hpp"
#include "ministl.hpp"
#include "locks.hpp"

extern char _start, _end;
const uint32_t default_priority=10;

struct sch_start{
	void (*ptr)(void*);
	void *param;
};

struct sch_thread{
	irq_regs context;
	bool runnable;
	uint32_t magic;
	void *original_esp;
	bool to_be_deleted;
	sch_start *start;
	uint32_t priority;
	uint32_t dynpriority;
	uint64_t ext_id;
	/* memory info */
};

vector<sch_thread> *threads;
size_t current_thread;
uint64_t current_thread_id;
size_t reaper_thread;
uint64_t cur_ext_id;

void thread_reaper(void*);
void sch_threadtest();
extern "C" void sch_do_thread(irq_regs regs);
extern "C" void sch_get_context(irq_regs *regs);

lock sch_lock;
bool sch_inited=false;

void sch_init(){
	dbgout("SCH: Init\n");
	init_lock(sch_lock);
	threads=new vector<sch_thread>();
	sch_thread mainthread;
	mainthread.runnable=true;
	mainthread.to_be_deleted=false;
	mainthread.priority=default_priority;
	mainthread.dynpriority=0;
	mainthread.magic=0xF00D;
	current_thread_id=mainthread.ext_id=++cur_ext_id;
	threads->push_back(mainthread);
	current_thread=threads->size()-1;
	reaper_thread=sch_new_thread(&thread_reaper, NULL, 4096);
	//sch_threadtest();
	IRQ_clear_mask(0);
	dbgout("SCH: Init complete.\n");
	sch_inited=true;
}

void test_priority(void *params){
	uint32_t *p=(uint32_t*)params;
	char c=(char)(p[0]);
	uint32_t priority=p[1];
	(*threads)[current_thread].priority=priority;
	free(params);
	while(true){
		printf("%c", c);
		asm("hlt");
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

int sch_add_thread(irq_regs context){
	sch_thread newthread;
	newthread.context=context;
	newthread.runnable=true;
	newthread.to_be_deleted=false;
	newthread.original_esp=(void*)(context.ebx);
	newthread.start=(sch_start*)context.eax;
	newthread.magic=0xBABE;
	newthread.priority=default_priority;
	newthread.dynpriority=0;
	take_lock(sch_lock);
	newthread.ext_id=++cur_ext_id;
	threads->push_back(newthread);
	size_t ret=threads->size()-1;
	release_lock(sch_lock);
	return ret;
}

extern "C" void sch_wrapper(){
	sch_start *start=(*threads)[current_thread].start;
	dbgpf("SCH: Starting new thread %i at %x (param %x) [%x].\n", current_thread, start->ptr, start->param, start);
	start->ptr(start->param);
	free(start);
	sch_end_thread();
}

int sch_new_thread(void (*ptr)(void*), void *param, size_t stack_size){
	irq_regs newcontext = {0};
	newcontext.cs = 0x08;
   	newcontext.ds = 0x10;
	newcontext.ss = 0x10;
	uint32_t eflags;
	asm volatile("pushfl; pop %0;": "=r"(eflags)::);
	newcontext.eflags=eflags;
	sch_start *start=(sch_start*)malloc(sizeof(sch_start));
	start->ptr=ptr;
	start->param=param;
	uint32_t stack=(uint32_t)malloc(stack_size);
	newcontext.ebx=stack;
	stack+=stack_size;
	newcontext.eax=(uint32_t)start;
	newcontext.eip=(uint32_t)&sch_wrapper;
	return sch_add_thread(newcontext);
}

void thread_reaper(void*){
	while(true){
		sch_block();
		bool changed=true;
		while(changed){
			hold_lock lck(sch_lock);
			for(int i=0; i<threads->size(); ++i){
				if((*threads)[i].to_be_deleted){
					uint64_t id=(*threads)[i].ext_id;
					free((*threads)[i].original_esp);
					threads->erase(i);
					changed=true;
					dbgpf("SCH: Reaped %i (%i).\n", i, (uint32_t)id);
					break;
				}
			}
			changed=false;
		}
	}
}

void sch_end_thread(){
	take_lock(sch_lock);
	(*threads)[current_thread].runnable=false;
	(*threads)[current_thread].to_be_deleted=true;
	(*threads)[reaper_thread].runnable=true;
	release_lock(sch_lock);
	sch_yield();
}

inline void out_regs(const irq_regs &ctx){
	dbgpf("SCH: INTERRUPT %x\n", ctx.int_no);
	dbgpf("EAX: %x EBX: %x ECX: %x EDX: %x\n", ctx.eax, ctx.ebx, ctx.ecx, ctx.edx);
	dbgpf("EDI: %x ESI: %x EBP: %x ESP: %x\n", ctx.edi, ctx.esi, ctx.ebp, ctx.esp);
	dbgpf("EIP: %x CS: %x SS: %x\n", ctx.eip, ctx.cs, ctx.ss);
	dbgpf("EFLAGS: %x ORESP: %x\n", ctx.eflags, ctx.useresp);
}

bool sch_find_thread(size_t &torun){
	//Find runnable threads and minimum dynamic priority
	int nrunnables=0;
	uint32_t min=0xFFFFFFFF;
	for(int i=0; i<threads->size(); ++i){
		if((*threads)[i].runnable){
			if(!(*threads)[i].priority) panic("(SCH) Thread priority 0 is not allowed.\n");
			nrunnables++;
			if((*threads)[i].dynpriority < min) min=(*threads)[i].dynpriority;
		}
	}

	//If there are no runnable threads, halt. Hopefully an interrupt will awaken one soon...
	if(nrunnables==0){
		dbgout("SCH: No runnable threads.\n");
		return false;
	}
	
	//Subtract minimum dynamic priority from all threads. If there is now a thread with dynamic priority 0
	//that isn't the current thread, record it
	bool foundtorun=false;
	for(int i=0; i<(*threads).size(); ++i){
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

void return_immediately(){
	asm("popl %%eax" : : : "eax");
	dbgout("SCH: Returning...\n");
	return;
}

void sch_irq(irq_regs *regs){
	//Confirm that required locks are available.
	if(!sch_inited || !try_take_lock(sch_lock)) return;
	
	//Save current thread's state
	irq_regs cregs;
	sch_get_context(&cregs);
	cregs.eip=(uint32_t)&return_immediately;
	(*threads)[current_thread].context=cregs;

	size_t torun;
	//If we found a thread to run, run it
	if(sch_find_thread(torun)){
		(*threads)[torun].dynpriority=(*threads)[torun].priority;
		*regs=(*threads)[torun].context;
		uint64_t lockthread=(*threads)[current_thread].ext_id;
		current_thread=torun;
		current_thread_id=(*threads)[torun].ext_id;
		release_lock(sch_lock, lockthread);
		sch_do_thread((*threads)[torun].context);
		return;		
	}else{
		//Nothing to run?
	}
	release_lock(sch_lock);
}

void sch_isr(isr_regs *context){
	//Confirm that required locks are available.
	if(!sch_inited || !try_take_lock(sch_lock)) return;

	dbgout("1\n");	
	//Save current thread's state
	irq_regs cregs;
	dbgout("2\n");
	sch_get_context(&cregs);
	dbgout("3\n");
	cregs.eip=(uint32_t)&return_immediately;
	dbgout("4\n");
	(*threads)[current_thread].context=cregs;
	dbgout("5\n");

	size_t torun;
	//If we found a thread to run, run it
	if(sch_find_thread(torun)){
		(*threads)[torun].dynpriority=(*threads)[torun].priority;
		uint64_t lockthread=(*threads)[current_thread].ext_id;
		current_thread=torun;
		current_thread_id=(*threads)[torun].ext_id;
		//Set thread running...
		irq_regs context=(*threads)[torun].context;
		dbgpf("SCH: Going to run thread %i.\n", current_thread_id);
		out_regs(context);
		release_lock(sch_lock, lockthread);
		sch_do_thread(context);
		return;	
	}else{
		//Nothing to run?
	}
	release_lock(sch_lock);
}

uint64_t sch_get_id(){
	if(!sch_inited) return 0;
	return current_thread_id;
}

void sch_yield(){
	dbgpf("SCH: Yeild (%i)\n", current_thread_id);
	sch_isr(NULL);
}

void sch_block(){
	take_lock(sch_lock);
	(*threads)[current_thread].runnable=false;
	release_lock(sch_lock);
	sch_yield();
}
