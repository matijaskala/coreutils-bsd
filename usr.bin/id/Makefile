include ../../common.mk

install: install-id
	ln -sf id $(BINDIR)/groups
	install -m644 groups.1 $(DESTDIR)/usr/share/man/man1
	ln -sf id $(BINDIR)/whoami
	install -m644 whoami.1 $(DESTDIR)/usr/share/man/man1
