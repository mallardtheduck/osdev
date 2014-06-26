#include "util.hpp"

#define swap(x,y) { x = x + y; y = x - y; x = x - y; }

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

void *memset(void *s, int c, size_t n)
{
	unsigned char* p=(unsigned char*)s;
	while(n--){
		*(p++) = (unsigned char)c;
	}
	return s;
}

int strcmp(const char *s1, const char *s2)
{
	while((*s1 && *s2) && (*s1++ == *s2++));
	if(!*s1 != !*s2) return *s1 - *s2;
	else return *(--s1) - *(--s2);
}

extern "C" char *strncpy(char *dest, const char *src, size_t size) 
{ 
        char *d = dest; 

        while (--size && *src != '\0') 
                *d++ = *src++; 
        *d = '\0'; 
        return dest; 
}

void* memcpy(void* dest, const void* src, size_t count) {
        char* dst8 = (char*)dest;
        char* src8 = (char*)src;

        while (count--) {
            *dst8++ = *src8++;
        }
        return dest;
}

void *memmove(void *v_dst, const void *v_src, size_t c)
{
	const char *src = (const char*)v_src;
	char *dst = (char*)v_dst;

	if (!c)
		return v_dst;

	/* Use memcpy when source is higher than dest */
	if (v_dst <= v_src)
		return memcpy(v_dst, v_src, c);

	/* copy backwards, from end to beginning */
	src += c;
	dst += c;

	/* Simple, byte oriented memmove. */
	while (c--)
		*--dst = *--src;

	return v_dst;
}

void panic(char *msg){
	printf("PANIC: %s", msg);
	dbgout("PANIC: ");dbgout(msg);
	disable_interrupts();
	asm volatile("hlt");
}
