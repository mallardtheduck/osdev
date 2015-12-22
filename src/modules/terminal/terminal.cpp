#include "module_stubs.h"
#include "fs_interface.h"
#include "terminal.hpp"
#include "vterm.hpp"
#include "device.hpp"
#include "console_backend.hpp"
#include "extension.h"
#include "api.hpp"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

uint64_t default_terminal;
uint16_t terminal_extension_id;

kernel_extension terminal_extension={
	"TERMINAL",
	NULL,
	&terminal_uapi_fn
};

#pragma GCC diagnostic ignored "-Wunused-parameter"

void init();

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
    init();
    return 0;
}

void init(){
	terminal_extension_id = add_extension(&terminal_extension);
	infofs_register("TERMS", &terms_infofs);
    init_device();
    terminals=new vterm_list();
    cons_backend=new console_backend();
    uint64_t id=terminals->create_terminal(cons_backend);
    terminals->get(id)->sync();
    cons_backend->switch_terminal(id);
    default_terminal=id;
}

extern "C" void __cxa_pure_virtual()
{
    panic("Pure virtual function call!");
}
