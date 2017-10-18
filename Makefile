CC = gcc
CFLAGS = -Wall -pedantic-errors
LFLAGS = -lasound
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

asaig: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f *.o