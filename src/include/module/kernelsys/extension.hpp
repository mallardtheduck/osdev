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

#endif