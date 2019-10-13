include ../../common.mk

chmod: chmod.c ../../pwcache.o

install: install-chmod
	ln -sf ../bin/chmod $(DESTDIR)/bin/chgrp
	install -d $(DESTDIR)/sbin
	ln -sf ../bin/chmod $(DESTDIR)/sbin/chown
	install -m644 chgrp.1 $(DESTDIR)/usr/share/man/man1
	install -d $(DESTDIR)/usr/share/man/man8
	install -m644 chown.8 $(DESTDIR)/usr/share/man/man8
