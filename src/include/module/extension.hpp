#ifndef _EXTENSION_H
#define _EXTENSION_H

#include "module_api.h"
#include "drivers.h"

class IKernelExtension{
public:
	virtual const char *GetName() = 0;
	virtual void UserAPIHandler(uint16_t fn, ICPUState &state);

	virtual ~IKernelExtension() {}
};

#ifndef __cplusplus
typedef struct kernel_extension kernel_extension;
#endif

#endif