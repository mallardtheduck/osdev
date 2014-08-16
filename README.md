osdev
=====

This repository contains my operating system, "BT/OS". A 32-bit pre-emtive multitasking/multithreading OS for Intel-compatible i686 (and possibly i586) processors.
It's not a UNIX-like system, but has some UNIX-like concepts (e.g. there is an equivelent of '/dev' and devices are accessed like files, but no a single-rooted filesystem, fork() call, etc.).

Building should be fairly simple, as long as it's cloned to ~/Projects/os, running setup-toolchain.sh will setup the compiler/linker/assembler/c-library, etc. Then "make" can build the OS. "make test" will run it in QEMU.
