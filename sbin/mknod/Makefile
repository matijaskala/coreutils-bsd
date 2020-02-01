include ../../common.mk

mknod: mknod.c pack_dev.c ../../pwcache.o

install: install-mknod
	ln -sf mknod $(BINDIR)/mkfifo
	install -d $(DESTDIR)/usr/share/man/man1
	install -m644 mkfifo.1 $(DESTDIR)/usr/share/man/man1
