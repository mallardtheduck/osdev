#ifndef KERNEL_SCHEDULER_IMPL_THREAD_HPP
#define KERNEL_SCHEDULER_IMPL_THREAD_HPP

#include "../../kernel.hpp"
#include <module/utils/unique_ptr.hpp>

constexpr uint32_t DefaultThreadPriority = 10;

class Thread : public IThread{
private:
	friend class Scheduler;

	static void ThreadWrapper();

	uint64_t id = 0;
	uint64_t pid = 0;
	ThreadStatus status = ThreadStatus::Runnable;

	uint64_t stackToken = 0;
	void *stackPointer = nullptr;
	void *stackBase = nullptr;
	size_t stackPages = 0;

	ThreadEntryFunction startFunction = nullptr;
	void *startParam = nullptr;

	uint32_t staticPriority = DefaultThreadPriority;
	uint32_t dynamicPriority = 0;
	uint32_t loadModifier = 0;
	
	BlockCheckFunction blockCheck = nullptr;

	int abortlevel = 0;
    bool userAbort = false;

	Thread *next = nullptr;
	uint32_t scheduleCycle = 0;

	thread_msg_status::Enum messagingStatus = thread_msg_status::Normal;
	uint8_t fpuState[512];
	uint32_t debugState[Debug_DRStateSize] = {0};
	unique_ptr<ICPUState> userState {GetHAL().GetDefaultCPUState().Clone()};

	uint32_t refCount = 0;
	bool awaitingDestruction = false;

	intptr_t diagnosticInstructionPointer = 0;

	Thread(ThreadEntryFunction fn, void *param, size_t stackSize);
	Thread();

	void End();
public:
	void Yield(IThread *to) override;
	void YieldIfPending() override;
	uint64_t ID() override;
	void Block() override;
	void Unblock() override;
	void SetPriority(uint32_t p) override;
	void SetPID(uint64_t pid) override;
	void SetBlock(BlockCheckFunction fn, IThread *to) override;
	void ClearBlock() override;
	void Join() override;
	void SetAbortable(bool a) override;
	int GetAbortLevel() override;
	void Abort() override;
	bool ShouldAbortAtUserBoundary() override;
	void UpdateUserState(const ICPUState &state) override;
	ICPUState &GetUserState() override;
	uint32_t *GetDebugState() override;

	void SetMessagingStatus(thread_msg_status::Enum v) override;
	thread_msg_status::Enum GetMessagingStatus() override;

	void SetStatus(ThreadStatus s) override;
	ThreadStatus GetStatus() override;

	void IncrementRefCount() override;
	void DecrementRefCount() override;

	uint8_t *GetFPUState() override;

	void SetDiagnosticInstructionPointer(intptr_t eip) override;
	intptr_t GetDiagnosticInstructionPointer() override; 
};

#endif