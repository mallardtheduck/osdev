#include <fstream>
#include <cstdlib>
#include <btos/table.hpp>

#include "debug.hpp"
#include "commands.hpp"

using namespace std;
using namespace btos_api;

uint16_t debug_ext_id;

const size_t thread_stack_size = 128 * 1024;

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
	printf("INTERRUPT %lx ERRCODE: %lx\n", ctx.interrupt_number, ctx.error_code);
	printf("EAX: %lx EBX: %lx ECX: %lx EDX: %lx\n", ctx.eax, ctx.ebx, ctx.ecx, ctx.edx);
	printf("EDI: %lx ESI: %lx EBP: %lx KESP: %lx\n", ctx.edi, ctx.esi, ctx.ebp, ctx.esp);
	printf("EIP: %lx CS: %lx SS*: %lx\n", ctx.eip, ctx.cs, ctx.userss);
	printf("UESP: %lx\n", ctx.useresp);
	printf("EFLAGS: %lx\n", ctx.eflags);
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

void debug_peek_string(char *dst, pid_t pid, uint32_t src, size_t max_size){
	for(size_t i = 0; i < max_size; ++i){
		debug_peek(&dst[i], pid, src + i, 1);
		if(dst[i] == '\0') return;
	}
}

void debug_poke(pid_t pid, uint32_t dst, void *src, size_t size){
	bt_debug_copy_params p;
	p.addr =  (void*)dst;
	p.pid = pid;
	p.size = size;
	call_debug(bt_debug_function::Poke, (uint32_t)src, (uint32_t)&p, 0);
}

void debug_stop(pid_t pid){
	call_debug(bt_debug_function::StopProcess, (uint32_t)pid, 0, 0);
}

void debug_continue(pid_t pid){
	call_debug(bt_debug_function::ContinueProcess, (uint32_t)pid, 0, 0);
}

bool debug_setbreakpoint(uint64_t thread, intptr_t addr, uint8_t type){
	return !!call_debug(bt_debug_function::SetBreakpoint, (uint32_t)&thread, addr, (uint32_t)type);
}

bool debug_clearbreakpoint(uint64_t thread, intptr_t addr){
	return !!call_debug(bt_debug_function::ClearBreakpoint, (uint32_t)&thread, addr, 0);
}

uint32_t debug_getbpinfo(uint64_t thread){
	return call_debug(bt_debug_function::GetBPInfo, (uint32_t)&thread, 0, 0);
}

int main(int argc, char **argv){
	std::cout << "BT/OS System Debugger" << std::endl;
    if(!init_debug()){
        std::cout << "Could not locate DEBUG extension." << std::endl;
        return 0;
    }
	
	//test_symbols(argv[0]);
    debug_register();
	
	if(argc == 2){
		pid_t pid = atoi(argv[1]);
		debug_stop(pid);
		ifstream info("INFO:/THREADS");
		table tbl = parsecsv(info);
		for(auto row: tbl.rows){
			if(atoi(row["PID"].c_str()) == pid){
				context ctx = get_context(atoi(row["ID"].c_str()));
				out_context(ctx);
				do_stacktrace(pid, ctx);
			}
		}
		debug_continue(pid);
		return 0;
	}

	btos_create_thread(&watch_thread, NULL, thread_stack_size);

	string cmd;
	do cmd = input_command();
	while(do_command(cmd));
	

    return 0;
}
