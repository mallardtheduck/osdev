.global _start
.extern main
.extern exit
_start:
call _init_signal
call main
call exit
.wait: hlt
jmp .wait
