/*
 * Portability declarations for public domain tar.
 *
 * @(#)port.h 1.1	86/03/11	Public Domain by John Gilmore, 1986
 */

/*
 * Everybody does wait() differently.  There seem to be no definitions
 * for this in V7 (e.g. you are supposed to shift and mask things out
 * using constant shifts and masks.)  So fuck 'em all -- my own non
 * standard but portable macros.  Don't change to a "union wait"
 * based approach -- the ordering of the elements of the struct 
 * depends on the byte-sex of the machine.  Foo!
 */
#define	TERM_SIGNAL(status)	((status) & 0x7F)
#define TERM_COREDUMP(status)	(((status) & 0x80) != 0)
#define TERM_VALUE(status)	((status) >> 8)


