#include "../../kernel.hpp"
#include "process.hpp"
#include "processmanager.hpp"

constexpr auto DefaultUserspaceStackSize = 65536;
constexpr auto UserThreadKernelStackSize = 16384;

constexpr auto DefaultUserspaceThreadPriority = 100;

static uint64_t pidCounter = 0;

void Environment::SetEnvironmentVariable(const char *name, const char *value, uint8_t flags, bool userspace){
	if(*pid != 0 && (flags & to_underlying(EnvironemntVariableFlags::Global))){
		GetProcessManager().SetGlobalEnvironmentVariable(name, value, flags);
		return;
	}
	auto upperName = to_upper(name);

	auto hl = lock->LockExclusive();
	if(userspace){
		if((flags & to_underlying(EnvironemntVariableFlags::Private))) return;
		if(environment.has_key(upperName)){
			auto &existingVariable = environment[upperName];
			if((existingVariable.flags & to_underlying(EnvironemntVariableFlags::Private))) return;
			if((existingVariable.flags & to_underlying(EnvironemntVariableFlags::ReadOnly))) return;
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

void Environment::GetEnvironmentVariable(const char *name, char *&value, uint8_t &flags){
	auto upperName = to_upper(name);
	auto hl = lock->LockExclusive();
	if(environment.has_key(upperName)){
		value = const_cast<char*>(environment[upperName].value.c_str());
		flags = environment[upperName].flags;
	}
}

const char *Environment::GetEnvironmentVariable(const char *name, bool userspace){
	//dbgpf("PROC: GetEnvironmentVariable: '%s' (%i)\n", name, (int)userspace);
	auto upperName = to_upper(name);

	uint8_t globalFlags = 0;
	auto global = GetProcessManager().GetGlobalEnvironmentVariable(upperName.c_str(), &globalFlags);
	if(userspace && (globalFlags & to_underlying(EnvironemntVariableFlags::Private))) return nullptr;
	else if(global) return global;
	
	auto hl = lock->LockExclusive();
	if(environment.has_key(upperName)){
		auto &evar = environment[upperName];
		if(userspace && (evar.flags & to_underlying(EnvironemntVariableFlags::Private))) return nullptr;
		return evar.value.c_str();
	}
	return nullptr;
}

size_t Environment::GetSize(){
	return environment.size();
}

IEnvironment::EnvironmentVariableInfo Environment::GetVariableInfo(size_t index){
	auto it = environment.begin();
	for(size_t i = 0; it != environment.end() && i < index; ++it, ++i);
	if(it == environment.end())	return {"", "", 0};
	EnvironmentVariableInfo info;
	info.name = it->first.c_str();
	info.value = it->second.value.c_str();
	info.flags = it->second.flags;
	return info;
}

void Environment::CopyIn(IEnvironment &env){
	auto realEnv = static_cast<Environment*>(&env);
	for(auto &e : realEnv->environment){
		if(!(e.second.flags & to_underlying(EnvironemntVariableFlags::NoInherit)) && !(e.second.flags & to_underlying(EnvironemntVariableFlags::Global))){
			environment[e.first] = e.second;
		}
	}
}

Process *Process::CreateKernelProcess(){
	auto kernelProcess = new Process();
	kernelProcess->name = "KERNEL";
	kernelProcess->pid = pidCounter++;
	kernelProcess->parent = 0;
	kernelProcess->status = btos_api::bt_proc_status::Running;
	//Thankfully, since the kernel process never ends, this should never try to delete the kernel page directory!
	kernelProcess->pageDirectory.reset(MM2::kernel_pagedir);
	return kernelProcess;
}

uintptr_t Process::AllocateStack(size_t size){
	size_t pages = size / MM2::MM2_Page_Size;
	uintptr_t baseAddress = 0 - (pages * MM2::MM2_Page_Size);
	dbgpf("PROC: Allocating initial process stack at %lx (%lu pages)\n", baseAddress, pages);
	MM2::current_pagedir->alloc_pages_at(pages, (void*)baseAddress);
	memset((void*)baseAddress, 0, size);
	return 0 - sizeof(void*);
}

Process::Process(const char *n, const vector<const char *> &a, IProcess &p)
:parent(p.ID()), name(n), pageDirectory(new MM2::PageDirectory()) {
	environment.pid = &pid;
	environment.CopyIn(p.GetEnvironment());
	args.push_back(name);
	for(auto &arg : a){
		args.push_back(arg);
	}
	status = btos_api::bt_proc_status::Starting;
}

bool Process::IsReadyForCleanup(){
	return readyForCleanup && status == btos_api::bt_proc_status::Ending;
}

Process::Process() {
	environment.pid = &pid;
}

void Process::CleanupProcess(){
	{
		auto hl = lock->LockRecursive();
		vector<ThreadPointer> threads;
		for(auto &h : handles){
			auto handle = KernelHandleCast<KernelHandles::Thread>(h.second);
			if(handle){
				threads.push_back(handle->GetData());
				h.second->Close();
				delete h.second;
				h.second = nullptr;
			}
		}
		for(auto &t : threads){
			t->Abort();
			t->Join();
		}
		threads.clear();
		bool pendingHandles = true;
		while(pendingHandles){
			pendingHandles = false;
			for(auto &h : handles){
				if(h.second){
					if(HandleDependencyCheck(h.second) != HandleDependencyCheckResult::Absent){
						pendingHandles = true;
						continue;
					}
					h.second->Close();
					delete h.second;
					h.second = nullptr;
				}
			}
		}
		if(GetScheduler().GetPIDThreadCount(pid) > 0){
			dbgpf("PROC: ThreadCount: %lu\n", GetScheduler().GetPIDThreadCount(pid));
			panic("(PROC) Thread count inconsistency!");
		}
		if(parent){
			auto parentProcess = GetProcessManager().GetByID(parent);
			if(parentProcess){
				parentProcess->SetChildReturnValue(pid, returnValue);
			}
		}
		static_cast<ProcessManager&>(GetProcessManager()).RemoveProcess(this);
		GetMessageManager().ClearMessages(*this);
		GetMessageManager().SendKernelEvent(btos_api::bt_kernel_messages::ProcessEnd, pid);
	}
	delete this;
}

void Process::GetEnvironmentVariable(const char *name, char *&value, uint8_t &flags){
	environment.GetEnvironmentVariable(name, value, flags);
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
		auto hl = lock->LockRecursive();
		if(status != btos_api::bt_proc_status::Ending){
			debug_event_notify(pid, 0, bt_debug_event::ProgramEnd);
			status = btos_api::bt_proc_status::Ending;
		}
	}
	if(&CurrentProcess() == this) GetProcessManager().SwitchProcess(0);
}

void Process::Terminate(){
	if(pid == 0) panic("(PROC) Kernel process terminate request!");
	bool endCurrentThread = false;
	{
		auto hl = lock->LockExclusive();
		returnValue = -1;
		if(&CurrentProcess() == this){
			GetProcessManager().SwitchProcess(0);
			endCurrentThread = true;
		}
		End();
	}
	GetScheduler().AbortThreadsByPID(pid);
	if(endCurrentThread) CurrentThread().Abort();
}

void Process::HoldBeforeUserspace(){
	//Prevents threads from returning to userspace, used by the memory manager
	if(status == btos_api::bt_proc_status::Held){
		CurrentThread().SetBlock([&]{
			return status != btos_api::bt_proc_status::Held;
		});
	}
}

void Process::SetEnvironmentVariable(const char *name, const char *value, uint8_t flags, bool userspace){
	environment.SetEnvironmentVariable(name, value, flags, userspace);
}

const char *Process::GetEnvironmentVariable(const char *name, bool userspace){
	return environment.GetEnvironmentVariable(name, userspace);
}

IEnvironment &Process::GetEnvironment(){
	return environment;
}

ThreadPointer Process::NewUserThread(ProcessEntryPoint p, void *param, void *stack){
	return GetScheduler().NewThread([=](){
		if(!GetProcessManager().SwitchProcess(pid)) return;
		CurrentThread().SetName("Userspace");
		auto stackPointer = stack ? (uintptr_t)stack : AllocateStack(DefaultUserspaceStackSize);
		CurrentThread().SetPriority(DefaultUserspaceThreadPriority);
		debug_event_notify(pid, CurrentThread().ID(), bt_debug_event::ThreadStart);
		CurrentProcess().SetStatus(btos_api::bt_proc_status::Running);
		dbgpf("PROC: Starting user thread at %p with stack %lx.\n", p, stackPointer);
		status = btos_api::bt_proc_status::Running;
		if(CurrentThread().GetLockCount() != 0) panic("PROC: Starting user thread with non-zero lock count!");
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
		if(HandleDependencyCheck(handle) == HandleDependencyCheckResult::Absent){
			handles.erase(h);
			handle->Close();
			delete handle;
			vector<bt_handle_t> successfullyClosedHandles;
			for(auto pendingHandleId : pendingHandleCloses){
				if(handles.has_key(pendingHandleId)){
					auto pendingHandle = handles[pendingHandleId];
					if(HandleDependencyCheck(pendingHandle) == HandleDependencyCheckResult::Absent){
						handles.erase(pendingHandleId);
						pendingHandle->Close();
						delete pendingHandle;
						successfullyClosedHandles.push_back(pendingHandleId);
					}
				}
			}
			for(auto closedHandleId : successfullyClosedHandles){
				auto index = pendingHandleCloses.find(closedHandleId);
				pendingHandleCloses.erase(index);
			}
		}else{
			pendingHandleCloses.push_back(h);
		}
	}
}

vector<handle_t> Process::GetHandlesByType(uint32_t type){
	vector<handle_t> ret;
	auto hl = lock->LockExclusive();
	for(auto &h : handles){
		if(!type || h.second->GetType() == type) ret.push_back(h.first);
	}
	return ret;
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

void Process::SetPermissions(uint16_t extensionID, uint64_t permission){
	auto hl = lock->LockExclusive();
	permissions[extensionID] = permission;
}

uint64_t Process::GetPermissions(uint16_t extensionID){
	auto hl = lock->LockExclusive();
	if(permissions.has_key(extensionID)) return permissions[extensionID];
	else return 0;
}

void Process::SetUserID(uint64_t u){
	auto hl = lock->LockExclusive();
	uid = u;
}

uint64_t Process::GetUID(){
	auto hl = lock->LockExclusive();
	return uid;
}

void Process::SetCurrentMessageID(uint64_t id){
	auto hl = lock->LockExclusive();
	currentMessageId = id;
}

uint64_t Process::GetCurrentMessageID(){
	auto hl = lock->LockExclusive();
	return currentMessageId;
}

void Process::SetReturnValue(int rV){
	auto hl = lock->LockExclusive();
	returnValue = rV;
}

int Process::GetChildReturnValue(bt_pid_t childPid){
	auto hl = lock->LockExclusive();
	if(childReturns.has_key(childPid)) return childReturns[pid];
	else return 0;
}

void Process::SetChildReturnValue(bt_pid_t childPid, int returnValue){
	auto hl = lock->LockExclusive();
	childReturns[childPid] = returnValue;
}

void Process::IncrementRefCount(){
	auto hl = lock->LockRecursive();
	++refCount;
	if(refCount > UINT32_MAX / 2) panic("(PROC) Process node refcount implausible!");
}

void Process::DecrementRefCount(){
	auto hl = lock->LockRecursive();
	if(refCount > 0) --refCount;
	if(!refCount && status == btos_api::bt_proc_status::Ending){
		readyForCleanup = true;
		static_cast<ProcessManager&>(GetProcessManager()).ScheduleCleanup();
	}
}

void Process::IncrementRefCountFromScheduler(){
	++refCount;
	if(refCount > UINT32_MAX / 2) panic("(PROC) Process node refcount implausible!");
}

void Process::DecrementRefCountFromScheduler(){
	if(refCount > 0) --refCount;
	if(!refCount && status == btos_api::bt_proc_status::Ending){
		readyForCleanup = true;
		static_cast<ProcessManager&>(GetProcessManager()).ScheduleCleanup();
	}
}

size_t Process::GetMemoryUsage(){
	return pageDirectory->get_user_used();
}
uint64_t Process::ParentID(){
	return parent;
}