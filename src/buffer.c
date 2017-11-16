/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

const int B_SIZE = 1024;

Buffer* newBuffer(){
	Buffer *ret;

	ret = malloc(sizeof(Buffer) + B_SIZE);
	if( !ret ){
		printf("Error: alloc buffer return null");
		exit(-1);
	}
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

Buffer* readFileToBuffer(FILE* file){
	Buffer *ret = newBuffer();
	int ch;
	
	for(ch=fgetc(file); ch != EOF; ch=fgetc(file)){
		ret = wrireCharToBuffer(ret,(char)ch);
	}

	// Append '\n','\0' to the file end, make lexcier easier.
	ret = wrireCharToBuffer(ret,'\n');
	ret = wrireCharToBuffer(ret,'\0');
	
	return ret;
}

// use for dubug, dump the buffer.
void printBuffer(Buffer* buf){
	printf("--- Debug: print Buffer ---\n");
	printf("Buffer nalloc: %d\n", buf->nalloc);
	printf("Buffer nchars: %d\n", buf->nchars);
	printf("Buffer data:\n%s",buf->data);
	printf("---------------------------\n");
}