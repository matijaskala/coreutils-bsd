PROGS = cat chmod cp date df domainname echo expr hostname kill ln ls mkdir mv pwd rm rmdir sleep stty sync test \
        md5 realpath arch base64 basename cksum comm csplit dirname split tty which yes chroot

all: $(PROGS:%=build-%)

install: $(PROGS:%=install-%)

clean: $(PROGS:%=clean-%)
	$(RM) bin/pwcache.o

build-%: bin/%
	@$(MAKE) -C $<

build-%: sbin/%
	@$(MAKE) -C $<

build-%: usr.bin/%
	@$(MAKE) -C $<

build-%: usr.sbin/%
	@$(MAKE) -C $<

install-%: bin/%
	@$(MAKE) -C $< install DESTDIR='$(shell test -n '$(DESTDIR)' && realpath '$(DESTDIR)')'

install-%: sbin/%
	@$(MAKE) -C $< install DESTDIR='$(shell test -n '$(DESTDIR)' && realpath '$(DESTDIR)')'

install-%: usr.bin/%
	@$(MAKE) -C $< install DESTDIR='$(shell test -n '$(DESTDIR)' && realpath '$(DESTDIR)')'

install-%: usr.sbin/%
	@$(MAKE) -C $< install DESTDIR='$(shell test -n '$(DESTDIR)' && realpath '$(DESTDIR)')'

clean-%: bin/%
	@$(MAKE) -C $< clean

clean-%: sbin/%
	@$(MAKE) -C $< clean

clean-%: usr.bin/%
	@$(MAKE) -C $< clean

clean-%: usr.sbin/%
	@$(MAKE) -C $< clean
