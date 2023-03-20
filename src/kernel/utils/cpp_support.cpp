#include "../kernel.hpp"

extern "C" void __cxa_pure_virtual()
{
    panic("Pure virtual function call!");
}

extern "C" int __cxa_atexit(void (*/*func*/) (void *), void * /*arg*/, void * /*dso_handle*/){
	return 0;
}

void *__dso_handle;