PROGS = xinstall

include ../../common.mk

CFLAGS += -D_GNU_SOURCE

xinstall: xinstall.c ../../pwcache.o

install-xinstall: xinstall install.1
	install -d $(BINDIR)
	install -T $< $(BINDIR)/install
	install -d $(DESTDIR)/usr/share/man/man$(subst $<.,,$(word 2,$^))
	install -m644 $(word 2,$^) $(DESTDIR)/usr/share/man/man1
