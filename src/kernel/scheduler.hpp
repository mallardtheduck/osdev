#ifndef _SCHEDULER_HPP
#define _SCHEDULER_HPP

#include "kernel.hpp"

const size_t default_stack_size=16*1024;
extern bool sch_inited;
typedef bool (*sch_blockcheck)(void*);

void sch_isr(int,isr_regs*);
void sch_init();
uint64_t sch_new_thread(void (*ptr)(void*), void *param, size_t stack_size=default_stack_size);
void sch_end_thread();
extern "C" void sch_yield();
const uint64_t &sch_get_id();
void sch_block();
void sch_unblock(uint64_t ext_id);
void sch_set_priority(uint32_t pri);
bool sch_active();
void sch_setpid(pid_t pid);
void sch_setblock(sch_blockcheck check, void *param);
void sch_clearblock();
void sch_wait(uint64_t ext_id);
extern "C" void sch_update_eip(uint32_t eip);

#endif
