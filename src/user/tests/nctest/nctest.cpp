#include <ncurses/ncurses.h>
#include <dev/rtc.h>

char dbgbuf[128];
#define dbgpf(s, ...) do{snprintf(dbgbuf, 128, "NCTEST: "s, __VA_ARGS__); bt_zero(dbgbuf);}while(0)
int main()
{	
	initscr();			/* Start curses mode 		  */
	printw("Hello World !!!");	/* Print Hello World		  */
	doupdate();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	int maxx, maxy;
	getmaxyx(stdscr, maxy, maxx);
	--maxx; --maxy;
	WINDOW *win = newwin(1, 2, maxy, maxx - 2);
	wprintw(win, ":)");
	wrefresh(win);
	getch();
	int ystep = -1;
	int xstep = -1;
	for(int i = 0; i < 1000; ++i){
		int x, y;
		getbegyx(win, y, x);
		if(x >= maxx - 2 || x <= 0) xstep = -xstep;
		if(y >= maxy || y <= 0) ystep = -ystep;
		mvwin(win, y + ystep, x + xstep);
		wclear(stdscr);
		wrefresh(stdscr);
		wrefresh(win);
		bt_rtc_sleep(100);
	}
	
	endwin();			/* End curses mode		  */

	return 0;
}
