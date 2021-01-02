#ifndef KERNEL_UTILS_HPP
#define KERNEL_UTILS_HP

#include "gcc_builtins.h"
#include "string.hpp"
#include "ministl.hpp"

//String
char* itoa(int num, char* str, int base=10);
string to_upper(const string &str);
bool starts_with(const string &str, const string &cmp);
vector<string> split_string(const string &str, const char c);

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