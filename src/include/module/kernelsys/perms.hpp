#ifndef MODULE_PERMS_HPP
#define MODULE_PERMS_HPP

#include <cstdint>
#include <cstddef>
#include <util/noncopyable.hpp>

class IPermissionManager : private nonmovable{
public:
	virtual bool HasPermission(uint16_t ext, uint8_t p, IProcess &proc = ::CurrentProcess()) = 0;
	virtual uint64_t SetPermissions(uint16_t ext, uint64_t pmask, IProcess &proc = ::CurrentProcess()) = 0;
	virtual bool SwitchUID(uint64_t uid, IProcess &proc = ::CurrentProcess()) = 0;

	virtual ~IPermissionManager() {}
};

#endif