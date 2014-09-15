#ifndef _LOCKTYPE_H
#define _LOCKTYPE_H

#if !defined(KERNEL) && !defined(KERNEL_MODULE)
#error locktype.hpp should not be included in userspace
#endif

struct lock{
    volatile uint64_t lock;
    uint32_t count;
};

#ifndef __cplusplus
typedef struct lock lock;
#endif

#endif