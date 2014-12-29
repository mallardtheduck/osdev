#include "module_stubs.h"
#include "module_cpp.hpp"
#include "keyboard.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

void init_keyboard();

extern "C" int module_main(syscall_table *systbl, char *params) {
    SYSCALL_TABLE = systbl;
    init_keyboard();
    return 0;
}