/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

const int B_SIZE = 1024;

Buffer* newBuffer(char* name){
	Buffer *ret;

	ret = malloc(sizeof(Buffer) + B_SIZE);
	if( !ret ){
		printf("Error: alloc buffer return null");
		exit(-1);
	}
	ret->filename = name;
	ret->nalloc = B_SIZE;
	ret->nchars = 0;
	return ret;
}

Buffer* growBuffer(Buffer* buf){
	Buffer *ret;

	ret = malloc(sizeof(Buffer) + buf->nalloc + B_SIZE);
	if( !ret ){
		printf("Error: grow buffer return null");
		exit(-1);
	}
	ret->filename = buf->filename;
	ret->nalloc = buf->nalloc + B_SIZE;
	ret->nchars = buf->nchars;
	memcpy(ret->data, buf->data, buf->nalloc);
	free(buf);
	return ret;
}

Buffer* wrireCharToBuffer(Buffer* buf, char ch){
	if( buf->nchars + 1 >= buf->nalloc ){
		buf = growBuffer(buf);
	}
	buf->data[buf->nchars++] = ch;

	return buf;
}

// Note: 如果文件打开失败，返回NULL
Buffer* readFileToBuffer(char *name){
	Buffer *ret;
	FILE* file;
	int ch;

	file = fopen(name, "r");
	if( !file){
		return NULL;
	}

	ret = newBuffer(name);

	for(ch=fgetc(file); ch != EOF; ch=fgetc(file)){
		ret = wrireCharToBuffer(ret,(char)ch);
	}
	// Append '\n','\0' to the file end, make lexcier easier.
	ret = wrireCharToBuffer(ret,'\n');
	ret = wrireCharToBuffer(ret,'\0');

	return ret;
}

void deleteBuffer(Buffer *buf){
	free(buf);
}

void printBuffer(Buffer* buf){
	printf("--- Debug: print Buffer ---\n");
	printf("Buffer filename: %s\n", buf->filename);
	printf("Buffer nalloc: %d\n", buf->nalloc);
	printf("Buffer nchars: %d\n", buf->nchars);
	printf("Buffer data:\n%s",buf->data);
	printf("---------------------------\n");
}