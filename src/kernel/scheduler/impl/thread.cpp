#include "../../kernel.hpp"
#include "thread.hpp"
#include "scheduler.hpp"

extern Scheduler *theScheduler;

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
	intptr_t stackAddr = (intptr_t)stackPointer;

	stackAddr += MM2::MM2_Page_Size;
	stackAddr += stackSize;
	stackAddr -= sizeof(void*);
	*(intptr_t*)stackAddr = (intptr_t)&ThreadWrapper;
	stackBase = (void*)stackAddr;
	stackToken = GetHAL().GenerateStackToken(stackAddr);

	abortlevel = 2;
	memcpy(fpuState, GetHAL().GetDefaultFPUState(), 512);
}

Thread::Thread(){
	memcpy(fpuState, GetHAL().GetDefaultFPUState(), 512);
}

Thread::~Thread(){
	if(userState) delete userState;
}

void Thread::End(){
	status = ThreadStatus::Ending;
	theScheduler->reaperThread->Unblock();
	Yield(nullptr);
	panic("(SCH) Running ended thread!");
}

void Thread::Yield(IThread */*to*/){
	GetHAL().YieldToScheduler();
}

void Thread::YieldIfPending(){
	GetHAL().YieldToScheduler();
}

uint64_t Thread::ID(){
	return id;
}

void Thread::Block(){
	switch(status){
		case ThreadStatus::Runnable:
			status = ThreadStatus::Blocked;
			break;
		case ThreadStatus::DebugStopped:
			status = ThreadStatus::DebugBlocked;
			break;
		case ThreadStatus::HeldRunnable:
			status = ThreadStatus::HeldBlocked;
			break;
	}
	if(theScheduler->current == this) Yield(nullptr);
}

void Thread::Unblock(){
	switch(status){
		case ThreadStatus::Blocked:
			status = ThreadStatus::Runnable;
			break;
		case ThreadStatus::DebugBlocked:
			status = ThreadStatus::DebugStopped;
			break;
		case ThreadStatus::HeldBlocked:
			status = ThreadStatus::HeldRunnable;
			break;
	}
}

void Thread::SetPriority(uint32_t p){
	staticPriority = p;
}

void Thread::SetPID(uint64_t p){
	pid = p;
}

void Thread::SetBlock(BlockCheckFunction fn, void *param, IThread */*to*/){
	blockCheckParam = param;
	blockCheck = fn;
	Block();
}

void Thread::ClearBlock(){
	Unblock();
	blockCheck = nullptr;
	blockCheckParam = nullptr;
}

void Thread::Join(){

}

void Thread::SetAbortable(bool a){
	if(a && abortlevel > 0) --abortlevel;
	else if(!a) ++abortlevel;
}

int Thread::GetAbortLevel(){
	return abortlevel;
}

void Thread::Abort(){
	if(theScheduler->current == this) panic("(SCH) Thread attempting to abort itself!");
	if(abortlevel == 0){
		status = ThreadStatus::Ending;
		theScheduler->reaperThread->Unblock();
	}
	else userAbort = true;
}

bool Thread::ShouldAbortAtUserBoundary(){
	return userAbort;
}

void Thread::UpdateUserState(ICPUState &state){
	if(userState) delete userState;
	userState = state.Clone();
}

ICPUState &Thread::GetUserState(){
	return *userState;
}

uint32_t *Thread::GetDebugState(){
	return debugState;
}

void Thread::SetMessagingStatus(thread_msg_status::Enum v){
	messagingStatus = v;
}

thread_msg_status::Enum Thread::GetMessagingStatus(){
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
}

void Thread::DecrementRefCount(){
	if(refCount > 0) --refCount;
	else panic("(SCH) Thread refCount inconsistency!");

	if(refCount == 0 && awaitingDestruction){
		theScheduler->reaperThread->Unblock();
	}
}