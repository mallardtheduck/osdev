#include "panic.hpp"
#include "io.hpp"

void panic(char *msg){
    printf("PANIC: %s", msg);
    dbgout("PANIC: ");dbgout(msg);
    disable_interrupts();
    asm volatile("hlt");
}