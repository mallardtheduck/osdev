#include "locks.hpp"

extern lock sch_lock;

bool lock_blockcheck(void *p){
	return !((lock*)p)->lockval;
}

void init_lock(lock &l){
    l.lockval=0;
    l.count=0;
}

uint64_t get_lock_owner(lock &l){
    return l.lockval;
}

void lock_transfer(lock &l, uint64_t to, uint64_t from){
    if(l.lockval!=from) panic("(LOCK) Attempt to transfer unowned lock!");
    l.lockval=to;
}

void take_lock_exclusive(lock &l, uint64_t thread){
    if(!sch_active()) return;
    if(l.lockval==thread && thread!=0) panic("(LOCK) Attempt to take lock that's already held!\n");
    if(thread==0) panic("(LOCK) Attempt to lock thread to invalid thread ID.");
    while(!__sync_bool_compare_and_swap(&l.lockval, 0, thread)){
        if(&l!=&sch_lock && sch_lock.lockval!=thread) sch_setblock(&lock_blockcheck, (void*)&l.lockval);
    }
    if(l.count != 0) panic("(LOCK) Newly acquired lock with non-zero count!");
    l.count++;
}

void take_lock_recursive(lock &l, uint64_t thread){
    if(!sch_active()) return;
    if(l.lockval==thread && thread!=0){
        l.count++;
        return;
    }
    if(thread==0) panic("(LOCK) Attempt to lock thread to invalid thread ID.");
    while(!__sync_bool_compare_and_swap(&l.lockval, 0, thread)){
        if(&l!=&sch_lock && sch_lock.lockval!=thread) sch_setblock(&lock_blockcheck, (void*)&l.lockval);
    }
    l.count++;
}

bool try_take_lock_exclusive(lock &l, uint64_t thread){
    if(!sch_active()) return true;
    if(l.lockval==thread && thread!=0) return false;
    bool ret=__sync_bool_compare_and_swap(&l.lockval, 0, thread);
    if(ret && l.count!=0) panic("(LOCK) Newly acquired lock with non-zero count!");
    if(ret) l.count++;
    return ret;
}

void release_lock(lock &l, uint64_t thread){
    if(!sch_active()) return;
    if(l.lockval!=thread) panic("(LOCK) Attempt to release lock that isn't held!\n");
    if(l.count==0) panic("(LOCK) Attempt to release lock with zero count!");
    l.count--;
    if(!l.count) __sync_bool_compare_and_swap(&l.lockval, thread, 0);
}