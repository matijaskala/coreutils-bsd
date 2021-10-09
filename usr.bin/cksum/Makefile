include ../../common.mk

CFLAGS += -D_GNU_SOURCE $(shell pkg-config --cflags --libs libmd)

cksum: base64.c cksum.c crc.c crc32.c sum1.c sum2.c

install: install-cksum
	ln -sf cksum $(BINDIR)/sum
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sum.1
