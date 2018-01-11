BT/OS
=====

This repository contains my operating system, "BT/OS". A 32-bit pre-emtive multitasking/multithreading OS for Intel-compatible i686 (and possibly i586) processors.
It's not a UNIX-like system, but has some UNIX-like concepts (e.g. there is an equivelent of '/dev' and devices are accessed like files, but no single-rooted filesystem, fork() call, etc.).

Building should be fairly simple, as long as it's cloned to ~/Projects/os, running setup-toolchain.sh will setup the compiler/linker/assembler/c-library, etc. Then "make" can build the OS. "make test" will run it in QEMU.

Unless otherwise indicated in the file itself, all files are GPLv2 licenced, with the following exceptions:

* Files under "src/include" are released as public domain or Creative Commons CC0 1.0 Universal at your option.

* Binary outputs produced from the "src/user/libs" tree with the file extension ".ell" are shared libraries. The following licence exception applies to those files specifically (and no others):

> Linking this library dynamically with other modules is making a combined work based on this library. Thus, the terms and conditions of the GNU General Public License cover the whole combination.

> As a special exception, the copyright holders of this library give you permission to link this library with independent modules to produce an executable, regardless of the license terms of these independent modules, and to copy and distribute the resulting executable under terms of your choice, provided that you also meet, for each linked independent module, the terms and conditions of the license of that module. An independent module is a module which is not derived from or based on this library. If you modify this library, you may extend this exception to your version of the library, but you are not obliged to do so. If you do not wish to do so, delete this exception statement from your version.

Please note that this exception covers only dynamic linking. Static linking is only permitted under the terms of the GPL.
