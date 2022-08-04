/*-
 * Copyright (c) 1988, 1993, 1994
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

#include <err.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static void alarmhandle(int);
static void usage(void);

int
main(int argc, char *argv[])
{
	struct timespec time_to_sleep;
	long double d, seconds;
	time_t original;
	char unit;
	char buf[2];
	int i, matches;

	(void)signal(SIGALRM, alarmhandle);

	if (argc < 2)
		usage();

	seconds = 0;
	for (i = 1; i < argc; i++) {
		matches = sscanf(argv[1], "%Lf%c%1s", &d, &unit, buf);
		if (matches == 2)
			switch (unit) {
			case 'd':
				d *= 24;
				/* FALLTHROUGH */
			case 'h':
				d *= 60;
				/* FALLTHROUGH */
			case 'm':
				d *= 60;
				/* FALLTHROUGH */
			case 's':
				break;
			default:
				usage();
			}
		else
			if (matches != 1)
				usage();
		seconds += d;
	}
	if (seconds > INT64_MAX)
		usage();
	if (seconds <= 0)
		return (0);
	original = time_to_sleep.tv_sec = (time_t)seconds;
	time_to_sleep.tv_nsec = 1e9 * (seconds - time_to_sleep.tv_sec);

	while (nanosleep(&time_to_sleep, &time_to_sleep) != 0) {
		if (errno != EINTR)
			err(1, "nanosleep");
	}
	return (0);
}

static void
usage(void)
{
	fprintf(stderr, "usage: sleep number[unit] ...\n");
	fprintf(stderr, "Unit can be 's' (seconds, the default), "
			"m (minutes), h (hours), or d (days).\n");
	exit(EXIT_FAILURE);
}

/* ARGSUSED */
static void
alarmhandle(int i)
{
	_exit(EXIT_SUCCESS);
}
