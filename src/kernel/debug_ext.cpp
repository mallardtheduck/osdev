#include "kernel.hpp"

static const size_t DEBUG_COPYLIMT=4096*1024;

static uint16_t debug_ext_id;
static pid_t debugger_pid=0;

void debug_copymem(pid_t fpid, void *faddr, pid_t tpid, void *taddr, size_t size);

void debug_extension_uapi(uint16_t fn, isr_regs *regs) {
	switch(fn) {
		case bt_debug_function::Query:
			regs->eax = (uint32_t) debugger_pid;
			break;
		case bt_debug_function::Register:
			debugger_pid = proc_current_pid;
			regs->eax = 1;
			break;
		case bt_debug_function::StopProcess:
			if(regs->ebx) sch_debug_stop(regs->ebx);
			break;
		case bt_debug_function::ContinueProcess:
			if(regs->ebx) sch_debug_resume(regs->ebx);
			break;
		case bt_debug_function::Peek:
			if(is_safe_ptr(regs->ebx, 0) && is_safe_ptr(regs->ecx, sizeof(bt_debug_copy_params))) {
				bt_debug_copy_params *p = (bt_debug_copy_params*)regs->ecx;
				if(p->pid && is_safe_ptr((uint32_t)p->addr, p->size, p->pid) && p->size <= DEBUG_COPYLIMT) {
					debug_copymem(p->pid, p->addr, proc_current_pid, (void*)regs->ebx, p->size);
				}
			}
			break;
		case bt_debug_function::Poke:
			if(is_safe_ptr(regs->ebx, 0) && is_safe_ptr(regs->ecx, sizeof(bt_debug_copy_params))) {
				bt_debug_copy_params *p = (bt_debug_copy_params*)regs->ecx;
				if(p->pid && is_safe_ptr((uint32_t)p->addr, p->size, p->pid) && p->size <= DEBUG_COPYLIMT) {
					debug_copymem(proc_current_pid, (void*)regs->ebx, p->pid, p->addr, p->size);
				}
			}
		case bt_debug_function::GetContext:
			if(is_safe_ptr(regs->ecx, sizeof(isr_regs))){
				void *dst = (void*)regs->ecx;
				void *src = sch_get_usercontext(regs->ebx);
				memcpy(dst, src, sizeof(isr_regs));
			}
			break;
		default:
			break;
	}
}

void debug_event_notify(pid_t pid, uint64_t thread, bt_debug_event::Enum event, bt_exception::Enum error) {
	if(debugger_pid && debugger_pid != pid && proc_get_status(pid) == proc_status::Running) {
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

module_api::kernel_extension debug_extension = {
	"DEBUG", NULL, &debug_extension_uapi
};

void init_debug_extension() {
	debug_ext_id = add_extension(&debug_extension);
}

void debug_copymem(pid_t fpid, void *faddr, pid_t tpid, void *taddr, size_t size) {
	void *buffer = malloc(size);
	if(!buffer) return;
	pid_t cpid = proc_current_pid;
	proc_switch(fpid);
	memcpy(buffer, faddr, size);
	proc_switch(tpid);
	memcpy(taddr, buffer, size);
	proc_switch(cpid);
	free(buffer);
}
