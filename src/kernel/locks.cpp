#include "locks.hpp"

extern lock sch_lock;

bool lock_blockcheck(void *p){
	return !((lock*)p)->lock;
}

void init_lock(lock &l){
    l.lock=0;
    l.count=0;
}

void take_lock_exclusive(lock &l, uint64_t thread){
    if(!sch_active()) return;
    if(l.lock==thread && thread!=0) panic("(LOCK) Attempt to take lock that's already held!\n");
    while(!__sync_bool_compare_and_swap(&l.lock, 0, thread)){
        if(&l!=&sch_lock && sch_lock.lock!=thread) sch_setblock(&lock_blockcheck, (void*)&l.lock);
    }
    if(l.count != 0) panic("(LOCK) Newly acquired lock with non-zero count!");
    l.count++;
}

void take_lock_recursive(lock &l, uint64_t thread){
    if(!sch_active()) return;
    if(l.lock==thread && thread!=0){
        l.count++;
        return;
    }
    while(!__sync_bool_compare_and_swap(&l.lock, 0, thread)){
        if(&l!=&sch_lock && sch_lock.lock!=thread) sch_setblock(&lock_blockcheck, (void*)&l.lock);
    }
    l.count++;
}

bool try_take_lock_exclusive(lock &l, uint64_t thread){
    if(!sch_active()) return true;
    if(l.lock==thread && thread!=0) return false;
    bool ret=__sync_bool_compare_and_swap(&l.lock, 0, thread);
    if(ret && l.count!=0) panic("(LOCK) Newly acquired lock with non-zero count!");
    if(ret) l.count++;
    return ret;
}

void release_lock(lock &l, uint64_t thread){
    if(!sch_active()) return;
    if(l.lock!=thread) panic("(LOCK) Attempt to release lock that isn't held!\n");
    if(l.count==0) panic("(LOCK) Attempt to release lock with zero count!");
    l.count--;
    if(!l.count) __sync_bool_compare_and_swap(&l.lock, thread, 0);
}