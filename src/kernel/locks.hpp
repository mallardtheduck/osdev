#ifndef _LOCKS_HPP
#define _LOCKS_HPP

#include "kernel.hpp"

typedef volatile uint64_t lock;

void init_lock(lock &l);

void take_lock(lock &l, uint64_t thread=sch_get_id());

bool try_take_lock(lock &l, uint64_t thread=sch_get_id());

void release_lock(lock &l, uint64_t thread=sch_get_id());

class hold_lock{
private:
	lock *l;
public:
	hold_lock(lock &lck): l(&lck) {take_lock(*l);}
	~hold_lock() {release_lock(*l);}
};

#endif
