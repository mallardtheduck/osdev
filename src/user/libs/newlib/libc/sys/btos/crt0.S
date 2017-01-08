.global _start
.extern main
.extern exit
.extern get_argc
.extern get_argv
.extern _init
.extern _fini
.extern btos_open_std_streams
_start:
call btos_open_std_streams
call _init
call get_argv
push %eax
call get_argc
push %eax
call main
push %eax
call _fini
pop %ebx
mov $0x0805, %eax
int $0x80
.wait:
jmp .wait

.section .data
    .global ___dso_handle
    .weak   ___dso_handle
___dso_handle:
	.long	0