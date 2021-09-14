#ifndef _KVARS_HPP
#define _KVARS_HPP

#include "utils/string.hpp"

class IKernelConfigVariables{
public:
	virtual void SetVariable(const char *name, const char *value) = 0;
	virtual const char *GetVariable(const char *name) = 0;
	virtual bool IsVariableSet(const char *name) = 0;

	virtual ~IKernelConfigVariables() {}
};

void KernelConfigVariables_Init();
IKernelConfigVariables &GetKernelConfigVariables();

#endif