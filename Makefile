name=out
libs=
CFLAGS=-Wall -Wextra -fsanitize=address $(libs)
SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:src/%.c=bin/%.o)
CC=gcc

main: CFLAGS+=
main: min

debug: CFLAGS+=-g
debug: min

min: $(OBJS)
	$(CC) $(OBJS) -o $(name) $(CFLAGS)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

bin:
	mkdir -p bin

clear:
	if ! [ -d "bin/" ] ; then \
		mkdir bin; \
	fi; \
	if ! [ -z "$$(ls -A ./bin 2>/dev/null)" ] ; then \
		rm bin/*; \
	fi; \
	if [ -f $(name)* ] ; then \
		rm $(name)*; \
	fi;

