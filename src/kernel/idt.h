#ifndef _IDH_H
#define _IDT_H

/* CPU-generated interrupt handler stubs; declared in interrupt.s */
extern "C" void isr0(); /* div by zero */
extern "C" void isr1(); /* debug */
extern "C" void isr2(); /* non-maskable interrupt */
extern "C" void isr3(); /* breakpoint */
extern "C" void isr4(); /* overflow */
extern "C" void isr5(); /* out of bounds */
extern "C" void isr6(); /* invalid opcode */
extern "C" void isr7(); /* no coprocessor */
extern "C" void isr8(); /* double fault (w/ error code) */
extern "C" void isr9(); /* coprocessor segment overrun */
extern "C" void isr10(); /* bad tss (w/ error code) */
extern "C" void isr11(); /* segment not present (w/ error code) */
extern "C" void isr12(); /* stack fault (w/ error code) */
extern "C" void isr13(); /* general protection fault (w/ error code) */
extern "C" void isr14(); /* page fault (w/ error code) */
extern "C" void isr15(); /* uknown interrupt */
extern "C" void isr16(); /* coprocessor fault */
extern "C" void isr17(); /* alignment check */
extern "C" void isr18(); /* machine exception */

/* Vectors 19 to 31 are reserved for __future__ by Intel */
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

/* Vectors 32 to 256 are configurable by us */

/* System call interrupt vector */
#define SYSCALL 128 /* 0x80 */
extern "C" void isr128();

typedef struct
{
    uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
    uint32_t interrupt_number;
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t oresp;
    uint32_t ss;
} __attribute__((packed)) handler_context_t;

#endif
