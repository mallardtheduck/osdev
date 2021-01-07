#include "../../kernel.hpp"

#include "processmanager.hpp"
#include "process.hpp"

bool ProcessManager::SwitchProcess(bt_pid_t pid) {
	if(!currentProcess || pid != currentProces->ID()){
		auto hl = lock->LockExclusive();
		for(auto &proc : process){
			if(proc->ID() == pid){
				CurrentThread().SetPID(pid);
				currentProcess = &proc;
				MM2::mm2_switch(currentProcess->pageDirectory.get());
				return true;
			}
		}
		return false;
	}
}

void ProcessManager::SwitchProcessFromScheduler(bt_pid_t pid) {
	if(!currentProcess || pid != currentProces->ID()){
		for(auto &proc : process){
			if(proc->ID() == pid){
				CurrentThread().SetPID(pid);
				currentProcess = &proc;
				MM2::mm2_switch(currentProcess->pageDirectory.get());
				return;
			}
		}
		panic("(PROC) Attempt to switch to unknown process.");
	}
}

ProcessPointer ProcessManager::NewProcess(const char *name, size_t argc, char **argv) {

}

ProcessPointer ProcessManager::Spawn(const char *name, size_t argc, char **argv) {

}

void ProcessManager::SetGlobalEnvironmentVariable(const char *name, const char *value, uint8_t flags = (uint8_t)EnvironemntVariableFlags::Global) {
}

const char *ProcessManager::GetGlobalEnvironmentVariable(const char *name) {

}

IProcess &ProcessManager::CurrentProcess() {

}

ProcessPointer ProcessManager::GetByID(bt_pid_t pid) {

}