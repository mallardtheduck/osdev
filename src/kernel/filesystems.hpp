#ifndef _FILESYSTEMS_HPP
#define _FILESYSTEMS_HPP

#include "kernel.hpp"
#include <btos/fs_interface.h>

#include <module/kernelsys/filesystems.hpp>

void Filesystem_Init();
IVirtualFilesystem &GetVirtualFilesystem();
IFilesystemManager &GetFilesystemManager();

#endif
