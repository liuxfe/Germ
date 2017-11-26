# Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved.

.c.o:
	cc -c -o $@  $<

OBJS =	src/routine.o	\
	src/buffer.o	\
	src/scanner.o	\
	src/xstring.o	\
	src/declare.o	\
	src/symbol.o	\
	src/germ.o

germ: $(OBJS)
	cc -o germ $(OBJS)

test: germ
	./germ example.germ

clean:
	-rm germ $(OBJS)