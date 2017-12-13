/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

void parseFuncParam(ParseState* ps, Vector* scope){
	Dtype* dt;
	String* name;
	Symbol* param;

	dt = ParseDtype(ps);
	if(!dt){
		ParseFatal(ps, "type");
	}

	if(ps->tokenList->tCode != TokenID){
		ParseFatal(ps, "id");
	}
	name = ps->tokenList->sValue;
	eatToken(ps);

	param = SymbolAlloc(ST_FuncParam);
	param->paramDtype = dt;
	param->sName = name;

	SymbolAppend(ps, scope, param);
}

void parseFuncDeclare(ParseState* ps, Dtype* dt, String* name, Vector* scope){
	Symbol* symbol;

	symbol = SymbolAllocFunc(dt, name);

	if(exceptToken(ps, ')')){
		goto param_over;
	}

    param_repeat:
	parseFuncParam(ps, &symbol->funcParam);
	if(exceptToken(ps, ',')){
		goto param_repeat;
	}
	exceptTokenDealError(ps, ')', ")");

   param_over:
	if(exceptToken(ps, ';')){	// no function body
		SymbolAppend(ps, scope, symbol);
	} else{				// has function body
		exceptTokenDealError(ps, '{', "{");
		while(!exceptToken(ps, '}')){
			eatToken(ps);
		}
		SymbolAppend(ps, scope, symbol);
	}
}

void parseVarDeclare(ParseState* ps, Dtype* dt, String* name, Vector* scope){
	Symbol* symbol;
	
	exceptTokenDealError(ps, ';', ";");

	symbol = SymbolAllocVar(dt, name);
	SymbolAppend(ps, scope, symbol);
}

void ParseExternalDeclare(ParseState* ps, Vector* scope){
	Dtype* dt;
	String* name;

	dt = ParseDtype(ps);
	if(!dt){
		ParseFatal(ps, "type");
	}

	if(ps->tokenList->tCode != TokenID){
		ParseFatal(ps, "id");
	}
	name = ps->tokenList->sValue;
	eatToken(ps);

	if(exceptToken(ps,'(')){
		parseFuncDeclare(ps, dt, name, scope);	
	} else{
		parseVarDeclare(ps, dt, name, scope);
	}
}