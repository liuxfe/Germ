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
	        Vector    modStmts;
	    };
	    struct{			// 变量
	        Dtype*    varDtype;
	    };
	    struct{			// 函数
	        Dtype*    funcRetType;
	        Token*    funcTokens;
	        Vector    funcParam;
	        Vector    funcLocal;
	    };
	    struct{
	    	Dtype*    lvarDtype;
	    };
	};
} Symbol;

/* values of sType*/
enum {
	ST_Module,
	ST_GlobalVar,
	ST_ParamVar,
	ST_LocalVar,
	ST_FieldVar,
	ST_Function,
};

Symbol* SymbolAlloc(int);
Symbol* SymbolAllocVariable(String*, Dtype*, int);
Symbol* SymbolAllocFunction(String*, Dtype*);
void SymbolFree(Symbol*);
void SymbolDump(Symbol*, int);
void SymbolAppend(ParseState*, Vector*, Symbol*);

#endif