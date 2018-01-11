#ifndef _BTOS_H
#define _BTOS_H

#pragma GCC diagnostic ignored "-Wstrict-prototypes"

#include "btos/btos_api.h"
#include "btos/bt_msg.h"
#include "btos/fs_interface.h"
#include "btos/ioctl.h"
#include "btos/kernel_calls.h"
#ifndef BTOS_NO_DEVICES
#include "btos/devices.h"
#endif
#include "btos/core.h"

#if defined(__cplusplus) && !defined(BTOS_NO_USING)
using namespace btos_api;
#endif

#endif
