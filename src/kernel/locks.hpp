#ifndef _LOCKS_HPP
#define _LOCKS_HPP

#include "kernel.hpp"


typedef volatile uint64_t lock;
bool lock_blockcheck(void *p);

inline void init_lock(lock &l){
	l=0;
}


inline void take_lock(lock &l, uint64_t thread=sch_get_id()){
	if(!sch_active()) return;
	if(l==thread && thread!=0) panic("(LOCK) Attempt to take lock that's already held!\n");
	while(!__sync_bool_compare_and_swap(&l, 0, thread)){
		sch_setblock(&lock_blockcheck, (void*)&l);
	}
}


inline bool try_take_lock(lock &l, uint64_t thread=sch_get_id()){
	if(!sch_active()) return true;
	return __sync_bool_compare_and_swap(&l, 0, thread);
}


inline void release_lock(lock &l, uint64_t thread=sch_get_id()){
	if(!sch_active()) return;
	if(!__sync_bool_compare_and_swap(&l, thread, 0)){
		panic("(LOCK) Attempt to release lock that isn't held!\n");
	}
}


class hold_lock{
private:
	lock *l;

public:
	hold_lock(lock &lck): l(&lck) {take_lock(*l);}
	~hold_lock() { release_lock(*l);}
};

#endif
