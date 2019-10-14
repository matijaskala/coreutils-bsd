include ../../common.mk

tail: forward.c misc.c read.c reverse.c tail.c

install: install-tail
	ln -sf tail $(BINDIR)/tac
	ln -sf tail.1 $(DESTDIR)/usr/share/man/man1/tac.1
