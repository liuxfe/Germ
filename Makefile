# Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved.

.c.o:
	cc -Wall -fno-builtin -c -o $@  $<

OBJS =	src/error.o	src/xroutine.o	src/vector.o	src/string.o	\
	src/input.o	\
	src/scanner.o	\
	src/parser.o	\
	src/symbol.o	\
	src/germ.o

germ: $(OBJS)
	cc -o germ $(OBJS)

test: germ
	./germ example.germ

clean:
	-rm germ $(OBJS)