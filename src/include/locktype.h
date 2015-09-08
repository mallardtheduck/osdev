#ifndef _LOCKTYPE_H
#define _LOCKTYPE_H

#if !defined(KERNEL) && !defined(KERNEL_MODULE)
#error This file is for kernel use only.
#endif

struct lock{
#ifdef __cplusplus
private:
#endif
    volatile uint64_t lockval;
    uint32_t count;
	bool waiting;
#if defined(__cplusplus) && defined(KERNEL)
    friend void init_lock(lock &l);
    friend uint64_t get_lock_owner(lock &l);
    friend void lock_transfer(lock &l, uint64_t to, uint64_t from);
    friend void take_lock_exclusive(lock &l, uint64_t thread);
    friend void take_lock_recursive(lock &l, uint64_t thread);
    friend bool try_take_lock_exclusive(lock &l, uint64_t thread);
    friend void release_lock(lock &l, uint64_t thread);
    friend bool lock_blockcheck(void *p);
#endif
};

#ifndef __cplusplus
typedef struct lock lock;
#endif

#endif