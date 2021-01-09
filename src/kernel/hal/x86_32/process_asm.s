.global proc_run_usermode
proc_run_usermode:
	cli
	movl $0x23, %eax
	movl %eax, %ds
	movl %eax, %es
	movl %eax, %fs
	movl %eax, %gs

	popl %eax
	popl %eax
	popl %ebx
	pushl $0x23
	pushl %eax
	pushf
	orl $0x200, (%esp)
	pushl $0x1B
	pushl %ebx
	iret
