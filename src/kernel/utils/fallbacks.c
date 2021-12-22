#include <stddef.h>

//Memory
void *memset(void *dest, int ch, size_t count){
	for(size_t i = 0; i < count; ++i) ((char*)dest)[i] = ch;
	return dest;
}

void* memcpy(void *dest, const void *src, size_t count){
	for(size_t i = 0; i < count; ++i) ((char*)dest)[i] = ((const char*)src)[i];
	return dest;
}

void *memmove(void *v_dst, const void *v_src, size_t c){
	const char *src = (const char*)v_src;
	char *dst = (char*)v_dst;

	if (!c) return v_dst;

	/* Use memcpy when source is higher than dest */
	if (v_dst <= v_src)	return memcpy(v_dst, v_src, c);

	/* copy backwards, from end to beginning */
	src += c;
	dst += c;

	/* Simple, byte oriented memmove. */
	while (c--)	*--dst = *--src;

	return v_dst;
}

//String
size_t strlen(const char *str){
	size_t len = 0;
	while(*str++) ++len;
	return len;
}

char *strncpy(char *dest, const char *src, size_t count){
	size_t i = 0;
	for(; i < count; ++i){
		dest[i] = src[i];
		if(!src[i]) break;
	}
	for(; i < count; ++i){
		dest[i] = '\0';
	}
	return dest;
}

int strcmp(const char *lhs, const char *rhs){
	int diff = 0;
	for(size_t i = 0; diff == 0 && rhs[i] && lhs[i]; ++i){
		diff = rhs[i] - lhs[i];
	}
	return diff;
}