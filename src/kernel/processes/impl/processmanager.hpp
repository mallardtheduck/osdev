#ifndef KERNEL_PROCESSES_IMPL_PROCESSMANAGER_HPP
#define KERNEL_PROCESSES_IMPL_PROCESSMANAGER_HPP

#include "../../kernel.hpp"

class ProcessManager : public IProcessManager{
private:
	friend class Process;

	bt_pid_t pidCounter = 0;
	vector<Process*> processes;
	Process *currentProcess = nullptr;
	Process *kernelProcess = nullptr;
	
	ILock *lock = NewLock();

	static char *ProcsInfoFS();
	static char *EnvInfoFS();

	void RemoveProcess(Process *p);
public:
	ProcessManager();

	bool SwitchProcess(bt_pid_t pid) override;
	void SwitchProcessFromScheduler(bt_pid_t pid) override;
	ProcessPointer NewProcess(const char *name, const vector<const char*> &args, IProcess &parent = ::CurrentProcess()) override;
	ProcessPointer Spawn(const char *name, const vector<const char*> &args, IProcess &parent = ::CurrentProcess()) override;

	void SetGlobalEnvironmentVariable(const char *name, const char *value, uint8_t flags = (uint8_t)EnvironemntVariableFlags::Global) override;
	const char *GetGlobalEnvironmentVariable(const char *name) override;

	IProcess &CurrentProcess() override;
	ProcessPointer GetByID(bt_pid_t pid) override;

	btos_api::bt_proc_status::Enum GetProcessStatusByID(bt_pid_t pid){
		auto ptr = GetByID(pid);
		if(!ptr) return btos_api::bt_proc_status::DoesNotExist;
		else return ptr->GetStatus();
	}
};

#endif