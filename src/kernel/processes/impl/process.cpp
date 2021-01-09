#include "../../kernel.hpp"
#include "process.hpp"
#include "processmanager.hpp"

constexpr auto DefaultUserspaceStackSize = 65536;
constexpr auto UserThreadKernelStackSize = 16384;

constexpr auto DefaultUserspaceThreadPriority = 100;

Process *Process::CreateKernelProcess(){
	auto kernelProcess = new Process();
	kernelProcess->name = "KERNEL";
	kernelProcess->pid = pidCounter++;
	kernelProcess->parent = 0;
	return kernelProcess;
}

intptr_t Process::AllocateStack(size_t size){
	size_t pages = size / MM2::MM2_Page_Size;
	intptr_t baseAddress = 0 - (pages * MM2::MM2_Page_Size);
	MM2::current_pagedir->alloc_pages_at(pages, (void*)baseAddress);
	memset((void*)baseAddress, 0, size));
	return 0 - sizeof(void*);
}

map<string, EnvironmentVariable> Process::CopyEnvironment(const IProcess &parent){
	map<string, EnvironmentVariable> newEnvironment;
	auto realParent = static_cast<Process&>(parent);
	auto parentLock = realParent.lock->LockExclusive();
	for(auto &e : realParent.environment){
		if(!(e.second.flags & proc_env_flags::NoInherit) && !(e.second.flags & proc_env_flags::Global){
			newEnvironment[e.first] = e.second;
		}
	}
	return newEnvironment;
}

Process::Process(const char *n, const vector<const char *> &a, IProcess &p)
:name(name), parent(p.ID()), pageDirectory(new MM2::PageDirectory()), environment(CopyEnvironment(p)) {
	for(auto &arg : a){
		args.push_back(arg);
	}
}

void Process::CleanUpProcess(){
	{
		auto hl = lock->LockRecursive();
		for(auto &h : handles){
			h.second->Close();
			delete h.second;
		}
		if(GetScheduler().GetPIDThreadCount(pid) > 0) panic("(PROC) Thread count inconsistency!");
		if(parent){
			auto parentProcess = GetProcessManager().GetByID(parent);
			if(parentProcess){
				parentProcess.SetChildReturnValue(returnValue);
			}
		}
		static_cast<ProcessManager&>(GetProcessManager()).RemoveProccess(this);
		msg_clear(pid);
		msg_send_event(btos_api::bt_kernel_messages::ProcessEnd, (void*)&pid, sizeof(pid));
	}
	delete this;
}

void Process::GetEnvironmentVariable(const char *name, char *&value, uint8_t &flags){
	auto upperName = to_upper(name);
	auto hl = lock->LockExclusive();
	if(environment.has_key(upperName)){
		value = environment[upperName].value.c_str();
		flags = environment[upperName].flags;
	}
}

uint64_t Process::ID(){
	return pid;
}

const char *Process::GetName(){
	return name.c_str();
}

void Process::End(){
	if(pid == 0) panic("(PROC) Kernel process attempting to end!");
	{
		auto hl = lock->LockExclusive();
		if(status != btos_api::bt_proc_status::Ending){
			debug_event_notify(pid, 0, bt_debug_event::ProgramEnd);
			status = btos_api::bt_proc_status::Ending;
		}
	}
	if(&CurrentProcess() == this) GetProcessManager().SwitchProcess(0);
}

void Process::Terminate(){
	if(pid == 0) panic("(PROC) Kernel process terminate request!");
	{
		auto hl = lock->LockExclusive();
		returnValue = -1;
		bool endCurrentThread = false;
		if(&CurrentProcess() == this){
			GetProcessManager().SwitchProcess(0);
			endCurrentThread = true;
		}
		End();
		if(endCurrentThread) CurrentThread().Abort();
	}

}

void Process::Hold(){
	//Don't think this is actually used?!?
	panic("Process::Hold()");
}

void Process::SetEnvironmentVariable(const char *name, const char *value, uint8_t flags, bool userspace){
	if(pid != 0 && (flags & EnvironemntVariableFlags::Global)){
		GetProcessManager().SetGlobalEnvironmentVariable(name, valaue, flags);
		return;
	}
	auto upperName = to_upper(name);

	auto hl = lock->LockExclusive();
	if(userspace){
		if((flags & EnvironemntVariableFlags::Private)) return;
		if(environment.has_key(upperName)){
			auto &existingVariable = environment[upperName];
			if((existingVariable.flags & EnvironemntVariableFlags::Private)) return;
			if((existingVariable.flags & EnvironemntVariableFlags::ReadOnly)) return;
		}
	}
	string stringValue = value;
	if(stringValue.length()){
		EnvironmentVariable evar;
		evar.value = stringValue;
		evar.flags = flags;
		environment[upperName] = evar;
	}else if(environment.has_key(upperName)) environment.erase(upperName);
}

const char *Process::GetEnvironmentVariable(const char *name, bool userspace = false){
	auto upperName = to_upper(name);

	uint8_t globalFlags = 0;
	auto global = GetProcessManager().GetGlobalEnvironmentVariable(upperName, globalFlags);
	if(userspace && (flags & (uint8_t)EnvironemntVariableFlags::Private)) return nullptr;
	
	auto hl = lock->LockExclusive();
	if(environment.has_key(upperName)){
		auto &evar = environment[upperName];
		if(userspace && (evar.flags & (uint8_t)EnvironemntVariableFlags::Private)) return nullptr;
		return evar.value.c_str();
	}
	return nullptr;
}

IThread *Process::NewUserThread(ProcessEntryPoint p, void *param, void *stack){
	GetScheduler().NewThread([=](){
		if(!GetProcessManager().SwitchProcess(pid)) return;
		auto stackPointer = AllocateStack(DefaultUserspaceStackSize);
		CurrentThread().SetPriority(DefaultUserspaceThreadPriority);
		//Deliberately twice.
		CurrentThread().SetAbortable(true);
		CurrentThread().SetAbortable(true);
		debug_event_notify(proc_current_pid, sch_get_id(), bt_debug_event::ThreadStart);
		CurrentProcess().SetStatus(btos_api::bt_proc_status::Running);
		GetHAL().RunUsermode(stackPointer, p);
	}, UserThreadKernelStackSize);
}

handle_t Process::AddHandle(IHandle *handle){
	auto hl = lock->LockExclusive();
	handles[++handleCounter] = handle;
	return handleCounter;
}

IHandle *Process::GetHandle(handle_t h){
	auto hl = lock->LockExclusive();
	if(handles.has_key(h)) return handles[h];
	return nullptr;
}

void Process::CloseAndRemoveHandle(handle_t h){
	auto hl = lock->LockExclusive();
	if(handles.has_key(h)){
		auto handle = handles[h];
		handles.erase(h);
		handle->Close();
		delete handle;
	}
}

void Process::SetExitCode(int value){
	auto hl = lock->LockExclusive();
	returnValue = value;
}

void Process::Wait(){
	CurrentThread().SetBlock([=](){
		auto status = GetProcessManager().GetProcessStatusByID(pid);
		return status == btos_api::bt_proc_status::DoesNotExist || status == btos_api::bt_proc_status::Ending;
	});
}

size_t Process::GetArgumentCount(){
	auto hl = lock->LockExclusive();
	return args.size();
}

size_t Process::GetArgument(size_t index, char *buf, size_t size){
	auto hl = lock->LockExclusive();
	if(index < args.size()){
		strncpy(buf, args[index].c_str(), size - 1);
		buf[size - 1] = '\0';
		return args[index].size();
	}
	return 0;
}

void Process::SetStatus(btos_api::bt_proc_status::Enum s){
	auto hl = lock->LockExclusive();
	status = s;
}

btos_api::bt_proc_status::Enum Process::GetStatus(){
	//Can't lock, since this may be called from the scheduler (via Wait)
	return status;
}

void Process::SetPermissions(uint16_t extensionID, uint64_t permissions);
uint64_t Process::GetPermissions(uint16_t extensionID);
void Process::SetUserID(uint64_t uid);
uint64_t Process::GetUID();

void Process::AddMessage(btos_api::bt_msg_header *msg);
void Process::RemoveMessage(btos_api::bt_msg_header *msg);
btos_api::bt_msg_header *Process::GetMessage(size_t index);
btos_api::bt_msg_header *Process::GetMessageByID(uint64_t id);
btos_api::bt_msg_header *Process::GetMessageMatch(const btos_api::bt_msg_filter &filter);
void Process::SetCurrentMessage(btos_api::bt_msg_header *msg);
btos_api::bt_msg_header *Process::GetCurrentMessage();

void Process::SetReturnValue(int rV){
	auto hl = lock->LockExclusive();
	returnValue = rV;
}
int Process::GetChildReturnValue(bt_pid_t childPid){
	auto hl = lock->LockExclusive();
	if(childReturns.has_key(childPid)) return childReturns[pid];
	else return 0;
}

void Process::IncrementRefCount(){
	auto hl = lock->LockExclusive();
	++refCount;
}

void Process::DecrementRefCount(){
	auto hl = lock->LockExclusive();
	if(refCount > 0) --refCount;
	if(!refCount && status == btos_api::bt_proc_status::Ending) CleanupProcess();
}