/*
 * List a tar archive.
 *
 * Also includes support routines for reading a tar archive.
 *
 * Pubic Domain version written 26 Aug 1985 by John Gilmore (ihnp4!hoptoad!gnu).
 *
 * @(#)list.c 1.18 9/23/86 Public Domain - gnu
 */
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <string.h>
#include <stdlib.h>

#include "stubs.h"

char *ctime();				/* From libc.a */

#define	isodigit(c)	( ((c) >= '0') && ((c) <= '7') )

#include "tar.h"

long from_oct();			/* Decode octal number */
void demode();				/* Print file mode */

union record *head;			/* Points to current archive header */
struct stat hstat[1];			/* Stat struct corresponding */

void print_header();
void skip_file();
int read_header();


/*
 * Main loop for reading an archive.
 */
void
read_and(do_something)
	void (*do_something)();
{
	int status = 1;
	int prev_status;

	name_gather();			/* Gather all the names */
	open_archive(1);		/* Open for reading */

	for(;;) {
		prev_status = status;
		status = read_header();
		switch (status) {

		case 1:			/* Valid header */
			/* We should decode next field (mode) first... */
			/* Ensure incoming names are null terminated. */
			head->header.name[NAMSIZ-1] = '\0';
			
			if (!name_match(head->header.name)) {
				/* Skip past it in the archive */
				userec(head);
				/* Skip to the next header on the archive */
				skip_file((long)hstat->st_size);
				continue;
			}

			(*do_something)();
			continue;

			/*
			 * If the previous header was good, tell them
			 * that we are skipping bad ones.
			 */
		case 0:			/* Invalid header */
		case0:
			userec(head);
			if (prev_status == 1) {
				annorec(stderr, tar);
				fprintf(stderr,
					"Skipping to next file header...\n");
			}
			continue;

		case 2:			/* Block of zeroes */
			if (f_ignorez)	
				goto case0;	/* Just skip if asked */
			/* FALL THRU */
		case EOF:		/* End of archive */
			break;
		}
		break;
	};

	close_archive();
	names_notfound();		/* Print names not found */
}		


/*
 * Print a header record, based on tar options.
 */
void
list_archive()
{

	/* Save the record */
	saverec(&head);

	/* Print the header record */
	print_header();

	/* Skip past it in the archive */
	saverec((union record **) 0);	/* Unsave it */
	userec(head);

	/* Skip to the next header on the archive */
	skip_file((long)hstat->st_size);
}


/*
 * Read a record that's supposed to be a header record.
 * Return its address in "head", and if it is good, the file's
 * size in hstat->st_size.
 *
 * Return 1 for success, 0 if the checksum is bad, EOF on eof,
 * 2 for a block full of zeros (EOF marker).
 *
 * You must always userec(head) to skip past the header which this
 * routine reads.
 */
int
read_header()
{
	register int	i;
	register long	sum, recsum;
	register char	*p;
	register union record *header;

	header = findrec();
	head = header;		/* This is our current header */
	if (NULL == header) return EOF;

	recsum = from_oct(8,  header->header.chksum);

	sum = 0;
	p = header->charptr;
	for (i = sizeof(*header); --i >= 0;) {
		/*
		 * We can't use unsigned char here because of old compilers,
		 * e.g. V7.
		 */
		sum += 0xFF & *p++;
	}

	/* Adjust checksum to count the "chksum" field as blanks. */
	for (i = sizeof(header->header.chksum); --i >= 0;)
		sum -= 0xFF & header->header.chksum[i];
	sum += ' '* sizeof header->header.chksum;	

	if (sum == recsum) {
		/*
		 * Good record.  Decode file size and return.
		 */
		if (header->header.linkflag == LF_LINK)
			hstat->st_size = 0;	/* Links 0 size on tape */
		else
			hstat->st_size = from_oct(1+12, header->header.size);
		return 1;
	}

	if (sum == 8*' ') {
		/*
		 * This is a zeroed block...whole block is 0's except
		 * for the 8 blanks we faked for the checksum field.
		 */
		return 2;
	}

	return 0;
}


/* 
 * Decode things from a file header record into a "struct stat".
 * Also set "*stdp" to !=0 or ==0 depending whether header record is "Unix
 * Standard" tar format or regular old tar format.
 *
 * read_header() has already decoded the checksum and length, so we don't.
 *
 * If wantug != 0, we want the uid/group info decoded from Unix Standard
 * tapes (for extraction).  If == 0, we are just printing anyway, so save time.
 */
void decode_header(header, st, stdp, wantug)
	register union record	*header;
	register struct stat	*st;
	int	*stdp;
	int	wantug;
{

	st->st_mode = from_oct(8,  header->header.mode);
	st->st_mtime = from_oct(1+12, header->header.mtime);
	
	if (0==strcmp(header->header.magic, TMAGIC)) {
		/* Unix Standard tar archive */
		*stdp = 1;
		if (wantug) {
			st->st_uid = finduid(header->header.uname);
			st->st_gid = findgid(header->header.gname);
		}
		switch  (header->header.linkflag) 
		case LF_BLK: case LF_CHR:
		    st->st_dev = makedev(from_oct(8, header->header.devmajor),
			 		 from_oct(8, header->header.devminor));
	} else {
		/* Old fashioned tar archive */
		*stdp = 0;
		st->st_uid = from_oct(8,  header->header.uid);
		st->st_gid = from_oct(8,  header->header.gid);
		st->st_dev = 0;
	}
}


/*
 * Quick and dirty octal conversion.
 *
 * Result is -1 if the field is invalid (all blank, or nonoctal).
 */
long
from_oct(digs, where)
	register int	digs;
	register char	*where;
{
	register long	value;

	while (isspace((unsigned)*where)) {		/* Skip spaces */
		where++;
		if (--digs <= 0)
			return -1;		/* All blank field */
	}
	value = 0;
	while (digs > 0 && isodigit(*where)) {	/* Scan til nonoctal */
		value = (value << 3) | (*where++ - '0');
		--digs;
	}

	if (digs > 0 && *where && !isspace((unsigned)*where))
		return -1;			/* Ended on non-space/nul */

	return value;
}


/*
 * Actually print it.
 */
#define	UGSWIDTH	11		/* min width of User, group, size */
#define	DATEWIDTH	19		/* Last mod date */
static int	ugswidth = UGSWIDTH;	/* Max width encountered so far */

void
print_header()
{
	char modes[11];
	char *timestamp;
	char uform[11], gform[11];	/* These hold formatted ints */
	char *user, *group;
	char size[24];		/* Holds a formatted long or maj, min */
	long longie;		/* To make ctime() call portable */
	int	pad;
	int	header_std;	/* Is header standard or not? */

	annofile(stdout, (char *)NULL);

	if (f_verbose) {
		decode_header(head, hstat, &header_std, 0);

		/* File type and modes */
		modes[0] = '?';
		switch (head->header.linkflag) {
		case LF_NORMAL:
		case LF_OLDNORMAL:
		case LF_LINK:
				modes[0] = '-'; 
				if ('/' == head->header.name[strlen(head->header.name)-1])
					modes[0] = 'd';
				break;
		case LF_DIR:	modes[0] = 'd'; break;
		case LF_SYMLINK:modes[0] = 'l'; break;
		case LF_BLK:	modes[0] = 'b'; break;
		case LF_CHR:	modes[0] = 'c'; break;
		case LF_FIFO:	modes[0] = 'f'; break;
		case LF_CONTIG:	modes[0] = '='; break;
		}

		demode((unsigned)hstat->st_mode, modes+1);

		/* Timestamp */
		longie = hstat->st_mtime;
		timestamp = ctime(&longie);
		timestamp[16] = '\0';
		timestamp[24] = '\0';

		/* User and group names */
		if (*head->header.uname && header_std) {
			user  = head->header.uname;
		} else {
			user = uform;
			(void)sprintf(uform, "%d", (int)hstat->st_uid);
		}
		if (*head->header.gname && header_std) {
			group = head->header.gname;
		} else {
			group = gform;
			(void)sprintf(gform, "%d", (int)hstat->st_gid);
		}

		/* Format the file size or major/minor device numbers */
		switch (head->header.linkflag) {
		case LF_CHR:
		case LF_BLK:
			(void)sprintf(size, "%d, %d",
					major(hstat->st_dev),
					minor(hstat->st_dev));
			break;

		default:
			(void)sprintf(size, "%ld", (long)hstat->st_size);
		}

		/* Figure out padding and print the whole line. */
		pad = strlen(user) + strlen(group) + strlen(size) + 1;
		if (pad > ugswidth) ugswidth = pad;

		printf("%s %s/%s %*s%s %s %s %.*s",
			modes,
			user,
			group,
			ugswidth - pad,
			"",
			size,
			timestamp+4, timestamp+20,
			(int)sizeof(head->header.name),
			head->header.name);
	} else {
		printf("%s", head->header.name);
	}

	if (f_verbose) switch (head->header.linkflag) {
	case LF_SYMLINK:
		printf(" -> %s\n", head->header.linkname);
		break;

	case LF_LINK:
		printf(" link to %s\n", head->header.linkname);
		break;

	default:
		printf(" unknown file type '%c'\n", head->header.linkflag);
		break;

	case LF_OLDNORMAL:
	case LF_NORMAL:
	case LF_CHR:
	case LF_BLK:
	case LF_DIR:
	case LF_FIFO:
	case LF_CONTIG:
		putc('\n', stdout);
		break;
	} else {
		putc('\n', stdout);
	}

	/* FIXME: we don't print major/minor device numbers */
}

/*
 * Print a similar line when we make a directory automatically.
 */
void
pr_mkdir(pathname, length, mode)
	char *pathname;
	int length;
	int mode;
{
	char modes[11];

	if (f_verbose) {
		/* File type and modes */
		modes[0] = 'd';
		demode((unsigned)mode, modes+1);

		annofile(stdout, (char *)NULL);
		printf("%s %*s %.*s\n",
			modes,
			ugswidth+DATEWIDTH,
			"Creating directory:",
			length,
			pathname);
	}
}


/*
 * Skip over <size> bytes of data in records in the archive.
 */
void
skip_file(size)
	register long size;
{
	union record *x;

	while (size > 0) {
		x = findrec();
		if (x == NULL) {	/* Check it... */
			annorec(stderr, tar);
			fprintf(stderr, "Unexpected EOF on archive file\n");
			exit(EX_BADARCH);
		}
		userec(x);
		size -= RECORDSIZE;
	}
}


/*
 * Decode the mode string from a stat entry into a 9-char string and a null.
 */
void
demode(mode, string)
	register unsigned mode;
	register char *string;
{
	register unsigned mask;
	register char *rwx = "rwxrwxrwx";

	for (mask = 0400; mask != 0; mask >>= 1) {
		if (mode & mask)
			*string++ = *rwx++;
		else {
			*string++ = '-';
			rwx++;
		}
	}

	if (mode & S_ISUID){
		if (string[-7] == 'x')
			string[-7] = 's';
		else
			string[-7] = 'S';
	}
	if (mode & S_ISGID){
		if (string[-4] == 'x')
			string[-4] = 's';
		else
			string[-4] = 'S';
	}
	if (mode & S_ISVTX){
		if (string[-1] == 'x')
			string[-1] = 't';
		else
			string[-1] = 'T';
	}
	*string = '\0';
}
