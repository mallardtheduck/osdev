#include "kernel.hpp"

static const size_t DEBUG_COPYLIMT=4096*1024;

static uint16_t debug_ext_id;
static bt_pid_t debugger_pid=0;

static IDebugDriver *debugDriver;

static void debug_copymem(bt_pid_t fpid, void *faddr, bt_pid_t tpid, void *taddr, size_t size);

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
			if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(state.GetRawSize()))){
				void *dst = (void*)state.Get32BitRegister(Generic_Register::GP_Register_C);
				uint64_t tid = state.Get32BitRegister(Generic_Register::GP_Register_B);
				auto thread = GetThread(tid);
				if(thread){
					auto hl = GetScheduler().LockScheduler();
					auto &tstate = thread->GetUserState();
					auto src = tstate.GetRaw();
					if(src) memcpy(dst, src, tstate.GetRawSize());
				}
			}
			break;
		case bt_debug_function::SetBreakpoint:
			if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
				uint64_t thread_id = *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
				auto thread = GetThread(thread_id);
				if(thread){
					state.Get32BitRegister(Generic_Register::GP_Register_A) = debugDriver->SetBreakpoint(thread, state.Get32BitRegister(Generic_Register::GP_Register_C), state.Get32BitRegister(Generic_Register::GP_Register_D));
				}else{
					state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
				}
			}
			break;
		case bt_debug_function::ClearBreakpoint:
			if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
				uint64_t thread_id = *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
				auto thread = GetThread(thread_id);
				if(thread){
					state.Get32BitRegister(Generic_Register::GP_Register_A) = debugDriver->ClearBreakpoint(thread, state.Get32BitRegister(Generic_Register::GP_Register_C));
				}else{
					state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
				}
			}
			break;
		case bt_debug_function::GetBPInfo:
			if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
				uint64_t thread_id = *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
				auto thread = GetThread(thread_id);
				if(thread){
					state.Get32BitRegister(Generic_Register::GP_Register_A) = debugDriver->GetBreakAddress(thread);
				}else{
					state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
				}
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
		auto &messageManager = GetMessageManager();
		uint64_t msg_id = messageManager.SendMessage(msg);
		btos_api::bt_msg_header reply = messageManager.AwaitMessageReply(msg_id);
		messageManager.AcknowledgeMessage(reply, true);
	}
}

class DebugExtension : public IKernelExtension{
public:
	const char *GetName() override{
		return "DEBUG";
	}

	void UserAPIHandler(uint16_t fn, ICPUState &state) override{
		debug_extension_uapi(fn, state);
	}
};

static void debug_isr(ICPUState &state){
	dbgpf("DEBUG: ISR (%li) from PID: %llu.\n", state.GetInterruptNo(), CurrentProcess().ID());
	//dbgpf("DEBUG: DR6: %lx\n", debug_getdr(6));
	debug_event_notify(CurrentProcess().ID(), CurrentThread().ID(), bt_debug_event::Breakpoint);
	state.BreakpointResume();
}

void init_debug_extension() {
	debugDriver = &GetHAL().GetDebugDriver();
	debug_ext_id = GetKernelExtensionManager().AddExtension(new DebugExtension());
	GetHAL().HandleHWBreakpoint(&debug_isr);
	GetHAL().HandleSWBreakpoint(&debug_isr);
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



