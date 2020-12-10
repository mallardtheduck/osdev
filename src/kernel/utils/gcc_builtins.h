#ifndef KERNEL_UTILS_GCC_BUILTINS_HPP
#define KERNEL_UTILS_GCC_BUILTINS_HPP

//Strings
#define strlen(s) __builtin_strlen(s)
#define strcmp(a, b) __builtin_strcmp(a, b)
#define strncpy(d, s, c) __builtin_strncpy(d, s, c)


//Memory
#define memset(s, c, n) __builtin_memset(s, c, n)
#define memmove(d, s, c) __builtin_memmove(d, s, c)
#define memcpy(d, s, c) __builtin_memcpy(d, s, c)

#endif