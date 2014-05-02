#include "kernel.hpp"
#include "ministl.hpp"

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
	mainthread.priority=1;
	mainthread.dynpriority=0;
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
	sch_new_thread(&test_thread1, (void*)20);
	sch_new_thread(&test_thread2, NULL);
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

bool sch_schedule_old(regs *regs){
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
		irq_ack(0);
		asm("hlt");
		return false;
	}
	current_thread = i;
	dbgpf("SCH: Now running thread: %i\n", current_thread);
	*regs=(*threads)[i].context;
	return true;
}

bool sch_schedule(regs *regs){
	dbgpf("SCH: Schedule. Current thread: %i, total threads: %i\n", current_thread, threads->size());
	(*threads)[current_thread].context=*regs;
	vector<sch_thread*> runnables;
	for(int i=0; i<threads->size(); ++i){
		if((*threads)[i].runnable){
			(*threads)[i].sch_id=i;
			runnables.push_back(&(*threads)[i]);
		}
	}
	if(runnables.size()==0){
		dbgout("SCH: No runnable threads.\n");
		irq_ack(0);
		asm("hlt");
		return false;
	}
	uint32_t min=0xFFFFFFFF;
	for(int i=0; i<runnables.size(); ++i){
		dbgpf("SCH: Thread %i, priority %i, dynpriority %i\n", 
			runnables[i]->sch_id, runnables[i]->priority, runnables[i]->dynpriority);
		if(runnables[i]->dynpriority < min) min=runnables[i]->dynpriority;
	}
	for(int i=0; i<runnables.size(); ++i){
		if(runnables[i]->dynpriority) runnables[i]->dynpriority-=min;
	}
	for(int i=0; i<runnables.size(); ++i){
		if(runnables[i]->dynpriority==0 && runnables[i]->sch_id != current_thread){
			runnables[i]->dynpriority=runnables[i]->priority;
			*regs=runnables[i]->context;
			current_thread=runnables[i]->sch_id;
			dbgpf("SCH: Running thread %i.\n", current_thread);
			return true;
		}
	}
	//Continue with current thread...
	(*threads)[current_thread].dynpriority=(*threads)[current_thread].priority;
	dbgpf("SCH: Running thread %i.\n", current_thread);
	return true;
}

bool sch_isr(regs *context){
	return sch_schedule(context);
}
