PROGS = cat chmod cp date dd df domainname echo expr hostname kill ln ls mkdir mv pwd rm rmdir sleep stty sync test \
        md5 mknod realpath \
        arch base64 basename cksum comm csplit cut dirname du env expand factor false fmt fold head id join \
        logname mktemp nice nl nohup od paste pathchk pr primes printenv printf seq sort split stat stdbuf \
        tail tee timeout touch tr true truncate tsort tty uname unexpand uniq users wc which who xinstall yes \
        chroot link

all: $(PROGS:%=build-%)

install: $(PROGS:%=install-%)

clean: $(PROGS:%=clean-%)
	$(RM) pwcache.o

build-%: bin/%
	@$(MAKE) -C $<

build-%: sbin/%
	@$(MAKE) -C $<

build-%: usr.bin/%
	@$(MAKE) -C $<

build-%: usr.sbin/%
	@$(MAKE) -C $<

install-%: bin/%
	@$(MAKE) -C $< install DESTDIR="$$(case '$(DESTDIR)' in /*) echo '$(DESTDIR)' ;; *) echo '$(CURDIR)/$(DESTDIR)' ;; esac )"

install-%: sbin/%
	@$(MAKE) -C $< install DESTDIR="$$(case '$(DESTDIR)' in /*) echo '$(DESTDIR)' ;; *) echo '$(CURDIR)/$(DESTDIR)' ;; esac )"

install-%: usr.bin/%
	@$(MAKE) -C $< install DESTDIR="$$(case '$(DESTDIR)' in /*) echo '$(DESTDIR)' ;; *) echo '$(CURDIR)/$(DESTDIR)' ;; esac )"

install-%: usr.sbin/%
	@$(MAKE) -C $< install DESTDIR="$$(case '$(DESTDIR)' in /*) echo '$(DESTDIR)' ;; *) echo '$(CURDIR)/$(DESTDIR)' ;; esac )"

clean-%: bin/%
	@$(MAKE) -C $< clean

clean-%: sbin/%
	@$(MAKE) -C $< clean

clean-%: usr.bin/%
	@$(MAKE) -C $< clean

clean-%: usr.sbin/%
	@$(MAKE) -C $< clean

pwcache.o: pwcache.c
	$(CC) $(CFLAGS) $(shell pkg-config --cflags --libs libbsd-overlay) -D_PW_BUF_LEN=1024 -D_GR_BUF_LEN=2624 -c $< -o $@
