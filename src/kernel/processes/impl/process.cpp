#include "../../kernel.hpp"
#include "process.hpp"
#include "processmanager.hpp"

Process *Process::CreateKernelProcess(){
	auto kernelProcess = new Process();
	kernelProcess->name = "KERNEL";
	kernelProcess->pid = pidCounter++;
	kernelProcess->parent = 0;
	return kernelProcess;
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
	auto hl = lock->LockExclusive();
	auto upperName = to_upper(name);
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

const char *Process::GetEnvironmentVariable(const char *name, bool userspace = false);

IThread *Process::NewUserThread(ProcessEntryPoint p, void *param, void *stack);

handle_t Process::AddHandle(IHandle *handle);
IHandle *Process::GetHandle(handle_t h);
void Process::RemoveHandle(handle_t h);

void Process::SetExitCode(int value);

void Process::Wait();

size_t Process::GetArgumentCount();
size_t Process::GetArgument(size_t index, char *buf, size_t size);

void Process::SetStatus(btos_api::bt_proc_status::Enum status);
btos_api::bt_proc_status::Enum Process::GetStatus();

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