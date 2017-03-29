/*
 * @(#)port.c 1.6	86/08/11	Public Domain, by John Gilmore, 1986
 *
 * These are routines not available in all environments.
 *
 * I know this introduces an extra level of subroutine calls and is
 * slightly slower.  Frankly, my dear, I don't give a damn.  Let the
 * Missed-Em Vee losers suffer a little.  This software is proud to
 * have been written on a BSD system.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

#include "port.h"

#define BSD42
#ifndef BSD42
/*
 * lstat() is a stat() which does not follow symbolic links.
 * If there are no symbolic links, just use stat().
 */
int
lstat (path, buf)
	char *path;
	struct stat *buf;
{
	extern int stat ();
	return (stat (path, buf));
}

/*
 * valloc() does a malloc() on a page boundary.  On some systems,
 * this can make large block I/O more efficient.
 */
char *
valloc (size)
	unsigned size;
{
	return (malloc (size));
}

/*
**				NMKDIR.C
**
** Written by Robert Rother, Mariah Corporation, August 1985. 
**
** I wrote this out of shear disgust with myself because I couldn't
** figure out how to do this in /bin/sh.
**
** If you want it, it's yours.  All I ask in return is that if you
** figure out how to do this in a Bourne Shell script you send me
** a copy.
**					sdcsvax!rmr or rmr@uscd
*
* Severely hacked over by John Gilmore to make a 4.2BSD compatible
* subroutine.	11Mar86; hoptoad!gnu
*/

/*
 * Make a directory.  Compatible with the mkdir() system call on 4.2BSD.
 */
int
mkdir(dpath, dmode)
	const char *dpath;
	mode_t dmode;
{
	int cpid, status;
	extern int errno;

	switch (cpid = fork()) {

	case -1:			/* Error in fork() */
		return(-1);		/* Errno is set already */

	case 0:				/* Child process */
		/*
		 * Cheap hack to set mode of new directory.  Since this
		 * child process is going away anyway, we zap its umask.
		 * FIXME, this won't suffice to set SUID, SGID, etc. on this
		 * directory.  Does anybody care?
		 */
		status = umask(0);	/* Get current umask */
		status = umask(status | (0777 & ~dmode)); /* Set for mkdir */
		execl("/bin/mkdir", "mkdir", dpath, (char *)0);
		_exit(-1);		/* Can't exec /bin/mkdir */
	
	default:			/* Parent process */
		while (cpid != wait(&status)) ;	/* Wait for kid to finish */
	}

	if (TERM_SIGNAL(status) != 0 || TERM_VALUE(status) != 0) {
		errno = EIO;		/* We don't know why, but */
		return -1;		/* /bin/mkdir failed */
	}

	return 0;
}
#endif

#ifdef USG
/*
 * Translate V7 style into Sys V style.
 */
#include <string.h>
#include <memory.h>

char *
index (s, c)
	char *s;
	int c;
{
	return (strchr (s, c));
}

char *
bcopy (s1, s2, n)
	char *s1, *s2;
	int n;
{
	(void) memcpy (s2, s1, n);
	return (s1);
}

void
bzero (s1, n)
	char *s1;
	int n;
{
	(void) memset(s1, 0, n);
}
#endif
