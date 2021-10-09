/*-
 * Copyright (c) 1991, 1993
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
 * @(#)sum1.c	8.1 (Berkeley) 6/6/93
 * $FreeBSD: src/usr.bin/cksum/sum1.c,v 1.8 2003/03/13 23:32:28 robert Exp $
 * $DragonFly: src/usr.bin/cksum/sum1.c,v 1.4 2005/04/10 20:55:38 drhodus Exp $
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "cksum.h"

void
SUM1_Init(CKSUM_CTX *ctx)
{
	ctx->crc = 0;
	ctx->len = 0;
}

void
SUM1_Update(CKSUM_CTX *ctx, const unsigned char *buf, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++) {
		if (ctx->crc & 1)
			ctx->crc |= 0x10000;
		ctx->crc = ((ctx->crc >> 1) + buf[i]) & 0xffff;
	}
	ctx->len += len;
}

void
SUM1_Final(CKSUM_CTX *ctx)
{
}

char *
SUM1_End(CKSUM_CTX *ctx, char *outstr)
{
	CRC32_Final(ctx);

	if (outstr == NULL) {
		if (asprintf(&outstr, "%u %lld", ctx->crc, (ctx->len + 1023) / 1024) == -1)
			return (NULL);
	} else {
		(void)snprintf(outstr, (size_t)CRC32_DIGEST_STRING_LENGTH,
		    "%u %lld", ctx->crc, (ctx->len + 1023) / 1024);
	}

	return (outstr);
}
