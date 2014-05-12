#ifndef _KERNEL_HPP
#define _KERNEL_HPP

#include <stddef.h>
#include <stdint.h>
 
/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#include "console.hpp"
#include "io.hpp"
#include "cpu.hpp"
#include "serdbg.hpp"

#include "fs_interface.hpp"
#include "filesystems.hpp"
#include "initfs/initfs.hpp"

extern "C"{

#include "multiboot.h"
#define PRINTF_LONG_SUPPORT
#include "printf.h"
#include "liballoc.h"

}

#include "util.hpp"
#include "mm.hpp"
#include "idt.hpp"
#include "pic.hpp"
#include "scheduler.hpp"
#include "drivermgr.hpp"
#include "devfs.hpp"

void GDT_init();
void IDT_init();

#define KERNEL_VERSION_MAJOR 0
#define KERNEL_VERSION_MINOR 0
#define KERNEL_VERSION_STRING "v0.0"
#define KERNEL_OS_NAME "BT/OS"
#define KERNEL_COPYRIGHT "(c) 2014 Stuart Brockman"

#endif
