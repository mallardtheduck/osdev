#ifndef KERNEL_LOCKS_HPP
#define KERNEL_LOCKS_HPP

#include "kernel.hpp"
#include <util/noncopyable.hpp>

class LockLock;

class ILock : private nonmovable{
public:
	virtual void TakeExclusive(bool forUserspace = false) = 0;
	virtual void TakeRecursive() = 0;

	[[nodiscard]] virtual bool TryTakeExclusive() = 0;
	[[nodiscard]] virtual bool TryTakeRecursive() = 0;

	virtual void Release(bool forUserspace = false) = 0;

	virtual uint64_t GetOwningThreadID() = 0;

	virtual bool IsLocked() = 0;

	operator bool(){
		return IsLocked();
	}

	[[nodiscard]] LockLock LockExclusive();
	[[nodiscard]] LockLock LockRecursive();

	virtual ~ILock() {}
};

class LockLock : private noncopyable{
private:
	ILock *theLock;
	bool release = true;
public:
	LockLock(ILock &lock) : theLock(&lock) {};
	LockLock(LockLock &&other) : theLock(other.theLock){
		other.release = false;
	}

	LockLock &operator=(LockLock &&other){
		if(this != &other){
			if(release) theLock->Release();
			theLock = other.theLock;
			other.release = false;
		}
		return *this;
	}

	~LockLock(){
		if(release) theLock->Release();
	}
};

inline LockLock ILock::LockExclusive(){
	TakeExclusive();
	return LockLock(*this);
}

inline LockLock ILock::LockRecursive(){
	TakeRecursive();
	return LockLock(*this);
}

ILock *NewLock();

#endif
