/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#ifndef _ToHack_CL_SYMBOL_H
#define _ToHack_CL_SYMBOL_H

typedef struct _symbol{
	int               sType;
	String*           sName;
	union{
	    struct{			// 模块
	        Vector    modPackage;
	        Vector    modSymbols;
	    };
	    struct{			// 变量
	        Dtype*    varDtype;
	    };
	    struct{			// 函数
	        Dtype*    funcRetType;
	        Vector    funcParam;
	    };
	    struct{
	    	Dtype*    paramDtype;
	    };
	};
} Symbol;

/* values of sType*/
enum {
	ST_Module,
	ST_Variable,
	ST_Function,
	ST_FuncParam,
};

Symbol* SymbolAlloc(int);
Symbol* SymbolAllocVar(Dtype*, String*);
Symbol* SymbolAllocFunc(Dtype*, String*);
void SymbolFree(Symbol*);
void SymbolDump(Symbol*, int);
void SymbolAppend(ParseState*, Vector*, Symbol*);

#endif