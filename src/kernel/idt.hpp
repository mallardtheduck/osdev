#ifndef _IDT_HPP
#define _IDT_HPP
#include <drivers.h>

extern "C" uint32_t syscall(uint32_t fn);

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
extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

extern "C" void isr48();
extern "C" void isr49();
extern "C" void isr50();
extern "C" void isr51();
extern "C" void isr52();
extern "C" void isr53();
extern "C" void isr54();
extern "C" void isr55();
extern "C" void isr56();
extern "C" void isr57();
extern "C" void isr58();
extern "C" void isr59();
extern "C" void isr60();
extern "C" void isr61();
extern "C" void isr62();
extern "C" void isr63();
extern "C" void isr64();
extern "C" void isr65();
extern "C" void isr66();
extern "C" void isr67();
extern "C" void isr68();
extern "C" void isr69();
extern "C" void isr70();
extern "C" void isr71();
extern "C" void isr72();
extern "C" void isr73();
extern "C" void isr74();
extern "C" void isr75();
extern "C" void isr76();
extern "C" void isr77();
extern "C" void isr78();
extern "C" void isr79();
extern "C" void isr80();
extern "C" void isr81();
extern "C" void isr82();
extern "C" void isr83();
extern "C" void isr84();
extern "C" void isr85();
extern "C" void isr86();
extern "C" void isr87();
extern "C" void isr88();
extern "C" void isr89();
extern "C" void isr90();
extern "C" void isr91();
extern "C" void isr92();
extern "C" void isr93();
extern "C" void isr94();
extern "C" void isr95();
extern "C" void isr96();
extern "C" void isr97();
extern "C" void isr98();
extern "C" void isr99();
extern "C" void isr100();
extern "C" void isr101();
extern "C" void isr102();
extern "C" void isr103();
extern "C" void isr104();
extern "C" void isr105();
extern "C" void isr106();
extern "C" void isr107();
extern "C" void isr108();
extern "C" void isr109();
extern "C" void isr110();
extern "C" void isr111();
extern "C" void isr112();
extern "C" void isr113();
extern "C" void isr114();
extern "C" void isr115();
extern "C" void isr116();
extern "C" void isr117();
extern "C" void isr118();
extern "C" void isr119();
extern "C" void isr120();
extern "C" void isr121();
extern "C" void isr122();
extern "C" void isr123();
extern "C" void isr124();
extern "C" void isr125();
extern "C" void isr126();
extern "C" void isr127();

/* System call interrupt vector */
#define SYSCALL 128 /* 0x80 */
extern "C" void isr128();

struct irq_regs {
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed));

void irq_ack(size_t);

irq_regs isr_regs2irq_regs(const isr_regs &r);

void int_handle(size_t intno, int_handler handler);
void irq_handle(size_t irqno, int_handler handler);

#endif
