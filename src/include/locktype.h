#ifndef _LOCKTYPE_H
#define _LOCKTYPE_H

#if !defined(KERNEL) && !defined(KERNEL_MODULE)
#error This file is for kernel use only.
#endif

struct lock{
    volatile uint64_t lock;
    uint32_t count;
};

#ifndef __cplusplus
typedef struct lock lock;
#endif

#endif