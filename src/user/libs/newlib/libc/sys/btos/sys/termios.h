#ifndef _SYS_TERMIOS_H
#define _SYS_TERMIOS_H

typedef char cc_t;
typedef char speed_t;
typedef char tcflag_t;

#define NCCS 2

#define VEOF 0
#define VEOL 0
#define VERASE 1
#define VINTR 0
#define VKILL 0
#define VMIN 0
#define VQUIT 0
#define VSTART 0
#define VSTOP 0
#define VSUSP 0

#define ECHO 0
#define ISIG 0

#define TCSAFLUSH 0

struct termios {
	cc_t	     c_cc[NCCS];  /* control characters */
	tcflag_t     c_cflag;     /* control modes */
	tcflag_t     c_iflag;     /* input modes */
	tcflag_t     c_lflag;     /* local modes */
	tcflag_t     c_oflag;     /* output modes */
	speed_t      c_ispeed;    /* input baudrate */
	speed_t      c_ospeed;    /* output baudrate */
};

int tcgetattr(int fildes, struct termios *termios_p);
int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p);

#endif