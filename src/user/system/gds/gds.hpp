#ifndef _GDS_HPP
#define _GDS_HPP

#include <btos.h>
#include <gd.h>
#include <gdpp.h>
#include <dev/video_dev.h>
#include <crt_support.h>
#include <dev/terminal.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <gdfonts.h>
#include <cstddef>
#include <sstream>

#include "drawingop.hpp"
#include "client.hpp"

#define dbgpf(...) do{snprintf(dbgbuf, 128, __VA_ARGS__); bt_zero(dbgbuf);}while(false)
#define DBG(x) do{std::stringstream dbgss; dbgss << x << endl; bt_zero(dbgss.str().c_str());}while(0)

extern char dbgbuf[128];

#endif //_GDS_HPP
