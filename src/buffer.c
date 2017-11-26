/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

const int B_SIZE = 1024;

Buffer* newBuffer(char* name){
	Buffer *ret = xmalloc(sizeof(Buffer) + B_SIZE);

	ret->filename = name;
	ret->nalloc = B_SIZE;
	ret->nchars = 0;
	return ret;
}

Buffer* growBuffer(Buffer* buf){
	Buffer *ret = malloc(sizeof(Buffer) + buf->nalloc + B_SIZE);

	ret->filename = buf->filename;
	ret->nalloc = buf->nalloc + B_SIZE;
	ret->nchars = buf->nchars;
	memcpy(ret->data, buf->data, buf->nalloc);
	xfree(buf);
	return ret;
}

Buffer* wrireCharToBuffer(Buffer* buf, char ch){
	if( buf->nchars + 1 >= buf->nalloc ){
		buf = growBuffer(buf);
	}
	buf->data[buf->nchars++] = ch;

	return buf;
}

Buffer* readFileToBuffer(char *name){
	int ch;

	FILE* file = xfopen(name, "r");
	Buffer* ret = newBuffer(name);

	for(ch=fgetc(file); ch != EOF; ch=fgetc(file)){
		ret = wrireCharToBuffer(ret,(char)ch);
	}
	// Append '\n','\0' to the file end, make lexcier easier.
	ret = wrireCharToBuffer(ret,'\n');
	ret = wrireCharToBuffer(ret,'\0');

	fclose(file);

	return ret;
}

void deleteBuffer(Buffer *buf){
	xfree(buf);
}

void printBuffer(Buffer* buf){
	printf("--- Debug: print Buffer ---\n");
	printf("Buffer filename: %s\n", buf->filename);
	printf("Buffer nalloc: %d\n", buf->nalloc);
	printf("Buffer nchars: %d\n", buf->nchars);
	printf("Buffer data:\n%s",buf->data);
	printf("---------------------------\n");
}