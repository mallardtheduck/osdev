#include "kernel.hpp"

bool has_perm(uint16_t ext, uint8_t p, bt_pid_t pid){
	if(!(ext == 0 && p == kperm::SuperPerm) && has_perm(0, kperm::SuperPerm, pid)) return true;

	uint64_t perms = GetProcess(pid)->GetPermissions(ext);
	if(((1 << p) & perms) == 0) return true;
	else return false;
}

uint64_t set_perms(uint16_t ext, uint64_t pmask, bt_pid_t pid){
	if(ext && !get_extension(ext)) return 0;
	auto proc = GetProcess(pid);
	uint64_t perms = proc->GetPermissions(ext);
	perms |= pmask;
	proc->SetPermissions(ext, perms);
	return perms;
}

bool switch_uid(uint64_t uid, bt_pid_t pid){
	if(!has_perm(0, kperm::SwitchUID, pid)) return false;
	GetProcess(pid)->SetUserID(uid);
	return true;
}
