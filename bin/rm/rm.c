/*-
 * Copyright (c) 1990, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * @(#) Copyright (c) 1990, 1993, 1994 The Regents of the University of California.  All rights reserved.
 * @(#)rm.c	8.5 (Berkeley) 4/18/94
 * $FreeBSD: src/bin/rm/rm.c,v 1.29.2.5 2002/07/12 07:25:48 tjr Exp $
 */

#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/param.h>
#include <sys/mount.h>
#include <sys/ioctl.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <fts.h>
#include <grp.h>
#include <pwd.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

const char *user_from_uid(uid_t uid, int noname);
const char *group_from_gid(gid_t gid, int noname);

static int dflag, eval, fflag, iflag, Pflag, vflag, Wflag, stdin_ok;
static int rflag, Iflag, xflag;
static uid_t uid;
static volatile sig_atomic_t info;

static int	check(const char *, const char *, struct stat *);
static int	check2(char **);
static void	checkdot(char **);
static void	rm_file(char **);
static int	rm_overwrite(const char *, struct stat *);
static void	rm_tree(char **);
static void	usage(void);

/*
 * rm --
 *	This rm is different from historic rm's, but is expected to match
 *	POSIX 1003.2 behavior.  The most visible difference is that -f
 *	has two specific effects now, ignore non-existent files and force
 * 	file removal.
 */
int
main(int argc, char *argv[])
{
	int ch;
	const char *p;
	pid_t tty_pgrp;

	/*
	 * Test for the special case where the utility is called as
	 * "unlink", for which the functionality provided is greatly
	 * simplified.
	 */
	if ((p = strrchr(argv[0], '/')) == NULL)
		p = argv[0];
	else
		++p;
	if (strcmp(p, "unlink") == 0) {
		while (getopt(argc, argv, "") != -1)
			usage();
		argc -= optind;
		argv += optind;
		if (argc != 1)
			usage();
		rm_file(&argv[0]);
		exit(eval);
	}

	Pflag = rflag = xflag = 0;
	while ((ch = getopt(argc, argv, "dfiIPRrvWx")) != -1) {
		switch(ch) {
		case 'd':
			dflag = 1;
			break;
		case 'f':
			fflag = 1;
			iflag = 0;
			break;
		case 'i':
			fflag = 0;
			iflag = 1;
			break;
		case 'I':
			/*
			 * The -I flag is intended to be generally aliasable
			 * in /etc/csh.cshrc.  We apply it only to foreground
			 * processes.
			 */
			if (ioctl(0, TIOCGPGRP, &tty_pgrp) == 0) {
				if (tty_pgrp == getpgrp())
					Iflag = 1;
			}
			break;
		case 'P':
			Pflag = 1;
			break;
		case 'R':
		case 'r':			/* Compatibility. */
			rflag = 1;
			break;
		case 'v':
			vflag = 1;
			break;
		case 'W':
			Wflag = 1;
			break;
		case 'x':
			xflag = 1;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc < 1) {
		if (fflag)
			return 0;
		usage();
	}

	checkdot(argv);
	uid = geteuid();
	
	if (*argv) {
		stdin_ok = isatty(STDIN_FILENO);

		if (Iflag && !iflag) {
			if (check2(argv) == 0)
				exit (1);
		}
		if (rflag)
			rm_tree(argv);
		else
			rm_file(argv);
	}

	exit (eval);
}

static void
rm_tree(char **argv)
{
	FTS *fts;
	FTSENT *p;
	int needstat;
	int flags;
	int rval;

	/*
	 * Remove a file hierarchy.  If forcing removal (-f), or interactive
	 * (-i) or can't ask anyway (stdin_ok), don't stat the file.
	 */
	needstat = !uid || (!fflag && !iflag && stdin_ok);

	/*
	 * If the -i option is specified, the user can skip on the pre-order
	 * visit.  The fts_number field flags skipped directories.
	 */
#define	SKIPPED	1

	flags = FTS_PHYSICAL;
	if (!needstat)
		flags |= FTS_NOSTAT;
	if (Wflag)
		flags |= FTS_WHITEOUT;
	if (xflag)
		flags |= FTS_XDEV;
	if ((fts = fts_open(argv, flags, NULL)) == NULL) {
		if (fflag && errno == ENOENT)
			return;
		err(1, "fts_open");
	}
	while ((p = fts_read(fts)) != NULL) {
		switch (p->fts_info) {
		case FTS_DNR:
			if (!fflag || p->fts_errno != ENOENT) {
				warnx("%s: %s",
				    p->fts_path, strerror(p->fts_errno));
				eval = 1;
			}
			continue;
		case FTS_ERR:
			errx(1, "%s: %s", p->fts_path, strerror(p->fts_errno));
		case FTS_NS:
		       /*
			* Assume that since fts_read() couldn't stat
			* the file, it can't be unlinked.
			*/
			if (!needstat)
				break;
			if (!fflag || p->fts_errno != ENOENT) {
				warnx("%s: %s",
				    p->fts_path, strerror(p->fts_errno));
				eval = 1;
			}
			continue;
		case FTS_D:
			/* Pre-order: give user chance to skip. */
			if (!fflag && !check(p->fts_path, p->fts_accpath,
			    p->fts_statp)) {
				fts_set(fts, p, FTS_SKIP);
				p->fts_number = SKIPPED;
			}
			continue;
		case FTS_DP:
			/* Post-order: see if user skipped. */
			if (p->fts_number == SKIPPED)
				continue;
			break;
		default:
			if (!fflag &&
			    !check(p->fts_path, p->fts_accpath, p->fts_statp))
				continue;
		}

		if (info) {
			info = 0;
			fprintf(stderr, "Currently removing: %s\n", p->fts_path);
		}

		rval = 0;

		if (rval == 0) {
			/*
			 * If we can't read or search the directory, may still be
			 * able to remove it.  Don't print out the un{read,search}able
			 * message unless the remove fails.
			 */
			switch (p->fts_info) {
			case FTS_DP:
			case FTS_DNR:
				rval = rmdir(p->fts_accpath);
				if (rval == 0 || (fflag && errno == ENOENT)) {
					if (rval == 0 && vflag)
						printf("%s\n",
						    p->fts_path);
					continue;
				}
				break;

			case FTS_NS:
			/*
			 * Assume that since fts_read() couldn't stat
			 * the file, it can't be unlinked.
			 */
				if (fflag)
					continue;
				/* FALLTHROUGH */
			default:
				if (Pflag)
					if (!rm_overwrite(p->fts_accpath, NULL))
						continue;
				rval = unlink(p->fts_accpath);
				if (rval == 0 || (fflag && errno == ENOENT)) {
					if (rval == 0 && vflag)
						printf("%s\n",
						    p->fts_path);
					continue;
				}
			}
		}
err:
		warn("%s", p->fts_path);
		eval = 1;
	}
	if (errno)
		err(1, "fts_read");
	fts_close(fts);
}

static void
rm_file(char **argv)
{
	struct stat sb;
	int rval;
	const char *f;

	/*
	 * Remove a file.  POSIX 1003.2 states that, by default, attempting
	 * to remove a directory is an error, so must always stat the file.
	 */
	while ((f = *argv++) != NULL) {
		if (info) {
			info = 0;
			fprintf(stderr, "Currently removing: %s\n", f);
		}

		/* Assume if can't stat the file, can't unlink it. */
		if (lstat(f, &sb)) {
			if (Wflag) {
				sb.st_mode = S_IWUSR|S_IRUSR;
			} else {
				if (!fflag || errno != ENOENT) {
					warn("%s", f);
					eval = 1;
				}
				continue;
			}
		} else if (Wflag) {
			warnx("%s: %s", f, strerror(EEXIST));
			eval = 1;
			continue;
		}

		if (S_ISDIR(sb.st_mode) && !dflag) {
			warnx("%s: is a directory", f);
			eval = 1;
			continue;
		}
		if (!fflag && !check(f, f, &sb))
			continue;
		rval = 0;
		if (rval == 0) {
			if (S_ISDIR(sb.st_mode))
				rval = rmdir(f);
			else {
				if (Pflag)
					if (!rm_overwrite(f, &sb))
						continue;
				rval = unlink(f);
			}
		}
		if (rval && (!fflag || errno != ENOENT)) {
			warn("%s", f);
			eval = 1;
		}
		if (vflag && rval == 0)
			printf("%s\n", f);
	}
}

/*
 * rm_overwrite --
 *	Overwrite the file 3 times with varying bit patterns.
 *
 * XXX
 * This is a cheap way to *really* delete files.  Note that only regular
 * files are deleted, directories (and therefore names) will remain.
 * Also, this assumes a fixed-block filesystem (like FFS, or a V7 or a
 * System V filesystem).  In a logging filesystem, you'll have to have
 * kernel support.
 */
static int 
rm_overwrite(const char *file, struct stat *sbp)
{
	struct stat sb;
	struct statfs fsb;
	off_t len;
	int bsize, fd, wlen;
	char *buf = NULL;

	fd = -1;
	if (sbp == NULL) {
		if (lstat(file, &sb))
			goto err;
		sbp = &sb;
	}
	if (!S_ISREG(sbp->st_mode)) {
		warnx("%s: cannot overwrite a non-regular file", file);
		return (1);
	}
	if (sbp->st_nlink > 1) {
		warnx("%s (inode %ju): not overwritten due to multiple links",
		      file, (uintmax_t)sbp->st_ino);
		return (0);
	}
	if ((fd = open(file, O_WRONLY)) == -1)
		goto err;
	if (fstatfs(fd, &fsb) == -1)
		goto err;
	bsize = MAX(fsb.f_bsize, 1024);
	if ((buf = malloc(bsize)) == NULL)
		err(1, "%s malloc failed", file);

#define	PASS(byte) {							\
	memset(buf, byte, bsize);					\
	for (len = sbp->st_size; len > 0; len -= wlen) {		\
		wlen = len < bsize ? len : bsize;			\
		if (write(fd, buf, wlen) != wlen)			\
			goto err;					\
	}								\
}
	PASS(0xff);
	if (fsync(fd) || lseek(fd, (off_t)0, SEEK_SET))
		goto err;
	PASS(0x00);
	if (fsync(fd) || lseek(fd, (off_t)0, SEEK_SET))
		goto err;
	PASS(0xff);
	if (!fsync(fd) && !close(fd)) {
		free(buf);
		return (1);
	}

err:	eval = 1;
	if (buf)
		free(buf);
	if (fd != -1)
		close(fd);
	warn("%s", file);
	return (0);
}


static int
check(const char *path, const char *name, struct stat *sp)
{
	static int perm_answer = -1;
	struct choice {
		int ch;
		const char *str;
		int res;
		int perm;
	} *choice, choices[] = {
		{ 'y', "yes"   , 1, 0 },
		{ 'n', "no"    , 0, 0 },
		{ 'a', "always", 1, 1 },
		{ 'v', "never" , 0, 1 },
		{ 0, NULL, 0, 0 }
	};
	char modep[15];

	if (perm_answer != -1)
		return (perm_answer);

	/* Check -i first. */
	if (iflag)
		fprintf(stderr, "remove %s? ", path);
	else {
		/*
		 * If it's not a symbolic link and it's unwritable and we're
		 * talking to a terminal, ask.  Symbolic links are excluded
		 * because their permissions are meaningless.  Check stdin_ok
		 * first because we may not have stat'ed the file.
		 * Also skip this check if the -P option was specified because
	         * we will not be able to overwrite file contents and will
	         * barf later.
		 */
		if (!stdin_ok || S_ISLNK(sp->st_mode) || !access(name, W_OK) ||
		    errno != EACCES)
			return (1);
		strmode(sp->st_mode, modep);
		fprintf(stderr, "override %s%s%s:%s for '%s'? ",
		    modep + 1, modep[9] == ' ' ? "" : " ",
		    user_from_uid(sp->st_uid, 0),
		    group_from_gid(sp->st_gid, 0),
		    path);
	}
	fflush(stderr);

	for (;;) {
		char *answer = NULL;
		size_t n = 0;
		size_t len;

		len = getline(&answer, &n, stdin);
		/* clearerr(stdin); */
		if (len == -1) {
			free(answer);
			return (0);
		}
		if (answer[len - 1] == '\n')
			len--;
		if (len == 0) {
			free(answer);
			continue;
		}

		for (choice = choices; choice->str != NULL; choice++) {
			if (len == 1 && choice->ch == answer[0]) {
				free(answer);
				goto valid_choice;
			}
			if (strncasecmp(answer, choice->str, len) == 0) {
				free(answer);
				goto valid_choice;
			}
		}

		fprintf(stderr, "invalid answer, try again (y/n/a/v): ");

		free(answer);
	}

valid_choice:
	if (choice->perm)
		perm_answer = choice->res;
	return (choice->res);
}

static int
check2(char **argv)
{
	struct stat st;
	int first;
	int ch;
	int fcount = 0;
	int dcount = 0;
	int i;
	const char *dname = NULL;

	for (i = 0; argv[i]; ++i) {
		if (lstat(argv[i], &st) == 0) {
			if (S_ISDIR(st.st_mode)) {
				++dcount;
				dname = argv[i];    /* only used if 1 dir */
			} else {
				++fcount;
			}
		}
	}
	first = 0;
	while (first != 'n' && first != 'N' && first != 'y' && first != 'Y') {
		if (dcount && rflag) {
			fprintf(stderr, "recursively remove");
			if (dcount == 1)
				fprintf(stderr, " %s", dname);
			else
				fprintf(stderr, " %d dirs", dcount);
			if (fcount == 1)
				fprintf(stderr, " and 1 file");
			else if (fcount > 1)
				fprintf(stderr, " and %d files", fcount);
		} else if (dcount + fcount > 3) {
			fprintf(stderr, "remove %d files", dcount + fcount);
		} else {
			return(1);
		}
		fprintf(stderr, "? ");
		fflush(stderr);

		first = ch = getchar();
		while (ch != '\n' && ch != EOF)
			ch = getchar();
		if (ch == EOF)
			break;
	}
	return (first == 'y' || first == 'Y');
}

#define ISDOT(a)	((a)[0] == '.' && (!(a)[1] || ((a)[1] == '.' && !(a)[2])))
static void
checkdot(char **argv)
{
	char *p, **save, **t;
	int complained;

	complained = 0;
	for (t = argv; *t;) {
		if ((p = strrchr(*t, '/')) != NULL)
			++p;
		else
			p = *t;
		if (ISDOT(p)) {
			if (!complained++)
				warnx("\".\" and \"..\" may not be removed");
			eval = 1;
			for (save = t; (t[0] = t[1]) != NULL; ++t)
				continue;
			t = save;
		} else
			++t;
	}
}

static void
usage(void)
{

	fprintf(stderr, "%s\n%s\n",
	    "usage: rm [-f | -i] [-dIPRrvWx] file ...",
	    "       unlink file");
	exit(EX_USAGE);
}
