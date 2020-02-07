/*
 * Extract files from a tar archive.
 *
 * Written 19 Nov 1985 by John Gilmore, ihnp4!hoptoad!gnu.
 *
 * @(#) extract.c 1.17 86/10/29 Public Domain - gnu
 */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef BSD42
#include <sys/file.h>
#endif

#ifdef USG
#include <fcntl.h>
#endif

#include "stubs.h"

extern int errno;			/* From libc.a */
extern char *index(const char *s, int c);		/* From libc.a or port.c */

#include "tar.h"

extern union record *head;		/* Points to current tape header */
extern struct stat hstat[1];		/* Stat struct corresponding */

extern void print_header();
extern void skip_file();
extern void pr_mkdir();

int make_dirs();			/* Makes required directories */

time_t now = 0;				/* Current time */

/*
 * Extract a file from the archive.
 */
void
extract_archive()
{
	register char *data;
	int fd, check, namelen, written;
	long size;
	time_t acc_upd_times[2];
	int	standard;		/* Is header standard? */

	saverec(&head);			/* Make sure it sticks around */
	userec(head);			/* And go past it in the archive */
	decode_header(head, hstat, &standard, 1);	/* Snarf fields */

	/* Print the record from 'head' and 'hstat' */
	if (f_verbose)
		print_header();

	switch (head->header.linkflag) {

	default:
		annofile(stderr, tar);
		fprintf(stderr, "Unknown file type %d for %s\n",
			head->header.linkflag, head->header.name);
		/* FALL THRU */

	case LF_OLDNORMAL:
	case LF_NORMAL:
		/*
		 * Appears to be a file.
		 * See if it's really a directory.
		 */
		namelen = strlen(head->header.name)-1;
		if (head->header.name[namelen] == '/')
			goto really_dir;

		/* FIXME, deal with protection issues */
		/* FIXME, f_keep doesn't work on V7, st_mode loses too */
	again_file:
		fd = open(head->header.name,
			f_keep?
			O_WRONLY|O_APPEND|O_CREAT|O_EXCL:
			O_WRONLY|O_APPEND|O_CREAT|O_TRUNC,
			hstat->st_mode);
		if (fd < 0) {
			if (make_dirs(head->header.name))
				goto again_file;
			annofile(stderr, tar);
			fprintf(stderr, "Could not make file ");
			perror(head->header.name);
			skip_file((long)hstat->st_size);
			goto quit;
		}

		for (size = hstat->st_size;
		     size > 0;
		     size -= written) {
			/*
			 * Locate data, determine max length
			 * writeable, write it, record that
			 * we have used the data, then check
			 * if the write worked.
			 */
			data = findrec()->charptr;
			written = endofrecs()->charptr - data;
			if (written > size) written = size;
			errno = 0;
			check = write (fd, data, written);
			/*
			 * The following is in violation of strict
			 * typing, since the arg to userec
			 * should be a struct rec *.  FIXME.
			 */
			userec(data + written - 1);
			if (check == written) continue;
			/*
			 * Error in writing to file.
			 * Print it, skip to next file in archive.
			 */
			annofile(stderr, tar);
			fprintf(stderr,
	"Tried to write %d bytes to file, could only write %d:\n",
				written, check);
			perror(head->header.name);
			(void) close(fd);
			skip_file((long)(size - written));
			goto quit;
		}

		check = close(fd);
		if (check < 0) {
			annofile(stderr, tar);
			fprintf(stderr, "Error while closing ");
			perror(head->header.name);
		}
		
		/* FIXME, deal with uid/gid/mtimes/suid */

		/*
		 * Set the modified time of the file.
		 * 
		 * Note that we set the accessed time to "now", which
		 * is really "the time we started extracting files".
		 */
		if (!f_modified) {
			if (!now)
				now = time((time_t *)0); /* Just do it once */
			acc_upd_times[0] = now;	         /* Accessed now */
			acc_upd_times[1] = hstat->st_mtime; /* Mod'd */
			if (utime(head->header.name, acc_upd_times) < 0) {
				annofile(stderr, tar);
				perror(head->header.name);
			}
		}

		/*
		 * If '-p' is not set, OR if the file has pretty normal
		 * mode bits, we can skip the chmod and save a sys call.
		 * This works because we did umask(0) if -p is set, so
		 * the open() that created the file will have set the modes
		 * properly.  
		 * FIXME: I don't know what open() does w/UID/GID/SVTX bits.
		 * However, if we've done a chown(), they got reset.
		 */
		if (f_use_protection
		    && (hstat->st_mode & (S_ISUID|S_ISGID|S_ISVTX))) {
			if (chmod(head->header.name, (int)hstat->st_mode) < 0) {
				annofile(stderr, tar);
				perror(head->header.name);
			}
		}

	quit:
		break;

	case LF_LINK:
	again_link:
		check = link (head->header.linkname,
			      head->header.name);
		/* FIXME, don't worry uid, gid, etc... */
		if (check == 0)
			break;
		if (make_dirs(head->header.linkname))
			goto again_link;
		annofile(stderr, tar);
		fprintf(stderr, "Could not link %s to ",
			head->header.name);
		perror(head->header.linkname);
		break;

#ifdef S_IFLNK
	case LF_SYMLINK:
	again_symlink:
		check = symlink(head->header.linkname,
			        head->header.name);
		/* FIXME, don't worry uid, gid, etc... */
		if (check == 0)
			break;
		if (make_dirs(head->header.linkname))
			goto again_symlink;
		annofile(stderr, tar);
		fprintf(stderr, "Could not create symlink ");
		perror(head->header.linkname);
		break;
#endif

	case LF_CHR:
		hstat->st_mode |= S_IFCHR;
		goto make_node;

	case LF_BLK:
		hstat->st_mode |= S_IFBLK;
	make_node:
		check = mknod(head->header.name, (int) hstat->st_mode,
			(int) hstat->st_dev);
		if (check != 0) {
			if (make_dirs(head->header.name))
				goto make_node;
			annofile(stderr, tar);
			fprintf(stderr, "Could not make special file ");
			perror(head->header.name);
			break;
		};
		break;

	case LF_DIR:
		/* Check for trailing / */
		namelen = strlen(head->header.name)-1;
	really_dir:
		while (namelen && head->header.name[namelen] == '/')
			head->header.name[namelen--] = '\0';	/* Zap / */
		
		/* FIXME, deal with umask */
	again_dir:
		check = mkdir(head->header.name, (int)hstat->st_mode);
		if (check != 0) {
			if (make_dirs(head->header.name))
				goto again_dir;
			annofile(stderr, tar);
			fprintf(stderr, "Could not make directory ");
			perror(head->header.name);
			break;
		}
		
		/* FIXME, deal with uid/gid */
		/* FIXME, Remember timestamps for after files created? */
		break;

	case LF_FIFO:
		abort();	/* FIXME */
		break;

	}

	/* We don't need to save it any longer. */
	saverec((union record **) 0);	/* Unsave it */
}

/*
 * After a file/link/symlink/dir creation has failed, see if
 * it's because some required directory was not present, and if
 * so, create all required dirs.
 */
int
make_dirs(pathname)
	char *pathname;
{
	char *p;			/* Points into path */
	int madeone = 0;		/* Did we do anything yet? */
	int save_errno = errno;		/* Remember caller's errno */
	int check;

	if (errno != ENOENT)
		return 0;		/* Not our problem */

	for (p = index(pathname, '/'); p != NULL; p = index(p+1, '/')) {
		/* Avoid mkdir of empty string, if leading or double '/' */
		if (p == pathname || p[-1] == '/')
			continue;
		/* Avoid mkdir where last part of path is '.' */
		if (p[-1] == '.' && (p == pathname+1 || p[-2] == '/'))
			continue;
		*p = 0;				/* Truncate the path there */
		check = mkdir (pathname, 0777);	/* Try to create it as a dir */
		*p = '/';
		if (check == 0) {
			/* FIXME chown, chgrp it same as file being created */
			/* FIXME, show mode as modified by current umask */
			pr_mkdir(pathname, p-pathname, 0777);
			madeone++;		/* Remember if we made one */
			continue;
		}
		if (errno == EEXIST)		/* Directory already exists */
			continue;
		/*
		 * Some other error in the mkdir.  We return to the caller.
		 */
		break;
	}

	errno = save_errno;		/* Restore caller's errno */
	return madeone;			/* Tell them to retry if we made one */
}
