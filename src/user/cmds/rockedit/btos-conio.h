#ifndef _BTOS_CONIO_H
#define _BTOS_CONIO_H
#include <util/bt_enum.h>

EXTERN_C_BEGIN

char getch();
void gotoxy(int c, int r);
void clearline();
void clearscreen();

void set_scrolling(int onoff);
EXTERN_C_END

#endif
