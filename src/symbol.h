/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _SYMBOL_H
#define _SYMBOL_H

union _symValue{
	uint i;
};
typedef union _symValue SymValue;

struct _symbol{
	uint     symType;
	SymValue symValue;
	struct _symbol symNext;
	struct _symbol symScope;
};
typedef struct _symbol Symbol;

/* values of symType*/
enum {
	ST_KeyWord = 100,
};

void initKeyWordSymbol();

#endif