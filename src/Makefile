# Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved.

CPPFLAG=-I./include -MM
CFLAGS =-I./include -Wall

OBJS   =error.o \
	alloc.o \
	xroutine.o \
	vector.o \
	string.o \
	input.o \
	token.o \
	scanner.o \
	parser.o \
	dtype.o \
	symbol.o \
	declare.o \
	expression.o \
	statement.o \
	module.o \
	main.o

germ: $(OBJS)
	$(CC) -o germ $(OBJS)

test: germ
	./germ ../test/example1.gm

clean:
	-rm germ $(OBJS)

depend:
	sed -n "1 , /\#\#\#depends/p" Makefile  >  tmpfile
	for i in $$(ls *.c) ; do                           \
		$(CC) $(CPPFLAG) $$i            >> tmpfile;\
	done
	mv tmpfile Makefile

###depends
alloc.o: alloc.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h
declare.o: declare.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h
dtype.o: dtype.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h
error.o: error.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h
expression.o: expression.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h
input.o: input.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h
main.o: main.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h include/module.h
module.o: module.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h include/scanner.h
parser.o: parser.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h
scanner.o: scanner.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h include/input.h
statement.o: statement.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h
string.o: string.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h
symbol.o: symbol.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h
token.o: token.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h
vector.o: vector.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h
xroutine.o: xroutine.c include/main.h include/error.h include/alloc.h \
 include/xroutine.h include/vector.h include/string.h include/token.h \
 include/parser.h include/dtype.h include/symbol.h include/declare.h \
 include/expression.h include/statement.h
