#include "include/btos_x86emu.h"
#include "include/x86emu.h"
#include <btos_module.h>

void *calloc(size_t n, size_t sz){
	size_t size = n * sz;
	void *ret = malloc(size);
	memset(ret, 0, size);
	return ret;
}

char *strcat(char *dest, const char *src){
    char *rdest = dest;

    while (*dest)
      dest++;
    while ((*dest++ = *src++))
      ;
    return rdest;
}

int abs(int i){      
	return (i < 0 ? -i : i);
}

time_t time(time_t *t){
	if(t) *t = 0;
	return 0;
}
