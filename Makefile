# Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved.

.c.o:
	cc -Wall -fno-builtin -c -o $@  $<

OBJS =	src/xroutine.o	\
	src/vector.o	\
	src/buffer.o	\
	src/scanner.o	\
	src/string.o	\
	src/declare.o	\
	src/symbol.o	\
	src/statement.o \
	src/germ.o

germ: $(OBJS)
	cc -o germ $(OBJS)

test: germ
	./germ example.germ

clean:
	-rm germ $(OBJS)