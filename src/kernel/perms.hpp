#ifndef _KERNEL_PERMS_H
#define _KERNEL_PERMS_H

#include "kernel.hpp"
#include <module/kernelsys/perms.hpp>
#include <btos/permissions.h>

namespace kperm = btos_api::perms::bt_kernel_perm;

class PermissionManager : public IPermissionManager{
public:
	bool HasPermission(uint16_t ext, uint8_t p, IProcess &proc = ::CurrentProcess()) override;
	uint64_t SetPermissions(uint16_t ext, uint64_t pmask, IProcess &proc = ::CurrentProcess()) override;
	bool SwitchUID(uint64_t uid, IProcess &proc = ::CurrentProcess()) override;
};

IPermissionManager &GetPermissionManager();

#endif