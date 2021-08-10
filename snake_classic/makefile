CC=gcc
CFLAGS=-Wall -Werror -lncurses -std=c99

clean:
	*.o

main: *.c *.h
	$(CC) $(CFLAGS) $^ -o $@.o

