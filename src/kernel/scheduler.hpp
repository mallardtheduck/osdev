#ifndef _SCHEDULER_HPP
#define _SCHEDULER_HPP

#include "kernel.hpp"

const size_t default_stack_size=16*1024;

bool sch_isr(regs *context);
void sch_init();
int sch_new_thread(void (*ptr)(void*), void *param, size_t stack_size=default_stack_size);
void sch_end_thread();
void sch_yield();

#endif
