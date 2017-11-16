/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

int doComplie(FILE* in, FILE* out){
	Buffer* buf;

	buf=readFileToBuffer(in);
	printBuffer(buf);
	return 0;
}

int main(int argc, char* argv[]){
	FILE* in;
	FILE* out;

	setvbuf(stdout, NULL, _IONBF, 0);

	if(argc != 2){
		printf("Usage: germ <source-file>\n");
		exit(-1);
	}

	in = fopen(argv[1], "r");
	if( !in ){
		printf("Error: source file %s can't open.\n", argv[1]);
		exit(-2);
	}

	out = stdout;

	return doComplie(in, out);
}