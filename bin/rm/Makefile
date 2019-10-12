include ../../common.mk

rm: rm.c ../pwcache.o

../pwcache.o:
	@$(MAKE) -C .. pwcache.o

install: install-rm
	ln -sf rm $(DESTDIR)/bin/unlink
	ln -sf rm.1 $(DESTDIR)/usr/share/man/man1/unlink.1
