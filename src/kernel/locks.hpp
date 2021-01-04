#ifndef KERNEL_LOCKS_HPP
#define KERNEL_LOCKS_HPP

#include "kernel.hpp"

class LockLock;

class ILock{
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

class LockLock{
private:
	ILock &theLock;
	bool release = true;
public:
	LockLock(ILock &lock) : theLock(lock) {};
	LockLock(LockLock &&other) : theLock(other.theLock){
		other.release = false;
	}

	LockLock &operator=(LockLock &&other){
		if(this != &other){
			if(release) theLock.Release();
			new (this) LockLock((LockLock &&)other);
		}
		return *this;
	}

	LockLock(const LockLock&) = delete;
	LockLock &operator=(const LockLock&) = delete;

	~LockLock(){
		if(release) theLock.Release();
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
