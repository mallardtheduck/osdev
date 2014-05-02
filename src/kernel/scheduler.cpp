#include "kernel.hpp"
#include "ministl.hpp"
#include "locks.hpp"

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
	size_t sch_id;
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
	mainthread.priority=100;
	mainthread.dynpriority=0;
	mainthread.magic=0xF00D;
	mainthread.ext_id=++cur_ext_id;
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
	p1[0]='A';
	p1[1]=20;
	sch_new_thread(&test_priority, (void*)p1);
	uint32_t* p2=(uint32_t*)malloc(sizeof(uint32_t)*2);
	p2[0]='B';
	p2[1]=40;
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
		take_lock(sch_lock);
		(*threads)[current_thread].runnable=false;
		release_lock(sch_lock);
		sch_yield();
		bool changed=true;
		while(changed){
			take_lock(sch_lock);
			for(int i=0; i<threads->size(); ++i){
				if((*threads)[i].to_be_deleted){
					free((*threads)[i].original_esp);
					threads->erase(i);
					changed=true;
					dbgpf("SCH: Reaped %i.\n", i);
					break;			
				}
			}
			release_lock(sch_lock);
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

extern lock mm_lock, la_lock; //locks required by scheduler.

bool sch_schedule(regs *regs){
	//Confirm that required locks are available.
	if(!sch_inited || !try_take_lock(sch_lock) || !try_take_lock(mm_lock) || !try_take_lock(la_lock)) return true;
	release_lock(mm_lock); release_lock(la_lock);
	
	//Save current thread's state
	(*threads)[current_thread].context=*regs;

	//Find runnable threads
	vector<sch_thread*> runnables;
	for(int i=0; i<threads->size(); ++i){
		if((*threads)[i].runnable){
			(*threads)[i].sch_id=i;
			if(!(*threads)[i].priority) panic("(SCH) Thread priority 0 is not allowed.\n");
			runnables.push_back(&(*threads)[i]);
		}
	}

	//If there are no runnable threads, halt. Hopefully an interrupt will awaken one soon...
	if(runnables.size()==0){
		dbgout("SCH: No runnable threads.\n");
		irq_ack(0);
		release_lock(sch_lock);
		asm("hlt");
		return false;
	}

	//Find lowest dynamic priority and subtract this from all runnable threads'
	uint32_t min=0xFFFFFFFF;
	for(int i=0; i<runnables.size(); ++i){
		if(runnables[i]->dynpriority < min) min=runnables[i]->dynpriority;
	}
	for(int i=0; i<runnables.size(); ++i){
		if(runnables[i]->dynpriority) runnables[i]->dynpriority-=min;
	}
	
	//Find a thread with dynamic priority 0 that isn't the current thread and run it
	for(int i=0; i<runnables.size(); ++i){
		if(runnables[i]->dynpriority==0 && runnables[i]->sch_id != current_thread){
			runnables[i]->dynpriority=runnables[i]->priority;
			*regs=runnables[i]->context;
			uint64_t lockthread=(*threads)[current_thread].ext_id;
			current_thread=runnables[i]->sch_id;
			release_lock(sch_lock, lockthread);
			return true;
		}
	}

	//If this thread is the only one with dynamic priority 0, continue with it...
	(*threads)[current_thread].dynpriority=(*threads)[current_thread].priority;
	release_lock(sch_lock);
	return true;
}

bool sch_isr(regs *context){
	return sch_schedule(context);
}

int sch_get_id(){
	//This is unsafe, but we can't lock without knowing the thread id...
	if(!sch_inited) return 0;
	return (*threads)[current_thread].ext_id;
}

void sch_block(){
	take_lock(sch_lock);
	(*threads)[current_thread].runnable=false;
	release_lock(sch_lock);
	sch_yield();
}
