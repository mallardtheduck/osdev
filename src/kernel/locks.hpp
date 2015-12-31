#ifndef _LOCKS_HPP
#define _LOCKS_HPP

#include "kernel.hpp"
#include <module/locktype.h>

bool lock_blockcheck(void *p);

void init_lock(lock &l);
uint64_t get_lock_owner(lock &l);
void take_lock_exclusive(lock &l, uint64_t thread = sch_get_id());
void take_lock_recursive(lock &l, uint64_t thread = sch_get_id());
bool try_take_lock_exclusive(lock &l, uint64_t thread = sch_get_id());
bool try_take_lock_recursive(lock &l, uint64_t thread = sch_get_id());
void release_lock(lock &l, uint64_t thread=sch_get_id());
void lock_transfer(lock &l, uint64_t to, uint64_t from = sch_get_id());
uint64_t get_lock_owner(lock &l);

class hold_lock{
private:
	lock *l;

public:
	hold_lock(lock &lck, bool exclusive=true): l(&lck) {
        if(exclusive) take_lock_exclusive(*l);
        else take_lock_recursive(*l);
    }
	~hold_lock() { release_lock(*l);}
};

template<typename T> T atomic_increment(T& var){
	return __sync_add_and_fetch(&var, 1);
}

template<typename T> T atomic_decrement(T& var){
	return __sync_sub_and_fetch(&var, 1);
}

#endif
