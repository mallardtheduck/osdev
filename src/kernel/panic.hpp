#ifndef _PANIC_H
#define _PANIC_H

#include <stddef.h>
#include <cstdint>
#include <module/drivers.h>

extern "C" void panic(char *msg) __attribute__ ((noreturn));
void kernel_debug_stacktrace(isr_regs *ctx);

#endif
