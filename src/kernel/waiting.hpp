#ifndef _WAITING_HPP
#define _WAITING_HPP

#include "kernel.hpp"

KernelHandles::Wait::handleType *MakeWaitAnyHandle(vector<IHandle*> handles);
KernelHandles::Wait::handleType *MakeWaitAllHandle(vector<IHandle*> handles);
size_t GetWaitIndex(KernelHandles::Wait::handleType *handle);

#endif