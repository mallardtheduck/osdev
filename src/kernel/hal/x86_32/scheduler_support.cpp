#include "../../kernel.hpp"

struct sch_stackinfo{
	uint32_t ss;
	uint32_t esp;
} __attribute__((packed));

sch_stackinfo curstack;

void *sch_stack;

static char sch_stack_buffer[4096];

extern "C" void sch_yield();

void HAL_sch_init(){
	sch_stack=(char*)sch_stack_buffer + 4096;
}

extern "C" sch_stackinfo *sch_schedule(uint32_t ss, uint32_t esp){
	auto &sch = GetScheduler();
	uint64_t token = ((uint64_t)ss << 32) | esp;
	token = sch.Schedule(token);
	curstack.ss = (token >> 32);
	curstack.esp = (uint32_t)token;
	//dbgpf("curstack: %lx:%lx\n", curstack.ss, curstack.esp);
	if(curstack.esp < 1024 * 1024) panic("(HAL) Invalid stack!");
	return &curstack;
}

extern "C" uint32_t sch_dolock(){
	auto &hal = GetHAL();
	auto &sch = GetScheduler();

	if(!hal.AreInterruptsEnabled()) hal.EnableInterrupts();
	if(!sch.DisableScheduler()){
		return 0;
	}
	return 1;
}

extern "C" void sch_unlock(){
	GetScheduler().EnableScheduler();
}

extern "C" void sch_isr_c(){
	auto &hal = GetHAL();

	if(!Scheduler_Ready()){
		hal.AcknowlegdeIRQIfPending(0);
		return;
	}

	auto &sch = GetScheduler();
	auto &thread = CurrentThread();

	if(sch.DisableScheduler()){
		thread.SetAbortable(true);
		sch.EnableScheduler();
		hal.EnableInterrupts();
		hal.AcknowlegdeIRQIfPending(0);
		sch_yield();
		hal.DisableInterrupts();
		thread.SetAbortable(false);
	}
	hal.AcknowlegdeIRQIfPending(0);
}

extern "C" void sch_update_eip(uint32_t eip){
	CurrentThread().SetDiagnosticInstructionPointer(eip);
}