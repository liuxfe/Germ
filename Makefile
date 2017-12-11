# Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved.

.c.o:
	cc -I./inc -Wall -fno-builtin -c -o $@  $<

OBJS =	src/error.o	src/xroutine.o	src/vector.o	src/string.o	\
									\
	src/input.o	src/scanner.o	src/parser.o			\
					src/declare.o 			\
					src/expression.o 		\
					src/statement.o 		\
	src/main.o

germ: $(OBJS)
	cc -o germ $(OBJS)

test: germ
	./germ test/step1.gm
	./germ test/step2.gm
	./germ test/step3.gm

clean:
	-rm germ $(OBJS)