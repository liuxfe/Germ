# Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved.

.c.o:
	cc -c -o $@  $<

OBJS =	src/buffer.o	\
	src/dynstr.o	\
	src/scanner.o	\
	src/declare.o	\
	src/germ.o

germ: $(OBJS)
	cc -o germ $(OBJS)

test: germ
	./germ example.germ

clean:
	-rm $(OBJS)
	-rm germ