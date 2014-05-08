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
	regs context;
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
size_t reaper_thread;
uint64_t cur_ext_id;

void thread_reaper(void*);
void sch_threadtest();

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
	mainthread.ext_id=++cur_ext_id;
	threads->push_back(mainthread);
	current_thread=threads->size()-1;
	reaper_thread=sch_new_thread(&thread_reaper, NULL, 4096);
	sch_threadtest();
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

int sch_add_thread(regs context){
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
	regs newcontext = {0};
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
					free((*threads)[i].original_esp);
					threads->erase(i);
					changed=true;
					dbgpf("SCH: Reaped %i.\n", i);
					break;
				}
			}
			changed=false;
		}
	}
}

void sch_yield(){
	asm("int $32");
}

void sch_end_thread(){
	take_lock(sch_lock);
	(*threads)[current_thread].runnable=false;
	(*threads)[current_thread].to_be_deleted=true;
	(*threads)[reaper_thread].runnable=true;
	release_lock(sch_lock);
	sch_yield();
}

bool sch_schedule(regs *regs){
	//Confirm that required locks are available.
	if(!sch_inited || !try_take_lock(sch_lock)) return true;
	
	//Save current thread's state
	(*threads)[current_thread].context=*regs;

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
		irq_ack(0);
		release_lock(sch_lock);
		asm("hlt");
		return false;
	}
	
	//Subtract minimum dynamic priority from all threads. If there is now a thread with dynamic priority 0
	//that isn't the current thread, record it
	bool foundtorun=false;
	size_t torun;
	for(int i=0; i<(*threads).size(); ++i){
		if((*threads)[i].runnable){
			if((*threads)[i].dynpriority) (*threads)[i].dynpriority-=min;
			if(i!=current_thread && (*threads)[i].dynpriority==0){
				foundtorun=true;
				torun=i;
			}
		}
	}

	//If we found a thread to run, run it
	if(foundtorun){
		(*threads)[torun].dynpriority=(*threads)[torun].priority;
		*regs=(*threads)[torun].context;
		uint64_t lockthread=(*threads)[current_thread].ext_id;
		current_thread=torun;
		release_lock(sch_lock);//, lockthread);
		if(regs->eip>(uint32_t)&_end || regs->eip<(uint32_t)&_start){
			dbgpf("SCH: Thread %i.\n", torun);
			panic("(SCH) Invalid thread state!\n");
		}
		if((*threads)[torun].magic!=0xF00D && (*threads)[torun].magic!=0xBABE){
			dbgpf("SCH: Thread %i.\n", torun);
			panic("(SCH) Invalid thread magic!\n");
		}
		return true;
	}

	//If this thread is the only one with dynamic priority 0, continue with it...
	(*threads)[current_thread].dynpriority=(*threads)[current_thread].priority;
	*regs=(*threads)[current_thread].context;
	if(regs->eip>(uint32_t)&_end || regs->eip<(uint32_t)&_start) panic("(SCH) Current thread has invalid state.\n");
	if((*threads)[current_thread].magic!=0xF00D && (*threads)[current_thread].magic!=0xBABE){
		panic("(SCH) Invalid current thread magic!\n");
	}
	release_lock(sch_lock);
	return true;
}

bool sch_isr(regs *context){
	return sch_schedule(context);
}

int sch_get_id(){
	//This is unsafe, but we can't lock without knowing the thread id...
	if(!sch_inited) return 0;
	return 0xCAFE;
//	return (*threads)[current_thread].ext_id;
}

void sch_block(){
	take_lock(sch_lock);
	(*threads)[current_thread].runnable=false;
	release_lock(sch_lock);
	sch_yield();
}
