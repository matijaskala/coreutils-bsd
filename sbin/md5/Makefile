include ../../common.mk

CFLAGS += $(shell pkg-config --cflags --libs libcrypto)

install: install-md5
	ln -sf md5 $(DESTDIR)/bin/rmd160
	ln -sf md5 $(DESTDIR)/bin/sha1
	ln -sf md5 $(DESTDIR)/bin/sha256
	ln -sf md5 $(DESTDIR)/bin/sha512
	ln -sf md5.1 $(DESTDIR)/usr/share/man/man1/rmd160.1
	ln -sf md5.1 $(DESTDIR)/usr/share/man/man1/sha1.1
	ln -sf md5.1 $(DESTDIR)/usr/share/man/man1/sha256.1
	ln -sf md5.1 $(DESTDIR)/usr/share/man/man1/sha512.1
