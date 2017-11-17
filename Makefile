# Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved.

SRCS = src/buffer.c src/scanner.c src/germ.c

target:
	cc  $(SRCS) -o germ.exe
	./germ.exe example.germ

clean:
	rm germ.exe