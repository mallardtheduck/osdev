#ifndef MODULE_MODULE_API_HPP
#define MODULE_MODULE_API_HPP

#include <cstddef>
#include <cstdint>

#include <module/utils/module_meta.hpp>

// typedef void(*threadFn)(void*);
// typedef char* (*infoFn)();

typedef uint64_t bt_pid_t;
typedef uint32_t bt_handle_t;

constexpr auto ENV_Global = 	(1<<0); //Use PID 0 (kernel) value instead
constexpr auto ENV_ReadOnly =	(1<<1); //Not changeable by user-mode code
constexpr auto ENV_Private =	(1<<2); //Not visible to user-mode code
constexpr auto ENV_NoInherit = 	(1<<3); //Do not copy from parent to child

class IModuleAPI;
MODULE_ONLY(extern IModuleAPI *API);

#include "kernelsys/hal.hpp"
#include "kernelsys/extension.hpp"
#include "kernelsys/scheduler.hpp"
#include "kernelsys/process.hpp"
#include "kernelsys/filesystems.hpp"
#include "kernelsys/locks.hpp"
#include "kernelsys/atoms.hpp"
#include "kernelsys/kvars.hpp"
#include "kernelsys/messaging.hpp"
#include "kernelsys/hwpnp.hpp"
#include "kernelsys/mm2.hpp"
#include "kernelsys/devices.hpp"
#include "kernelsys/perms.hpp"

class IModuleAPI{
public:
	virtual void Panic(const char *msg) = 0;

	virtual void *MemAlloc(size_t bytes) = 0;
	virtual void Free(void *ptr) = 0;
	virtual void *ReAlloc(void *ptr, size_t new_size) = 0;

	virtual void *MemSet(void *ptr, int value, size_t num) = 0;
	virtual void *MemCopy(void *dst, const void *src, size_t size) = 0;
	virtual void *MemMove(void *dst, void *src, size_t size) = 0;

	virtual int StrCompare(const char *a, const char *b) = 0;
	virtual void StrCopy(char *dst, const char *src, size_t size) = 0;

	virtual IMemoryManager &GetMemoryManager() = 0;

	virtual ILock *NewLock() = 0;
	virtual IAtom *NewAtom(uint64_t value = 0) = 0;

	virtual void DebugOutput(const char *msg) = 0;
	virtual int VStrPrintF(char *str, const char *fmt, __builtin_va_list ap) = 0;
	virtual int VStrPrintF(char *str, size_t size, const char *fmt, __builtin_va_list ap) = 0;

	virtual IScheduler &GetScheduler() = 0;
	virtual IThread &CurrentThread() = 0;
	virtual ThreadPointer GetThread(uint64_t id) = 0;

	virtual IVisibleDeviceManager &GetVisibleDeviceManager() = 0;

	virtual IHAL &GetHAL() = 0;

	virtual IVirtualFilesystem &GetVirtualFilesystem() = 0;
	virtual IFilesystemManager &GetFilesystemManager() = 0;

	virtual void LoadModule(const char *path, const char *params) = 0;

	virtual IProcessManager &GetProcessManager() = 0;
	virtual IProcess &CurrentProcess() = 0;
	virtual ProcessPointer GetProcess(bt_pid_t pid) = 0;
	
	virtual void InfoRegister(const char *name, function<char*()> fn) = 0;

	virtual IKernelExensionManager &GetKernelExtensionManager() = 0;

	virtual IMessageManager &GetMessageManager() = 0;

	virtual IKernelConfigVariables &GetKernelConfigVariables() = 0;

	virtual IHwPnpManager &GetHwPnPManager() = 0;

	virtual IPermissionManager &GetPermissionManager() = 0;

	~IModuleAPI() {}
};

#endif