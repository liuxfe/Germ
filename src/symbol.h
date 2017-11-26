/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _SYMBOL_H
#define _SYMBOL_H

struct _symStr{
	struct _symbol* symList;
	struct _symStr* hashNext;
	uint            hashKey;
	char            data[0];
};
typedef struct _symStr symStr;

struct _symbol{
	symStr* keystr;
	struct _symbol symNext;
	struct _symbol symScope;
};
typedef struct _symbol symbol;


uint hashValue(char*, char*);
symStr* newSymStr(char*, char*, uint);
symStr* lookUpSymStr(char*, char*, uint);
symStr* insertSymStr(char*, char*);
#endif