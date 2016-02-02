#include <btos_module.h>

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

#pragma GCC diagnostic ignored "-Wunused-parameter"

int module_main(syscall_table *systbl, char *params){
		SYSCALL_TABLE=systbl;
    	return 0;
}