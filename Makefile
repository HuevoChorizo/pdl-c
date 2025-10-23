name=out
#libs=
CFLAGS=-Wall -Wextra -ansi -pedantic #$(libs)
SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:src/%.c=bin/%.o)

main: CFLAGS+=
main: min

debug: CFLAGS+=-g
debug: min

min: $(OBJS)
	$(CC) $(OBJS) -o $(name) $(CFLAGS)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


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

