#ifndef _BTOS_MODULE_H
#define _BTOS_MODULE_H

#if !defined(KERNEL) && !defined(KERNEL_MODULE)
#error This file is for kernel use only.
#endif

#ifndef BTOS_MODULE_NO_IO
#include "module/io.h"
#endif

#include "module/module_c.h"

#ifdef __cplusplus
#include "module/module_api.hpp"
#include "module/module_cpp.hpp"
#endif

#endif
