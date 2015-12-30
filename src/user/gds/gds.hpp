#ifndef _GDS_HPP
#define _GDS_HPP

#include <btos.h>
#include <gd.h>
#include <gdpp.h>
#include <dev/video_dev.h>
#include <crt_support.h>
#include <module/drivers.h>
#include <dev/terminal.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <gdfonts.h>
#include <cstddef>

#include "drawingop.hpp"
#include "client.hpp"

#define dbgpf(...) do{snprintf(dbgbuf, 128, __VA_ARGS__); bt_zero(dbgbuf);}while(false)

extern char dbgbuf[128];

#endif //_GDS_HPP
