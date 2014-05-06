#ifndef _LOCKS_HPP
#define _LOCKS_HPP

#include "kernel.hpp"

#define cmpxchg( ptr, _old, _new ) { \
  volatile uint32_t *__ptr = (volatile uint32_t *)(ptr);   \
  uint32_t __ret;                                     \
  asm volatile( "lock; cmpxchgl %2,%1"           \
    : "=a" (__ret), "+m" (*__ptr)                \
    : "r" (_new), "0" (_old)                     \
    : "memory");				 \
  );                                             \
  __ret;                                         \
}

typedef volatile uint64_t lock;

inline void init_lock(lock &l){
	l=0;
}

inline void take_lock(lock &l, uint64_t thread=sch_get_id()){
	while(!__sync_bool_compare_and_swap(&l, 0, thread)) sch_yield();
}

inline bool try_take_lock(lock &l, uint64_t thread=sch_get_id()){
	return __sync_bool_compare_and_swap(&l, 0, thread);
}

inline void release_lock(lock &l, uint64_t thread=sch_get_id()){
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
