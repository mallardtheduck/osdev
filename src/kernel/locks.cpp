#include "locks.hpp"

static void RaiseUserLockingError(){
	debug_event_notify(proc_current_pid, CurrentThread().ID(), bt_debug_event::Exception, bt_exception::BadLocking);
	proc_terminate();
}

class Lock : public ILock{
	volatile uint64_t owningThreadID = 0;
	uint32_t recursionCount = 0;
	bool waiting = false;

	static bool BlockCheck(void *p){
		Lock *thisLock = (Lock*)p;
		thisLock->waiting = true;
		return thisLock->owningThreadID == 0;
	}
public:
	void TakeExclusive(bool forUserspace = false) override{
		if(!Scheduler_Ready()) return;
		auto currentThreadID = CurrentThread().ID();
		if(owningThreadID != 0 && owningThreadID == currentThreadID){
			if(forUserspace) RaiseUserLockingError();
			else panic("(LOCK) Attempt to take lock that's already held!");
		}
		while(owningThreadID != currentThreadID) {
			while (!__sync_bool_compare_and_swap(&owningThreadID, 0, currentThreadID)) {
				CurrentThread().SetBlock(&BlockCheck, (void*)this);
			}
		}
		waiting = false;
		if(recursionCount != 0) panic("(LOCK) Newly acquired lock with non-zero recursionCount!");
		++recursionCount;
		CurrentThread().SetAbortable(false);
	}

	void TakeRecursive() override{
		if(!Scheduler_Ready()) return;
		auto currentThreadID = CurrentThread().ID();
		if(owningThreadID == currentThreadID) ++recursionCount;
		else TakeExclusive(false);
	}

	bool TryTakeExclusive() override{
		if(!Scheduler_Ready()) return;
		auto currentThreadID = CurrentThread().ID();
		if(owningThreadID != 0 && owningThreadID == currentThreadID) return false;
		if(!__sync_bool_compare_and_swap(&owningThreadID, 0, currentThreadID)) return false;
		waiting = false;
		if(recursionCount != 0) panic("(LOCK) Newly acquired lock with non-zero recursionCount!");
		++recursionCount;
		CurrentThread().SetAbortable(false);
		return true;
	}

	bool TryTakeRecursive() override{
		if(!Scheduler_Ready()) return;
		auto currentThreadID = CurrentThread().ID();
		if(owningThreadID == currentThreadID){
			++recursionCount;
			return true;
		}
		else return TryTakeExclusive();
	}

	void Release(bool forUserspace = false) override{
		if(!Scheduler_Ready()) return;
		auto currentThreadID = CurrentThread().ID();
		if(owningThreadID != currentThreadID){
			if(forUserspace) RaiseUserLockingError();
			else panic("(LOCK) Attempt to release lock that isn't held!\n");
		}
		--recursionCount;
		if(recursionCount == 0){
			__sync_bool_compare_and_swap(&owningThreadID, currentThreadID, 0);
			if(waiting) CurrentThread().Yield();
			CurrentThread().YieldIfPending();
		}
	}

	uint64_t GetOwningThreadID() override{
		return owningThreadID;
	}

	virtual bool IsLocked(){
		return owningThreadID != 0;
	}
};

ILock *NewLock(){
	return new Lock();
}