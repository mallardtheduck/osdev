#ifndef KERNEL_SCHEDULER_IMPL_SCHEDULER_HPP
#define KERNEL_SCHEDULER_IMPL_SCHEDULER_HPP

class Scheduler : public IScheduler{
private:
	friend class Thread;
	friend void Scheduler_Init();
	
	static void TheIdleThread(void*);
	static void TheReaperThread(void*);

	vector<Thread*> threads;
	volatile Thread *current = nullptr;
	uint64_t idCounter = 0;
	uint32_t scheduleCyle = 0;

	lock lock;

	Thread *idleThread;
	Thread *reaperThread;

	Scheduler();

	Thread *PlanCycle();
public:
	IThread &NewThread(ThreadEntryFunction fn, void *param, size_t stackSize) override;

	IThread &CurrentThread() override;
	IThread *GetByID(uint64_t id) override;
	size_t GetPIDThreadCount(uint64_t pid) override;

	void DebugStopThreadsByPID(uint64_t pid) override;
	void DebugResumeThreadsByPID(uint64_t pid) override;
	void HoldThreadsByPID(uint64_t pid) override;
	void UnHoldThreadsByPID(uint64_t pid) override;
	
	bool IsActive() override;
	bool CanLock() override;

	uint64_t Schedule(uint64_t stackToken) override;
};

#endif