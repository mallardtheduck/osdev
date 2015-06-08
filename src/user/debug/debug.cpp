#include "debug.hpp"

uint16_t debug_ext_id;

bool init_debug(){
    debug_ext_id = bt_query_extension("DEBUG");
    return debug_ext_id != 0;
}

uint32_t call_debug(uint16_t fn, uint32_t b, uint32_t c, uint32_t d){
    uint32_t a = (debug_ext_id << 16) + fn;
    return btos_call(a, b, c, d);
}

void debug_register(){
    call_debug(bt_debug_function::Register, 0, 0, 0);
}

void out_context(const context ctx){
	printf("INTERRUPT %x ERRCODE: %x\n", ctx.interrupt_number, ctx.error_code);
	printf("EAX: %x EBX: %x ECX: %x EDX: %x\n", ctx.eax, ctx.ebx, ctx.ecx, ctx.edx);
	printf("EDI: %x ESI: %x EBP: %x KESP: %x\n", ctx.edi, ctx.esi, ctx.ebp, ctx.esp);
	printf("EIP: %x CS: %x SS*: %x\n", ctx.eip, ctx.cs, ctx.userss);
	printf("UESP: %x\n", ctx.useresp);
	printf("EFLAGS: %x\n", ctx.eflags);
}

context get_context(uint64_t thread){
	context ctx;
	call_debug(bt_debug_function::GetContext, (uint32_t)thread, (uint32_t)&ctx, 0);
	return ctx;
}

void debug_showcontext(uint64_t thread){
	context ctx = get_context(thread);
	out_context(ctx);
}

void debug_peek(void *dst, pid_t pid, uint32_t src, size_t size){
	bt_debug_copy_params p;
	p.addr = (void*)src;
	p.pid = pid;
	p.size = size;
	call_debug(bt_debug_function::Peek, (uint32_t)dst, (uint32_t)&p, 0);
}

void debug_poke(pid_t pid, uint32_t dst, void *src, size_t size){
	bt_debug_copy_params p;
	p.addr =  (void*)dst;
	p.pid = pid;
	p.size = size;
	call_debug(bt_debug_function::Poke, (uint32_t)src, (uint32_t)&p, 0);
}

int main(int /*argc*/, char **/*argv*/){
	std::cout << "BT/OS System Debugger" << std::endl;
    if(!init_debug()){
        std::cout << "Could not locate DEBUG extension." << std::endl;
        return 0;
    }
	
	//test_symbols(argv[0]);
    debug_register();

    bt_msg_header msg = bt_recv(true);
    while(true){
        if(msg.from == 0 && msg.source == debug_ext_id) {
            bt_debug_event_msg content;
            bt_msg_content(&msg, (void *) &content, sizeof(content));
			out_event(content);
			if(content.event == bt_debug_event::Exception){
				context ctx = get_context(content.thread);
				out_context(ctx);
				do_stacktrace(content.pid, ctx);
			}
            bt_msg_header reply;
            reply.to = 0;
            reply.reply_id = msg.id;
            reply.flags = bt_msg_flags::Reply;
            reply.length = 0;
            bt_send(reply);
        }
        bt_next_msg(&msg);
    }

    return 0;
}
