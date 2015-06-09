#ifndef _GDS_HPP
#define _GDS_HPP

#include <gd.h>
#include <gdpp.h>
#include <btos_stubs.h>
#include <video_dev.h>
#include <crt_support.h>
#include <ioctl.h>
#include <drivers.h>
#include <terminal.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <gdfonts.h>
#include <cstddef>

#define dbgpf(...) do{snprintf(dbgbuf, 128, __VA_ARGS__); bt_zero(dbgbuf);}while(false)

extern char dbgbuf[128];

#endif //_GDS_HPP
