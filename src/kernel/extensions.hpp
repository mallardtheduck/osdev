#ifndef KERNEL_EXTENSIONS_HPP
#define KERNEL_EXTENSIONS_HPP

#include "kernel.hpp"
namespace module_api {
#include <module/extension.hpp>
}

class IKernelExensionManager : private nonmovable{
public:
	virtual uint16_t AddExtension(module_api::IKernelExtension *ext) = 0;
	virtual module_api::IKernelExtension *GetExtension(uint16_t id) = 0;
	virtual uint16_t GetExtensionID(const char *name) = 0;
	virtual void ExtensionUserCall(uint16_t id, uint16_t fn, ICPUState &state) = 0;

	virtual ~IKernelExensionManager() {}
};

void Extensions_Init();
IKernelExensionManager &GetKernelExtensionManager();

#endif