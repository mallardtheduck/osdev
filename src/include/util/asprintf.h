#ifndef _ASPRINTF_H
#define _ASPRINTF_H

#if defined(KERNEL_MODULE)
#include <btos_module.h>
#elif !defined(KERNEL)
#error "This asprintf.h is for kernel-mode only"
#endif

#ifndef KERNEL
inline static int strlen(const char *str){
	int len;
    for (len = 0; str[len]; (len)++);
	return len;
}
#endif

#ifdef printf
#define printf_is_macro
#pragma push_macro("printf")
#undef printf
#endif

inline static int vasprintf(char **strp, const char *fmt, va_list ap){
	size_t size = vsnprintf(NULL, 0, fmt, ap) + 1;
	*strp = (char*)malloc(size);
	return vsnprintf(*strp, size, fmt, ap);
}

inline static int asprintf(char **strp, const char *fmt, ...) __attribute__((format (printf, 2, 3)));

inline static int asprintf(char **strp, const char *fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	int retval = vasprintf(strp, fmt, ap);
	va_end(ap);
	return retval;
}

inline static int vreasprintf_append(char **strp, const char *fmt, va_list ap){
	size_t extrasize = vsnprintf(NULL, 0, fmt, ap) + 1;
	size_t size = strlen(*strp) + extrasize;
	*strp = (char*)realloc(*strp, size);
	return vsnprintf(*strp + strlen(*strp), extrasize, fmt, ap);
}

inline static int reasprintf_append(char **strp, const char *fmt, ...) __attribute__((format (printf, 2, 3)));

inline static int reasprintf_append(char **strp, const char *fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	int retval = vreasprintf_append(strp, fmt, ap);
	va_end(ap);
	return retval;
}

#ifdef printf_is_macro
#pragma pop_macro("printf")
#undef printf_is_macro
#endif

#endif