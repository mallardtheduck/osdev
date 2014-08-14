.global _start
.extern main
.extern exit
_start:
#call _init_signal
call main
#call exit
mov $0x0805, %eax
int $0x80
.wait:
jmp .wait
