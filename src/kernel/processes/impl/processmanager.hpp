#ifndef KERNEL_PROCESSES_IMPL_PROCESSMANAGER_HPP
#define KERNEL_PROCESSES_IMPL_PROCESSMANAGER_HPP

#include "../../kernel.hpp"

class Process;

class ProcessManager : public IProcessManager{
private:
	bt_pid_t pidCounter = 0;
	vector<Process*> processes;
	Process *currentProcess = nullptr;

	struct EnvironmentVariable{
		string value;
		uint8_t flags;
	};
	map<string, EnvironmentVariable> globalEnvironment;
	
	ILock *lock = NewLock();
public:
	bool SwitchProcess(bt_pid_t pid) override;
	void SwitchProcessFromScheduler(bt_pid_t pid) override;
	ProcessPointer NewProcess(const char *name, size_t argc, char **argv, IProcess &parent = ::CurrentProcess()) override;
	ProcessPointer Spawn(const char *name, size_t argc, char **argv, IProcess &parent = ::CurrentProcess()) override;

	void SetGlobalEnvironmentVariable(const char *name, const char *value, uint8_t flags = (uint8_t)EnvironemntVariableFlags::Global) override;
	const char *GetGlobalEnvironmentVariable(const char *name) override;

	IProcess &CurrentProcess() override;
	ProcessPointer GetByID(bt_pid_t pid) override;
};

#endif