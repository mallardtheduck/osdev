#include "module_stubs.h"
#include "fs_interface.h"
#include "terminal.hpp"
#include "vterm.hpp"
#include "device.hpp"
#include "console_backend.hpp"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

#pragma GCC diagnostic ignored "-Wunused-parameter"

void init();

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
    init();
    return 0;
}

void init(){
    cons_backend=new console_backend();
    terminals=new vterm_list();
    uint64_t id=terminals->create_terminal(cons_backend);
    terminals->get(id)->sync();
    terminals->switch_terminal(id);
    init_device();
}

extern "C" void __cxa_pure_virtual()
{
    panic("Pure virtual function call!");
}
