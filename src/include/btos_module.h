#ifndef _BTOS_MODULE_H
#define _BTOS_MODULE_H

#if !defined(KERNEL) && !defined(KERNEL_MODULE)
#error This file is for kernel use only.
#endif

#include "module/module_api.h"
#include "module/drivers.h"
#include "module/extension.h"
#include "module/handle.hpp"
#ifndef BTOS_MODULE_NO_IO
#include "module/io.h"
#endif
#include "module/module_stubs.h"

#ifdef __cplusplus
#include "module/module_cpp.hpp"
#endif

#endif
