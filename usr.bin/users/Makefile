include ../../common.mk

CFLAGS += -std=c11

CPPFLAGS += -I../who -DSUPPORT_UTMP -D_GNU_SOURCE

users: users.c ../who/utmpentry.c
