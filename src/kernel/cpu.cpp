#include "kernel.hpp"
extern "C"{
	#include "cpuid.h"
}


static inline int cpuid_string(int code, int where[4]) {
  __asm__ volatile ("cpuid":"=a"(*where),"=b"(*(where+0)),
               "=d"(*(where+1)),"=c"(*(where+2)):"a"(code));
  return (int)where[0];
}

void init_cpu(){
	char *idstring=cpu_idstring();
	uint64_t speed=cpu_get_speed();	
	char *brandstring=get_brandstring();
	printf("CPU: %s %s. Speed: %i UMIPS.\n", idstring, brandstring, speed/1000000);
}

char *cpu_idstring() {
	static char s[16] = "BogusProces!";
	cpuid_string(0, (int*)(s));
	return s;
}

char *cpu_brandstring(){
	return get_brandstring();
}

uint64_t cpu_get_speed(){	
	outb(0x43,0x34);
	outb(0x40,0);
	outb(0x40,0);
	uint64_t start = rdtsc();
	for (volatile int i=0x10000;i>0;i--) (void)i;
	outb(0x43,0x04);
	uint64_t end=rdtsc();
	uint8_t lo=inb(0x40);
	uint8_t hi=inb(0x40);
	uint32_t ticks=(0x10000 - (hi*256+lo));
	return (end-start)*1193180 / ticks;
}
