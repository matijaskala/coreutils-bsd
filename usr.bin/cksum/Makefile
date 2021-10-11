include ../../common.mk

CFLAGS += -D_GNU_SOURCE
SRCS = base64.c cksum.c crc.c crc32.c md2.c md2hl.c md4c.c md4hl.c md5c.c md5hl.c rmd160.c rmd160hl.c \
       sha1.c sha1hl.c sha224hl.c sha256c.c sha256hl.c sha384hl.c sha512c.c sha512hl.c sha512thl.c sum1.c sum2.c

cksum: $(SRCS)

install: install-cksum
	ln -sf cksum $(BINDIR)/sum
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
