#include "../kernel.hpp"

namespace StaticAllocInitPolicies::Private{
	void TakeLock(ILock *lock){
		lock->TakeExclusive();
	}

	void ReleaseLock(ILock *lock){
		lock->Release();
	}
}