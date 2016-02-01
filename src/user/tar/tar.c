/*
 * A public domain tar(1) program.
 * 
 * Written by John Gilmore, ihnp4!hoptoad!gnu, starting 25 Aug 85.
 *
 * @(#)tar.c 1.21 10/29/86 Public Domain - gnu
 */

#include <stdio.h>
#include <sys/types.h>		/* Needed for typedefs in tar.h */
#include <stdlib.h>
#include <string.h>

extern char	*strncpy();
extern char	*optarg;	/* Pointer to argument */
extern int	optind;		/* Global argv index from getopt */

/*
 * The following causes "tar.h" to produce definitions of all the
 * global variables, rather than just "extern" declarations of them.
 */
#define TAR_EXTERN /**/
#include "tar.h"

/*
 * We should use a conversion routine that does reasonable error
 * checking -- atoi doesn't.  For now, punt.  FIXME.
 */
#define intconv	atoi
extern int	getoldopt();
extern void	read_and();
extern void	list_archive();
extern void	extract_archive();
extern void	create_archive();

static FILE	*namef;		/* File to read names from */
static char	**n_argv;	/* Argv used by name routines */
static int	n_argc;	/* Argc used by name routines */
				/* They also use "optind" from getopt(). */

void	describe();
void options(int	argc, char **argv);
void name_init(int	argc, char **argv);
void addname(char *name);
	

/*
 * Main routine for tar.
 */
int main(argc, argv)
	int	argc;
	char	**argv;
{

	/* Uncomment this message in particularly buggy versions...
	fprintf(stderr,
	 "tar: You are running an experimental PD tar, maybe use /bin/tar.\n");
	 */

	tar = "tar";		/* Set program name */

	options(argc, argv);

	name_init(argc, argv);

	if (f_create) {
		if (f_extract || f_list) goto dupflags;
		create_archive();
	} else if (f_extract) {
		if (f_list) goto dupflags;
		read_and(extract_archive);
	} else if (f_list) {
		read_and(list_archive);
	} else {
dupflags:
		fprintf (stderr,
"tar: you must specify exactly one of the c, t, or x options\n");
		describe();
		exit(EX_ARGSBAD);
	}
	exit(0);
	return 0;
}


/*
 * Parse the options for tar.
 */
void 
options(argc, argv)
	int	argc;
	char	**argv;
{
	register int	c;		/* Option letter */

	/* Set default option values */
	blocking = 20;		/* From Makefile */
	ar_file = "archive.tar";		/* From Makefile */

	/* Parse options */
	while ((c = getoldopt(argc, argv, "b:BcdDf:hikmopstT:vxzZ")
		) != EOF) {
		switch (c) {

		case 'b':
			blocking = intconv(optarg);
			break;

		case 'B':
			f_reblock++;		/* For reading 4.2BSD pipes */
			break;

		case 'c':
			f_create++;
			break;

		case 'd':
			f_debug++;		/* Debugging code */
			break;			/* Yes, even with dbx */

		case 'D':
			f_sayblock++;		/* Print block #s for debug */
			break;			/* of bad tar archives */

		case 'f':
			ar_file = optarg;
			break;

		case 'h':
			f_follow_links++;	/* follow symbolic links */
			break;

		case 'i':
			f_ignorez++;		/* Ignore zero records (eofs) */
			/*
			 * This can't be the default, because Unix tar
			 * writes two records of zeros, then pads out the
			 * block with garbage.
			 */
			break;

		case 'k':			/* Don't overwrite files */
			f_keep++;
			break;

		case 'm':
			f_modified++;
			break;

		case 'o':			/* Generate old archive */
			f_oldarch++;
			break;

		case 'p':
			f_use_protection++;
			(void)umask(0);		/* Turn off kernel "help" */
			break;

		case 's':
			f_sorted_names++;	/* Names to extr are sorted */
			break;

		case 't':
			f_list++;
			break;

		case 'T':
			name_file = optarg;
			f_namefile++;
			break;

		case 'v':
			f_verbose++;
			break;

		case 'x':
			f_extract++;
			break;

		case 'z':		/* Easy to type */
		case 'Z':		/* Like the filename extension .Z */
			f_compress++;
			break;

		case '?':
			describe();
			exit(EX_ARGSBAD);

		}
	}

	blocksize = blocking * RECORDSIZE;
}


/* FIXME, describe tar options here */
void
describe()
{

	fputs("tar: valid options:\n\
-b N	blocking factor N (block size = Nx512 bytes)\n\
-B	reblock as we read (for reading 4.2BSD pipes)\n\
-c	create an archive\n\
-D	dump record number within archive with each message\n\
-f F	read/write archive from file or device F\n\
-h	don't dump symbolic links; dump the files they point to\n\
-i	ignore blocks of zeros in the archive, which normally mean EOF\n\
-k	keep existing files, don't overwrite them from the archive\n\
-m	don't extract file modified time\n\
-o	write an old V7 format archive, rather than ANSI [draft 6] format\n\
-p	do extract all protection information\n\
-s	list of names to extract is sorted to match the archive\n\
-t	list a table of contents of an archive\n\
-T F	get names to extract or create from file F\n\
-v	verbosely list what files we process\n\
-x	extract files from an archive\n\
-z or Z	run the archive through compress(1)\n\
", stderr);
}


/*
 * Set up to gather file names for tar.
 *
 * They can either come from stdin or from argv.
 */
void name_init(argc, argv)
	int	argc;
	char	**argv;
{

	if (f_namefile) {
		if (optind < argc) {
			fprintf(stderr, "tar: too many args with -T option\n");
			exit(EX_ARGSBAD);
		}
		if (!strcmp(name_file, "-")) {
			namef = stdin;
		} else {
			namef = fopen(name_file, "r");
			if (namef == NULL) {
				fprintf(stderr, "tar: ");
				perror(name_file);
				exit(EX_BADFILE);
			}
		}
	} else {
		/* Get file names from argv, after options. */
		n_argc = argc;
		n_argv = argv;
	}
}

/*
 * Get the next name from argv or the name file.
 *
 * Result is in static storage and can't be relied upon across two calls.
 */
char *
name_next()
{
	static char	buffer[NAMSIZ+2];	/* Holding pattern */
	register char	*p;
	register char	*q;

	if (namef == NULL) {
		/* Names come from argv, after options */
		if (optind < n_argc)
			return n_argv[optind++];
		return (char *)NULL;
	}
	p = fgets(buffer, NAMSIZ+1 /*nl*/, namef);
	if (p == NULL) return p;	/* End of file */
	q = p+strlen(p)-1;		/* Find the newline */
	*q-- = '\0';			/* Zap the newline */
	while (*q == '/')  *q-- = '\0';	/* Zap trailing slashes too */
	return p;
}


/*
 * Close the name file, if any.
 */
void name_close()
{

	if (namef != NULL && namef != stdin) fclose(namef);
}


/*
 * Gather names in a list for scanning.
 * Could hash them later if we really care.
 *
 * If the names are already sorted to match the archive, we just
 * read them one by one.  name_gather reads the first one, and it
 * is called by name_match as appropriate to read the next ones.
 * At EOF, the last name read is just left in the buffer.
 * This option lets users of small machines extract an arbitrary
 * number of files by doing "tar t" and editing down the list of files.
 */
void name_gather()
{
	register char *p;
	static struct name namebuf[1];	/* One-name buffer */

	if (f_sorted_names) {
		p = name_next();
		if (p) {
			namebuf->length = strlen(p);
			if (namebuf->length >= (int)sizeof namebuf->name) {
				fprintf(stderr, "Argument name too long: %s\n",
					p);
				namebuf->length = (sizeof namebuf->name) - 1;
			}
			strncpy(namebuf->name, p, namebuf->length);
			namebuf->next = (struct name *)NULL;
			namebuf->found = 0;
			namelist = namebuf;
			namelast = namelist;
		}
		return;
	}

	/* Non sorted names -- read them all in */
	while (NULL != (p = name_next())) {
		addname(p);
	}
}

/*
 * A name from the namelist has been found.
 * If it's just a list, 
 */
/*
 * Add a name to the namelist.
 */
void addname(name)
	char	*name;			/* pointer to name */
{
	register int	i;		/* Length of string */
	register struct name	*p;	/* Current struct pointer */

	i = strlen(name);
	/*NOSTRICT*/
	p = (struct name *)
		malloc((unsigned)(i + sizeof(struct name) - NAMSIZ));
	p->next = (struct name *)NULL;
	p->length = i;
	p->found = 0;
	strncpy(p->name, name, i);
	p->name[i] = '\0';	/* Null term */
	if (namelast) namelast->next = p;
	namelast = p;
	if (!namelist) namelist = p;
}


/*
 * Match a name from an archive, p, with a name from the namelist.
 *
 * FIXME: Allow regular expressions in the name list.
 */
int name_match(p)
	register char *p;
{
	register struct name	*nlp;
	register int		len;

again:
	if (0 == (nlp = namelist))	/* Empty namelist is easy */
		return 1;
	len = strlen(p);
	for (; nlp != 0; nlp = nlp->next) {
		if ( nlp->name[0] == p[0]	/* First chars match */
		 && nlp->length <= len		/* Archive len >= specified */
		 && (p[nlp->length] == '\0' || p[nlp->length] == '/')
						/* Full match on file/dirname */
		 && strncmp(p, nlp->name, nlp->length) == 0) /* Name compare */
		{
			nlp->found = 1;		/* Remember it matched */
			return 1;		/* We got a match */
		}
	}
	/*
	 * Filename from archive not found in namelist.
	 * If we have the whole namelist here, just return 0.
	 * Otherwise, read the next name in and compare it.
	 * If this was the last name, namelist->found will remain on.
	 * If not, we loop to compare the newly read name.
	 */
	if (f_sorted_names && namelist->found) {
		name_gather();		/* Read one more */
		if (!namelist->found) goto again;
	}
	return 0;
}


/*
 * Print the names of things in the namelist that were not matched.
 */
void names_notfound()
{
	register struct name	*nlp;
	register char		*p;

	for (nlp = namelist; nlp != 0; nlp = nlp->next) {
		if (!nlp->found) {
			fprintf(stderr, "tar: %s not found in archive\n",
				nlp->name);
		}
		/*
		 * We could free() the list, but the process is about
		 * to die anyway, so save some CPU time.  Amigas and
		 * other similarly broken software will need to waste
		 * the time, though.
		 */
#ifndef unix
		if (!f_sorted_names)
			free(nlp);
#endif //unix
	}
	namelist = (struct name *)NULL;
	namelast = (struct name *)NULL;

	if (f_sorted_names) {
		while (0 != (p = name_next()))
			fprintf(stderr, "tar: %s not found in archive\n", p);
	}
}
