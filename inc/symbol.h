/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_SYMBOL_H
#define _ToHack_CL_SYMBOL_H

typedef struct _symbol Symbol;
struct _symbol{
	uint             sType;
	String*          sName;
	Symbol*          sScope;
	union{
	    struct{
	        Vector    modPackage;
	        Vector    modImports;			// 模块
	        Vector    modSymbols;
	    };
	    struct{
	        DataType* varDataType;
	    };
	};
};

/* values of sType*/
enum {
	ST_Module,
	ST_Variable,
};

Symbol* newSymbol(uint);

#endif