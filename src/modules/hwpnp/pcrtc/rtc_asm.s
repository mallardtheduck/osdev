.extern tick_counter
.extern update_msec_counter
.extern resync_flag
.global rtc_irq_handler

rtc_irq_handler:
	push %eax
	push %ebx
	push %ecx
	mov $0x0C, %eax
	outb %al, $0x70
	inb $0x71, %al
	mov %eax, %ecx
	and $0x40, %al
	jz 2f
	mov tick_counter, %ebx
	cmp $0xFFFFFFFF, %ebx
	jne 1f
	pusha
	call update_msec_counter
	popa
	mov $0, %ebx
1:
	inc %ebx
	mov %ebx, tick_counter
2:
	mov %ecx, %eax
	and $0x10, %al
	jz 3f
	mov resync_flag, %eax
	cmp $1, %eax
	jne 3f
	pusha
	call resync_clock
	popa
3:
	mov $0x20, %al
	outb %al, $0xA0
	outb %al, $0x20
	pop %ecx
	pop %ebx
	pop %eax
	iret
