#ifndef KERNEL_LOCKS_HPP
#define KERNEL_LOCKS_HPP

#include "kernel.hpp"

#include <module/kernelsys/locks.hpp>

constexpr size_t LockSize = 32;

ILock *NewLock();
ILock *PlaceNewLock(char (&buffer)[LockSize]);

class StaticAllocLock : private nonmovable{
private:
	ILock *lock;
	char buffer[LockSize];
public:
	void Init(){
		lock = PlaceNewLock(buffer);
	}

	ILock &operator*(){
		return *lock;
	}

	ILock *operator->(){
		return lock;
	}

	~StaticAllocLock(){
		lock->~ILock();
	}

	ILock *get(){
		return lock;
	}
};

#endif
