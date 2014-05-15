#include "module_stubs.h"

typedef int (*syscall_vector)(int, void*);
syscall_vector syscall;

int getthenumber(){
	return 42;
}

int module_main(syscall_vector sys){
	syscall=sys;
	int thenumber=getthenumber();
	dbgout("TEST: Hello world!\n");
	return thenumber*2;
}
