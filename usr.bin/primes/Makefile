include ../../common.mk

CFLAGS += -lm

primes: pattern.c pr_tbl.c primes.c spsp.c

install-primes: primes
	install -d $(BINDIR)
	install $< $(BINDIR)
