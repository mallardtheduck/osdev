#ifndef _HANDLES_HPP
#define _HANDLES_HPP

#include <module/handle.hpp>
#include <module/kernelsys/handles.hpp>

void init_handles();

void AddHandleDependencyOn(IHandle *h);
void RemoveHandleDependencyOn(IHandle *h);

HandleDependencyCheckResult HandleDependencyCheck(IHandle *h);

void WaitOnHandle(IHandle *h);

#endif
