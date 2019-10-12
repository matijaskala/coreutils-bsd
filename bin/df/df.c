/*	$NetBSD: df.c,v 1.93 2018/08/26 23:34:52 sevan Exp $ */

/*
 * Copyright (c) 1980, 1990, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
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
 */

#include <sys/cdefs.h>
#ifndef lint
__COPYRIGHT(
"@(#) Copyright (c) 1980, 1990, 1993, 1994\
 The Regents of the University of California.  All rights reserved.");
#endif /* not lint */

#ifndef lint
#if 0
static char sccsid[] = "@(#)df.c	8.7 (Berkeley) 4/2/94";
#else
__RCSID("$NetBSD: df.c,v 1.93 2018/08/26 23:34:52 sevan Exp $");
#endif
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/mount.h>

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <locale.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mntent.h>

char *strspct(char *buf, size_t bufsiz, intmax_t numerator, intmax_t denominator, size_t digits);

static struct mntent	*getmntptr(const char *, size_t, struct mntent *);
static void	 prtstat(struct mntent *, struct statvfs *, int);
static int	 selected(const char *);
static void	 maketypelist(char *);
static void usage(void);
static void	 prthumanval(int64_t, const char *);
static void	 prthuman(struct statvfs *, int64_t, int64_t);

static int	 gflag, hflag, iflag, Pflag;
static long	 usize;
static char	**typelist;

struct strs {
	char *str;
	struct strs *next;
};

static void strs_append(struct strs **strs, char *str) {
	struct strs *r = malloc(sizeof *r);
	r->next = *strs;
	r->str = strdup(str);
	*strs = r;
}

int
main(int argc, char *argv[])
{
	struct mntent *mntbuf, *e;
	long mntsize;
	int ch, i, j, maxwidth, width;
	struct strs *strs;
	FILE *f;

	setprogname(argv[0]);
	(void)setlocale(LC_ALL, "");

	while ((ch = getopt(argc, argv, "GghikmPt:")) != -1)
		switch (ch) {
		case 'g':
			hflag = 0;
			usize = 1024 * 1024 * 1024;
			break;
		case 'G':
			gflag = 1;
			break;
		case 'h':
			hflag = 1;
			usize = 0;
			break;
		case 'i':
			iflag = 1;
			break;
		case 'k':
			hflag = 0;
			usize = 1024;
			break;
		case 'm':
			hflag = 0;
			usize = 1024 * 1024;
			break;
		case 'P':
			Pflag = 1;
			break;
		case 't':
			if (typelist != NULL)
				errx(EXIT_FAILURE,
				    "only one -t option may be specified.");
			maketypelist(optarg);
			break;
		case '?':
		default:
			usage();
		}

	if (gflag && (Pflag || iflag))
		errx(EXIT_FAILURE,
		    "only one of -G and -P or -i may be specified");
	if (Pflag && iflag)
		errx(EXIT_FAILURE,
		    "only one of -P and -i may be specified");
#if 0
	/*
	 * The block size cannot be checked until after getbsize() is called.
	 */
	if (Pflag && (hflag || (usize != 1024 && usize != 512)))
		errx(EXIT_FAILURE,
		    "non-standard block size incompatible with -P");
#endif
	argc -= optind;
	argv += optind;

	i = 8;
	mntsize = 0;
	mntbuf = malloc(i * sizeof *mntbuf);
	strs = NULL;
	f = setmntent("/etc/mtab", "r");
	while ((e = getmntent(f))) {
		if (mntsize == i)
			mntbuf = realloc(mntbuf, (i *= 2) * sizeof *mntbuf);
		mntbuf[mntsize] = *e;
		strs_append(&strs, e->mnt_fsname);
		mntbuf[mntsize].mnt_fsname = strs->str;
		strs_append(&strs, e->mnt_dir);
		mntbuf[mntsize].mnt_dir = strs->str;
		strs_append(&strs, e->mnt_type);
		mntbuf[mntsize].mnt_type = strs->str;
		strs_append(&strs, e->mnt_opts);
		mntbuf[mntsize].mnt_opts = strs->str;
		mntsize++;
	}
	endmntent(f);
	for (i = 0, j = 0; i < mntsize; i++) {
		if (!selected(mntbuf[i].mnt_type))
			continue;
		mntbuf[j] = mntbuf[i];
		j++;
	}
	if (argc != 0) {
		struct mntent *mntbuf2;
		if ((mntbuf2 = malloc(argc * sizeof(*mntbuf2))) == NULL)
			err(EXIT_FAILURE, "can't allocate statvfs array");
		size_t mntsize2 = 0;
		for (/*EMPTY*/; argc != 0; argv++, argc--) {
			if ((e = getmntptr(*argv, mntsize, mntbuf)) == 0) {
				fprintf(stderr, "%s: %s: can't find mount point\n", getprogname(), *argv);
				continue;
			}
			mntbuf2[mntsize2] = *e;
			if  (!selected(e->mnt_type))
				warnx("Warning: %s mounted as a %s %s",
				    *argv,
				    e->mnt_type,
				    "file system");
			else
				++mntsize;
		}
		free(mntbuf);
		mntbuf = mntbuf2;
		mntsize = mntsize2;
	}

	maxwidth = 0;
	for (i = 0; i < mntsize; i++) {
		width = (int)strlen(mntbuf[i].mnt_fsname);
		if (width > maxwidth)
			maxwidth = width;
	}
	for (i = 0; i < mntsize; i++) {
		struct statvfs sfsp;
		if (statvfs(mntbuf[i].mnt_dir, &sfsp))
			warn("%s", mntbuf[i].mnt_dir);
		prtstat(&mntbuf[i], &sfsp, maxwidth);
	}
	free(mntbuf);
	while (strs) {
		struct strs *tmp = strs->next;
		free(strs);
		strs = tmp;
	}
	return 0;
}

static struct mntent *
getmntptr(const char *name, size_t mntsize, struct mntent *mntbuf)
{
	size_t i;
	if (mntsize == 0)
		err(EXIT_FAILURE, "Can't get mount information");
	for (i = 0; i < mntsize; i++) {
		if (!strcmp(mntbuf[i].mnt_fsname, name))
			return &mntbuf[i];
	}
	for (i = 0; i < mntsize; i++) {
		if (!strcmp(mntbuf[i].mnt_dir, name))
			return &mntbuf[i];
	}
	return 0;
}

static enum { IN_LIST, NOT_IN_LIST } which;

static int
selected(const char *type)
{
	char **av;

	/* If no type specified, it's always selected. */
	if (typelist == NULL)
		return 1;
	for (av = typelist; *av != NULL; ++av)
		if (!strcmp(type, *av))
			return which == IN_LIST ? 1 : 0;
	return which == IN_LIST ? 0 : 1;
}

static void
maketypelist(char *fslist)
{
	size_t i;
	char *nextcp, **av;

	if ((fslist == NULL) || (fslist[0] == '\0'))
		errx(EXIT_FAILURE, "empty type list");

	/*
	 * XXX
	 * Note: the syntax is "noxxx,yyy" for no xxx's and
	 * no yyy's, not the more intuitive "noyyy,noyyy".
	 */
	if (fslist[0] == 'n' && fslist[1] == 'o') {
		fslist += 2;
		which = NOT_IN_LIST;
	} else
		which = IN_LIST;

	/* Count the number of types. */
	for (i = 1, nextcp = fslist;
	    (nextcp = strchr(nextcp, ',')) != NULL; i++)
		++nextcp;

	/* Build an array of that many types. */
	if ((av = typelist = malloc((i + 1) * sizeof(*av))) == NULL)
		err(EXIT_FAILURE, "can't allocate type array");
	av[0] = fslist;
	for (i = 1, nextcp = fslist;
	    (nextcp = strchr(nextcp, ',')) != NULL; i++) {
		*nextcp = '\0';
		av[i] = ++nextcp;
	}
	/* Terminate the array. */
	av[i] = NULL;
}

static void
prthumanval(int64_t bytes, const char *pad)
{
	char buf[6];

	(void)humanize_number(buf, sizeof(buf) - (bytes < 0 ? 0 : 1),
	    bytes, "", HN_AUTOSCALE,
	    HN_B | HN_NOSPACE | HN_DECIMAL);

	(void)printf("%s %6s", pad, buf);
}

static void
prthuman(struct statvfs *sfsp, int64_t used, int64_t bavail)
{

	prthumanval((int64_t)(sfsp->f_blocks * sfsp->f_frsize), "   ");
	prthumanval((int64_t)(used * sfsp->f_frsize), "    ");
	prthumanval((int64_t)(bavail * sfsp->f_frsize), "    ");
}

/*
 * Convert statvfs returned filesystem size into BLOCKSIZE units.
 * Attempts to avoid overflow for large filesystems.
 */
#define fsbtoblk(num, fsbs, bs)					\
	(((fsbs) != 0 && (uint64_t)(fsbs) < (uint64_t)(bs)) ?	\
	    (int64_t)(num) / (int64_t)((bs) / (fsbs)) :		\
	    (int64_t)(num) * (int64_t)((fsbs) / (bs)))

/*
 * Print out status about a filesystem.
 */
static void
prtstat(struct mntent *e, struct statvfs *sfsp, int maxwidth)
{
	static long blocksize;
	static int headerlen, timesthrough;
	static const char *header;
	static const char full[] = "100";
	static const char empty[] = "  0";
	int64_t used, availblks, inodes;
	int64_t bavail;
	char pb[64];

	if (gflag) {
		/*
		 * From SunOS-5.6:
		 *
		 * /var               (/dev/dsk/c0t0d0s3 ):         8192 block size          1024 frag size
		 *   984242 total blocks     860692 free blocks   859708 available         249984 total files
		 *   248691 free files      8388611 filesys id
		 *      ufs fstype       0x00000004 flag             255 filename length
		 *
		 */
		(void)printf("%10s (%-12s): %7ld block size %12ld frag size\n",
		    e->mnt_dir, e->mnt_fsname,
		    sfsp->f_bsize,	/* On UFS/FFS systems this is
					 * also called the "optimal
					 * transfer block size" but it
					 * is of course the file
					 * system's block size too.
					 */
		    sfsp->f_frsize);	/* not so surprisingly the
					 * "fundamental file system
					 * block size" is the frag
					 * size.
					 */
		(void)printf("%10" PRId64 " total blocks %10" PRId64
		    " free blocks  %10" PRId64 " available\n",
		    (uint64_t)sfsp->f_blocks, (uint64_t)sfsp->f_bfree,
		    (uint64_t)sfsp->f_bavail);
		(void)printf("%10" PRId64 " total files  %10" PRId64
		    " free files %12lx filesys id\n",
		    (uint64_t)sfsp->f_ffree, (uint64_t)sfsp->f_files,
		    sfsp->f_fsid);
		(void)printf("%10s fstype  %#15lx flag  %17ld filename "
		    "length\n", e->mnt_type, sfsp->f_flag,
		    sfsp->f_namemax);
//		(void)printf("%10lu owner %17" PRId64 " syncwrites %12" PRId64
//		    " asyncwrites\n\n", (unsigned long)sfsp->f_owner,
//		    sfsp->f_syncwrites, sfsp->f_asyncwrites);

		/*
		 * a concession by the structured programming police to the
		 * indentation police....
		 */
		return;
	}
	if (maxwidth < 12)
		maxwidth = 12;
	if (++timesthrough == 1) {
		switch (blocksize = usize) {
		case 1024:
			header = Pflag ? "1024-blocks" : "1K-blocks";
			headerlen = (int)strlen(header);
			break;
		case 1024 * 1024:
			header = "1M-blocks";
			headerlen = (int)strlen(header);
			break;
		case 1024 * 1024 * 1024:
			header = "1G-blocks";
			headerlen = (int)strlen(header);
			break;
		default:
			if (hflag) {
				header = "Size";
				headerlen = (int)strlen(header);
			} else
				header = getbsize(&headerlen, &blocksize);
			break;
		}
		if (Pflag) {
			/*
			 * either:
			 *  "Filesystem 1024-blocks Used Available Capacity Mounted on\n"
			 * or:
			 *  "Filesystem 512-blocks Used Available Capacity Mounted on\n"
			 */
			if (blocksize != 1024 && blocksize != 512)
				errx(EXIT_FAILURE,
				    "non-standard block size incompatible with -P");
			(void)printf("%-*.*s %s       Used  Available Capacity "
			    "Mounted on\n",
			    maxwidth - (headerlen - 10),
			    maxwidth - (headerlen - 10),
			    "Filesystem", header);
		} else {
			(void)printf("%-*.*s %s       Used      Avail %%Cap",
			    maxwidth - (headerlen - 10),
			    maxwidth - (headerlen - 10),
			    "Filesystem", header);
			if (iflag)
				(void)printf("    iUsed   iAvail %%iCap");
			(void)printf(" Mounted on\n");
		}
	}
	used = sfsp->f_blocks - sfsp->f_bfree;
	bavail = sfsp->f_bavail;
	availblks = bavail + used;
	if (Pflag) {
		assert(hflag == 0);
		assert(blocksize > 0);
		/*
		 * "%s %d %d %d %s %s\n", <file system name>, <total space>,
		 * <space used>, <space free>, <percentage used>,
		 * <file system root>
		 */
		(void)printf("%-*.*s %10" PRId64 " %10" PRId64 " %10" PRId64 " %7s%% %s\n",
		    maxwidth, maxwidth, e->mnt_fsname,
		    fsbtoblk(sfsp->f_blocks, sfsp->f_frsize, blocksize),
		    fsbtoblk(used, sfsp->f_frsize, blocksize),
		    fsbtoblk(bavail, sfsp->f_frsize, blocksize),
		    availblks == 0 ? full : strspct(pb, sizeof(pb), used,
		    availblks, 0), e->mnt_dir);
		/*
		 * another concession by the structured programming police to
		 * the indentation police....
		 *
		 * Note iflag cannot be set when Pflag is set.
		 */
		return;
	}

	(void)printf("%-*.*s ", maxwidth, maxwidth, e->mnt_fsname);

	if (hflag)
		prthuman(sfsp, used, bavail);
	else
		(void)printf("%10" PRId64 " %10" PRId64 " %10" PRId64,
		    fsbtoblk(sfsp->f_blocks, sfsp->f_frsize, blocksize),
		    fsbtoblk(used, sfsp->f_frsize, blocksize),
		    fsbtoblk(bavail, sfsp->f_frsize, blocksize));
	(void)printf(" %3s%%",
	    availblks == 0 ? full :
	    strspct(pb, sizeof(pb), used, availblks, 0));
	if (iflag) {
		inodes = sfsp->f_files;
		used = inodes - sfsp->f_ffree;
		(void)printf(" %8jd %8jd %4s%%",
		    (intmax_t)used, (intmax_t)sfsp->f_ffree,
		    inodes == 0 ? (used == 0 ? empty : full) :
		    strspct(pb, sizeof(pb), used, inodes, 0));
	}
	(void)printf(" %s\n", e->mnt_dir);
}

static void
usage(void)
{

	(void)fprintf(stderr,
	    "Usage: %s [-agln] [-Ghkm|-ihkm|-Pk] [-t type] [file | "
	    "file_system ...]\n",
	    getprogname());
	exit(1);
	/* NOTREACHED */
}
