#ifndef _SCHEDULER_HPP
#define _SCHEDULER_HPP

#include "kernel.hpp"

const size_t default_stack_size=16*1024;
extern bool sch_inited;

/*void sch_isr(isr_regs *context);
void sch_irq(irq_regs *context);*/
void sch_init();
int sch_new_thread(void (*ptr)(void*), void *param, size_t stack_size=default_stack_size);
void sch_end_thread();
extern "C" void sch_yield();
uint64_t sch_get_id();
void sch_block();

#endif
