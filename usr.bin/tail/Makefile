include ../../common.mk

tail: forward.c misc.c read.c reverse.c tail.c

install: install-tail
	ln -sf tail $(BINDIR)/tac
	install -m644 tac.1 $(DESTDIR)/usr/share/man/man1
