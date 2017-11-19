/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _BUFFER_H
#define _BUFFER_H

typedef struct _buffer{
	char*   filename;
	int     nalloc;
	int     nchars;
	char    data[0];
} Buffer;

Buffer* newBuffer(char*);
Buffer* growBuffer(Buffer*);
Buffer* writeCharToBuffer(Buffer*,char);
Buffer* readFileToBuffer(char*);
void deleteBuffer(Buffer*);
void printBuffer(Buffer*);

#endif