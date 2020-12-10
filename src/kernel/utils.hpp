#ifndef KERNEL_UTILS_HPP
#define KERNEL_UTILS_HP

#include "utils/gcc_builtins.h"

//String
char* itoa(int num, char* str, int base=10);

//C++ new/delete operators
inline void *operator new(size_t size)
{
    return malloc(size);
}
 
inline void *operator new[](size_t size)
{
    return malloc(size);
}
 
inline void operator delete(void *p)
{
    free(p);
}
 
inline void operator delete[](void *p)
{
    free(p);
}

template<typename T> void *operator new (size_t, T* ptr)
{
	return ptr;
}

#endif