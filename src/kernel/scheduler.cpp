#include "kernel.hpp"
#include "ministl.hpp"

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
	/* memory info */
};

vector<sch_thread> *threads;
size_t current_thread;
size_t reaper_thread;

void thread_reaper(void*);
void sch_threadtest();

void sch_init(){
	dbgout("SCH: Init\n");
	threads=new vector<sch_thread>();
	sch_thread mainthread;
	mainthread.runnable=true;
	mainthread.to_be_deleted=false;
	mainthread.magic=0xF00D;
	threads->push_back(mainthread);
	current_thread=threads->size()-1;
	reaper_thread=sch_new_thread(&thread_reaper, NULL, 4096);
	sch_threadtest();
	IRQ_clear_mask(0);
	dbgout("SCH: Init complete.\n");
}

void test_thread1(void* limit){
	int lim=(int)limit;
	int i=0;
	while(true){
		i++;
		dbgout("SCH: TEST THREAD 1\n");
		asm("hlt");
		if(i>=lim){
			dbgpf("SCH: TEST THREAD 1 (%i) ENDING\n", current_thread);
			return;
		}
	}
}

void test_thread2(void*){
	while(true){
		dbgout("SCH: TEST THREAD 2\n");
		asm("hlt");
	}
}

void sch_threadtest(){
	sch_new_thread(&test_thread1, (void*)20);
	sch_new_thread(&test_thread2, NULL);
}

int sch_add_thread(regs context){
	sch_thread newthread;
	newthread.context=context;
	newthread.runnable=true;
	newthread.to_be_deleted=false;
	newthread.original_esp=(void*)(context.ebx);
	newthread.start=(sch_start*)context.eax;
	newthread.magic=0xBABE;
	threads->push_back(newthread);
	return threads->size()-1;
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
		(*threads)[current_thread].runnable=false;
		sch_yield();
		bool changed=true;
		while(changed){
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
	(*threads)[current_thread].runnable=false;
	(*threads)[current_thread].to_be_deleted=true;
	(*threads)[reaper_thread].runnable=true;
	sch_yield();
}

bool sch_schedule(regs *regs){
	dbgpf("SCH: Schedule. Current thread: %i, total threads: %i\n", current_thread, threads->size());
	(*threads)[current_thread].context=*regs;
	int i=current_thread + 1;
	int count = 0;
	while((i>=threads->size() || !(*threads)[i].runnable) && count <= threads->size()){
		++i; ++count;
		if(i >= threads->size()) i = 0;
		dbgpf("SCH: Thread %i is%s runnable. (%x)\n", i, (*threads)[i].runnable?"":" not", (*threads)[i].magic);
	}
	if(count > threads->size()){
		dbgout("SCH: No runnable threads.\n");
		asm("hlt");
		irq_ack(0);
		return false;
	}
	current_thread = i;
	dbgpf("SCH: New thread: %i\n", current_thread);
	*regs=(*threads)[i].context;
	return true;
}

bool sch_isr(regs *context){
	return sch_schedule(context);
}
