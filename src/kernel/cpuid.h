#ifndef _CPUID_H
#define _CPUID_H

int do_intel(void);
int do_amd(void);
void printregs(int eax, int ebx, int ecx, int edx);
int detect_cpu(void);
char *get_brandstring();

#endif
