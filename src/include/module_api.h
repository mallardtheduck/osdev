#ifndef _MODULE_API_H
#define _MODULE_API_H

#include <stddef.h>

typedef int (*syscall_vector)(int, void*);
extern syscall_vector syscall;

#define SYS_PANIC 	0x00
#define SYS_MALLOC 	0x01
#define SYS_FREE 	0x02
#define SYS_MEMSET	0x03
#define SYS_MEMCPY	0x04
#define SYS_MEMMOVE	0x05
#define SYS_STRCMP	0x06
#define SYS_STRNCPY	0x07
#define SYS_INITLOCK	0x08
#define SYS_TAKELOCK	0x09
#define SYS_TRYLOCK	0x0a
#define SYS_UNLOCK	0x0b
#define SYS_DBGOUT	0x0c

#define SYS_NEWTHREAD	0x10
#define SYS_BLOCK	0x11
#define SYS_YIELD	0x12
#define SYS_THREADID	0x13
#define SYS_PRIORITY	0x14
#define SYS_ENDTHREAD	0x15

#define SYS_ADDDEVICE	0x20
#define SYS_GETDEVICE	0x21
#define SYS_FIRSTDEVICE	0x22
#define SYS_NEXTDEVICE	0x23
#define SYS_DEVOPEN	0x24
#define SYS_DEVCLOSE	0x25
#define SYS_DEVREAD	0x26
#define SYS_DEVWRITE	0x27
#define SYS_DEVSEEK	0x28
#define SYS_DEVIOCTL	0x29
#define SYS_DEVTYPE	0x2a
#define SYS_DEVDESC	0x2b
#define SYS_HANDLEINT	0x2c

#define SYS_ADDFS	0x30
#define SYS_FSMOUNT	0x31
#define SYS_FSUNMOUNT	0x32
#define SYS_FOPEN	0x33
#define SYS_FCLOSE	0x34
#define SYS_FREAD	0x35
#define SYS_FWRITE	0x36
#define SYS_FSEEK	0x37
#define SYS_FIOCTL	0x38
#define SYS_DIROPEN	0x39
#define SYS_DIRCLOSE	0x3a
#define SYS_DIRREAD	0x3b
#define SYS_DIRSEEK	0x3c
#define SYS_FSTAT	0x3d

#define SYS_MODLOAD	0x40
#define SYS_MODUNLOAD	0x41
#define SYS_MODINFO	0x42

#endif
