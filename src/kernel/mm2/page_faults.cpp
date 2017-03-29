#include "../kernel.hpp"
#include "mm2_internal.hpp"

char *modules_infofs();

namespace MM2{
	static const uint32_t ec_user = (1 << 2);

	void page_fault_handler(int, isr_regs *regs){
		uint32_t addr;
		asm volatile("mov %%cr2, %%eax\r\n mov %%eax,%0": "=m"(addr): : "eax");
		uint32_t physaddr=current_pagedir->virt2phys((void*)addr);
		if(current_pagedir->handle_pf((void*)addr)){
			//dbgout("MM2: PF resolved by current pagedir.\n");
		}else if(kernel_pagedir->handle_pf((void*)addr)){
			//dbgout("MM2: PF resolved by kernel pagedir.\n");
		}else if(regs->error_code & ec_user){
			dbgpf("MM2: Page fault on %x at %x (ec: %x)!\n", addr, regs->eip, regs->error_code);
			//dbgpf("MM2: Page fault on %x at %x!\n", addr, regs->eip);
			out_int_info(*regs);
			debug_event_notify(proc_current_pid, sch_get_id(), bt_debug_event::Exception, bt_exception::UnresolvedPageFault);
			//If a process kills itself, the thread will be assigned PID 0 and will #PF when attempting to return to userspace
			//Therefore, if we encounter a userspace #PF on PID 0, end the thread.
			if(proc_current_pid)proc_terminate();
			else sch_end_thread();
		}else{
			out_int_info(*regs);
			dbgpf("MM2: Page fault on %x at %x!\n", addr, regs->eip);
			dbgpf("MM2: Physical address: %x\n", physaddr);
			kernel_debug_stacktrace(regs);
			dbgout(modules_infofs());
			if (addr < MM2_Page_Size) {
				panic("(MM2) Probable NULL pointer dereference!");
			} else panic("(MM2) Page fault!");
		}
	}

}