/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

void _parseFuncParam(ParseState* ps, Vector* scope){
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

	param = SymbolAllocLVar(dt, name);
	
	SymbolAppend(ps, scope, param);
}

void _parseFuncDeclare(ParseState* ps, Dtype* dt, String* name, Vector* scope){
	Symbol* symbol;

	symbol = SymbolAllocFunc(dt, name);

	if(exceptToken(ps, ')')){
		goto param_over;
	}

    param_repeat:
	_parseFuncParam(ps, &symbol->funcParam);
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
			ParseInternalStmt(ps, symbol);
		}
		SymbolAppend(ps, scope, symbol);
	}
}

void _parseVarDeclare(ParseState* ps, Dtype* dt, String* name, Vector* scope){
	Symbol* symbol;
	
	exceptTokenDealError(ps, ';', ";");

	symbol = SymbolAllocGVar(dt, name);
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
		_parseFuncDeclare(ps, dt, name, scope);
	} else{
		_parseVarDeclare(ps, dt, name, scope);
	}
}

void ParseInternalDeclare(ParseState* ps, Dtype* dt, Vector* scope){
	String* name;
	Symbol* symbol;

	if(ps->tokenList->tCode != TokenID){
		ParseFatal(ps, "id");
	}
	name = ps->tokenList->sValue;
	eatToken(ps);

	exceptTokenDealError(ps, ';', ";");

	symbol = SymbolAllocLVar(dt, name);
	SymbolAppend(ps, scope, symbol);
}