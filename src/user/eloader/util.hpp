#ifndef _UTIL_HPP
#define _UTIL_HPP

#include <btos.h>
#include <stddef.h>

bool btos_path_parse(const char *opath, char *buffer, size_t size);
bool btos_path_is_absolute(const char *path);
int strlen(const char *s);
char *strncpy(char *s1, const char *s2, size_t n);
void *memset(void *s, int c, size_t n);
int strcmp(const char *s1, const char *s2);

#endif