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

#define true  1
#define false 0

// xrourine.c
FILE* xfopen(char*, char*);
void  xfclose(FILE*);
void* xmalloc(uint);
void  xfree(void*);
void  xmemcpy(void*, void*, int);
int   xstrlen(char*);
int   xstrcmp(char*, char*);
void  xstrncpy(char*, char*, int);
int   xhex2num(char);

// vector.c
typedef struct _vector{
	int    solt;
	int    item;
	void** data;
} Vector;

void pushToVector(Vector*, void*);
void deleteVector(Vector*);

// string.c
typedef struct _string String;
struct _string{
	Vector  symbol;
	String* next;
	uint	hash;
	uint	nalloc;
	uint	nchars;
	char	data[0];
};

String* CreateDynString();
String* AppendCharToDynString(String*, char);
String* scanStringLiteral(char**);
String* lookUpString(String*);
String* storeString(char*, int);
void printHashTable();

#include "scanner.h"
#include "symbol.h"
#include "declare.h"
#include "statement.h"

extern int wantDumpTokenVector;

#endif