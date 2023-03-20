#ifndef MODULE_MODULE_C_H
#define MODULE_MODULE_C_H

#include <btos_module.h>
#ifdef __cplusplus
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#else
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#endif

#include <util/bt_enum.h>

EXTERN_C void panic(const char *msg);

EXTERN_C void *malloc(size_t bytes);
EXTERN_C void free(void *ptr);
EXTERN_C void *realloc(void *ptr, size_t new_size);

EXTERN_C void *memset(void *ptr, int value, size_t num);
EXTERN_C void *memcpy(void *dst, const void *src, size_t size);
EXTERN_C void *memmove(void *dst, void *src, size_t size);

EXTERN_C int strcmp(const char *a, const char *b);
EXTERN_C void strncpy(char *dst, const char *src, size_t size);

EXTERN_C void dbgout(const char *msg);

EXTERN_C int vsprintf(char *str, const char *fmt, __builtin_va_list ap);
EXTERN_C int vsnprintf(char *str, size_t size, const char *fmt, __builtin_va_list ap);

EXTERN_C int sprintf(char *str, const char *fmt, ...);
EXTERN_C int snprintf(char *str, size_t size, const char *fmt, ...);

EXTERN_C int dbgpf(const char *fmt, ...);

#endif