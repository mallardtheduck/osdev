#include "kernel.hpp"
#include <util/bitset.hpp>

static const size_t DEBUG_COPYLIMT=4096*1024;
static const uint32_t CR4_DE=(1 << 3);

static uint16_t debug_ext_id;
static bt_pid_t debugger_pid=0;

static void debug_copymem(bt_pid_t fpid, void *faddr, bt_pid_t tpid, void *taddr, size_t size);
static bool debug_setbreakpoint(uint64_t thread_id, uint32_t addr, uint8_t type);
static bool debug_clearbreakpoint(uint64_t thread_id, uint32_t addr);
static uint32_t debug_getbpinfo(uint64_t thread_id);

void debug_extension_uapi(uint16_t fn, ICPUState &state) {
	switch(fn) {
		case bt_debug_function::Query:
			state.Get32BitRegister(Generic_Register::GP_Register_A) = (uint32_t) debugger_pid;
			break;
		case bt_debug_function::Register:
			debugger_pid = CurrentProcess().ID();
			state.Get32BitRegister(Generic_Register::GP_Register_A) = 1;
			break;
		case bt_debug_function::StopProcess:
			if(state.Get32BitRegister(Generic_Register::GP_Register_B) && GetProcessManager().GetProcessStatusByID(state.Get32BitRegister(Generic_Register::GP_Register_B)) != btos_api::bt_proc_status::DoesNotExist) GetScheduler().DebugStopThreadsByPID(state.Get32BitRegister(Generic_Register::GP_Register_B));
			break;
		case bt_debug_function::ContinueProcess:
			if(state.Get32BitRegister(Generic_Register::GP_Register_B) && GetProcessManager().GetProcessStatusByID(state.Get32BitRegister(Generic_Register::GP_Register_B)) != btos_api::bt_proc_status::DoesNotExist) GetScheduler().DebugResumeThreadsByPID(state.Get32BitRegister(Generic_Register::GP_Register_B));
			break;
		case bt_debug_function::Peek:
			if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), 0) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(bt_debug_copy_params))) {
				bt_debug_copy_params *p = (bt_debug_copy_params*)state.Get32BitRegister(Generic_Register::GP_Register_C);
				if(p->pid && GetProcessManager().GetProcessStatusByID(p->pid) != btos_api::bt_proc_status::DoesNotExist && is_safe_ptr((uint32_t)p->addr, p->size, p->pid) && p->size <= DEBUG_COPYLIMT) {
					debug_copymem(p->pid, p->addr, CurrentProcess().ID(), (void*)state.Get32BitRegister(Generic_Register::GP_Register_B), p->size);
				}
			}
			break;
		case bt_debug_function::Poke:
			if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), 0) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(bt_debug_copy_params))) {
				bt_debug_copy_params *p = (bt_debug_copy_params*)state.Get32BitRegister(Generic_Register::GP_Register_C);
				if(p->pid && GetProcessManager().GetProcessStatusByID(p->pid) != btos_api::bt_proc_status::DoesNotExist && is_safe_ptr((uint32_t)p->addr, p->size, p->pid) && p->size <= DEBUG_COPYLIMT) {
					debug_copymem(CurrentProcess().ID(), (void*)state.Get32BitRegister(Generic_Register::GP_Register_B), p->pid, p->addr, p->size);
				}
			}
			break;
		case bt_debug_function::GetContext:
			//TODO: Fix for HAL ICPUContext
			// if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(isr_regs))){
			// 	void *dst = (void*)state.Get32BitRegister(Generic_Register::GP_Register_C);
			// 	void *src = sch_get_usercontext(state.Get32BitRegister(Generic_Register::GP_Register_B));
			// 	if(src) memcpy(dst, src, sizeof(isr_regs));
			// }
			break;
		case bt_debug_function::SetBreakpoint:
			if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
				uint64_t thread_id = *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
				state.Get32BitRegister(Generic_Register::GP_Register_A) = debug_setbreakpoint(thread_id, state.Get32BitRegister(Generic_Register::GP_Register_C), state.Get32BitRegister(Generic_Register::GP_Register_D));
			}
			break;
		case bt_debug_function::ClearBreakpoint:
			if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
				uint64_t thread_id = *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
				state.Get32BitRegister(Generic_Register::GP_Register_A) = debug_clearbreakpoint(thread_id, state.Get32BitRegister(Generic_Register::GP_Register_C));
			}
			break;
		case bt_debug_function::GetBPInfo:
			if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
				uint64_t thread_id = *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
				state.Get32BitRegister(Generic_Register::GP_Register_A) = debug_getbpinfo(thread_id);
			}
			break;
		default:
			break;
	}
}

void debug_event_notify(bt_pid_t pid, uint64_t thread, bt_debug_event::Enum event, bt_exception::Enum error) {
	if(debugger_pid && debugger_pid != pid && GetProcessManager().GetProcessStatusByID(pid) == btos_api::bt_proc_status::Running && GetProcessManager().GetProcessStatusByID(debugger_pid) == btos_api::bt_proc_status::Running) {
		btos_api::bt_msg_header msg;
		msg.from = 0;
		msg.source = debug_ext_id;
		msg.to = debugger_pid;
		msg.flags = 0;
		msg.type = 1;
		bt_debug_event_msg content;
		content.pid = pid;
		content.thread = thread;
		content.event = event;
		content.error = error;
		msg.length = sizeof(content);
		msg.content = (void*)&content;
		uint64_t msg_id = msg_send(msg);
		btos_api::bt_msg_header reply = msg_recv_reply_block(msg_id);
		msg_acknowledge(reply, true);
	}
}

static inline void debug_setdr(char dr, uint32_t value){
	switch(dr){
		case 0:
			asm volatile("mov %0, %%dr0":: "b"(value));
			break;
		case 1:
			asm volatile("mov %0, %%dr1":: "b"(value));
			break;
		case 2:
			asm volatile("mov %0, %%dr2":: "b"(value));
			break;
		case 3:
			asm volatile("mov %0, %%dr3":: "b"(value));
			break;

		case 6:
			asm volatile("mov %0, %%dr6":: "b"(value));
			break;
		case 7:
			asm volatile("mov %0, %%dr7":: "b"(value));
			break;
	};
}

static inline uint32_t debug_getdr(char dr){
	uint32_t ret = 0;
	switch(dr){
		case 0:
			asm volatile("mov %%dr0, %0": "=b"(ret));
			break;
		case 1:
			asm volatile("mov %%dr1, %0": "=b"(ret));
			break;
		case 2:
			asm volatile("mov %%dr2, %0": "=b"(ret));
			break;
		case 3:
			asm volatile("mov %%dr3, %0": "=b"(ret));
			break;

		case 6:
			asm volatile("mov %%dr6, %0": "=b"(ret));
			break;
		case 7:
			asm volatile("mov %%dr7, %0": "=b"(ret));
			break;
	};
	return ret;
}

module_api::kernel_extension debug_extension = {
	(char*)"DEBUG", NULL, &debug_extension_uapi
};

static void debug_isr(ICPUState &state){
	dbgpf("DEBUG: ISR (%li) from PID: %llu.\n", state.GetInterruptNo(), CurrentProcess().ID());
	dbgpf("DEBUG: DR6: %lx\n", debug_getdr(6));
	debug_event_notify(CurrentProcess().ID(), CurrentThread().ID(), bt_debug_event::Breakpoint);
	state.BreakpointResume();
}

void init_debug_extension() {
	uint32_t cr4;
	asm volatile("mov %%cr4, %0": "=b"(cr4));
	cr4 |= CR4_DE;
	asm volatile("mov %0, %%cr4":: "b"(cr4));
	debug_ext_id = add_extension(&debug_extension);
	GetHAL().HandleHWBreakpoint(&debug_isr);
	GetHAL().HandleSWBreakpoint(&debug_isr);
	debug_setdr(7, 0xF00);
}

static void debug_copymem(bt_pid_t fpid, void *faddr, bt_pid_t tpid, void *taddr, size_t size) {
	if((uint32_t)faddr + size < MM2::MM2_Kernel_Boundary || (uint32_t)taddr + size < MM2::MM2_Kernel_Boundary) return;
	void *buffer = malloc(size);
	if(!buffer) return;
	bt_pid_t cpid = CurrentProcess().ID();
	GetProcessManager().SwitchProcess(fpid);
	memcpy(buffer, faddr, size);
	GetProcessManager().SwitchProcess(tpid);
	memcpy(taddr, buffer, size);
	GetProcessManager().SwitchProcess(cpid);
	free(buffer);
}

void debug_setbreaks(bool state){
	if(state){
		uint32_t dr7 = 0xF00;
		for(char i = 0; i < 4; ++i){
			if(debug_getdr(i)){
				dr7 |= (1 << (i * 2));
				dr7 |= (1 << ((i * 2) + 1));
			}
		}
		debug_setdr(7, dr7);
	}else{
		debug_setdr(7, 0);
	}
}

void debug_getdrstate(uint32_t *buffer){
	buffer[0] = debug_getdr(0);
	buffer[1] = debug_getdr(1);
	buffer[2] = debug_getdr(2);
	buffer[3] = debug_getdr(3);
	buffer[4] = debug_getdr(6);
	buffer[5] = debug_getdr(7);
}

void debug_setdrstate(const uint32_t *buffer){
	debug_setdr(0, buffer[0]);
	debug_setdr(1, buffer[1]);
	debug_setdr(2, buffer[2]);
	debug_setdr(3, buffer[3]);
	debug_setdr(6, buffer[4]);
	debug_setdr(7, buffer[5]);
}

static size_t debug_dridx(char dr){
	if(dr >= 0 && dr <= 3) return dr;
	if(dr == 6) return 4;
	if(dr == 7) return 5;
	return 0xFFFFFFFF;
}

static void configure_dr7(size_t i, bool enable, uint8_t type, uint32_t &dr7){
	BitSet dr7Bits(32);
	dr7Bits.SetBits((void*)&dr7, 32);
	auto controlIndex = i * 2;
	dr7Bits.Set(controlIndex + 0, enable);
	dr7Bits.Set(controlIndex + 1, enable);
	auto typeIndex = 16 + (i * 4);
	BitSet typeBits(8);
	typeBits.SetBits((void*)&type, 8);
	dr7Bits.Set(typeIndex + 0, typeBits.IsSet(0));
	dr7Bits.Set(typeIndex + 1, typeBits.IsSet(1));
	dr7Bits.Set(typeIndex + 2, typeBits.IsSet(2));
	dr7Bits.Set(typeIndex + 3, typeBits.IsSet(3));
	memcpy(&dr7, dr7Bits.GetBits(), 4);
}

static bool debug_setbreakpoint(uint64_t thread_id, uint32_t addr, uint8_t type){
	bool ret = false;
	auto thread = GetScheduler().GetByID(thread_id);
	if(!thread) return false;
	uint32_t *state = thread->GetDebugState();
	if(!state) return false;
	uint32_t dr7 = state[debug_dridx(7)];
	for(size_t i = 0; i < 4; ++i){
		if(state[debug_dridx(i)] == 0){
			state[debug_dridx(i)] = addr;
			configure_dr7(i, true, type, dr7);
			ret = true;
			dbgpf("DEBUG: Set breakpoint %lu at %p for thread %llu (DR7: %lx).\n", i, (void*)addr, thread_id, dr7);
			break;
		}
	}
	state[debug_dridx(7)] = dr7;
	return ret;
}

static bool debug_clearbreakpoint(uint64_t thread_id, uint32_t addr){
	bool ret = false;
	auto thread = GetScheduler().GetByID(thread_id);
	if(!thread) return false;
	uint32_t *state = thread->GetDebugState();
	if(!state) return false;
	uint32_t dr7 = state[debug_dridx(7)];
	for(size_t i = 0; i < 4; ++i){
		if(state[debug_dridx(i)] == addr){
			state[debug_dridx(i)] = 0;
			configure_dr7(i, false, 0, dr7);
			ret = true;
			break;
		}
	}
	state[debug_dridx(7)] = dr7;
	return ret;
}

static uint32_t debug_getbpinfo(uint64_t thread_id){
	auto thread = GetScheduler().GetByID(thread_id);
	if(!thread) return false;
	uint32_t *state = thread->GetDebugState();
	if(!state) return 0;
	return state[debug_dridx(6)];
}

