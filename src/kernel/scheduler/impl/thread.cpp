#include "../../kernel.hpp"
#include "thread.hpp"
#include "scheduler.hpp"

void Thread::ThreadWrapper(){
	Thread *myThread = theScheduler->current;

	ThreadEntryFunction startFunction = myThread->startFunction;
	void *startParam = myThread->startParam;

	startFunction(startParam);

	myThread->End();
}

Thread::Thread(ThreadEntryFunction fn, void *param, size_t stackSize){
	startFunction = fn;
	startParam = param;

	stackPages = stackSize / MM2::MM2_Page_Size;
	if(stackPages * MM2::MM2_Page_Size < stackSize) ++stackPages;
	stackPointer = mm2_virtual_alloc(stackPages + 1);
	mm2_virtual_free(stackPointer, 1);

	MM2::current_pagedir->guard_page_at(stackPointer);
	uintptr_t stackAddr = (uintptr_t)stackPointer;

	stackAddr += MM2::MM2_Page_Size;
	stackAddr += stackSize;
	stackAddr -= sizeof(void*);
	*(uintptr_t*)stackAddr = (uintptr_t)&ThreadWrapper;
	stackBase = (void*)stackAddr;
	stackToken = GetHAL().GenerateStackToken(stackAddr);

	memcpy(fpuState, GetHAL().GetDefaultFPUState(), 512);
}

Thread::Thread(){
	memcpy(fpuState, GetHAL().GetDefaultFPUState(), 512);
}

ThreadStatus Thread::CheckStatus(){
	if(status == ThreadStatus::Blocked && blockCheck){
		if(blockCheck()){
			status = ThreadStatus::Runnable;
			blockCheck = nullptr;
		}
	}
	return status;
}

void Thread::End(){
	if(lockCount != 0) panic("(SCH) Ending thread with non-zero lock count!");
	if(pid) GetProcessManager().SwitchProcess(0);
	status = ThreadStatus::Ending;
	theScheduler->reaperThread->Unblock();
	Yield(theScheduler->reaperThread);
	panic("(SCH) Running ended thread!");
}

void Thread::Yield(IThread */*to*/){
	if(!theScheduler->CanYield()){
		yieldPending = true;
		return;
	}
	if(theScheduler->ShouldYield()) {
		if(status == ThreadStatus::Runnable) theScheduler->yieldSchedule = true;
		GetHAL().YieldToScheduler();
	}
}

void Thread::YieldIfPending(){
	if(!theScheduler->CanYield()) return;
	if(yieldPending){
		if(theScheduler->ShouldYield()) GetHAL().YieldToScheduler();
		yieldPending = false;
	}
}

uint64_t Thread::ID(){
	return id;
}

void Thread::Block(){
	if(theScheduler->idleThread == this) panic("(SCH) Attempt to block idle thread!");
	switch(status){
		case ThreadStatus::Runnable:
			status = ThreadStatus::Blocked;
			break;
		case ThreadStatus::DebugStopped:
			status = ThreadStatus::DebugBlocked;
			break;
		default: break;
	}
	if(theScheduler->current == this){
		if(!theScheduler->CanYield()) panic("(SCH) Attempt to block while holding scheduler lock!");
		Yield(nullptr);
	}
}

bool Thread::AbortableBlock(){
	SetBlock([&]{
		return userAbort;
	}, nullptr);
	return !userAbort;
}

void Thread::Unblock(){
	switch(status){
		case ThreadStatus::Blocked:
			if(blockCheck){
				if(blockCheck()){
					status = ThreadStatus::Runnable;
					blockCheck = nullptr;
				}
			}else{
				status = ThreadStatus::Runnable;
			}
			break;
		case ThreadStatus::DebugBlocked:
			if(!blockCheck)	status = ThreadStatus::DebugStopped;
			break;
		default: break;
	}
}

void Thread::SetPriority(uint32_t p){
	staticPriority = p;
}

void Thread::SetPID(uint64_t p){
	pid = p;
}

uint64_t Thread::GetPID(){
	return pid;
}

void Thread::SetBlock(BlockCheckFunction fn, IThread */*to*/){
	if(theScheduler->idleThread == this) panic("(SCH) Attempt to block idle thread!");
	blockCheck = fn;
	Block();
}

bool Thread::SetAbortableBlock(BlockCheckFunction fn, IThread *to){
	SetBlock([&]{
		return userAbort || fn();
	}, to);
	return !userAbort;
}

void Thread::ClearBlock(){
	blockCheck = nullptr;
	Unblock();
}

void Thread::IncrementLockCount(){
	++lockCount;
	//if(id == 8) dbgpf("%s called from %p on thread %llu (%i)\n", __PRETTY_FUNCTION__,  __builtin_return_address(0), id, lockCount);
}

void Thread::DecrementLockCount(){
	--lockCount;
	//if(id == 8) dbgpf("%s called from %p on thread %llu (%i)\n", __PRETTY_FUNCTION__,  __builtin_return_address(0), id, lockCount);
}

int Thread::GetLockCount(){
	return lockCount;
}

void Thread::Abort(){
	userAbort = true;
}

bool Thread::ShouldAbortAtUserBoundary(){
	return userAbort;
}

void Thread::HoldBeforeUserspace(){
	if(hold) SetBlock([&]{
		return !hold;
	}, nullptr);
}

void Thread::UpdateUserState(const ICPUState &state){
	userState->Copy(state);
}

ICPUState &Thread::GetUserState(){
	return *userState;
}

uint32_t *Thread::GetDebugState(){
	return debugState;
}

void Thread::SetMessagingStatus(btos_api::thread_msg_status::Enum v){
	messagingStatus = v;
}

btos_api::thread_msg_status::Enum Thread::GetMessagingStatus(){
	return messagingStatus;
}

void Thread::SetStatus(ThreadStatus s){
	status = s;
}

ThreadStatus Thread::GetStatus(){
	return status;
}

void Thread::IncrementRefCount(){
	++refCount;
	if(refCount > UINT32_MAX / 2) panic("(SCH) Thread refcount implausible!");
	//dbgpf("SCH: %llu Thread::IncrementRefCount: %lu\n", id, refCount);
}

void Thread::DecrementRefCount(){
	if(refCount > 0) --refCount;
	else panic("(SCH) Thread refCount inconsistency!");

	if(refCount == 0 && awaitingDestruction){
		theScheduler->reaperThread->Unblock();
	}
	if(refCount > UINT32_MAX / 2) panic("(SCH) Thread refcount implausible!");
	//dbgpf("SCH: %llu Thread::DecrementRefCount: %lu\n", id, refCount);
}

uint8_t *Thread::GetFPUState(){
	return fpuState;
}

void Thread::SetDiagnosticInstructionPointer(uintptr_t eip){
	diagnosticInstructionPointer = eip;
}

uintptr_t Thread::GetDiagnosticInstructionPointer(){
	return diagnosticInstructionPointer;
}

const char *Thread::GetName(){
	return name.c_str();
}

void Thread::SetName(const char *n){
	name = n;
}

WeakThreadRef Thread::GetWeakReference(){
	return WeakThreadRef([=]{
		return GetScheduler().GetByID(id);
	});
}