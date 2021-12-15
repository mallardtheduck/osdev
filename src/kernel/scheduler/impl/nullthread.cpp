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
	void Unblock() override {}
	void SetPriority(uint32_t) override {}
	void SetPID(uint64_t pid) override {}
	void SetBlock(BlockCheckFunction, IThread *) override {}
	void ClearBlock() override {}
	void Join() override {}
	void SetAbortable(bool a) override {}
	int GetAbortLevel() override {return 1;}
	void Abort() override {}
	bool ShouldAbortAtUserBoundary() override {return false;}
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
};

NullThread theNullThread;

IThread &GetNullThread(){
	return theNullThread;
}