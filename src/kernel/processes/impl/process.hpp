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

	map<bt_pid_t, int> childReturns;

	unique_ptr<MM2::PageDirectory> pageDirectory;
	unique_ptr<ILock> lock { NewLock() };

	map<bt_handle_t, IHandle*> handles;

	struct EnvironmentVariable{
		string value;
		uint8_t flags;
	};
	map<string, EnvironmentVariable> environment;

	uint32_t refCount = 0;

	static Process *CreateKernelProcess();
	static map<string, EnvironmentVariable> CopyEnvironment(const IProcess &parent);

	void CleanupProcess();
public:
	Process(const char *name, const vector<const char*> &args, IProcess &parent);

	bt_pid_t ID() override;
	const char *GetName() override;
	
	void End() override;
	void Terminate() override;
	void Hold() override;

	void SetEnvironmentVariable(const char *name, const char *value, uint8_t flags = 0, bool userspace = false)  override;
	const char *GetEnvironmentVariable(const char *name, bool userspace = false) override;

	IThread *NewUserThread(ProcessEntryPoint p, void *param, void *stack) override;

	handle_t AddHandle(IHandle *handle) override;
	IHandle *GetHandle(handle_t h) override;
	void RemoveHandle(handle_t h) override;
	
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

	void AddMessage(btos_api::bt_msg_header *msg) override;
	void RemoveMessage(btos_api::bt_msg_header *msg) override;
	btos_api::bt_msg_header *GetMessage(size_t index) override;
	btos_api::bt_msg_header *GetMessageByID(uint64_t id) override;
	btos_api::bt_msg_header *GetMessageMatch(const btos_api::bt_msg_filter &filter) override;
	void SetCurrentMessage(btos_api::bt_msg_header *msg) override;
	btos_api::bt_msg_header *GetCurrentMessage() override;

	void SetReturnValue(int returnValue) override;
	int GetChildReturnValue(bt_pid_t childPid) override;

	void IncrementRefCount() override;
	void DecrementRefCount() override;
};

#endif