#ifndef _KVARS_HPP
#define _KVARS_HPP

#include "utils/string.hpp"

#include <module/kernelsys/kvars.hpp>

void KernelConfigVariables_Init();
IKernelConfigVariables &GetKernelConfigVariables();

#endif