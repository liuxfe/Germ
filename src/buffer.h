/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _BUFFER_H
#define _BUFFER_H

typedef struct _buffer{
	int     nalloc;
	int     nchars;
	char    data[0];
} Buffer;

Buffer* newBuffer();
Buffer* growBuffer(Buffer*);
Buffer* writeCharToBuffer(Buffer*,char);
Buffer* readFileToBuffer(FILE*);

void printBuffer(Buffer*);

#endif