/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

Symbol* SymbolAlloc(int type){
	Symbol* ret;

	ret = Xmalloc(sizeof(Symbol), __FILE__, __LINE__);
	ret->sType = type;

	return ret;
}

void SymbolFree(Symbol* s){
	Xfree(s, __FILE__, __LINE__);
}

/* Append symbol to its scope */
void SymbolAppend(ParseState* ps, Vector* scope, Symbol* symbol){
	Symbol* s;
	int i;

	for(i=0; i<scope->item; i+=1){
		s = scope->data[i];
		if(s->sName != symbol->sName){
			continue;
		}
		Error(ps->filename, ps->tokenList->tLine, "redefined (%s)", symbol->sName->data);
	}
	VectorPush(scope, symbol);
}

void SymbolDump(Symbol* symbol, int indent){
	String* str;
	char tmp[80];
	int i;

	for(i=0; i<indent; i+=1){
		tmp[i]=' ';
	}
	tmp[i]=0;

	switch(symbol->sType){
	    case ST_Module:
		printf("%sModule: %s\n", tmp, symbol->sName->data);
		printf("%s  package: ", tmp);
		for(i=0; i<symbol->modPackage.item; i+=1){
			str=symbol->modPackage.data[i];
			printf("%s.", str->data);
		}
		printf("\b\n");
		for(i=0; i< symbol->modSymbols.item; i+=1){
			SymbolDump(symbol->modSymbols.data[i], indent+2);
		}
		break ;
	    case ST_Variable:
		printf("%sVariable: %s\n", tmp, symbol->sName->data);
		break ;
	    case ST_Function:
		printf("%sFunciton: %s\n", tmp, symbol->sName->data);
		for(i=0; i< symbol->funcParam.item; i+=1){
			SymbolDump(symbol->funcParam.data[i], indent+2);
		}
		break;
	    case ST_FuncParam:
		printf("%sParam: %s\n", tmp, symbol->sName->data);
		break;
	}
	return ;
}