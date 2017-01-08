.section .init
.global  _init
_init:
	push %ebp

.section .fini
.global  _fini
_fini:
	push %ebp

.section .data
    .global __dso_handle
    .weak   __dso_handle
    .hidden __dso_handle
__dso_handle:
	.long	0