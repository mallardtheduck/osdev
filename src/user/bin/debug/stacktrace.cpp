#include "debug.hpp"
#include "symbols.hpp"

using namespace std;

static bt_pid_t curpid = 0;
static vector<symbol> symbols;

vector<symbol> load_symbols(bt_pid_t pid, bool force_reload){
	if(force_reload || pid != curpid){
		symbols = get_symbols(pid);
		curpid = pid;
	}
	return symbols;
}

void do_stacktrace(bt_pid_t pid, context ctx){
	if(pid != curpid){
		symbols = get_symbols(pid);
		curpid = pid;
	}
	uint32_t bp = 0;
	uint32_t stack[2] = {ctx.ebp, ctx.eip};
	for(int count = 0; count < 100; ++count){
		symbol sym = get_symbol(symbols, stack[1]);
		printf("%p : %s in %s\n", (void*)stack[1], sym.name.c_str(), sym.file.c_str());
		if(stack[0] != bp){ 
			bp = stack[0];
			debug_peek((void*)stack, pid, bp, sizeof(stack));
		}
		else break;
	}
}
