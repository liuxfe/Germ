# Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved.

CPPFLAG=-I./inc -MM
CFLAGS =-I./inc -Wall

OBJS   =src/error.o \
	src/alloc.o \
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
	src/module.o \
	src/main.o

germ: $(OBJS)
	$(CC) -o germ $(OBJS)

test: germ
	./germ test/example1.gm

clean:
	-rm germ $(OBJS)

depend:
	sed -n "1 , /\#\#\#depends/p" Makefile    >  tmpfile
	for i in $$(ls src/*.c) ; do                         \
		echo "src/$$($(CC) $(CPPFLAG) $$i)" >> tmpfile;\
	done
	mv tmpfile Makefile

###depends
src/alloc.o: src/alloc.c inc/main.h inc/error.h inc/alloc.h inc/xroutine.h \
 inc/vector.h inc/string.h inc/token.h inc/parser.h inc/dtype.h \
 inc/symbol.h inc/declare.h inc/expression.h inc/statement.h
src/declare.o: src/declare.c inc/main.h inc/error.h inc/alloc.h \
 inc/xroutine.h inc/vector.h inc/string.h inc/token.h inc/parser.h \
 inc/dtype.h inc/symbol.h inc/declare.h inc/expression.h inc/statement.h
src/dtype.o: src/dtype.c inc/main.h inc/error.h inc/alloc.h inc/xroutine.h \
 inc/vector.h inc/string.h inc/token.h inc/parser.h inc/dtype.h \
 inc/symbol.h inc/declare.h inc/expression.h inc/statement.h
src/error.o: src/error.c inc/main.h inc/error.h inc/alloc.h inc/xroutine.h \
 inc/vector.h inc/string.h inc/token.h inc/parser.h inc/dtype.h \
 inc/symbol.h inc/declare.h inc/expression.h inc/statement.h
src/expression.o: src/expression.c inc/main.h inc/error.h inc/alloc.h \
 inc/xroutine.h inc/vector.h inc/string.h inc/token.h inc/parser.h \
 inc/dtype.h inc/symbol.h inc/declare.h inc/expression.h inc/statement.h
src/input.o: src/input.c inc/main.h inc/error.h inc/alloc.h inc/xroutine.h \
 inc/vector.h inc/string.h inc/token.h inc/parser.h inc/dtype.h \
 inc/symbol.h inc/declare.h inc/expression.h inc/statement.h
src/main.o: src/main.c inc/main.h inc/error.h inc/alloc.h inc/xroutine.h \
 inc/vector.h inc/string.h inc/token.h inc/parser.h inc/dtype.h \
 inc/symbol.h inc/declare.h inc/expression.h inc/statement.h inc/module.h
src/module.o: src/module.c inc/main.h inc/error.h inc/alloc.h inc/xroutine.h \
 inc/vector.h inc/string.h inc/token.h inc/parser.h inc/dtype.h \
 inc/symbol.h inc/declare.h inc/expression.h inc/statement.h \
 inc/scanner.h
src/parser.o: src/parser.c inc/main.h inc/error.h inc/alloc.h inc/xroutine.h \
 inc/vector.h inc/string.h inc/token.h inc/parser.h inc/dtype.h \
 inc/symbol.h inc/declare.h inc/expression.h inc/statement.h
src/scanner.o: src/scanner.c inc/main.h inc/error.h inc/alloc.h \
 inc/xroutine.h inc/vector.h inc/string.h inc/token.h inc/parser.h \
 inc/dtype.h inc/symbol.h inc/declare.h inc/expression.h inc/statement.h \
 inc/input.h
src/statement.o: src/statement.c inc/main.h inc/error.h inc/alloc.h \
 inc/xroutine.h inc/vector.h inc/string.h inc/token.h inc/parser.h \
 inc/dtype.h inc/symbol.h inc/declare.h inc/expression.h inc/statement.h
src/string.o: src/string.c inc/main.h inc/error.h inc/alloc.h inc/xroutine.h \
 inc/vector.h inc/string.h inc/token.h inc/parser.h inc/dtype.h \
 inc/symbol.h inc/declare.h inc/expression.h inc/statement.h
src/symbol.o: src/symbol.c inc/main.h inc/error.h inc/alloc.h inc/xroutine.h \
 inc/vector.h inc/string.h inc/token.h inc/parser.h inc/dtype.h \
 inc/symbol.h inc/declare.h inc/expression.h inc/statement.h
src/token.o: src/token.c inc/main.h inc/error.h inc/alloc.h inc/xroutine.h \
 inc/vector.h inc/string.h inc/token.h inc/parser.h inc/dtype.h \
 inc/symbol.h inc/declare.h inc/expression.h inc/statement.h
src/vector.o: src/vector.c inc/main.h inc/error.h inc/alloc.h inc/xroutine.h \
 inc/vector.h inc/string.h inc/token.h inc/parser.h inc/dtype.h \
 inc/symbol.h inc/declare.h inc/expression.h inc/statement.h
src/xroutine.o: src/xroutine.c inc/main.h inc/error.h inc/alloc.h \
 inc/xroutine.h inc/vector.h inc/string.h inc/token.h inc/parser.h \
 inc/dtype.h inc/symbol.h inc/declare.h inc/expression.h inc/statement.h
