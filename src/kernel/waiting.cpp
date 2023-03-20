#include "kernel.hpp"

struct WaitList{
	vector<IHandle*> handles;
	size_t index = 0;
	
	WaitList(vector<IHandle*> hs) : handles(hs) {}
};

static void delete_waitlist(WaitList *wl){
	for(auto h : wl->handles){
		RemoveHandleDependencyOn(h);
	}
	delete wl;
};

static bool wait_any_waiter(WaitList *lst){
	for(size_t i = 0; i < lst->handles.size(); ++i){
		auto chk = HandleDependencyCheck(lst->handles[i]);
		if(chk == HandleDependencyCheckResult::Present){
			if(lst->handles[i]->Wait()){
				lst->index = i;
				return true;	
			}
		}
	}
	return false;
};


static bool wait_all_waiter(WaitList *lst){
	for(size_t i = 0; i < lst->handles.size(); ++i){
		auto chk = HandleDependencyCheck(lst->handles[i]);
		if(chk == HandleDependencyCheckResult::Present){
			if(!lst->handles[i]->Wait()){
				lst->index = i;
				return false;
			}
		}else if(chk == HandleDependencyCheckResult::NotAvailable) return false;
	}
	return true;
};

KernelHandles::Wait::handleType *MakeWaitAnyHandle(vector<IHandle*> handles){
	auto wl = new WaitList{handles};
	for(auto h : handles) AddHandleDependencyOn(h);
	return MakeKernelGenericHandle<KernelHandles::Wait>(wl, &delete_waitlist, &wait_any_waiter);
}

KernelHandles::Wait::handleType *MakeWaitAllHandle(vector<IHandle*> handles){
	auto wl = new WaitList{handles};
	for(auto h : handles) AddHandleDependencyOn(h);
	return MakeKernelGenericHandle<KernelHandles::Wait>(wl, &delete_waitlist, &wait_all_waiter);
}

size_t GetWaitIndex(KernelHandles::Wait::handleType *h){
	return h->GetData()->index;
}
