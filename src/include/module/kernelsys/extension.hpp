#ifndef MODULE_EXTENSION_HPP
#define MODULE_EXTENSION_HPP

#include <cstddef>
#include <cstdint>
#include "hal.hpp"

class IKernelExtension{
public:
	virtual const char *GetName() = 0;
	virtual void UserAPIHandler(uint16_t fn, ICPUState &state);

	virtual ~IKernelExtension() {}
};

class IKernelExensionManager : private nonmovable{
public:
	virtual uint16_t AddExtension(IKernelExtension *ext) = 0;
	virtual IKernelExtension *GetExtension(uint16_t id) = 0;
	virtual uint16_t GetExtensionID(const char *name) = 0;
	virtual void ExtensionUserCall(uint16_t id, uint16_t fn, ICPUState &state) = 0;

	virtual ~IKernelExensionManager() {}
};

#endif