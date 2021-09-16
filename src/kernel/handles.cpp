#include "kernel.hpp"
#include "locks.hpp"

static OnDemandStaticAlloc<vector<IHandle*>> handlesWithDependencies;
static StaticAllocLock handleDepenciesLock;

void init_handles(){
	handleDepenciesLock.Init();
}

void AddHandleDependencyOn(IHandle *h){
	auto hl = handleDepenciesLock->LockExclusive();
	handlesWithDependencies->push_back(h);
}

void RemoveHandleDependencyOn(IHandle *h){
	auto hl = handleDepenciesLock->LockExclusive();
	auto i = handlesWithDependencies->find(h);
	if(i != handlesWithDependencies->npos){
		handlesWithDependencies->erase(i);
	}
}

HandleDependencyCheckResult HandleDependencyCheck(IHandle *h){
	auto result = HandleDependencyCheckResult::NotAvailable;
	if(handleDepenciesLock->TryTakeExclusive()){
		if(handlesWithDependencies->find(h) != handlesWithDependencies->npos){
			result = HandleDependencyCheckResult::Present;
		}else{
			result = HandleDependencyCheckResult::Absent;
		}
		handleDepenciesLock->Release();
	}
	return result;
}



void WaitOnHandle(IHandle *handle){
	AddHandleDependencyOn(handle);
	CurrentThread().SetBlock([&](){
		if(handle) return handle->Wait();
		else return true;
	});
	RemoveHandleDependencyOn(handle);
}