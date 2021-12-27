#include "../kernel.hpp"
#include "mm2_internal.hpp"

char *modules_infofs();

namespace MM2{
	static const uint32_t ec_user = (1 << 2);

	void page_fault_handler(ICPUState &state){
		uint32_t addr = state.GetPageFaultAddress();
		uint32_t physaddr=current_pagedir->virt2phys((void*)addr);
		if(current_pagedir->handle_pf((void*)addr)){
			//dbgout("MM2: PF resolved by current pagedir.\n");
		}else if(kernel_pagedir->handle_pf((void*)addr)){
			//dbgout("MM2: PF resolved by kernel pagedir.\n");
		}else if(state.GetErrorCode() & ec_user){
			dbgpf("MM2: Page fault on %lx at %lx (ec: %lx) PID: %llu!\n", 
				addr, state.Get32BitRegister(Generic_Register::Instruction_Pointer), state.GetErrorCode(), CurrentProcess().ID());
			//state.DebugOutput();
			debug_event_notify(CurrentProcess().ID(), CurrentThread().ID(), bt_debug_event::Exception, bt_exception::UnresolvedPageFault);
			//If a process kills itself, the thread will be assigned PID 0 and will #PF when attempting to return to userspace
			//Therefore, if we encounter a userspace #PF on PID 0, end the thread.
			if(CurrentProcess().ID()) CurrentProcess().Terminate();
			else CurrentThread().Abort();
		}else{
			state.DebugOutput();
			dbgpf("MM2: Page fault on %lx at %lx!\n", addr, state.Get32BitRegister(Generic_Register::Instruction_Pointer));
			dbgpf("MM2: Physical address: %lx\n", physaddr);
			state.DebugStackTrace();
			//TODO: Reinstate this somehow...
			//dbgout(modules_infofs());
			if (addr < MM2_Page_Size) {
				panic("(MM2) Probable NULL pointer dereference!");
			} else panic("(MM2) Page fault!");
		}
	}

}