#include "locks.hpp"

extern lock sch_lock;

bool lock_blockcheck(void *p){
	return !((lock*)p)->lock;
}

void init_lock(lock &l){
    l.lock=0;
    l.count=0;
}

void take_lock(lock &l, uint64_t thread){
    if(!sch_active()) return;
    if(l.lock==thread && thread!=0) panic("(LOCK) Attempt to take lock that's already held!\n");
    while(!__sync_bool_compare_and_swap(&l.lock, 0, thread)){
        if(&l!=&sch_lock && sch_lock.lock!=thread) sch_setblock(&lock_blockcheck, (void*)&l.lock);
    }
}

bool try_take_lock(lock &l, uint64_t thread){
    if(!sch_active()) return true;
    if(l.lock==thread && thread!=0) return false;
    return __sync_bool_compare_and_swap(&l.lock, 0, thread);
}

void release_lock(lock &l, uint64_t thread){
    if(!sch_active()) return;
    if(!__sync_bool_compare_and_swap(&l.lock, thread, 0)){
        panic("(LOCK) Attempt to release lock that isn't held!\n");
    }
}