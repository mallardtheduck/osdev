#include "debug.hpp"
#include "symbols.hpp"

using namespace std;

void do_stacktrace(bt_pid_t pid, context ctx){
	vector<symbol> symbols = get_symbols(pid);
	uint32_t bp = 0;
	uint32_t stack[2] = {ctx.ebp, ctx.eip};
	for(int count = 0; count < 100; ++count){
		symbol sym = get_symbol(symbols, stack[1]);
		printf("%p : %s\n", (void*)stack[1], sym.name.c_str());
		if(stack[0] != bp){ 
			bp = stack[0];
			debug_peek((void*)stack, pid, bp, sizeof(stack));
		}
		else break;
	}
}