include ../../common.mk

CFLAGS += -DHAVE_OPENSSL $(shell pkg-config --cflags --libs libcrypto)

factor: factor.c pr_tbl.c

install: install-factor
	ln -sf factor.6 $(DESTDIR)/usr/share/man/man6/primes.6
