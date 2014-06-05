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

ISR_NOERRCODE	48
ISR_NOERRCODE	49
ISR_NOERRCODE	50
ISR_NOERRCODE	51
ISR_NOERRCODE	52
ISR_NOERRCODE	53
ISR_NOERRCODE	54
ISR_NOERRCODE	55
ISR_NOERRCODE	56
ISR_NOERRCODE	57
ISR_NOERRCODE	58
ISR_NOERRCODE	59
ISR_NOERRCODE	60
ISR_NOERRCODE	61
ISR_NOERRCODE	62
ISR_NOERRCODE	63
ISR_NOERRCODE	64
ISR_NOERRCODE	65
ISR_NOERRCODE	66
ISR_NOERRCODE	67
ISR_NOERRCODE	68
ISR_NOERRCODE	69
ISR_NOERRCODE	70
ISR_NOERRCODE	71
ISR_NOERRCODE	72
ISR_NOERRCODE	73
ISR_NOERRCODE	74
ISR_NOERRCODE	75
ISR_NOERRCODE	76
ISR_NOERRCODE	77
ISR_NOERRCODE	78
ISR_NOERRCODE	79
ISR_NOERRCODE	80
ISR_NOERRCODE	81
ISR_NOERRCODE	82
ISR_NOERRCODE	83
ISR_NOERRCODE	84
ISR_NOERRCODE	85
ISR_NOERRCODE	86
ISR_NOERRCODE	87
ISR_NOERRCODE	88
ISR_NOERRCODE	89
ISR_NOERRCODE	90
ISR_NOERRCODE	91
ISR_NOERRCODE	92
ISR_NOERRCODE	93
ISR_NOERRCODE	94
ISR_NOERRCODE	95
ISR_NOERRCODE	96
ISR_NOERRCODE	97
ISR_NOERRCODE	98
ISR_NOERRCODE	99
ISR_NOERRCODE	100
ISR_NOERRCODE	101
ISR_NOERRCODE	102
ISR_NOERRCODE	103
ISR_NOERRCODE	104
ISR_NOERRCODE	105
ISR_NOERRCODE	106
ISR_NOERRCODE	107
ISR_NOERRCODE	108
ISR_NOERRCODE	109
ISR_NOERRCODE	110
ISR_NOERRCODE	111
ISR_NOERRCODE	112
ISR_NOERRCODE	113
ISR_NOERRCODE	114
ISR_NOERRCODE	115
ISR_NOERRCODE	116
ISR_NOERRCODE	117
ISR_NOERRCODE	118
ISR_NOERRCODE	119
ISR_NOERRCODE	120
ISR_NOERRCODE	121
ISR_NOERRCODE	122
ISR_NOERRCODE	123
ISR_NOERRCODE	124
ISR_NOERRCODE	125
ISR_NOERRCODE	126
ISR_NOERRCODE	127
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
IRQ_ENTRY 1, 33
IRQ_ENTRY 2, 34
IRQ_ENTRY 3, 35
IRQ_ENTRY 4, 36
IRQ_ENTRY 5, 37
IRQ_ENTRY 6, 38
IRQ_ENTRY 7, 39
IRQ_ENTRY 8, 40
IRQ_ENTRY 9, 41
IRQ_ENTRY 10, 42
IRQ_ENTRY 11, 43
IRQ_ENTRY 12, 44
IRQ_ENTRY 13, 45
IRQ_ENTRY 14, 46
IRQ_ENTRY 15, 47


.global syscall
syscall:
	pop %eax
	int $128
	ret

.global get_ss
get_ss:
	mov %ss, %eax
	ret
