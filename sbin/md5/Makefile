include ../../common.mk

CFLAGS += $(shell pkg-config --cflags --libs libmd)

install: install-md5
	ln -sf md5 $(BINDIR)/rmd160
	ln -sf md5 $(BINDIR)/sha1
	ln -sf md5 $(BINDIR)/sha256
	ln -sf md5 $(BINDIR)/sha512
	ln -sf ../sbin/md5 $(DESTDIR)/bin/md5sum
	ln -sf ../sbin/md5 $(DESTDIR)/bin/rmd160sum
	ln -sf ../sbin/md5 $(DESTDIR)/bin/sha1sum
	ln -sf ../sbin/md5 $(DESTDIR)/bin/sha256sum
	ln -sf ../sbin/md5 $(DESTDIR)/bin/sha512sum
	ln -sf md5.1 $(DESTDIR)/usr/share/man/man1/md5sum.1
	ln -sf md5.1 $(DESTDIR)/usr/share/man/man1/rmd160.1
	ln -sf md5.1 $(DESTDIR)/usr/share/man/man1/rmd160sum.1
	ln -sf md5.1 $(DESTDIR)/usr/share/man/man1/sha1.1
	ln -sf md5.1 $(DESTDIR)/usr/share/man/man1/sha1sum.1
	ln -sf md5.1 $(DESTDIR)/usr/share/man/man1/sha256.1
	ln -sf md5.1 $(DESTDIR)/usr/share/man/man1/sha256sum.1
	ln -sf md5.1 $(DESTDIR)/usr/share/man/man1/sha512.1
	ln -sf md5.1 $(DESTDIR)/usr/share/man/man1/sha512sum.1
