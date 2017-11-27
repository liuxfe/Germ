/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _XSTRING_H
#define _XSTRING_H

typedef struct _string String;
struct _string{
	Symbol* symbol;
	String* next;
	uint	hash;
	uint	nalloc;
	uint	nchars;
	char	data[0];
};

String* scanStringLiteral(char**);
String* lookUpString(String*);
String* storeString(char*, int);
void printHashTable();

#endif