CC = gcc

ifndef DEBUG
	CFLAGS = -Wall -Wextra -O2 -pthread
else
	CFLAGS = -Wall -Wextra -g -pthread
endif
LDFLAGS = $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $? -c -o $@

dist: dist.o main.o

clean:
	$(RM) dist dist.o main.o

.PHONY: clean
