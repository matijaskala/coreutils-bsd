CFLAGS += $(shell pkg-config --cflags --libs libbsd-overlay)

pwcache.o: pwcache.c
	$(CC) $(CFLAGS) -D_PW_BUF_LEN=1024 -D_GR_BUF_LEN=2624 -c $< -o $@
