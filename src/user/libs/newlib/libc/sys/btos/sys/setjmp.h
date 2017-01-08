#ifndef _SYS_SETJMP_H
#define _SYS_SETJMP_H

#include <setjmp.h>

//typedef struct {} jmp_buf;
typedef struct {} sigjmp_buf;

//void longjmp(jmp_buf, int);
void siglongjmp(sigjmp_buf, int);
void _longjmp(jmp_buf, int);

//int setjmp(jmp_buf);
int sigsetjmp(sigjmp_buf, int);
int _setjmp(jmp_buf);

#endif