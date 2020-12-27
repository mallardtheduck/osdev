#ifndef KERNEL_SCHEDULER_IMPL_THREAD_HPP
#define KERNEL_SCHEDULER_IMPL_THREAD_HPP

#include "../../kernel.hpp"

class Thread : public IThread{
private:
	friend class Scheduler;

	uint64_t id = 0;
	uint64_t pid = 0;
	ThreadStatus status = ThreadStatus::Runnable;

	uint64_t stackToken = 0;
	void *stackPointer;
	void *stackBase;
	size_t stackPages;

	ThreadEntryFunction start = nullptr;

	uint32_t staticPriority;
	uint32_t dynamicPriority;
	uint32_t loadModifier;
	
	BlockCheckFunction blockCheck = nullptr;
	void *blockCheckParam = nullptr;

	int abortlevel = 0;
    bool userAbort = false;

	Thread *next = nullptr;
	uint32_t scheduleCycle = 0;

	thread_msg_status::Enum msgstatus;
	uint8_t fpu_xmm_data[512];
	uint32_t debug_state[Debug_DRStateSize];

	Thread(ThreadEntryFunction fn, void *param, size_t stackSize);
	Thread();
public:
	void Yield(IThread *to) override;
	void YieldIfPending() override;
	uint64_t ID() override;
	void Block() override;
	void Unblock() override;
	void SetPriority(uint32_t p) override;
	void SetPID(uint64_t pid) override;
	void SetBlock(BlockCheckFunction fn, void *param, IThread *to) override;
	void ClearBlock() override;
	void Join(IThread *j) override;
	void SetAbortable(bool a) override;
	int GetAbortLevel() override;
	void Abort() override;
	bool ShouldAbortAtUserBoundary() override;
	void UpdateUserState(ICPUState &state) override;
	ICPUState GetUserState() override;

	void SetMessagingStatus(thread_msg_status::Enum v) override;
	thread_msg_status::Enum GetMessagingStatus() override;

	void SetStatus(ThreadStatus s) override;
	ThreadStatus GetStatus() override;
};

#endif