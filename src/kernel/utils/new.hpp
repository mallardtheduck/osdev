#ifndef KERNEL_UTILS_NEW
#define KERNEL_UTILS_NEW

#ifndef VSCODE //VSCode reports spruious errors here...
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

inline void operator delete(void *p, size_t)
{
	free(p);
}
 
inline void operator delete[](void *p)
{
	free(p);
}

inline void operator delete[](void *p, size_t)
{
	free(p);
}

template<typename T> void *operator new (size_t, T* ptr)
{
	return ptr;
}
#endif

#endif