/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _SYMBOL_H
#define _SYMBOL_H

typedef union _symbolValue symbolValue;
union _symbolValue{
	uint i;
};

// defined at xstring.h
typedef struct _string String;

typedef struct _symbol Symbol;
struct _symbol{
	uint           sType;
	Symbol*        sNext;
	Symbol*        sScope;
	String*        sID;
	symbolValue    sValue;
};

/* values of symType*/
enum {
	ST_KeyWord = 100,
};

Symbol* newSymbol(uint);

#endif