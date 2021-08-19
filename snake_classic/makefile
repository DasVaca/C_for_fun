cc=gcc
cflags=-Wall -Werror -lncurses -std=c99 -g
objects=snake.o graphics.o common.o utils.o err.o main.o

snake: $(objects)
	$(cc) $(cflags) $^ -o snake

$(objects): %.o: %.c
	$(cc) -c $(cflags) $< -o $@
