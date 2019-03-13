#ifndef _SCHEDULER_HPP
#define _SCHEDULER_HPP

#include "kernel.hpp"

const size_t default_stack_size=16*1024;
extern bool sch_inited;
typedef bool (*sch_blockcheck)(void*);

namespace sch_thread_status {
	enum Enum{
		Runnable = 0,
		Blocked = 1,
		DebugStopped = 2,
		DebugBlocked = 3,
		Ending = 4,
		Special = 5,
		HeldRunnable = 6,
		HeldBlocked = 7
	};
}

void sch_init();
uint64_t sch_new_thread(void (*ptr)(void*), void *param, size_t stack_size=default_stack_size);
void sch_end_thread();
extern "C" void sch_yield();
extern "C" void sch_update_eip(uint32_t eip);
const volatile uint64_t &sch_get_id();
void sch_block();
void sch_block(pid_t to);
void sch_unblock(uint64_t ext_id);
void sch_set_priority(uint32_t pri);
bool sch_active();
void sch_setpid(pid_t pid);
void sch_setblock(sch_blockcheck check, void *param);
void sch_setblock(sch_blockcheck check, void *param, pid_t to);
void sch_clearblock();
void sch_wait(uint64_t ext_id);
void sch_abortable(bool abortable, uint64_t ext_id=sch_get_id());
void sch_abort(uint64_t ext_id);
uint32_t sch_get_eip(bool lock=true);
bool sch_can_lock();
bool sch_user_abort();
void sch_set_msgstaus(thread_msg_status::Enum status, uint64_t ext_id=sch_get_id());
thread_msg_status::Enum sch_get_msgstatus(uint64_t ext_id=sch_get_id());
void sch_deferred_yield();
uint8_t *sch_get_fpu_xmm_data();
size_t sch_get_pid_threadcount(pid_t pid, bool ignore_current = false, uint64_t ext_id = sch_get_id());
void sch_debug_stop(pid_t pid);
void sch_debug_resume(pid_t pid);
void sch_hold_proc(pid_t pid = proc_current_pid);
void sch_unhold_proc(pid_t pid = proc_current_pid);
void sch_update_usercontext(isr_regs *uc, uint64_t ext_id=sch_get_id());
void *sch_get_usercontext(uint64_t ext_id=sch_get_id());
int sch_get_abortlevel();
uint32_t *sch_getdebugstate(uint64_t ext_id = sch_get_id());
void sch_yield_to(pid_t pid);

#endif
