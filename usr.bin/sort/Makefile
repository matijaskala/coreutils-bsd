include ../../common.mk

CFLAGS += -D_GNU_SOURCE

all: sort sort.1

sort: bwstring.c coll.c file.c mem.c radixsort.c sort.c vsort.c

install-sort: all

sort.1: sort.1.in
	sed $(MAN_SUB) $^ > $@

clean: clean-generated

clean-generated:
	$(RM) sort.1

NLS += C

ifneq ($(MK_SORT_THREADS), "no")
CFLAGS+= -DSORT_THREADS -lpthread
MAN_SUB+= -e 's|%%THREADS%%||g'
else
MAN_SUB+= -e 's|%%THREADS%%|\.\\"|g'
endif

ifneq ($(MK_NLS), "no")
NLS+=	hu_HU.ISO8859-2
NLSSRCFILES= ${NLS:S@$@.msg@}
MAN_SUB+= -e 's|%%NLS%%||g'
else
CFLAGS+= -DWITHOUT_NLS
MAN_SUB+= -e 's|%%NLS%%|\.\\"|g'
endif
