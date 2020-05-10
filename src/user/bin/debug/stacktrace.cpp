#include "debug.hpp"
#include "symbols.hpp"
#include <sstream>

using namespace std;
using namespace btos_api;

static bt_pid_t curpid = 0;
static vector<symbol> symbols;

string stacksymname(size_t n){
	stringstream ss;
	ss << "STACK#" << n;
	return ss.str();
}

vector<symbol> stack_symbols(bt_pid_t pid, context ctx){
	vector<symbol> ret;
	uint32_t bp = 0;
	uint32_t stack[2] = {ctx.ebp, ctx.eip};
	for(int count = 0; count < 100; ++count){
		if(stack[1] == 0) break;
		symbol sym;
		sym.address = stack[0];
		if(ret.size()){
			sym.size = sym.address - ret.back().address;
		}else{
			sym.size = ctx.ebp - ctx.useresp;
		}
		sym.name = stacksymname(ret.size());
		sym.file = "(None)";
		ret.push_back(sym);
		if(stack[0] != bp){ 
			bp = stack[0];
			debug_peek((void*)stack, pid, bp, sizeof(stack));
		}
		else break;
	}
	return ret;
}

vector<symbol> load_symbols(bt_pid_t pid, bool force_reload){
	if(force_reload || pid != curpid){
		symbols = get_symbols(pid);
		curpid = pid;
	}
	return symbols;
}

void do_stacktrace(bt_pid_t pid, context ctx, size_t limit){
	if(pid != curpid){
		symbols = get_symbols(pid);
		curpid = pid;
	}
	uint32_t bp = 0;
	uint32_t stack[2] = {ctx.ebp, ctx.eip};
	for(size_t count = 0; count < limit; ++count){
		if(stack[1] == 0) break;
		symbol sym = get_symbol(symbols, stack[1]);
		printf("%p : %s in %s\n", (void*)stack[1], sym.name.c_str(), sym.file.c_str());
		if(stack[0] != bp){ 
			bp = stack[0];
			debug_peek((void*)stack, pid, bp, sizeof(stack));
		}
		else break;
	}
}
