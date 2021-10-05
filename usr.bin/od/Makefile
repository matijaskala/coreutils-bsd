include ../../common.mk

CFLAGS += -D_GNU_SOURCE

od: conv.c display.c hexsyntax.c od.c odsyntax.c parse.c

install: install-od
	ln -sf od $(BINDIR)/hd
	install -m644 hd.1 $(DESTDIR)/usr/share/man/man1
