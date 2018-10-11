#ifndef _MODULE_CPP_HPP
#define _MODULE_CPP_HPP

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

#define USE_PURE_VIRTUAL extern "C" void __cxa_pure_virtual() \
{ \
    panic("Pure virtual function call!"); \
}

#define USE_STATIC_INIT extern "C" int __cxa_atexit(void (*/*func*/) (void *), void * /*arg*/, void * /*dso_handle*/) {return 0;} void *__dso_handle

#endif