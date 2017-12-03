/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _SYMBOL_H
#define _SYMBOL_H

typedef struct _symbol Symbol;
struct _symbol{
	uint           sType;
	Symbol*        sScope;
	String*        sID;
};

typedef struct _variableSymbol{
	uint           sType;
	Symbol*        sScope;
	String*        szID;
} VariableSymbol;

/* values of symType*/
enum {
	ST_KeyWord = 100,
};

Symbol* newSymbol(uint);

#endif