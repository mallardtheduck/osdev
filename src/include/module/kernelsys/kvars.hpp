#ifndef MODULE_KVARS_HPP
#define MODULE_KVARS_HPP

#include <util/noncopyable.hpp>

class IKernelConfigVariables : private nonmovable{
public:
	virtual void SetVariable(const char *name, const char *value) = 0;
	virtual const char *GetVariable(const char *name) = 0;
	virtual bool IsVariableSet(const char *name) = 0;

	virtual ~IKernelConfigVariables() {}
};

#endif