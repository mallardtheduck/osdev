#include "kernel.hpp"
#include "locks.hpp"
#include <util/asprintf.h>

class ModuleManager : public IModuleManager{
private:
	ILock *lock;

	struct Module{
		string filename;
		string params;
		ILoadedElf *elf;
		IFileHandle *file;
	};

	vector<Module> modules;

	static char *InfoFS();
public:
	ModuleManager(){
		lock = NewLock();
		InfoRegister("MODULES", &InfoFS);
	}

	void LoadModule(const char *path, char *params = nullptr) override{
		Module mod;
		{
			auto hl = lock->LockExclusive();
			for(auto &m : modules){
				if(to_upper(m.filename) == to_upper(path)){
					dbgpf("MOD: Module '%s' already loaded!\n", path);
					return;
				}
			}
			auto node = GetVirtualFilesystem().GetNode(path);
			IFileHandle *file = nullptr;
			if(node) file = node->OpenFile(FS_Read);
			if(!node || !file){
				dbgpf("MOD: Could not open '%s'!\n", path);
				return;
			}
			mod.filename = path;
			mod.params = (params) ? params : "";
			mod.elf = LoadElfModule(*file);
			mod.file = file;
			modules.push_back(mod);
		}
		mod.elf->Execute(params);
	}
};

static ManualStaticAlloc<ModuleManager> theModuleManager;

char *ModuleManager::InfoFS(){
	char *buffer=nullptr;
	asprintf(&buffer, "# address, path, parameters\n");
	for(auto &mod : theModuleManager->modules){
		reasprintf_append(&buffer, "%lx, \"%s\", \"%s\"\n", mod.elf->GetBaseAddress(), mod.filename.c_str(), mod.params.c_str());
	}
	return buffer;
}

void Modules_Init(){
	theModuleManager.Init();
}

IModuleManager &GetModuleManager(){
	return *theModuleManager;
}
