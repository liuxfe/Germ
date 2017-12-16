/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"
#include <assert.h>

int doComplie(char* file){
	ParseFile(file);

	return 0;
}

int main(int argc, char* argv[]){
	FILE* out = stdout;

	assert(sizeof(int8)  ==1);
	assert(sizeof(int16) ==2);
	assert(sizeof(int32) ==4);
	assert(sizeof(int64) ==8);
	assert(sizeof(uint8) ==1);
	assert(sizeof(uint16)==2);
	assert(sizeof(uint32)==4);
	assert(sizeof(uint64)==8);
	assert(sizeof(bool)  ==1);
	assert(sizeof(void*) ==8);
	//assert(sizeof(int)   ==8);
	//assert(sizeof(uint)  ==8);
	
	if(argc != 2){
		printf("Usage: germ <source-file>\n");
		exit(-1);
	}

	setvbuf(out, NULL, _IONBF, 0);

	return doComplie(argv[1]);
}