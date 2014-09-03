.extern sch_inited
.extern sch_stack
.extern sch_new_stack
.extern sch_update_eip

.global sch_yield
sch_yield:
	pusha
	mov 32(%esp), %eax
	push %eax
	call sch_update_eip
	pop %eax
	mov $0x0, %eax
	mov sch_inited, %ebx
	cmp %eax, %ebx
	jne inited
	popa
	ret
inited:
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
	// Call C++ scheduler
	call sch_switchstack
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa
	ret

sch_switchstack:
	call sch_dolock
	cmp $0x0, %eax
	jne lock_ok
	ret
lock_ok:
	mov %ss, %eax
	mov %esp, %ebx
	mov $0x10, %cx
	movw %cx, %ss
	mov sch_stack, %esp
	push %ebx
	push %eax
	call sch_schedule
	pop %eax
	pop %ebx
	mov $curstack, %eax
	mov (%eax), %ebx
	mov %ebx, %ss
	mov 4(%eax), %ebx
	mov %ebx, %esp
	call sch_unlock
	ret
