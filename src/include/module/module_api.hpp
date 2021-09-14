#ifndef MODULE_MODULE_API_HPP
#define MODULE_MODULE_API_HPP

#include <cstddef>
#include <cstdint>

#include "kernelsys/hal.hpp"
#include "kernelsys/extension.hpp"

typedef void(*threadFn)(void*);
typedef char* (*infoFn)();

typedef uint64_t bt_pid_t;
typedef uint32_t bt_handle_t;

constexpr auto ENV_Global = 	(1<<0); //Use PID 0 (kernel) value instead
constexpr auto ENV_ReadOnly =	(1<<1); //Not changeable by user-mode code
constexpr auto ENV_Private =	(1<<2); //Not visible to user-mode code
constexpr auto ENV_NoInherit = 	(1<<3); //Do not copy from parent to child

class IModuleAPI{
public:
	virtual void Panic(const char *msg) = 0;

	virtual void *MemAlloc(size_t bytes) = 0;
	virtual void Free(void *ptr) = 0;
	virtual void *ReAlloc(void *ptr, size_t new_size) = 0;

	virtual void *MemSet(void *ptr, int value, size_t num) = 0;
	virtual void *MemCopy(void *dst, const void *src, size_t size) = 0;
	virtual void *MemMove(void *dst, void *src, size_t size) = 0;

	virtual int StrCompare(char *a, char *b) = 0;
	virtual void StrCopy(char *dst, char *src, size_t size) = 0;

	virtual void *GetMemoryManager() = 0;

	virtual void *NewLock() = 0;

	virtual void DebugOutput(const char *msg) = 0;
	virtual int VStrPrintF(char *str, const char *fmt, __builtin_va_list ap) = 0;
	virtual int VStrPrintF(char *str, size_t size, const char *fmt, __builtin_va_list ap) = 0;

	virtual void *NewThread(threadFn entry, void *param) = 0;
	virtual void *CurrentThread() = 0;

	virtual void *GetDeviceManager() = 0;

	virtual IHAL &GetHAL() = 0;

	virtual void *GetFilesystem() = 0;

	virtual void LoadModule(const char *path, const char *params) = 0;

	virtual void *NewProcess(const char *exec, size_t argc, char **argv) = 0;
	virtual void *CurrentProcess() = 0;
	virtual void *GetProcess(bt_pid_t pid) = 0;
	
	virtual void AddInfoFSItem(const char *name, infoFn fn) = 0;

	virtual void *GetExtensionManager() = 0;

	virtual void *SendMessage(void *message) = 0;
	virtual bool RecieveMessageReply(void *message, void *reply) = 0;
	virtual void *RecieveMessageReply(void *message) = 0;

	virtual bt_handle_t NewHandle(void *handle, void *process) = 0;
	virtual void *GetHandle(bt_handle_t, void *process) = 0;

	virtual void SetKernelVariable(const char *name, const char *value) = 0;
	virtual size_t GetKernelVariable(const char *name, char *buffer, size_t size) = 0;

	virtual void *GetPnPManager() = 0;

	~IModuleAPI() {}
};

#endif