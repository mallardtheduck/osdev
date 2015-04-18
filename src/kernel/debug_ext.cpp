#include "kernel.hpp"

static uint16_t debug_ext_id;
static pid_t debugger_pid=0;

void debug_extension_uapi(uint16_t fn, isr_regs *regs){
	switch(fn){
		case 0:
			debugger_pid = proc_current_pid;
			regs->eax = 1;
			break;
		default:
			break;
	}
}

void debug_event_notify(pid_t pid, uint64_t thread, bt_debug_event::Enum event, bt_exception::Enum error){
	if(debugger_pid && debugger_pid != pid && proc_get_status(pid) == proc_status::Running){
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

void init_debug_extension(){
	debug_ext_id = add_extension(&debug_extension);
}