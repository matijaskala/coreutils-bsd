CFLAGS += $(shell pkg-config --cflags --libs libbsd-overlay)
PROGS = $(shell basename $(CURDIR))

all: $(PROGS)

install: $(PROGS:%=install-%)

install-%: % %.[12345678]
	install -d $(DESTDIR)/bin
	install $< $(DESTDIR)/bin
	install -d $(DESTDIR)/usr/share/man/man$(subst $<.,,$(word 2,$^))
	install -m644 $(word 2,$^) $(DESTDIR)/usr/share/man/man$(subst $<.,,$(word 2,$^))

clean:
	$(RM) $(PROGS)
