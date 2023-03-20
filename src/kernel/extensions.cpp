#include "kernel.hpp"
#include "utils/ministl.hpp"
#include <util/asprintf.h>

class KernelExensionManager : public IKernelExensionManager{
private:
	map<uint16_t, IKernelExtension*> extensions;

	char *InfoFS(){
		char *buffer=nullptr;
		asprintf(&buffer, "# id, name\n");
		for(auto &ext : extensions){
			reasprintf_append(&buffer, "%i, %s\n", (int)ext.first, ext.second->GetName());
		}
		return buffer;
	}
public:
	KernelExensionManager(){
		InfoRegister("EXTENSIONS", [&]{
			return InfoFS();
		});
	}
	
	uint16_t AddExtension(IKernelExtension *ext) override{
		uint16_t ret=1;
		while(extensions.has_key(ret)) ++ret;
		extensions[ret] = ext;
		return ret;
	}

	IKernelExtension *GetExtension(uint16_t id) override{
		if(extensions.has_key(id)) return extensions[id];
		else return nullptr;
	}

	uint16_t GetExtensionID(const char *name) override{
		for(auto &ext : extensions){
			if(string(ext.second->GetName()) == name) return ext.first;
		}
		return 0;
	}

	void ExtensionUserCall(uint16_t id, uint16_t fn, ICPUState &state) override{
		if(extensions.has_key(id)){
			extensions[id]->UserAPIHandler(fn, state);
		}else{
			dbgpf("EXT: Unknown API extension: %i (PID: %i, EIP:%lx)!\n", (int)id, (int)CurrentProcess().ID(), state.Get32BitRegister(Generic_Register::Instruction_Pointer));
			state.Get32BitRegister(Generic_Register::GP_Register_A)=(uint32_t)-1;
		}
	}
};

ManualStaticAlloc<KernelExensionManager> theKernelExtensionManager;

void Extensions_Init(){
	theKernelExtensionManager.Init();
}

IKernelExensionManager &GetKernelExtensionManager(){
	return *theKernelExtensionManager;
}