.global proc_run_usermode
proc_run_usermode:
	movl $0x23, %eax
	movl %eax, %ds
	movl %eax, %es
	movl %eax, %fs
	movl %eax, %gs

	popl %eax
	popl %eax
	popl %ebx
	popl %ecx
	popl %edx
	pushl $0x23
	pushl %eax
	pushf
	pushl $0x1B
	pushl %ebx
	iret
