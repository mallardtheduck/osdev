#ifndef _DEVICE_HPP
#define _DEVICE_HPP

void init_device();
extern lock term_lock;

extern const char *terminal_var;
uint64_t atoi64(char *str);
char* i64toa(uint64_t num, char* str, int base);

#endif