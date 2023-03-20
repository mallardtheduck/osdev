#ifndef KERNEL_EXTENSIONS_HPP
#define KERNEL_EXTENSIONS_HPP

#include "kernel.hpp"
#include <module/kernelsys/extension.hpp>

void Extensions_Init();
IKernelExensionManager &GetKernelExtensionManager();

#endif