#ifndef MODULE_MODULE_C_H
#define MODULE_MODULE_C_H

#include <btos_module.h>
#ifdef __cplusplus
#include <cstdarg>
#include <cstddef>
#else
#include <stdarg.h>
#include <stddef.h>
#endif

extern "C" void panic(const char *msg);

extern "C" void *malloc(size_t bytes);
extern "C" void free(void *ptr);
extern "C" void *realloc(void *ptr, size_t new_size);

extern "C" void *memset(void *ptr, int value, size_t num);
extern "C" void *memcpy(void *dst, const void *src, size_t size);
extern "C" void *memmove(void *dst, void *src, size_t size);

extern "C" int strcmp(char *a, char *b);
extern "C" void strncpy(char *dst, char *src, size_t size);

extern "C" void dbgout(const char *msg);

extern "C" int vsprintf(char *str, const char *fmt, __builtin_va_list ap);
extern "C" int vsnprintf(char *str, size_t size, const char *fmt, __builtin_va_list ap);

extern "C" int sprintf(char *str, const char *fmt, ...);
extern "C" int snprintf(char *str, size_t size, const char *fmt, ...);

extern "C" int dbgprintf(const char *fmt, ...);

#endif