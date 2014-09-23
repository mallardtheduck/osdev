#ifndef _TERMINAL_HPP
#define _TERMINAL_HPP

#include "module_cpp.hpp"

extern char video_device_path[BT_MAX_PATH];
extern char input_device_path[BT_MAX_PATH];

extern file_handle *video_device_handle;
extern file_handle *input_device_handle;

#endif