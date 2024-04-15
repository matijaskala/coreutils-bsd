/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1991, 1993, 1994
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
 */

#include <sys/cdefs.h>

#include <sys/param.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void usage(void) __dead2;

static char *strippath(char *path) {
	size_t bufl = 32;
	char *buf = NULL, *t;
	while (*path != '/') {
		buf = realloc(buf, bufl);
		if (!buf)
			err(1, NULL);
		errno = 0;
		if (getcwd(buf, bufl)) {
			t = strrchr(buf, '/');
			while (t >= buf && !strcmp(t, "/"))
				*t-- = 0;
			break;
		}
		if (errno != ERANGE)
			err(1, NULL);
		bufl *= 2;
	}
	if (!buf) {
		buf = malloc(bufl);
		if (!buf)
			err(1, NULL);
		*buf = 0;
	}
	t = strtok(path, "/");
	do {
		if (!strcmp(t, "."))
			continue;
		if (!strcmp(t, "..")) {
			t = strrchr(buf, '/');
			while (t && *t == '/')
				*t-- = 0;
		}
		else {
			while (bufl < strlen(buf) + 1 + strlen(t) + 1) {
				buf = realloc(buf, bufl *= 2);
				if (!buf)
					err(1, NULL);
			}
			sprintf(buf + strlen(buf), "/%s", t);
		}
	} while (t = strtok(NULL, "/"));
	if (!*buf)
		strcpy(buf, "/");
	free(path);
	return buf;
}

int
main(int argc, char *argv[])
{
	char buf[PATH_MAX];
	char *p;
	const char *path;
	int ch, qflag, sflag, rval;

	qflag = 0;
	while ((ch = getopt(argc, argv, "qs")) != -1) {
		switch (ch) {
		case 'q':
			qflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	path = *argv != NULL ? *argv++ : ".";
	rval  = 0;
	do {
		if (sflag) {
			p = strippath(strdup(path));
			(void)printf("%s\n", p);
			free(p);
		}
		else if ((p = realpath(path, buf)) == NULL) {
			if (!qflag)
				warn("%s", path);
			rval = 1;
		} else
			(void)printf("%s\n", p);
	} while ((path = *argv++) != NULL);
	exit(rval);
}

static void
usage(void)
{

	(void)fprintf(stderr, "usage: realpath [-q] [-s] [path ...]\n");
  	exit(1);
}
