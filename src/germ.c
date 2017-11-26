/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

int doComplie(char* file){
	token* tlist = scanFile(file);
	printHashTable();
	printTokenList(tlist);

	return 0;
}

int main(int argc, char* argv[]){
	FILE* in;
	FILE* out = stdout;

	if(argc != 2){
		printf("Usage: germ <source-file>\n");
		exit(-1);
	}

	setvbuf(out, NULL, _IONBF, 0);

	initKeyWordSymbol();
	return doComplie(argv[1]);
}