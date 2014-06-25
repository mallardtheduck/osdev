#include "module_stubs.h"

syscall_table *SYSCALL_TABLE;

#include "ini.h"

static int handler(void*, const char* section, const char* name, const char* value){
	dbgout("BOOT: [");
	dbgout((char*)section);
	dbgout("] ");
	dbgout((char*)name);
	dbgout("=");
	dbgout((char*)value);
	dbgout("\n");
	return 1;
}

extern "C" int module_main(syscall_table *systbl){
	SYSCALL_TABLE=systbl;
	dbgout("BOOT: Boot manager loaded.\n");
	if (ini_parse("INIT:/config.ini", handler, NULL) < 0) {
            dbgout("Can't load 'config.ini'\n");
            return 1;
        }
	return 0;
}