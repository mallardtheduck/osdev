#ifndef _VIRT_HANDLES_HPP
#define _VIRT_HANDLES_HPP

#include <crt_support.h>
#include <iostream>

virtual_handle MemoryVirtualHandle(const char *data, const size_t size);
virtual_handle FileOffsetVirtualHandle(int fd, off_t offset, off_t size, bool close = false);

#endif