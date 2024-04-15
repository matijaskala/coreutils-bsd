/*	$OpenBSD: crc.h,v 1.4 2019/01/25 00:19:25 millert Exp $	*/

/*
 * Copyright (c) 2004 Todd C. Miller <millert@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#define	CRC_DIGEST_LENGTH		4
#define	CRC_DIGEST_STRING_LENGTH	(10 + 1 + 20 + 1)

#define	CRC32_DIGEST_LENGTH		4
#define	CRC32_DIGEST_STRING_LENGTH	(10 + 1 + 20 + 1)

#define	SUM1_DIGEST_LENGTH		4
#define	SUM1_DIGEST_STRING_LENGTH	(10 + 1 + 20 + 1)

#define	SUM2_DIGEST_LENGTH		4
#define	SUM2_DIGEST_STRING_LENGTH	(10 + 1 + 20 + 1)

typedef struct CKSUMContext {
	uint32_t crc;
	long long len;
} CKSUM_CTX;

void	 CRC_Init(CKSUM_CTX *);
void	 CRC_Update(CKSUM_CTX *, const uint8_t *, size_t);
void	 CRC_Final(CKSUM_CTX *);
char    *CRC_End(CKSUM_CTX *, char *);
char    *CRC_Data(const uint8_t *, size_t, char *);

void	 CRC32_Init(CKSUM_CTX *);
void	 CRC32_Update(CKSUM_CTX *, const uint8_t *, size_t);
void	 CRC32_Final(CKSUM_CTX *);
char    *CRC32_End(CKSUM_CTX *, char *);
char    *CRC32_Data(const uint8_t *, size_t, char *);

void	 SUM1_Init(CKSUM_CTX *);
void	 SUM1_Update(CKSUM_CTX *, const uint8_t *, size_t);
void	 SUM1_Final(CKSUM_CTX *);
char    *SUM1_End(CKSUM_CTX *, char *);
char    *SUM1_Data(const uint8_t *, size_t, char *);

void	 SUM2_Init(CKSUM_CTX *);
void	 SUM2_Update(CKSUM_CTX *, const uint8_t *, size_t);
void	 SUM2_Final(CKSUM_CTX *);
char    *SUM2_End(CKSUM_CTX *, char *);
char    *SUM2_Data(const uint8_t *, size_t, char *);

int b64_ntop(const unsigned char *src, size_t srclength, char *target, size_t targsize);
