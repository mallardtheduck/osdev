#ifndef KERNEL_PROCESSES_ABSTRACT_HPP
#define KERNEL_PROCESSES_ABSTRACT_HPP

#include "../kernel.hpp"
#include "../utils/string.hpp"
#include "../utils/refcountpointer.hpp"

typedef uint64_t bt_pid_t;
typedef uint32_t handle_t;

namespace btos_api{
	struct bt_msg_header;
	struct bt_msg_filter;
}

enum class EnvironemntVariableFlags{
	Global		= (1<<0), //Use PID 0 (kernel) value instead
	ReadOnly	= (1<<1), //Not changeable by user-mode code
	Private		= (1<<2), //Not visible to user-mode code
	NoInherit	= (1<<3), //Do not copy from parent to child
};

class IProcess{
public:
	virtual uint64_t ID() = 0;
	virtual const char *GetName() = 0;
	
	virtual void End() = 0;
	virtual void Terminate() = 0;
	virtual void Hold() = 0;

	virtual void SetEnvironmentVariable(const char *name, const char *value, uint8_t flags = 0, bool userspace = false)  = 0;
	virtual const char *GetEnvironmentVariable(const char *name, bool userspace = false) = 0;

	virtual ThreadPointer NewUserThread(ProcessEntryPoint p, void *param, void *stack) = 0;

	virtual handle_t AddHandle(IHandle *handle) = 0;
	virtual IHandle *GetHandle(handle_t h) = 0;
	virtual void CloseAndRemoveHandle(handle_t h) = 0;
	
	virtual void SetExitCode(int value) = 0;

	virtual void Wait() = 0;

	virtual size_t GetArgumentCount() = 0;
	virtual size_t GetArgument(size_t index, char *buf, size_t size);

	virtual void SetStatus(btos_api::bt_proc_status::Enum status) = 0;
	virtual btos_api::bt_proc_status::Enum GetStatus() = 0;

	virtual void SetPermissions(uint16_t extensionID, uint64_t permissions) = 0;
	virtual uint64_t GetPermissions(uint16_t extensionID) = 0;
	virtual void SetUserID(uint64_t uid) = 0;
	virtual uint64_t GetUID() = 0;

	virtual void AddMessage(btos_api::bt_msg_header *msg) = 0;
	virtual void RemoveMessage(btos_api::bt_msg_header *msg) = 0;
	virtual btos_api::bt_msg_header *GetMessage(size_t index) = 0;
	virtual btos_api::bt_msg_header *GetMessageByID(uint64_t id) = 0;
	virtual btos_api::bt_msg_header *GetMessageMatch(const btos_api::bt_msg_filter &filter) = 0;
	virtual void SetCurrentMessage(btos_api::bt_msg_header *msg) = 0;
	virtual btos_api::bt_msg_header *GetCurrentMessage() = 0;

	virtual void SetReturnValue(int returnValue) = 0;
	virtual int GetChildReturnValue(bt_pid_t childPid) = 0;
	virtual void SetChildReturnValue(bt_pid_t childPid, int returnValue) = 0;

	virtual void IncrementRefCount() = 0;
	virtual void DecrementRefCount() = 0;

	virtual ~IProcess() {}
};

typedef RefCountPointer<IProcess> ProcessPointer;

IProcess &CurrentProcess();

class IProcessManager{
public:
	[[nodiscard]] virtual bool SwitchProcess(bt_pid_t pid) = 0;
	virtual void SwitchProcessFromScheduler(bt_pid_t pid) = 0;
	virtual ProcessPointer NewProcess(const char *name, const vector<const char*> &args, IProcess &parent = ::CurrentProcess()) = 0;
	virtual ProcessPointer Spawn(const char *name, const vector<const char*> &args, IProcess &parent = ::CurrentProcess()) = 0;

	virtual void RemoveProcess(const IProcess &proc) = 0;

	virtual void SetGlobalEnvironmentVariable(const char *name, const char *value, uint8_t flags = (uint8_t)EnvironemntVariableFlags::Global) = 0;
	virtual const char *GetGlobalEnvironmentVariable(const char *name, uint8_t *flags = nullptr) = 0;

	virtual IProcess &CurrentProcess() = 0;
	virtual ProcessPointer GetByID(bt_pid_t pid) = 0;

	btos_api::bt_proc_status::Enum GetProcessStatusByID(bt_pid_t pid){
		auto ptr = GetByID(pid);
		if(!ptr) return btos_api::bt_proc_status::DoesNotExist;
		else return ptr->GetStatus();
	}

	virtual ~IProcessManager() {}
};

void Processes_Init();
IProcessManager &GetProcessManager();

inline ProcessPointer GetProcess(bt_pid_t pid){
	auto ptr = GetProcessManager().GetByID(pid);
	if(!ptr) panic("(PROC) Process does not exist!");
	return ptr;
}

#endif
