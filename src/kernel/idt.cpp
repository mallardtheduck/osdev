#include "kernel.hpp"
#include "idt.hpp"
#include "locks.hpp"

const int IRQ_BASE=32;
volatile unsigned int imode=0;

/* Defines an IDT entry */
struct idt_entry
{
    uint16_t base_lo;
    uint16_t sel;        /* Our kernel segment goes here! */
    uint8_t always0;     /* This will ALWAYS be set to 0! */
    uint8_t flags;       /* Set using the above table! */
    uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

int_handler handlers[256]={NULL};

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
struct idt_entry idt[256];
struct idt_ptr idtp;

extern "C" void idt_flush();
extern "C" uint32_t get_ss();

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	/* We'll leave you to try and code this function: take the
	*  argument 'base' and split it up into a high and low 16-bits,
	*  storing them in idt[num].base_hi and base_lo. The rest of the
	*  fields that you must set in idt[num] are fairly self-
	*  explanatory when it comes to setup */

	   idt[num].base_lo = base & 0xFFFF;
	   idt[num].base_hi = (base >> 16) & 0xFFFF;

	   idt[num].sel = sel;
	   idt[num].always0 = 0;
	   // We must uncomment the OR below when we get to using user-mode.
	   // It sets the interrupt gate's privilege level to 3.
	   idt[num].flags   = flags /* | 0x60 */;
}

/* Installs the IDT */
void IDT_init()
{
	dbgout("IDT init\n");
	/* Sets the special IDT pointer up, just like in 'gdt.c' */
	idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
	idtp.base = (uint32_t)&idt;

	/* Clear out the entire IDT, initializing it to zeros */
	memset(&idt, 0, sizeof(struct idt_entry) * 256);

	idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
	idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8E);
	idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8E);
	idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8E);
	idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8E);
	idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8E);
	idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8E);
	idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
	idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8E);
	idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
	idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
	idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
	idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
	idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
	idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
	idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
	idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
	idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
	idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
	idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
	idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
	idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
	idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
	idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
	idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
	idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
	idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
	idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
	idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
	idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
	idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

	idt_set_gate(48, (uint32_t)isr48, 0x08, 0x8E);
    idt_set_gate(49, (uint32_t)isr49, 0x08, 0x8E);
    idt_set_gate(50, (uint32_t)isr50, 0x08, 0x8E);
    idt_set_gate(51, (uint32_t)isr51, 0x08, 0x8E);
    idt_set_gate(52, (uint32_t)isr52, 0x08, 0x8E);
    idt_set_gate(53, (uint32_t)isr53, 0x08, 0x8E);
    idt_set_gate(54, (uint32_t)isr54, 0x08, 0x8E);
    idt_set_gate(55, (uint32_t)isr55, 0x08, 0x8E);
    idt_set_gate(56, (uint32_t)isr56, 0x08, 0x8E);
    idt_set_gate(57, (uint32_t)isr57, 0x08, 0x8E);
    idt_set_gate(58, (uint32_t)isr58, 0x08, 0x8E);
    idt_set_gate(59, (uint32_t)isr59, 0x08, 0x8E);
    idt_set_gate(60, (uint32_t)isr60, 0x08, 0x8E);
    idt_set_gate(61, (uint32_t)isr61, 0x08, 0x8E);
    idt_set_gate(62, (uint32_t)isr62, 0x08, 0x8E);
    idt_set_gate(63, (uint32_t)isr63, 0x08, 0x8E);
    idt_set_gate(64, (uint32_t)isr64, 0x08, 0x8E);
    idt_set_gate(65, (uint32_t)isr65, 0x08, 0x8E);
    idt_set_gate(66, (uint32_t)isr66, 0x08, 0x8E);
    idt_set_gate(67, (uint32_t)isr67, 0x08, 0x8E);
    idt_set_gate(68, (uint32_t)isr68, 0x08, 0x8E);
    idt_set_gate(69, (uint32_t)isr69, 0x08, 0x8E);
    idt_set_gate(70, (uint32_t)isr70, 0x08, 0x8E);
    idt_set_gate(71, (uint32_t)isr71, 0x08, 0x8E);
    idt_set_gate(72, (uint32_t)isr72, 0x08, 0x8E);
    idt_set_gate(73, (uint32_t)isr73, 0x08, 0x8E);
    idt_set_gate(74, (uint32_t)isr74, 0x08, 0x8E);
    idt_set_gate(75, (uint32_t)isr75, 0x08, 0x8E);
    idt_set_gate(76, (uint32_t)isr76, 0x08, 0x8E);
    idt_set_gate(77, (uint32_t)isr77, 0x08, 0x8E);
    idt_set_gate(78, (uint32_t)isr78, 0x08, 0x8E);
    idt_set_gate(79, (uint32_t)isr79, 0x08, 0x8E);
    idt_set_gate(80, (uint32_t)isr80, 0x08, 0x8E);
    idt_set_gate(81, (uint32_t)isr81, 0x08, 0x8E);
    idt_set_gate(82, (uint32_t)isr82, 0x08, 0x8E);
    idt_set_gate(83, (uint32_t)isr83, 0x08, 0x8E);
    idt_set_gate(84, (uint32_t)isr84, 0x08, 0x8E);
    idt_set_gate(85, (uint32_t)isr85, 0x08, 0x8E);
    idt_set_gate(86, (uint32_t)isr86, 0x08, 0x8E);
    idt_set_gate(87, (uint32_t)isr87, 0x08, 0x8E);
    idt_set_gate(88, (uint32_t)isr88, 0x08, 0x8E);
    idt_set_gate(89, (uint32_t)isr89, 0x08, 0x8E);
    idt_set_gate(90, (uint32_t)isr90, 0x08, 0x8E);
    idt_set_gate(91, (uint32_t)isr91, 0x08, 0x8E);
    idt_set_gate(92, (uint32_t)isr92, 0x08, 0x8E);
    idt_set_gate(93, (uint32_t)isr93, 0x08, 0x8E);
    idt_set_gate(94, (uint32_t)isr94, 0x08, 0x8E);
    idt_set_gate(95, (uint32_t)isr95, 0x08, 0x8E);
    idt_set_gate(96, (uint32_t)isr96, 0x08, 0x8E);
    idt_set_gate(97, (uint32_t)isr97, 0x08, 0x8E);
    idt_set_gate(98, (uint32_t)isr98, 0x08, 0x8E);
    idt_set_gate(99, (uint32_t)isr99, 0x08, 0x8E);
    idt_set_gate(100, (uint32_t)isr100, 0x08, 0x8E);
    idt_set_gate(101, (uint32_t)isr101, 0x08, 0x8E);
    idt_set_gate(102, (uint32_t)isr102, 0x08, 0x8E);
    idt_set_gate(103, (uint32_t)isr103, 0x08, 0x8E);
    idt_set_gate(104, (uint32_t)isr104, 0x08, 0x8E);
    idt_set_gate(105, (uint32_t)isr105, 0x08, 0x8E);
    idt_set_gate(106, (uint32_t)isr106, 0x08, 0x8E);
    idt_set_gate(107, (uint32_t)isr107, 0x08, 0x8E);
    idt_set_gate(108, (uint32_t)isr108, 0x08, 0x8E);
    idt_set_gate(109, (uint32_t)isr109, 0x08, 0x8E);
    idt_set_gate(110, (uint32_t)isr110, 0x08, 0x8E);
    idt_set_gate(111, (uint32_t)isr111, 0x08, 0x8E);
    idt_set_gate(112, (uint32_t)isr112, 0x08, 0x8E);
    idt_set_gate(113, (uint32_t)isr113, 0x08, 0x8E);
    idt_set_gate(114, (uint32_t)isr114, 0x08, 0x8E);
    idt_set_gate(115, (uint32_t)isr115, 0x08, 0x8E);
    idt_set_gate(116, (uint32_t)isr116, 0x08, 0x8E);
    idt_set_gate(117, (uint32_t)isr117, 0x08, 0x8E);
    idt_set_gate(118, (uint32_t)isr118, 0x08, 0x8E);
    idt_set_gate(119, (uint32_t)isr119, 0x08, 0x8E);
    idt_set_gate(120, (uint32_t)isr120, 0x08, 0x8E);
    idt_set_gate(121, (uint32_t)isr121, 0x08, 0x8E);
    idt_set_gate(122, (uint32_t)isr122, 0x08, 0x8E);
    idt_set_gate(123, (uint32_t)isr123, 0x08, 0x8E);
    idt_set_gate(124, (uint32_t)isr124, 0x08, 0x8E);
    idt_set_gate(125, (uint32_t)isr125, 0x08, 0x8E);
    idt_set_gate(126, (uint32_t)isr126, 0x08, 0x8E);
    idt_set_gate(127, (uint32_t)isr127, 0x08, 0x8E);
	idt_set_gate(128, (uint32_t)isr128, 0x08, 0xEE);

	idt_set_gate(32, (uint32_t)irq0 , 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)irq1 , 0x08, 0x8E);
    idt_set_gate(34, (uint32_t)irq2 , 0x08, 0x8E);
    idt_set_gate(35, (uint32_t)irq3 , 0x08, 0x8E);
    idt_set_gate(36, (uint32_t)irq4 , 0x08, 0x8E);
    idt_set_gate(37, (uint32_t)irq5 , 0x08, 0x8E);
    idt_set_gate(38, (uint32_t)irq6 , 0x08, 0x8E);
    idt_set_gate(39, (uint32_t)irq7 , 0x08, 0x8E);
    idt_set_gate(40, (uint32_t)irq8 , 0x08, 0x8E);
    idt_set_gate(41, (uint32_t)irq9 , 0x08, 0x8E);
    idt_set_gate(42, (uint32_t)irq10 , 0x08, 0x8E);
    idt_set_gate(43, (uint32_t)irq11 , 0x08, 0x8E);
    idt_set_gate(44, (uint32_t)irq12 , 0x08, 0x8E);
    idt_set_gate(45, (uint32_t)irq13 , 0x08, 0x8E);
    idt_set_gate(46, (uint32_t)irq14 , 0x08, 0x8E);
    idt_set_gate(47, (uint32_t)irq15 , 0x08, 0x8E);

    idt_set_gate(166, (uint32_t)irq14, 0x08, 0x8E);

	/* Points the processor's internal register to the new IDT */
	idt_flush();
}

void out_int_info(const isr_regs ctx){
	dbgpf("INTERRUPT %x ERRCODE: %x\n", ctx.interrupt_number, ctx.error_code);
	dbgpf("EAX: %x EBX: %x ECX: %x EDX: %x\n", ctx.eax, ctx.ebx, ctx.ecx, ctx.edx);
	dbgpf("EDI: %x ESI: %x EBP: %x ESP: %x\n", ctx.edi, ctx.esi, ctx.ebp, ctx.esp);
	dbgpf("EIP: %x CS: %x SS*: %x\n", ctx.eip, ctx.cs, get_ss());
	dbgpf("EFLAGS: %x\n", ctx.eflags);
}

extern size_t current_thread;

extern "C" void isr_handler(isr_regs *ctx){
    imode++;
    if(sch_can_lock()) {
        sch_update_eip(ctx->eip);
        sch_abortable(false);
    }
	if(handlers[ctx->interrupt_number]) handlers[ctx->interrupt_number](ctx->interrupt_number, ctx);
	else if(ctx->interrupt_number==0x06){
		dbgpf("\nInterrupt %i at %x!\n", ctx->interrupt_number, ctx->eip);
		dbgpf("Current thread: %i (%i)\n", current_thread, (uint32_t)sch_get_id());
		out_int_info(*ctx);
		if(ctx->eip < VMM_USERSPACE_START) panic("Invalid opcode.");
        else proc_terminate();
	}
	else if(ctx->interrupt_number==0x0D){
		dbgpf("\nInterrupt %i at %x!\n", ctx->interrupt_number, ctx->eip);
		dbgpf("Current thread: %i (%i)\n", current_thread, (uint32_t)sch_get_id());
		out_int_info(*ctx);
        if(ctx->eip < VMM_USERSPACE_START) panic("General Protection Fault.");
        else proc_terminate();
	}
	else if(ctx->interrupt_number==0x08){
		dbgpf("\nInterrupt %i at %x!\n", ctx->interrupt_number, ctx->eip);
		dbgpf("Current thread: %i (%i)\n", current_thread, (uint32_t)sch_get_id());
		out_int_info(*ctx);
        if(ctx->eip < VMM_USERSPACE_START) panic("Double fault.");
        else proc_terminate();
	}else if(ctx->interrupt_number==0x00){
        dbgpf("\nInterrupt %i at %x!\n", ctx->interrupt_number, ctx->eip);
        dbgpf("Current thread: %i (%i)\n", current_thread, (uint32_t)sch_get_id());
        out_int_info(*ctx);
        if(ctx->eip < VMM_USERSPACE_START) panic("Devide by zero!");
        else proc_terminate();
    }else{
		dbgpf("\nInterrupt %i at %x!\n", ctx->interrupt_number, ctx->eip);
		dbgpf("Current thread: %i (%i)\n", current_thread, (uint32_t)sch_get_id());
		out_int_info(*ctx);
	}
    disable_interrupts();
    if(sch_can_lock()) {
        sch_abortable(true);
    }
    imode--;
}

void irq_ack(size_t irq_no) {
    PIC_sendEOI(irq_no);
}

inline void out_regs(const irq_regs ctx){
	dbgpf("INTERRUPT %x\n", ctx.int_no);
	dbgpf("EAX: %x EBX: %x ECX: %x EDX: %x\n", ctx.eax, ctx.ebx, ctx.ecx, ctx.edx);
	dbgpf("EDI: %x ESI: %x EBP: %x ESP: %x\n", ctx.edi, ctx.esi, ctx.ebp, ctx.esp);
	dbgpf("EIP: %x CS: %x SS: %x\n", ctx.eip, ctx.cs, ctx.ss);
	dbgpf("EFLAGS: %x ORESP: %x\n", ctx.eflags, ctx.useresp);
}

extern "C" void irq_handler(irq_regs *r) {
    imode++;
    if(sch_can_lock()) {
        sch_update_eip(r->eip);
        sch_abortable(false);
    }
	//out_regs(*r);
	int irq=r->int_no-IRQ_BASE;
	if(handlers[r->int_no]) handlers[r->int_no](r->int_no, (isr_regs*)r);
    irq_ack(irq);
    disable_interrupts();
    if(sch_can_lock()) {
        sch_abortable(true);
    }
    imode--;
}

irq_regs isr_regs2irq_regs(const isr_regs &r){
	irq_regs ret;
	ret.eax=r.eax; ret.ebx=r.ebx; ret.ecx=r.ecx; ret.edx=r.edx;
	ret.edi=r.edi; ret.esi=r.esi; ret.ebp=r.ebp; ret.esp=r.esp;
	ret.eip=r.eip; ret.cs=r.cs; ret.eflags=r.eflags;
	ret.ss=get_ss();
	return ret;
}

void int_handle(size_t intno, int_handler handler){
	handlers[intno]=handler;
}

void irq_handle(size_t irqno, int_handler handler){
	handlers[irqno+IRQ_BASE]=handler;
}

bool is_imode(){
    return imode;
}