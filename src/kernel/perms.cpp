#include "kernel.hpp"

bool PermissionManager::HasPermission(uint16_t ext, uint8_t p, IProcess &proc){
	if(!(ext == 0 && p == kperm::SuperPerm) && HasPermission(0, kperm::SuperPerm, proc)) return true;

	uint64_t perms = proc.GetPermissions(ext);
	if(((1 << p) & perms) == 0) return true;
	else return false;
}

uint64_t PermissionManager::SetPermissions(uint16_t ext, uint64_t pmask, IProcess &proc){
	if(ext && !GetKernelExtensionManager().GetExtension(ext)) return 0;
	uint64_t perms = proc.GetPermissions(ext);
	perms |= pmask;
	proc.SetPermissions(ext, perms);
	return perms;
}

bool PermissionManager::SwitchUID(uint64_t uid, IProcess &proc){
	if(!HasPermission(0, kperm::SwitchUID, proc)) return false;
	proc.SetUserID(uid);
	return true;
}

static OnDemandStaticAlloc<PermissionManager> thePermissionManager;

IPermissionManager &GetPermissionManager(){
	return *thePermissionManager;
}