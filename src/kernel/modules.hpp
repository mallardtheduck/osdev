#ifndef _MODULES_HPP
#define _MODULES_HPP

#include "kernel.hpp"

class IModuleManager{
public:
	virtual void LoadModule(const char *path, char *params = nullptr) = 0;

	virtual ~IModuleManager() {}
};

void Modules_Init();
IModuleManager &GetModuleManager();

#endif
