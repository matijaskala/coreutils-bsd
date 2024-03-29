/*	$NetBSD: md2.h,v 1.5 2005/09/25 00:48:21 xtraeme Exp $	*/

#ifndef _MD2_H_
#define _MD2_H_

#include <sys/types.h>

#include <stdint.h>

#define	MD2_DIGEST_LENGTH		16
#define	MD2_DIGEST_STRING_LENGTH	33

/* MD2 context. */
typedef struct MD2Context {
	uint32_t i;
	unsigned char C[16];		/* checksum */
	unsigned char X[48];		/* input buffer */
} MD2_CTX;

#ifdef __cplusplus
extern "C" {
#endif

void	MD2Init(MD2_CTX *);
void	MD2Update(MD2_CTX *, const unsigned char *, unsigned int);
void	MD2Final(unsigned char[16], MD2_CTX *);
char	*MD2End(MD2_CTX *, char *);
char	*MD2Fd(int, char *);
char	*MD2FdChunk(int, char *, off_t, off_t);
char	*MD2File(const char *, char *);
char	*MD2FileChunk(const char *, char *, off_t, off_t);
char	*MD2Data(const void *, unsigned int, char *);

#ifdef __cplusplus
}
#endif

#endif /* _MD2_H_ */
