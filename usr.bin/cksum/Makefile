include ../../common.mk

CFLAGS += -D_GNU_SOURCE
SRCS = base64.c cksum.c crc.c crc32.c md2.c md2hl.c md4c.c md4hl.c md5c.c md5hl.c rmd160.c rmd160hl.c \
       sha1.c sha1hl.c sha224hl.c sha256c.c sha256hl.c sha384hl.c sha512c.c sha512hl.c sha512thl.c sum1.c sum2.c

cksum: $(SRCS)

install: install-cksum
	ln -sf cksum $(BINDIR)/crc32
	ln -sf cksum $(BINDIR)/crc32sum
	ln -sf cksum $(BINDIR)/md5
	ln -sf cksum $(BINDIR)/md5sum
	ln -sf cksum $(BINDIR)/rmd160
	ln -sf cksum $(BINDIR)/rmd160sum
	ln -sf cksum $(BINDIR)/sha1
	ln -sf cksum $(BINDIR)/sha1sum
	ln -sf cksum $(BINDIR)/sha224
	ln -sf cksum $(BINDIR)/sha224sum
	ln -sf cksum $(BINDIR)/sha256
	ln -sf cksum $(BINDIR)/sha256sum
	ln -sf cksum $(BINDIR)/sha384
	ln -sf cksum $(BINDIR)/sha384sum
	ln -sf cksum $(BINDIR)/sha512
	ln -sf cksum $(BINDIR)/sha512sum
	ln -sf cksum $(BINDIR)/sha512t256
	ln -sf cksum $(BINDIR)/sha512t256sum
	ln -sf cksum $(BINDIR)/sum
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/crc32.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/crc32sum.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/md5.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/md5sum.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/rmd160.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/rmd160sum.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sha1.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sha1sum.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sha224.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sha224sum.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sha256.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sha256sum.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sha384.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sha384sum.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sha512.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sha512sum.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sha512t256.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sha512t256sum.1
	ln -sf cksum.1 $(DESTDIR)/usr/share/man/man1/sum.1

%hl.c: mdXhl.c.in
	( echo '#define LENGTH $(shell TMP="$$(echo $@ | sed "s@^[a-z]*@@")" ; echo "$$(($${TMP%hl.c} / 8))")' ; \
	sed -e 's@mdX@$(shell TMP="$@" ; echo "$${TMP%hl.c}")@g' \
	    -e 's@MDX@$(shell TMP="$@" ; echo "$${TMP%hl.c}_" | tr "[:lower:]" "[:upper:]")@g' \
	    -e 's@$(shell TMP="$@" ; echo "$${TMP%hl.c}__@$${TMP%hl.c}_" | tr "[:lower:]" "[:upper:]")@g' \
	$< ) > $@

md%hl.c: mdXhl.c.in
	( echo '#define LENGTH 16' ; \
	sed -e 's@mdX@$(shell TMP="$@" ; echo "$${TMP%hl.c}")@g' \
	    -e 's@MDX@$(shell TMP="$@" ; echo "$${TMP%hl.c}" | tr "[:lower:]" "[:upper:]")@g' \
	$< ) > $@

rmd%hl.c: mdXhl.c.in
	( echo '#define LENGTH $(shell TMP="$$(echo $@ | sed "s@^[a-z]*@@")" ; echo "$$(($${TMP%hl.c} / 8))")' ; \
	sed -e 's@mdX@$(shell TMP="$@" ; echo "$${TMP%hl.c}")@g' \
	    -e 's@MDX@$(shell TMP="$@" ; echo "$${TMP%hl.c}" | tr "[:lower:]" "[:upper:]")@g' \
	$< ) > $@

sha1hl.c: mdXhl.c.in
	( echo '#define LENGTH 20' ; \
	sed -e 's@mdX@$(shell TMP="$@" ; echo "$${TMP%hl.c}")@g' \
	    -e 's@MDX@$(shell TMP="$@" ; echo "$${TMP%hl.c}" | tr "[:lower:]" "[:upper:]")@g' \
	$< ) > $@

sha512thl.c: mdXhl.c.in
	( echo '#define LENGTH 32' ; \
	sed -e 's/mdX/sha512t/g' -e 's/MDX/SHA512_256_/g' \
	    -e 's/SHA512_256__/SHA512_256_/g' -e 's/SHA512_256_CTX/SHA512_CTX/g' \
	$< ) > $@
