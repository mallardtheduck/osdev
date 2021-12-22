.extern sch_inited
.extern sch_stack

.extern sch_update_eip
.extern sch_isr_c

.global sch_yield
.global sch_isr_asm

sch_isr_asm:
	pusha
	call sch_isr_c
	popa
	iret

sch_yield:
	pusha
	mov $0x0, %eax
	mov sch_inited, %ebx
	cmp %eax, %ebx
	jne 1f
	popa
	ret
1:
	call sch_dolock
	cmp $0x0, %eax
	jne 2f
	popa
	ret
2:
	mov 32(%esp), %eax
	push %eax
	call sch_update_eip
	pop %eax
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
	call sch_switchstack
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa
	ret

sch_switchstack:
	mov %ss, %eax
	mov %esp, %ebx
	mov $0x10, %cx
	movw %cx, %ss
	mov sch_stack, %esp
	push %ebx
	push %eax
	// Call C++ scheduler
	call sch_schedule
	pop %edx
	pop %edx
	mov (%eax), %ebx
	mov %ebx, %ss
	mov 4(%eax), %ebx
	mov %ebx, %esp
	call sch_unlock
	ret
