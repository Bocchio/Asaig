CC = gcc
CFLAGS = -std=c99 -Wall -pedantic-errors
LFLAGS = -lasound
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

asaig: dist $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o dist/$@

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: dist
dist:
	mkdir -p dist

.PHONY: clean
clean:
	rm -f *.o