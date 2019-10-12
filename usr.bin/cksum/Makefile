include ../../common.mk

cksum: cksum.c crc.c print.c sum1.c sum2.c crc32.c

install: install-cksum
	ln -sf cksum $(BINDIR)/sum
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sum.1
