/*
 * Create a tar archive.
 *
 * Written 25 Aug 1985 by John Gilmore, ihnp4!hoptoad!gnu.
 *
 * @(#)create.c 1.19 9/9/86 Public Domain - gnu
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/dir.h>

#ifdef USG
#include <sys/sysmacros.h>	/* major() and minor() defined here */
#endif

/*
 * V7 doesn't have a #define for this.
 */
#ifndef O_RDONLY
#define	O_RDONLY	0
#endif

#include "tar.h"
#include "stubs.h"

/*
 * If there are no symbolic links, there is no lstat().  Use stat().
 */
#ifndef S_IFLNK
#define lstat stat
#endif

extern char	*strcpy();
extern char	*strncpy();
extern int	errno;

union record *start_header();
void finish_header();
void finduname();
void findgname();
char *name_next();
void to_oct();
int dump_file(char *p);
void write_eot();

void
create_archive()
{
	register char	*p;

	open_archive(0);		/* Open for writing */

	while ((p = name_next())) {
		dump_file(p);
	}

	write_eot();
	close_archive();
	name_close();
}		

/*
 * Dump a single file.  If it's a directory, recurse.
 * Result is 1 for success, 0 for failure.
 */
int
dump_file(p)
	char	*p;			/* File name to dump */
{
	struct stat	statbuf[1];
	union record	*header;
	char type;

	/*
	 * Use stat if following (rather than dumping) 4.2BSD's
	 * symbolic links.  Otherwise, use lstat (which, on non-4.2
	 * systems, is #define'd to stat anyway.
	 */
	if (0 != f_follow_links? stat(p, statbuf): lstat(p, statbuf))
	{
badperror:
		perror(p);
badfile:
		errors++;
		return 0;
	}

	switch (statbuf->st_mode & S_IFMT) {

	case S_IFREG:			/* Regular file */
	{
		int	f;		/* File descriptor */
		int	bufsize, count;
		register long	sizeleft;
		register union record 	*start;

		/*
		 * Handle a regular file with multiple links.
		 *
		 * We maintain a list of all such files that we've written so
		 * far.  Any time we see another, we check the list and
		 * avoid dumping the data again if we've done it once already.
		 */
		if (statbuf->st_nlink > 1) {
			register struct link	*lp;

			/* First quick and dirty.  Hashing, etc later FIXME */
			for (lp = linklist; lp; lp = lp->next) {
				if (lp->ino == statbuf->st_ino &&
				    lp->dev == statbuf->st_dev) {
					/* We found a link. */
					statbuf->st_size = 0;
					header = start_header(p, statbuf);
					if (header == NULL) goto badfile;
					strcpy(header->header.linkname,
						lp->name);
					header->header.linkflag = LF_LINK;
					finish_header(header);
					if (f_verbose)
						annorec(stdout, (char *)NULL);
						printf("%s link to %s\n",
							p, lp->name);
			/* Maybe remove from list after all links found? */
		/* If so, have to compare names in case he dumps twice. */
			/* Later: I don't understand the above.  If she
			 * dumps the file twice, it would be BAD to dump
			 * it the second time as a link...  gnu 25Jul86
			 */
					/* FIXME */
					goto donefile;
				}
			}

			/* Not found.  Add it to the list. */
			lp = (struct link *) malloc( (unsigned)
				(strlen(p) + sizeof(struct link) - NAMSIZ));
			lp->ino = statbuf->st_ino;
			lp->dev = statbuf->st_dev;
			strcpy(lp->name, p);
			lp->next = linklist;
			linklist = lp;
		}

		sizeleft = statbuf->st_size;
		/* Don't bother opening empty, world readable files. */
		if (sizeleft > 0 || 0444 != (0444 & statbuf->st_mode)) {
			f = open(p, O_RDONLY);
			if (f < 0) goto badperror;
		} else {
			f = -1;
		}
		header = start_header(p, statbuf);
		if (header == NULL) goto badfile;
		finish_header(header);
		while (sizeleft > 0) {
			start = findrec();
			bufsize = endofrecs()->charptr - start->charptr;
			if (sizeleft < bufsize)
				bufsize = sizeleft;
			count = read(f, start->charptr, bufsize);
			if (count < 0) {
				annorec(stderr, tar);
				fprintf(stderr,
				  "read error at byte %ld, reading %d bytes, in file ",
					statbuf->st_size - sizeleft,
					bufsize);
				perror(p);	/* FIXME */
				goto padit;
			}
			sizeleft -= count;
			userec(start+(count-1)/RECORDSIZE);
			if (count == bufsize) continue;
			annorec(stderr, tar);
			fprintf(stderr,
	"%s: file shrunk by %ld bytes, padding with zeros.\n",
				p, sizeleft);
			goto padit;		/* Short read */
		}
		if (f >= 0)
			(void)close(f);

		/* Clear last block garbage to zeros, FIXME */

		if (f_verbose) {
			annorec(stdout, (char *)NULL);
			printf("%s\n", p);
		}
	donefile:
		break;

		/*
		 * File shrunk or gave error, pad out tape to match
		 * the size we specified in the header.
		 */
	padit:
		abort();
	}

#ifdef S_IFLNK
	case S_IFLNK:			/* Symbolic link */
	{
		int size;

		statbuf->st_size = 0;		/* Force 0 size on symlink */
		header = start_header(p, statbuf);
		if (header == NULL) goto badfile;
		size = readlink(p, header->header.linkname, NAMSIZ);
		if (size < 0) goto badperror;
		if (size == NAMSIZ) {
			annorec(stderr, tar);
			fprintf(stderr,
				"%s: symbolic link too long\n", p);
			break;
		}
		header->header.linkname[size] = '\0';
		header->header.linkflag = LF_SYMLINK;
		finish_header(header);		/* Nothing more to do to it */
		if (f_verbose) {
			annorec(stdout, (char *)NULL);
			printf("%s\n", p);
		}
	}
		break;
#endif

	case S_IFDIR:			/* Directory */
	{
		register DIR *dirp;
		register struct direct *d;
		char namebuf[NAMSIZ+2];
		register int len;

		/* Build new prototype name */
		strncpy(namebuf, p, sizeof (namebuf));
		len = strlen(namebuf);
		while (len >= 1 && '/' == namebuf[len-1]) 
			len--;			/* Delete trailing slashes */
		namebuf[len++] = '/';		/* Now add exactly one back */

		/*
		 * Output directory header record with permissions
		 * FIXME, do this AFTER files, to avoid R/O dir problems?
		 * If Unix Std format, don't put / on end of dir name
		 * If old archive format, don't write record at all.
		 */
		if (!f_oldarch) {
			statbuf->st_size = 0;	/* Force 0 size on dir */
			/*
			 * If people could really read standard archives,
			 * this should be:		(FIXME)
			header = start_header(f_standard? p: namebuf, statbuf);
			 * but since they'd interpret LF_DIR records as
			 * regular files, we'd better put the / on the name.
			 */
			header = start_header(namebuf, statbuf);
			if (header == NULL)
				goto badfile;	/* eg name too long */
			if (f_standard) {
				header->header.linkflag = LF_DIR;
			}
			finish_header(header);	/* Done with directory header */
		}
		if (f_verbose) {
			annorec(stdout, (char *)NULL);
			printf("%s\n", p);
		}

		/* Hack to remove "./" from the front of all the file names */
		if (len == 2 && namebuf[0] == '.') {
			len = 0;
		}

		/* Now output all the files in the directory */
		errno = 0;
		dirp = opendir(p);
		if (!dirp) {
			if (errno) {
				perror (p);
			} else {
				annorec(stderr, tar);
				fprintf(stderr, "%s: error opening directory",
					p);
			}
			break;
		}
		
		/* Should speed this up by cd-ing into the dir, FIXME */
		while (NULL != (d=readdir(dirp))) {
			/* Skip . and .. */
			if (d->d_name[0] == '.') {
				if (d->d_name[1] == '\0') continue;
				if (d->d_name[1] == '.') {
					if (d->d_name[2] == '\0') continue;
				}
			}
			if (d->d_namlen + len >= NAMSIZ) {
				annorec(stderr, tar);
				fprintf(stderr, "%s%s: name too long\n", 
					namebuf, d->d_name);
				continue;
			}
			strcpy(namebuf+len, d->d_name);
			dump_file(namebuf);
		}

		closedir(dirp);
	}
		break;

	case S_IFCHR:			/* Character special file */
		type = LF_CHR;
		goto easy;

	case S_IFBLK:			/* Block     special file */
		type = LF_BLK;
		goto easy;

#ifdef S_IFIFO
	case S_IFIFO:			/* Fifo      special file */
		type = LF_FIFO;
#endif //S_IFIFO

	easy:
		if (!f_standard) goto unknown;

		statbuf->st_size = 0;		/* Force 0 size */
		header = start_header(p, statbuf);
		if (header == NULL) goto badfile;	/* eg name too long */

		header->header.linkflag = type;
		if (type != LF_FIFO) {
			to_oct((long) major(statbuf->st_rdev), 8,
				header->header.devmajor);
			to_oct((long) minor(statbuf->st_rdev), 8,
				header->header.devminor);
		}

		finish_header(header);
		if (f_verbose) {
			annorec(stdout, (char *)NULL);
			printf("%s\n", p);
		}
		break;

	default:
	unknown:
		annorec(stderr, tar);
		fprintf(stderr,
			"%s: Unknown file type; file ignored.\n", p);
		break;
	}

	return 1;			/* Success */
}


/*
 * Make a header block for the file  name  whose stat info is  st .
 * Return header pointer for success, NULL if the name is too long.
 */
union record *
start_header(name, st)
	char	*name;
	register struct stat *st;
{
	register union record *header;

	header = (union record *) findrec();
	bzero(header->charptr, sizeof(*header)); /* XXX speed up */
	strcpy(header->header.name, name);
	if (header->header.name[NAMSIZ-1]) {
		annorec(stderr, tar);
		fprintf(stderr, "%s: name too long\n", name);
		return NULL;
	}
	to_oct((long) (st->st_mode & ~S_IFMT),
					8,  header->header.mode);
	to_oct((long) st->st_uid,	8,  header->header.uid);
	to_oct((long) st->st_gid,	8,  header->header.gid);
	to_oct((long) st->st_size,	1+12, header->header.size);
	to_oct((long) st->st_mtime,	1+12, header->header.mtime);
	/* header->header.linkflag is left as null */

#ifndef NONAMES
	/* Fill in new Unix Standard fields if desired. */
	if (f_standard) {
		header->header.linkflag = LF_NORMAL;	/* New default */
		strcpy(header->header.magic, TMAGIC);	/* Mark as Unix Std */
		finduname(header->header.uname, st->st_uid);
		findgname(header->header.gname, st->st_gid);
	}
#endif
	return header;
}

/* 
 * Finish off a filled-in header block and write it out.
 */
void
finish_header(header)
	register union record *header;
{
	register int	i, sum;
	register char	*p;

	bcopy(CHKBLANKS, header->header.chksum, sizeof(header->header.chksum));

	sum = 0;
	p = header->charptr;
	for (i = sizeof(*header); --i >= 0; ) {
		/*
		 * We can't use unsigned char here because of old compilers,
		 * e.g. V7.
		 */
		sum += 0xFF & *p++;
	}

	/*
	 * Fill in the checksum field.  It's formatted differently
	 * from the other fields:  it has [6] digits, a null, then a
	 * space -- rather than digits, a space, then a null.
	 * We use to_oct then write the null in over to_oct's space.
	 * The final space is already there, from checksumming, and
	 * to_oct doesn't modify it.
	 *
	 * This is a fast way to do:
	 * (void) sprintf(header->header.chksum, "%6o", sum);
	 */
	to_oct((long) sum,	8,  header->header.chksum);
	header->header.chksum[6] = '\0';	/* Zap the space */

	userec(header);
	return;
}


/*
 * Quick and dirty octal conversion.
 * Converts long "value" into a "digs"-digit field at "where",
 * including a trailing space and room for a null.  "digs"==3 means
 * 1 digit, a space, and room for a null.
 *
 * We assume the trailing null is already there and don't fill it in.
 * This fact is used by start_header and finish_header, so don't change it!
 *
 * This should be equivalent to:
 *	(void) sprintf(where, "%*lo ", digs-2, value);
 * except that sprintf fills in the trailing null and we don't.
 */
void
to_oct(value, digs, where)
	register long	value;
	register int	digs;
	register char	*where;
{
	
	--digs;				/* Trailing null slot is left alone */
	where[--digs] = ' ';		/* Put in the space, though */

	/* Produce the digits -- at least one */
	do {
		where[--digs] = '0' + (value & 7);	/* one octal digit */
		value >>= 3;
	} while (digs > 0 && value != 0);

	/* Leading spaces, if necessary */
	while (digs > 0)
		where[--digs] = ' ';

}


/*
 * Write the EOT block(s).
 */
void write_eot()
{
	union record *p;

	p = findrec();
	bzero(p->charptr, RECORDSIZE);
	userec(p);
	/* FIXME, only one EOT block should be needed. */
	p = findrec();
	bzero(p->charptr, RECORDSIZE);
	userec(p);
}
