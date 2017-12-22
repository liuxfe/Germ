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

	if(ps->tokenList->tCode != Token_ID){
		ParseFatal(ps, "id");
	}
	name = ps->tokenList->sValue;
	eatToken(ps);

	param = SymbolAllocLVar(dt, name);
	
	SymbolAppend(ps, scope, param);
}

void _parseFuncDeclare(ParseState* ps, Dtype* dt, String* name, Vector* scope){
	int lparens;
	Token* token;
	Symbol* symbol = SymbolAllocFunc(dt, name);

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
	if(!exceptToken(ps, ';')){	 // no function body
		exceptTokenDealError(ps, '{', "{");
		if(!exceptToken(ps, '}')){ // not empty function
			lparens = 1;
			symbol->funcTokens = ps->tokenList;
			token = ps->tokenList;
			while(lparens){
				token = token->tNext;
				if(token->tCode =='{'){
					lparens += 1;
				}
				if(token->tCode =='}'){
					lparens -= 1;
				}
			}
			ps->tokenList = token->tNext;
			token->tNext = TokenAlloc(Token_EOF);
		}
	}
	SymbolAppend(ps, scope, symbol);
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

	if(ps->tokenList->tCode != Token_ID){
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

	if(ps->tokenList->tCode != Token_ID){
		ParseFatal(ps, "id");
	}
	name = ps->tokenList->sValue;
	eatToken(ps);

	exceptTokenDealError(ps, ';', ";");

	symbol = SymbolAllocLVar(dt, name);
	SymbolAppend(ps, scope, symbol);
}