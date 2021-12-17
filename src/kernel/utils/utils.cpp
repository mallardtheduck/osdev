#include "../kernel.hpp"

namespace StaticAllocInitPolicies{
	StaticAllocLock initLock;
}

void Utils_Init(){
	StaticAllocInitPolicies::initLock.Init();
}

namespace StaticAllocInitPolicies::Private{
	void TakeLock(ILock *lock){
		lock->TakeExclusive();
	}

	void ReleaseLock(ILock *lock){
		lock->Release();
	}
}