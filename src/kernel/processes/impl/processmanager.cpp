#include "../../kernel.hpp"

#include "processmanager.hpp"
#include "process.hpp"

bool ProcessManager::SwitchProcess(bt_pid_t pid) {
	if(!currentProcess) return false;
	if(pid != currentProcess->ID()){
		auto proc = GetByID(pid);
		if(proc){
			CurrentThread().SetPID(pid);
			currentProcess = (Process*)proc.get();
			MM2::mm2_switch(currentProcess->pageDirectory.get());
			return true;
		}
		return false;
	}
	return true;
}

void ProcessManager::SwitchProcessFromScheduler(bt_pid_t pid) {
	if(!currentProcess || pid != currentProcess->ID()){
		for(auto &proc : processes){
			if(proc->ID() == pid){
				CurrentThread().SetPID(pid);
				currentProcess = proc;
				MM2::mm2_switch(currentProcess->pageDirectory.get());
				return;
			}
		}
		panic("(PROC) Attempt to switch to unknown process.");
	}
}

ProcessPointer ProcessManager::NewProcess(const char *name, size_t argc, char **argv, IProcess &parent) {
	auto *proc = new Process(name, argc, argv, parent);
	{
		auto hl = lock->LockExclusive();
		vector<Process*> newProcList = processes;
		newProcList.push_back(proc);
		{
			auto sl = GetScheduler().LockScheduler();
			newProcList.swap(processes);
		}
	}
	return proc;
}

ProcessPointer ProcessManager::Spawn(const char *name, size_t argc, char **argv, IProcess &parent) {
	auto proc = NewProcess(name, argc, argv, parent);
	auto pid = proc->ID();
	IFileHandle *file;
	if(!GetKernelConfigVariables().IsVariableSet("LOADER")){
		file = GetVirtualFilesystem().OpenFile(name, FS_Read);
	}else{
		string loader = GetKernelConfigVariables().GetVariable("LOADER");
		file = GetVirtualFilesystem().OpenFile(loader.c_str(), FS_Read);		
	}
	if(!file){
		proc->Terminate();
		return nullptr;
	}
	unique_ptr<ILoadedElf> elf { LoadElfProcess(pid, *file) };
	debug_event_notify(pid, 0, bt_debug_event::ProgramStart);
	proc->AddHandle(file);
	proc->NewUserThread(elf->GetEntryPoint(), nullptr, nullptr);
	msg_send_event(btos_api::bt_kernel_messages::ProcessStart, (void*)&pid, sizeof(pid));
	return proc;
}

void ProcessManager::SetGlobalEnvironmentVariable(const char *name, const char *value, uint8_t flags) {
	if(!(flags & (uint8_t)EnvironemntVariableFlags::Global)) return;
	EnvironmentVariable env;
	env.value = value;
	env.flags = flags;
	{
		auto hl = lock->LockExclusive();
		globalEnvironment[name] = env;
	}
}

const char *ProcessManager::GetGlobalEnvironmentVariable(const char *name) {
	auto hl = lock->LockExclusive();
	if(!globalEnvironment.has_key(name)) return nullptr;
	return globalEnvironment[name].value.c_str();
}

IProcess &ProcessManager::CurrentProcess() {
	return *currentProcess;
}

ProcessPointer ProcessManager::GetByID(bt_pid_t pid) {
	auto hl = lock->LockExclusive();
	for(auto &proc : processes){
		if(proc->ID() == pid) return proc;
	}
	return nullptr;
}