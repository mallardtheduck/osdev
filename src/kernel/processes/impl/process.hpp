#ifndef KERNEL_PROCESSES_IMPL_PROCESS_HPP
#define KERNEL_PROCESSES_IMPL_PROCESS_HPP

#include "../../kernel.hpp"

class Process : public IProcess{
private:
	friend class ProcessManager;
	
	bt_pid_t pid;
	bt_pid_t parent;
	string name;
	vector<string> args;
	int returnValue = 0;
	btos_api::bt_proc_status::Enum status = btos_api::bt_proc_status::DoesNotExist;

	map<bt_pid_t, int> childReturns;

	unique_ptr<MM2::PageDirectory> pageDirectory;
	unique_ptr<ILock> lock { NewLock() };

	map<bt_handle_t, IHandle*> handles;
	handle_t handleCounter = 0;
	vector<bt_handle_t> pendingHandleCloses;

	struct EnvironmentVariable{
		string value;
		uint8_t flags;
	};
	map<string, EnvironmentVariable> environment;
	map<uint16_t, uint64_t> permissions;
	uint64_t uid = 0;

	uint64_t currentMessageId;

	uint32_t refCount = 0;

	static Process *CreateKernelProcess();
	static map<string, EnvironmentVariable> CopyEnvironment(const IProcess &parent);
	static uintptr_t AllocateStack(size_t size);

	void GetEnvironmentVariable(const char *name, char *&value, uint8_t &flags);
	void CleanupProcess();
	Process();
public:
	Process(const char *name, const vector<const char*> &args, IProcess &parent);

	bt_pid_t ID() override;
	const char *GetName() override;
	
	void End() override;
	void Terminate() override;
	void HoldBeforeUserspace() override;

	void SetEnvironmentVariable(const char *name, const char *value, uint8_t flags = 0, bool userspace = false)  override;
	const char *GetEnvironmentVariable(const char *name, bool userspace = false) override;

	ThreadPointer NewUserThread(ProcessEntryPoint p, void *param, void *stack) override;

	handle_t AddHandle(IHandle *handle) override;
	IHandle *GetHandle(handle_t h) override;
	void CloseAndRemoveHandle(handle_t h) override;
	vector<handle_t> GetHandlesByType(uint32_t type) override;
	
	void SetExitCode(int value) override;

	void Wait() override;

	size_t GetArgumentCount() override;
	size_t GetArgument(size_t index, char *buf, size_t size);

	void SetStatus(btos_api::bt_proc_status::Enum status) override;
	btos_api::bt_proc_status::Enum GetStatus() override;

	void SetPermissions(uint16_t extensionID, uint64_t permissions) override;
	uint64_t GetPermissions(uint16_t extensionID) override;
	void SetUserID(uint64_t uid) override;
	uint64_t GetUID() override;

	void SetCurrentMessageID(uint64_t id) override;
	uint64_t GetCurrentMessageID() override;

	void SetReturnValue(int returnValue) override;
	int GetChildReturnValue(bt_pid_t childPid) override;
	void SetChildReturnValue(bt_pid_t childPid, int returnValue) override;

	void IncrementRefCount() override;
	void DecrementRefCount() override;
};

#endif