#ifndef KERNEL_LOCKS_HPP
#define KERNEL_LOCKS_HPP

#include "kernel.hpp"

#include <module/kernelsys/locks.hpp>

ILock *NewLock();
ILock *PlaceNewLock(char (&buffer)[LockSize]);

class StaticAllocLock : private nonmovable{
private:
	ILock *lock;
	char buffer[LockSize];
public:
	StaticAllocLock() : lock(PlaceNewLock(buffer)) {}

	ILock &operator*(){
		return *lock;
	}

	ILock *operator->(){
		return lock;
	}

	~StaticAllocLock(){
		lock->~ILock();
	}
};

#endif
