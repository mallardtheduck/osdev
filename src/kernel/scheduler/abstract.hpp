#ifndef KERNEL_SCHEDULER_ABSTRACT_HPP
#define KERNEL_SCHEDULER_ABSTRACT_HPP

#include <module/utils/function.hpp>
#include "../utils/refcountpointer.hpp"

constexpr size_t DefaultStackSize = 16 * 1024;
typedef void(*ThreadEntryFunction)(void*);
typedef function<bool()> BlockCheckFunction;

enum class ThreadStatus{
	Runnable = 0,
	Blocked = 1,
	DebugStopped = 2,
	DebugBlocked = 3,
	Ending = 4,
	Special = 5,
	HeldRunnable = 6,
	HeldBlocked = 7
};

class IThread{
public:
	virtual void Yield(IThread *to = nullptr) = 0;
	virtual void YieldIfPending() = 0;
	virtual uint64_t ID() = 0;
	virtual void Block() = 0;
	virtual void Unblock() = 0;
	virtual void SetPriority(uint32_t p) = 0;
	virtual void SetPID(uint64_t pid) = 0;
	virtual void SetBlock(BlockCheckFunction fn, IThread *to = nullptr) = 0;
	virtual void ClearBlock() = 0;
	virtual void Join() = 0;
	virtual void SetAbortable(bool a) = 0;
	virtual int GetAbortLevel() = 0;
	virtual void Abort() = 0;
	virtual bool ShouldAbortAtUserBoundary() = 0;
	virtual void UpdateUserState(const ICPUState &state) = 0;
	virtual ICPUState &GetUserState() = 0;
	virtual uint32_t *GetDebugState() = 0;

	virtual void SetMessagingStatus(btos_api::thread_msg_status::Enum v) = 0;
	virtual btos_api::thread_msg_status::Enum GetMessagingStatus() = 0;

	virtual void SetStatus(ThreadStatus s) = 0;
	virtual ThreadStatus GetStatus() = 0;

	virtual void IncrementRefCount() = 0;
	virtual void DecrementRefCount() = 0;

	virtual uint8_t *GetFPUState() = 0;

	virtual void SetDiagnosticInstructionPointer(intptr_t eip) = 0;
	virtual intptr_t GetDiagnosticInstructionPointer() = 0; 

	virtual ~IThread() {}
};

typedef RefCountPointer<IThread> ThreadPointer;

class SchedulerLock;

class IScheduler{
private:
	static void FunctionStart(void *fn){
		auto func = (function<void()>*)fn;
		(*func)();
		delete func;
	}
public:
	virtual ThreadPointer NewThread(ThreadEntryFunction fn, void *param, size_t stackSize = DefaultStackSize) = 0;
	ThreadPointer NewThread(const function<void()> &fn, size_t stackSize = DefaultStackSize){
		auto func = new function<void()>(fn);
		return NewThread(&FunctionStart, (void*)func, stackSize);
	}

	virtual IThread &CurrentThread() = 0;
	virtual ThreadPointer GetByID(uint64_t id) = 0;
	virtual size_t GetPIDThreadCount(uint64_t pid) = 0;

	virtual void DebugStopThreadsByPID(uint64_t pid) = 0;
	virtual void DebugResumeThreadsByPID(uint64_t pid) = 0;
	virtual void HoldThreadsByPID(uint64_t pid) = 0;
	virtual void UnHoldThreadsByPID(uint64_t pid) = 0;
	
	virtual bool CanLock() = 0;

	virtual uint64_t Schedule(uint64_t stackToken) = 0;

	virtual void EnableScheduler() = 0;
	virtual bool DisableScheduler() = 0;

	[[nodiscard]] SchedulerLock LockScheduler();

	virtual ~IScheduler() {}
};

void Scheduler_Init();
bool Scheduler_Ready();
IScheduler &GetScheduler();

inline IThread &CurrentThread(){
	return GetScheduler().CurrentThread();
}


class SchedulerLock{
private:
	IScheduler &sch;
	bool enable;
public:
	SchedulerLock(IScheduler &s) : sch(s), enable(true){
		sch.DisableScheduler();
	}

	SchedulerLock(SchedulerLock &&other) : sch(other.sch), enable(true){
		other.enable = false;
	}

	SchedulerLock &operator=(SchedulerLock &&other){
		new (this) SchedulerLock((SchedulerLock &&)other);
		return *this;
	}

	SchedulerLock(const SchedulerLock&) = delete;
	SchedulerLock &operator=(const SchedulerLock&) = delete;

	~SchedulerLock(){
		if(enable)sch.EnableScheduler();
	}
};

inline SchedulerLock IScheduler::LockScheduler(){
	return SchedulerLock(*this);
}

#endif