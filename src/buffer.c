/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "germ.h"

const int B_SIZE = 1024;

Buffer* _newBuffer(char* name){
	Buffer *ret = xmalloc(sizeof(Buffer) + B_SIZE);
	ret->filename = name;
	ret->nalloc = B_SIZE;
	return ret;
}

Buffer* _growBuffer(Buffer* buf){
	Buffer *ret = xmalloc(sizeof(Buffer) + buf->nalloc + B_SIZE);
	ret->filename = buf->filename;
	ret->nalloc = buf->nalloc + B_SIZE;
	ret->nchars = buf->nchars;
	xmemcpy(ret->data, buf->data, buf->nalloc);
	xfree(buf);
	return ret;
}

Buffer* _wrireCharToBuffer(Buffer* buf, char ch){
	if( buf->nchars + 1 >= buf->nalloc ){
		buf = _growBuffer(buf);
	}
	buf->data[buf->nchars++] = ch;
	return buf;
}

Buffer* readFileToBuffer(char *name){
	int ch;

	FILE* file = xfopen(name, "r");
	Buffer* ret = _newBuffer(name);

	for(ch=fgetc(file); ch != EOF; ch=fgetc(file)){
		ret = _wrireCharToBuffer(ret,(char)ch);
	}
	// Append '\n','\0' to the file end, make lexcier easier.
	ret = _wrireCharToBuffer(ret,'\n');
	ret = _wrireCharToBuffer(ret,'\0');

	xfclose(file);

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