#ifndef _PANIC_H
#define _PANIC_H

extern "C" void panic(const char *msg) __attribute__ ((noreturn));

#endif
