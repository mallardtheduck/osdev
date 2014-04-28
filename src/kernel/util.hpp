#ifndef _UTIL_HPP
#define _UTIL_HPP

#include "kernel.hpp"

char* itoa(int num, char* str, int base=10);
void *memset(void *s, int c, size_t n);
void panic(char *msg);
int strcmp(const char *s1, const char *s2);
char *strncpy(char *dest, const char *src, size_t size);
 
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

#endif
