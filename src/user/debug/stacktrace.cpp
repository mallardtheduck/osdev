#include "debug.hpp"

void do_stacktrace(bt_pid_t pid, context ctx){
	uint32_t bp = 0;
	uint32_t stack[2] = {ctx.ebp, ctx.eip};
	for(int count = 0; count < 100; ++count){
		printf("%p\n", (void*)stack[1]);
		if(stack[0] != bp){ 
			bp = stack[0];
			debug_peek((void*)stack, pid, bp, sizeof(stack));
		}
		else break;
	}
}