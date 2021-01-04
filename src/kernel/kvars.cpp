#include "kernel.hpp"
#include "utils/ministl.hpp"
#include "locks.hpp"
#include <util/asprintf.h>

class KernelConfigVariables : public IKernelConfigVariables{
private:
	map<string, string> variables;
	ILock *lock = NewLock();

	static char *InfoFS();
public:
	KernelConfigVariables(){
		infofs_register("KVARS", &InfoFS);
	}

	void SetVariable(const char *name, const char *value) override{
		auto hl = lock->LockExclusive();
		variables[name] = value;
	}

	const char *GetVariable(const char *name) override{
		auto hl = lock->LockExclusive();
		return variables[name].c_str();
	}

	bool IsVariableSet(const char *name) override{
		auto hl = lock->LockExclusive();
		return variables.has_key(name);
	}
};

static char kernelConfigVariablesBuffer[sizeof(KernelConfigVariables)];
static KernelConfigVariables *theKernelConfigVariables = nullptr;

void KernelConfigVariables_Init(){
	theKernelConfigVariables = new(kernelConfigVariablesBuffer) KernelConfigVariables();
}

IKernelConfigVariables &GetKernelConfigVariables(){
	return *theKernelConfigVariables;
}

char *KernelConfigVariables::InfoFS(){
	char *buffer=nullptr;
	asprintf(&buffer, "# name, value\n");
	for(auto &var : theKernelConfigVariables->variables){
		reasprintf_append(&buffer, "\"%s\", \"%s\"\n", var.first.c_str(), var.second.c_str());
	}
    return buffer;
}
