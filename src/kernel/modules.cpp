#include "kernel.hpp"
#include "locks.hpp"
#include <util/asprintf.h>

class ModuleManager : public IModuleManager{
private:
	ILock *lock;

	struct Module{
		string filename;
		string params;
		loaded_elf_module elf;
		file_handle file;
	};

	vector<Module> modules;

	static char *InfoFS();
public:
	ModuleManager(){
		lock = NewLock();
		infofs_register("MODULES", &InfoFS);
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
			file_handle file=fs_open(path, FS_Read);
			if(!file.valid){
				dbgpf("MOD: Could not open '%s'!\n", path);
				return;
			}
			mod.filename = path;
			mod.params = (params) ? params : "";
			mod.elf = elf_load_module(file);
			mod.file = file;
			modules.push_back(mod);
		}
		mod.elf.entry(&MODULE_SYSCALL_TABLE, params);
	}
};

static char moduleManagerBuffer[sizeof(ModuleManager)] = {0};
ModuleManager *theModuleManager = nullptr;

char *ModuleManager::InfoFS(){
	char *buffer=nullptr;
	asprintf(&buffer, "# address, path, parameters\n");
	for(auto &mod : theModuleManager->modules){
		reasprintf_append(&buffer, "%p, \"%s\", \"%s\"\n", mod.elf.mem.aligned, mod.filename.c_str(), mod.params.c_str());
	}
	return buffer;
}

void Modules_Init(){
	theModuleManager = new(moduleManagerBuffer) ModuleManager();
}

IModuleManager &GetModuleManager(){
	return *theModuleManager;
}
