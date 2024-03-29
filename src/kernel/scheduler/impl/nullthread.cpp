#include "../../kernel.hpp"

constexpr uint32_t DefaultThreadPriority = 10;

static uint32_t debugState[Debug_DRStateSize] = {0};
static uint8_t fpuState[512];

class NullThread : public IThread{
private:
public:
	void Yield(IThread *) override {}
	void YieldIfPending() override {}
	uint64_t ID() override {return 0;}
	void Block() override {}
	bool AbortableBlock() override {return true;}
	void Unblock() override {}
	void SetPriority(uint32_t) override {}
	void SetPID(uint64_t pid) override {}
	uint64_t GetPID() override {return 0;}
	void SetBlock(BlockCheckFunction, IThread *) override {}
	bool SetAbortableBlock(BlockCheckFunction, IThread *) override {return true;}
	void ClearBlock() override {}
	void IncrementLockCount() override {}
	void DecrementLockCount() override {}
	int GetLockCount() override {return 0;}
	void Abort() override {}
	void End() override {}
	bool ShouldAbortAtUserBoundary() override {return false;}
	void HoldBeforeUserspace() override {}
	void UpdateUserState(const ICPUState &) override {}
	ICPUState &GetUserState() override { return const_cast<ICPUState&>(GetHAL().GetDefaultCPUState()); }
	uint32_t *GetDebugState() override { return debugState; }

	void SetMessagingStatus(btos_api::thread_msg_status::Enum) override {}
	btos_api::thread_msg_status::Enum GetMessagingStatus() override {return btos_api::thread_msg_status::Normal;}

	void SetStatus(ThreadStatus) override {}
	ThreadStatus GetStatus() override { return ThreadStatus::Runnable; }

	void IncrementRefCount() override {}
	void DecrementRefCount() override {}

	uint8_t *GetFPUState() override {return fpuState;}

	void SetDiagnosticInstructionPointer(uintptr_t) override {}
	uintptr_t GetDiagnosticInstructionPointer() override {return 0;}

	const char *GetName() override {return "NULL";}
	void SetName(const char*) override {}

	virtual WeakThreadRef GetWeakReference(){
		return WeakThreadRef([]{return nullptr;});
	}
};

ManualStaticAlloc<NullThread> theNullThread;

IThread &GetNullThread(){
	panic("GetNullThread!");
	theNullThread.Init();
	return *theNullThread;
}