/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

typedef struct _buffer{
	int     nalloc;
	int     nchars;
	char*   data;
} Buffer;

void _insertCharToBuffer(Buffer* buf, char ch){
	const int FB_GROWSIZE = 1024;
	char* tmp;
	if(buf->nchars+1 >= buf->nalloc){
		tmp = Xmalloc(buf->nalloc + FB_GROWSIZE, __FILE__, __LINE__);
		if(buf->data){
			Xmemcpy(tmp, buf->data, buf->nchars);
			Xfree(buf->data, __FILE__, __LINE__);
		}
		buf->nalloc = buf->nalloc + FB_GROWSIZE;
		buf->data = tmp;
	}
	buf->data[buf->nchars++] = ch;
}

char* LoadFile(char* filename){
	int  ch;

	Buffer buf = {0, 0, NULL};
	FILE* file = Xfopen(filename, "r", __FILE__, __LINE__);

	for(ch=fgetc(file); ch != EOF; ch=fgetc(file)){
		_insertCharToBuffer(&buf,(char)ch);
	}
	_insertCharToBuffer(&buf,'\0');

	Xfclose(file, __FILE__, __LINE__);

	return buf.data;
}