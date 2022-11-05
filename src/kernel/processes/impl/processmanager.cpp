#include "../../kernel.hpp"

#include "processmanager.hpp"
#include "process.hpp"

ManualStaticAlloc<ProcessManager> theProcessManager;

void CleanupThread(ProcessManager *that){
	auto &myThread = CurrentThread();
	myThread.SetPriority(1);
	while(true){
		{
			vector<Process*> cleanUps;
			{
				auto hl = that->lock->LockExclusive();
				for(auto &p : that->processes){
					auto proc = static_cast<Process*>(p.get());
					if(proc->IsReadyForCleanup()) cleanUps.push_back(static_cast<Process*>(p.get()));
				}
			}
			for(auto &proc : cleanUps){
				auto hl = that->lock->LockExclusive();
				proc->CleanupProcess();
			}
		}
		myThread.Block();
	}
}

void ProcessManager::RemoveProcess(const Process *p){
	auto hl = lock->LockRecursive();
	auto index = processes.find(const_cast<Process*>(p));
	if(index){
		auto hl2 = GetScheduler().LockScheduler();
		processes.erase(index);
	}
}

char *ProcessManager::ProcsInfoFS(){
	auto &that = *theProcessManager;
	bool done = false;
	size_t bufferSize = 4096;
	char *buffer;
	while(!done){
		done = true;
		buffer=(char*)malloc(bufferSize);
		snprintf(buffer, bufferSize, "# PID, path, memory, parent\n");
		size_t kmem=MM2::current_pagedir->get_kernel_used();
		{auto hl = that.lock->LockExclusive();
			for(auto &proc : that.processes){
				auto pid = proc->ID();
				auto path = proc->GetName();
				auto memory = proc->GetMemoryUsage();
				auto parent = proc->ParentID();

				auto count = snprintf(buffer, bufferSize, "%s%llu, \"%s\", %lu, %llu\n", buffer,
					pid, path, (pid == 0) ? kmem : memory, parent);

				if((size_t)count > bufferSize){
					free(buffer);
					buffer = nullptr;
					bufferSize *= 2;
					done = false;
					break;
				}
			}
	    }
	}
    return buffer;
}

char *ProcessManager::EnvInfoFS(){
	return nullptr;
}

void ProcessManager::ScheduleCleanup(){
	cleanupThread->Unblock();
}

ProcessManager::ProcessManager(){
	kernelProcess = Process::CreateKernelProcess();
	vector<ProcessPointer> newProcList;
	newProcList.push_back(kernelProcess);
	{
		auto sl = GetScheduler().LockScheduler();
		newProcList.swap(processes);
	}
	currentProcess = kernelProcess;
	cleanupThread = GetScheduler().NewThread([&]{
		CurrentThread().SetName("Process Cleanup");
		CleanupThread(this);
	});
	InfoRegister("PROCS", &ProcsInfoFS);
}

bool ProcessManager::SwitchProcess(bt_pid_t pid) {
	if(!currentProcess || pid != currentProcess->ID()){
		if(currentProcess) currentProcess->DecrementRefCount();
		auto proc = GetByID(pid);
		if(proc){
			CurrentThread().SetPID(pid);
			currentProcess = (Process*)proc.get();
			currentProcess->IncrementRefCount();
			GetMemoryManager().SwitchPageDirectory(currentProcess->pageDirectory.get());
			return true;
		}
		return false;
	}
	return true;
}

void ProcessManager::SwitchProcessFromScheduler(bt_pid_t pid) {
	if(!currentProcess || pid != currentProcess->ID()){
		if(currentProcess) currentProcess->DecrementRefCountFromScheduler();
		for(auto &proc : processes){
			if(proc->ID() == pid){
				CurrentThread().SetPID(pid);
				currentProcess = (Process*)proc.get();
				currentProcess->IncrementRefCountFromScheduler();
				GetMemoryManager().SwitchPageDirectory(currentProcess->pageDirectory.get());
				return;
			}
		}
		panic("(PROC) Attempt to switch to unknown process.");
	}
}

ProcessPointer ProcessManager::NewProcess(const char *name, const vector<const char*> &args, IProcess &parent) {
	auto proc = new Process(name, args, parent);
	proc->pid = ++pidCounter;
	{
		auto hl = lock->LockExclusive();
		vector<ProcessPointer> newProcList = processes;
		newProcList.push_back(proc);
		{
			auto sl = GetScheduler().LockScheduler();
			newProcList.swap(processes);
		}
	}
	return proc;
}

ProcessPointer ProcessManager::Spawn(const char *name, const vector<const char*> &args, IProcess &parent) {
	auto proc = NewProcess(name, args, parent);
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
	GetMessageManager().SendKernelEvent(btos_api::bt_kernel_messages::ProcessStart, pid);
	return proc;
}

void ProcessManager::RemoveProcess(const IProcess &proc){
	RemoveProcess(static_cast<const Process*>(&proc));
}

void ProcessManager::SetGlobalEnvironmentVariable(const char *name, const char *value, uint8_t flags) {
	if(!(flags & (uint8_t)EnvironemntVariableFlags::Global)) return;
	kernelProcess->SetEnvironmentVariable(name, value, flags);
}

const char *ProcessManager::GetGlobalEnvironmentVariable(const char *name, uint8_t *flagsPtr) {
	char *value = nullptr;
	uint8_t flags = 0;
	kernelProcess->GetEnvironmentVariable(name, value, flags);
	if((flags & (uint8_t)EnvironemntVariableFlags::Global)){
		if(flagsPtr) *flagsPtr = flags;
		return value;
	}
	return nullptr;
}

IProcess &ProcessManager::CurrentProcess() {
	return *currentProcess;
}

ProcessPointer ProcessManager::GetByID(bt_pid_t pid) {
	for(auto &proc : processes){
		if(proc->ID() == pid) return proc;
	}
	return nullptr;
}

btos_api::bt_proc_status::Enum ProcessManager::GetProcessStatusByID(bt_pid_t pid){
	for(auto &proc : processes){
		if(proc->ID() == pid) return proc->GetStatus();
	}
	return btos_api::bt_proc_status::DoesNotExist;
}

void Processes_Init(){
	theProcessManager.Init();
}

bool Processes_Ready(){
	return theProcessManager;
}

IProcessManager &GetProcessManager(){
	return *theProcessManager;
}