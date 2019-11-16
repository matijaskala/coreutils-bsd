include ../../common.mk

hexdump: conv.c display.c hexdump.c hexsyntax.c odsyntax.c parse.c

install: install-hexdump
	ln -sf hexdump $(BINDIR)/od
	ln -sf hexdump $(BINDIR)/hd
	install -m644 od.1 $(DESTDIR)/usr/share/man/man1
	ln -sf hexdump.1 $(DESTDIR)/usr/share/man/man1/hd.1
