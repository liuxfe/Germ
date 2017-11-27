/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _GERM_H
#define _GERM_H

#include <stdio.h>
#include <stdlib.h>

// some basic types in germ.
typedef   signed char   int8;
typedef unsigned char  uint8;
typedef   signed short  int16;
typedef unsigned short uint16;
typedef   signed int    int32;
typedef unsigned int   uint32;
typedef   signed long   int64;
typedef unsigned long  uint64;
typedef unsigned int   uint;

typedef char bool;

#define true  1;
#define false 0;

// xrourine.c
void* xmalloc(uint);
void  xfree(void*);
int   xstrlen(char*);
int   xstrcmp(char*, char*);
void  xmemcpy(void*, void*, int);
void  xstrncpy(char*, char*, int);
uint  escapeChar(char**);
FILE* xfopen(char*, char*);
void  xfclose(FILE*);

// vector.c
typedef struct _vector Vector;
struct _vector{
	int    solt;
	int    item;
	void** data;
};

void pushToVector(Vector*, void*);
void deleteVector(Vector*);

// buffer.c
typedef struct _buffer Buffer;
struct _buffer{
	char*   filename;
	int     nalloc;
	int     nchars;
	char    data[0];
};

Buffer* readFileToBuffer(char*);
void deleteBuffer(Buffer*);

#include "symbol.h"
#include "string.h"
#include "scanner.h"
#include "declare.h"
#include "statement.h"

#endif