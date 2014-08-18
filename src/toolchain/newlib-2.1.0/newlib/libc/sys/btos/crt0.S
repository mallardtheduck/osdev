.global _start
.extern main
.extern exit
.extern get_argc
.extern get_argv
_start:
#call _init_signal
call get_argv
push %eax
call get_argc
push %eax
call main
#call exit
mov $0x0805, %eax
int $0x80
.wait:
jmp .wait
