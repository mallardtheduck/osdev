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

#endif