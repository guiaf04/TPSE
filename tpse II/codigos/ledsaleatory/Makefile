CFLAGS=-Wall -g
PROGS=ledsaleatory

all: $(PROGS)

$(PROGS): $(PROGS).c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm -f $(PROGS)

install:
	cp $(PROGS) $(TARGET_DIR)/usr/local/bin
