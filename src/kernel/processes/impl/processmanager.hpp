#ifndef KERNEL_PROCESSES_IMPL_PROCESSMANAGER_HPP
#define KERNEL_PROCESSES_IMPL_PROCESSMANAGER_HPP

#include "../../kernel.hpp"

class Process;

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

	void RemoveProcess(const Process *p);
public:
	ProcessManager();

	bool SwitchProcess(bt_pid_t pid) override;
	void SwitchProcessFromScheduler(bt_pid_t pid) override;
	ProcessPointer NewProcess(const char *name, const vector<const char*> &args, IProcess &parent = ::CurrentProcess()) override;
	ProcessPointer Spawn(const char *name, const vector<const char*> &args, IProcess &parent = ::CurrentProcess()) override;

	void RemoveProcess(const IProcess &proc) override;

	void SetGlobalEnvironmentVariable(const char *name, const char *value, uint8_t flags = (uint8_t)EnvironemntVariableFlags::Global) override;
	const char *GetGlobalEnvironmentVariable(const char *name, uint8_t *flags = nullptr) override;

	IProcess &CurrentProcess() override;
	ProcessPointer GetByID(bt_pid_t pid) override;
};

#endif