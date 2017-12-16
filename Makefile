# Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved.

CFLAGS =-I./inc -Wall -fno-builtin

OBJS   =src/error.o \
	src/xroutine.o \
	src/vector.o \
	src/string.o \
	src/input.o \
	src/token.o \
	src/scanner.o \
	src/parser.o \
	src/dtype.o \
	src/symbol.o \
	src/declare.o \
	src/expression.o \
	src/statement.o \
	src/main.o

germ: $(OBJS)
	$(CC) -o germ $(OBJS)

test: germ
	./germ test/step1.gm
	./germ test/step2.gm
	./germ test/step3.gm
	./germ test/step4.gm
	./germ test/step5.gm

clean:
	-rm germ $(OBJS)