#ifndef KERNEL_SCHEDULER_ABSTRACT_HPP
#define KERNEL_SCHEDULER_ABSTRACT_HPP

constexpr size_t DefaultStackSize = 16 * 1024;
typedef void(*ThreadEntryFunction)(void*);
typedef bool (*BlockCheckFunction)(void*);

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
	virtual void SetBlock(BlockCheckFunction fn, void *param, IThread *to = nullptr) = 0;
	virtual void ClearBlock() = 0;
	virtual void Join() = 0;
	virtual void SetAbortable(bool a) = 0;
	virtual int GetAbortLevel() = 0;
	virtual void Abort() = 0;
	virtual bool ShouldAbortAtUserBoundary() = 0;
	virtual void UpdateUserState(ICPUState &state) = 0;
	virtual ICPUState &GetUserState() = 0;
	virtual uint32_t *GetDebugState() = 0;

	virtual void SetMessagingStatus(thread_msg_status::Enum v) = 0;
	virtual thread_msg_status::Enum GetMessagingStatus() = 0;

	virtual void SetStatus(ThreadStatus s) = 0;
	virtual ThreadStatus GetStatus() = 0;

	virtual void IncrementRefCount() = 0;
	virtual void DecrementRefCount() = 0;

	virtual ~IThread() {}
};

class ThreadPointer{
private:
	IThread *theThread;
public:
	ThreadPointer(IThread *ptr) : theThread(ptr){
		theThread->IncrementRefCount();
	}

	ThreadPointer(const ThreadPointer &other) : ThreadPointer(other.theThread) {}

	ThreadPointer(ThreadPointer &&other) : theThread(other.theThread){
		other.theThread = nullptr;
	}

	~ThreadPointer(){
		if(theThread) theThread->DecrementRefCount();
	}

	ThreadPointer &operator=(const ThreadPointer &other){
		if(&other != this){
			if(theThread) theThread->DecrementRefCount();
			theThread = other.theThread;
			if(theThread) theThread->IncrementRefCount();
		}
		return *this;
	}

	ThreadPointer &operator=(ThreadPointer &&other){
		if(&other != this){
			if(theThread) theThread->DecrementRefCount();
			theThread = other.theThread;
			other.theThread = nullptr;
		}
		return *this;
	}

	operator bool(){
		return theThread;
	}

	IThread *operator->(){
		return theThread;
	}
};

class IScheduler{
public:
	virtual ThreadPointer NewThread(ThreadEntryFunction fn, void *param, size_t stackSize = DefaultStackSize) = 0;
	virtual IThread &CurrentThread() = 0;
	virtual ThreadPointer GetByID(uint64_t id) = 0;
	virtual size_t GetPIDThreadCount(uint64_t pid) = 0;

	virtual void DebugStopThreadsByPID(uint64_t pid) = 0;
	virtual void DebugResumeThreadsByPID(uint64_t pid) = 0;
	virtual void HoldThreadsByPID(uint64_t pid) = 0;
	virtual void UnHoldThreadsByPID(uint64_t pid) = 0;
	
	virtual bool IsActive() = 0;
	virtual bool CanLock() = 0;

	virtual uint64_t Schedule(uint64_t stackToken) = 0;

	virtual ~IScheduler() {}
};

void Scheduler_Init();
IScheduler &GetScheduler();

inline IThread &CurrentThread(){
	return GetScheduler().CurrentThread();
}

#endif