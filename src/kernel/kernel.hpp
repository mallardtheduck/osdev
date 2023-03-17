#ifndef _KERNEL_HPP
#define _KERNEL_HPP

#include <stddef.h>
#include <stdint.h>

#include <btos/btos_api.h>
 
/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This OS needs to be compiled with a ix86-elf compiler"
#endif

#include "serdbg.hpp"

extern "C"{

#include "multiboot.h"
#define PRINTF_LONG_SUPPORT
#include "printf.h"
#include "liballoc.h"

}

#include "utils/utils.hpp"
#include "locks.hpp"

#include "panic.hpp"
#include "mm2.hpp"
#include "hal/abstract.hpp"
#include "scheduler/abstract.hpp"
#include "handles.hpp"
#include "kvars.hpp"
#include "filesystems.hpp"
#include "initfs.hpp"
#include "processes/abstract.hpp"
#include "messaging.hpp"
#include "devices.hpp"
#include "devfs.hpp"
#include "load_elf.hpp"
#include "extensions.hpp"
#include "module.hpp"
#include "syscalls.hpp"
#include "modules.hpp"
#include "user_api.hpp"
#include "infofs.hpp"
#include "debug_ext.hpp"
#include "atoms.hpp"
#include "hwpnp_kernel.hpp"
#include "rtc/rtc.hpp"
#include "waiting.hpp"
#include "perms.hpp"

void GDT_init();
void IDT_init();
void gdt_set_kernel_stack(void* ptr);

#define MACRO_XSTR(a) MACRO_STR(a)
#define MACRO_STR(a) #a

#define KERNEL_VERSION_MAJOR 0
#define KERNEL_VERSION_MINOR 2
#define KERNEL_REVISION "A"
#define KERNEL_VERSION_STRING "v" MACRO_XSTR(KERNEL_VERSION_MAJOR) "." MACRO_XSTR(KERNEL_VERSION_MINOR) KERNEL_REVISION
#define KERNEL_OS_NAME "BT/OS"
#define KERNEL_COPYRIGHT "(c) 2014-2023 S. Brockman"
extern char *kernel_buildid;

extern multiboot_info_t *mbt;

#endif
