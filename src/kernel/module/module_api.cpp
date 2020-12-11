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

	void *GetMemoryManager() override {
		return nullptr;
	}

	void *NewLock() override {
		return nullptr;
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

	void *NewThread(threadFn entry, void *param) override {
		return nullptr;
	}
	void *CurrentThread() override {
		return nullptr;
	}

	void *GetDeviceManager() override {
		return nullptr;
	}

	IHAL &GetHAL() override {
		return GetHAL();
	}

	void *GetFilesystem() override {
		return nullptr;
	}

	void LoadModule(const char *path, const char *params) override {
		load_module(path, (char*)params);
	}

	void *NewProcess(const char *exec, size_t argc, char **argv) override {
		return nullptr;
	}
	void *CurrentProcess() override {
		return nullptr;
	}
	void *GetProcess(bt_pid_t pid) override {
		return nullptr;
	}
	
	void AddInfoFSItem(const char *name, infoFn fn) override {
		infofs_register(name, fn);
	}

	void *GetExtensionManager() override {
		return nullptr;
	}

	void *SendMessage(void *message) override {
		return nullptr;
	}
	bool RecieveMessageReply(void *message, void *reply) override {
		return false;
	}
	void *RecieveMessageReply(void *message) override {
		return nullptr;
	}

	bt_handle_t NewHandle(void *handle, void *process) override {
		return 0;
	}
	void *GetHandle(bt_handle_t, void *process) override {
		return nullptr;
	}

	void SetKernelVariable(const char *name, const char *value) override {
		set_kvar(name, value);
	}
	size_t GetKernelVariable(const char *name, char *buffer, size_t size) override {
		auto value = get_kvar(name);
		strncpy(buffer, value.c_str(), size - 1);
		buffer[size - 1] = 0;
		return value.size();
	}

	void *GetPnPManager() override {
		return nullptr;
	}
};

ModuleAPI theModuleAPI;

IModuleAPI &GetModuleAPI(){
	return theModuleAPI;
}