include ../../common.mk

CFLAGS += $(shell pkg-config --cflags --libs ncurses) -DCOLORLS -D_GNU_SOURCE

ls: cmp.c ls.c print.c util.c ../../pwcache.o
