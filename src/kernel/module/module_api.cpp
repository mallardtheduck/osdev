#include "../kernel.hpp"
#include <module/module_api.hpp>

class ModuleAPI : public IModuleAPI{
public:
	void Panic(const char *msg) override{
		panic(msg);
	}

	void *MemAlloc(size_t bytes) override{
		return malloc(bytes);
	}
	void Free(void *ptr) override{
		free(ptr);
	}
	void *ReAlloc(void *ptr, size_t new_size) override{
		return realloc(ptr, new_size);
	}

	void *MemSet(void *ptr, int value, size_t num) override{
		return memset(ptr, value, num);
	}
	void *MemCopy(void *dst, const void *src, size_t size) override{
		return memcpy(dst, src, size);
	}
	void *MemMove(void *dst, void *src, size_t size) override{
		return memmove(dst, src, size);
	}

	int StrCompare(char *a, char *b) override {
		return strcmp(a, b);
	}
	void StrCopy(char *dst, char *src, size_t size) override{
		strncpy(dst, src, size);
	}

	IMemoryManager &GetMemoryManager() override {
		return ::GetMemoryManager();
	}

	ILock *NewLock() override {
		return ::NewLock();
	}

	IAtom *NewAtom(uint64_t value = 0) override{
		return ::NewAtom(value);
	}

	void DebugOutput(const char *msg) override {
		dbgout(msg);
	}
	int VStrPrintF(char *str, const char *fmt, __builtin_va_list ap) override {
		return vsprintf(str, fmt, ap);
	}
	int VStrPrintF(char *str, size_t size, const char *fmt, __builtin_va_list ap) override {
		return vsnprintf(str, size, fmt, ap);
	}

	IScheduler &GetScheduler() override{
		return ::GetScheduler();
	}

	IThread &CurrentThread() override{
		return ::CurrentThread();
	}

	ThreadPointer GetThread(uint64_t id) override{
		return ::GetThread(id);
	}

	IVisibleDeviceManager &GetVisibleDeviceManager() override{
		return ::GetVisibleDeviceManager();
	}

	IHAL &GetHAL() override {
		return GetHAL();
	}

	IVirtualFilesystem &GetVirtualFilesystem() override{
		return ::GetVirtualFilesystem();
	}

	IFilesystemManager &GetFilesystemManager() override{
		return ::GetFilesystemManager();
	}

	void LoadModule(const char *path, const char *params) override {
		GetModuleManager().LoadModule(path, (char*)params);
	}

	IProcessManager &GetProcessManager() override{
		return ::GetProcessManager();
	}

	IProcess &CurrentProcess() override{
		return ::CurrentProcess();
	}

	ProcessPointer GetProcess(bt_pid_t pid) override{
		return ::GetProcess(pid);
	}
	
	void InfoRegister(const char *name, function<char*()> fn) override{
		::InfoRegister(name, fn);
	}

	IKernelExensionManager &GetKernelExtensionManager() override{
		return ::GetKernelExtensionManager();
	}

	IMessageManager &GetMessageManager() override{
		return ::GetMessageManager();
	}

	IKernelConfigVariables &GetKernelConfigVariables() override{
		return ::GetKernelConfigVariables();
	}

	void *GetPnPManager() override {
		return nullptr;
	}
};

static ManualStaticAlloc<ModuleAPI> theModuleAPI;

IModuleAPI &GetModuleAPI(){
	if(!theModuleAPI) theModuleAPI.Init();
	return *theModuleAPI;
}