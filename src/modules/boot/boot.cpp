#include "module_stubs.h"

syscall_table *SYSCALL_TABLE;

extern "C" int module_main(syscall_table *systbl){
	SYSCALL_TABLE=systbl;
	dbgout("BOOT: Boot manager loaded.\n");
	return 0;
}