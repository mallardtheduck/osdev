#ifndef _BTOS_MODULE_H
#define _BTOS_MODULE_H

#if !defined(KERNEL) && !defined(KERNEL_MODULE)
#error This file is for kernel use only.
#endif

#pragma GCC diagnostic ignored "-Wstrict-prototypes"

#include "module/module_api.h"
#include "module/drivers.h"
#include "module/extension.h"
#include "module/handle.h"
#include "module/io.h"
#include "module/locktype.h"
#include "module/module_stubs.h"

#ifdef __cplusplus
#include "module/module_cpp.hpp"
#endif

#endif