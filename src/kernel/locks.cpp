#include "locks.hpp"

extern lock sch_lock;

static void lock_raise_us_error(){
    debug_event_notify(proc_current_pid, sch_get_id(), bt_debug_event::Exception, bt_exception::BadLocking);
    proc_terminate();
}

bool lock_blockcheck(void *p){
	lock *l = (lock*)p;
	l->waiting = true;
	return !l->lockval;
}

void init_lock(lock &l){
    l.lockval=0;
    l.count=0;
	l.waiting=false;
}

uint64_t get_lock_owner(lock &l){
    return l.lockval;
}

void lock_transfer(lock &l, uint64_t to, uint64_t from){
    if(l.lockval!=from) panic("(LOCK) Attempt to transfer unowned lock!");
	if(&l != &sch_lock) sch_abortable(true, from);
    l.lockval=to;
	if(&l != &sch_lock) sch_abortable(false, to);
    if(l.lockval==0) panic("(LOCK) Something bad happened!");
}

void take_lock_exclusive(lock &l, uint64_t thread, bool us){
    if(!sch_active()) return;
    if(l.lockval==thread && thread!=0){
        if(us) lock_raise_us_error();
        else panic("(LOCK) Attempt to take lock that's already held!\n");
    }
    if(thread==0) panic("(LOCK) Attempt to lock thread to invalid thread ID.");
    while(l.lockval != thread) {
        while (!__sync_bool_compare_and_swap(&l.lockval, 0, thread)) {
            if (&l != &sch_lock && sch_lock.lockval != thread) sch_setblock(&lock_blockcheck, (void*)&l, l.lockval);
            else panic("(LOCK) Deadlock - waiting for lock while holding scheduler lock!");
        }
    }
	l.waiting=false;
    if(l.count != 0) panic("(LOCK) Newly acquired lock with non-zero count!");
    l.count++;
    if(l.lockval==0) panic("(LOCK) Lock value not set!");
	if(&l != &sch_lock) sch_abortable(false);
}

void take_lock_recursive(lock &l, uint64_t thread){
    if(!sch_active()) return;
    if(l.lockval==thread && thread!=0){
		if(&l != &sch_lock) sch_abortable(false);
        l.count++;
        return;
    }
    if(thread==0) panic("(LOCK) Attempt to lock thread to invalid thread ID.");
    while(l.lockval != thread) {
        while (!__sync_bool_compare_and_swap(&l.lockval, 0, thread)) {
            if (&l != &sch_lock && sch_lock.lockval != thread) sch_setblock(&lock_blockcheck, (void*)&l, l.lockval);
            else panic("(LOCK) Deadlock - waiting for lock while holding scheduler lock!");
        }
    }
	l.waiting=false;
    l.count++;
    if(l.lockval==0) panic("(LOCK) Lock value not set!");
	if(&l != &sch_lock) sch_abortable(false);
}

bool try_take_lock_exclusive(lock &l, uint64_t thread){
    if(!sch_active()) return true;
    if(l.lockval==thread && thread!=0) return false;
    bool ret=__sync_bool_compare_and_swap(&l.lockval, 0, thread);
    if(ret) {
        if (l.count != 0) panic("(LOCK) Newly acquired lock with non-zero count!");
        l.count++;
		if(&l != &sch_lock) sch_abortable(false);
    }
    if(l.lockval==0) panic("(LOCK) Lock value not set!");
    return ret;
}

bool try_take_lock_recursive(lock &l, uint64_t thread){
    if(!sch_active()) return true;
	if(l.lockval==thread && thread!=0){
        l.count++;
		if(&l != &sch_lock) sch_abortable(false);
        return true;
    }
    bool ret=__sync_bool_compare_and_swap(&l.lockval, 0, thread);
    if(ret) {
        if (l.count != 0) panic("(LOCK) Newly acquired lock with non-zero count!");
        l.count++;
		if(&l != &sch_lock) sch_abortable(false);
    }
    if(l.lockval==0) panic("(LOCK) Lock value not set!");
    return ret;
}

void release_lock(lock &l, uint64_t thread, bool us){
    if(!sch_active()) return;
    if(l.lockval!=thread){
		dbgpf("LOCK: %i != %i\n", (int)l.lockval, (int)thread);
		if(us) lock_raise_us_error();
		else panic("(LOCK) Attempt to release lock that isn't held!\n");
	}
    if(l.count==0) panic("(LOCK) Attempt to release lock with zero count!");
    l.count--;
    if(!l.count) {
		bool waiters = l.waiting;
		{
			interrupt_lock il;
			__sync_bool_compare_and_swap(&l.lockval, thread, 0);
			if (l.lockval != 0) panic("(LOCK) Lock value still set!");
		}
		if(waiters) sch_yield();
    }
	if(&l != &sch_lock) sch_abortable(true);
    sch_deferred_yield();
}
