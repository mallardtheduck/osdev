.global gdt_flush #Allows the C code to call gdt_flush().
.extern gdt_ptr

gdt_flush:
	lgdt gdt_ptr

	movw $0x10,%ax    # 0x10 is the offset in the GDT to our data segment
	movw %ax,%ds      # Load all data segment selectors
	movw %ax,%es
	movw %ax,%fs
	movw %ax,%gs
	movw %ax,%ss
	ljmp $0x08, $flush2   # 0x08 is the offset to our code segment: Far jump!
flush2: 
   	ret

.global idt_flush
.extern idtp

idt_flush:
	lidt idtp
	ret

.extern isr_handler

.macro ISR_NOERRCODE num
	.global isr\num
	isr\num:
		cli
		pushl $0
		pushl $\num
		jmp isr_common_stub
.endm

.macro ISR_ERRCODE num
	.global isr\num
	isr\num:
		cli
		pushl $\num
		jmp isr_common_stub
.endm

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31
ISR_NOERRCODE 128

isr_common_stub:
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %esp, %eax
	push %eax
	// Call the C kernel hardware interrupt handler
	call isr_handler
	popl %eax
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa
	add $8, %esp
	iret

.macro IRQ_ENTRY irq num
	.global irq\irq
	irq\irq:
		cli
		pushl $0
		pushl $\num
		jmp irq_common_stub
.endm

irq_common_stub:
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %esp, %eax
	push %eax
	// Call the kernel IRQ handler
	call irq_handler
	popl %eax
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa
	add $8, %esp
	iret

IRQ_ENTRY 0, 32

/*.global sch_yield
sch_yield:
	push $0
	call syscall
	ret*/

.global syscall
syscall:
	pop %eax
	int $128
	ret

.global get_ss
get_ss:
	mov %ss, %eax
	ret

.global sch_do_thread
temp:
	.byte 0x00, 0x00, 0x00, 0x00
t_cs:
	.byte 0x00, 0x00
t_eip:
	.byte 0x00, 0x00, 0x00, 0x00

sch_do_thread:
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popl %edi
	popl %esi
	popl %ebp
	popl %esp
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax
	popl temp
	popl temp
	popl t_eip
	popl temp
	pushl %eax
	movw temp, %ax
	movw %ax, t_cs
	popl %eax
	popf
	popl temp
	popl %ss
	ljmp *t_cs
	ret

.global sch_get_context
sch_get_context:
	pop %eax
	mov %gs, (%eax)
	mov %fs, 4(%eax)
	mov %es, 8(%eax)
	mov %ds, 12(%eax)
	mov %edi, 16(%eax)
	mov %esi, 20(%eax)
	mov %ebp, 24(%eax)
	mov %esp, 28(%eax)
	mov %ebx, 32(%eax)
	mov %edx, 36(%eax)
	mov %ecx, 40(%eax)
	movl $0, 44(%eax)
	movl $0, 48(%eax)
	movl $0, 52(%eax)
	movl $0, 56(%eax)
	mov %cs, 60(%eax)
	pushf
	pop %ebx
	mov %ebx, 64(%eax)
	movl $0, 68(%eax)
	mov %ss, 72(%eax)
	push %eax
	ret
