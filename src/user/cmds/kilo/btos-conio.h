#ifndef _BTOS_CONIO_H
#define _BTOS_CONIO_H
#include <btos.h>
#include <util/bt_enum.h>
#ifdef __cplusplus
#include <cstdio>
#else
#include <stdio.h>
#endif

EXTERN_C_BEGIN

char getch();
void gotoxy(int c, int r);
void clearline();
void clearscreen();
size_t getline(char **lineptr, size_t *n, FILE *stream);

void set_scrolling(int onoff);
EXTERN_C_END

#endif
