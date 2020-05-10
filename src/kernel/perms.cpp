#include "kernel.hpp"

bool has_perm(uint16_t ext, uint8_t p, pid_t pid){
	if(!(ext == 0 && p == kperm::SuperPerm) && has_perm(0, kperm::SuperPerm, pid)) return true;

	uint64_t perms = proc_get_perms(ext, pid);
	if(((1 << p) & perms) == 0) return true;
	else return false;
}

uint64_t set_perms(uint16_t ext, uint64_t pmask, pid_t pid){
	if(ext && !get_extension(ext)) return 0;
	uint64_t perms = proc_get_perms(ext, pid);
	perms |= pmask;
	proc_set_perms(ext, perms, pid);
	return perms;
}

bool switch_uid(uint64_t uid, pid_t pid){
	if(!has_perm(0, kperm::SwitchUID, pid)) return false;
	proc_set_uid(uid, pid);
	return true;
}
