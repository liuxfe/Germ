/* Copyright (c) 2017 Tohack<tohack@foxmail.com>. All Rights Reserved. */

#include "main.h"

void _parseFuncParam(ParseState* ps, Vector* scope){
	Dtype* dt;
	Symbol* param;

	dt = ParseDtype(ps);
	if(!dt){
		ParseFatal(ps, "type");
	}

	param = SymbolAllocVariable(ParseExceptTokenTD(ps), dt, ST_ParamVar);

	SymbolAppend(ps, scope, param);
}

void _parseFuncDeclare(ParseState* ps, Dtype* dt, String* name, Vector* scope){
	Symbol* symbol = SymbolAllocFunction(name, dt);

	if(exceptToken(ps, Token_rparen)){
		goto param_over;
	}

    param_repeat:
	_parseFuncParam(ps, &symbol->funcParam);
	if(exceptToken(ps, Token_comma)){
		goto param_repeat;
	}
	ParseMatchToken(ps, Token_rparen);

   param_over:
	if(!exceptToken(ps, Token_semicon)){	 // no function body
		ParseMatchToken(ps, Token_lbrace);
		while(!exceptToken(ps, Token_rbrace)){ // not empty function
			ParseInternalStmt(ps, symbol);
		}
	}
	SymbolAppend(ps, scope, symbol);
}

void _parseVarDeclare(ParseState* ps, Dtype* dt, String* name, Vector* scope){
	ParseMatchToken(ps, Token_semicon);

	Symbol* symbol = SymbolAllocVariable(name, dt, ST_GlobalVar);
	SymbolAppend(ps, scope, symbol);
}

void ParseExternalDeclare(ParseState* ps, Vector* scope){
	Dtype* dt;
	String* name;

	dt = ParseDtype(ps);
	if(!dt){
		ParseFatal(ps, "type");
	}

	name = ParseExceptTokenTD(ps);

	if(exceptToken(ps, Token_lparen)){
		_parseFuncDeclare(ps, dt, name, scope);
	} else{
		_parseVarDeclare(ps, dt, name, scope);
	}
}

void ParseInternalDeclare(ParseState* ps, Dtype* dt, Vector* scope){
	String* name;
	Symbol* symbol;

	name = ParseExceptTokenTD(ps);

	ParseMatchToken(ps, Token_semicon);

	symbol = SymbolAllocVariable(name, dt, ST_LocalVar);
	SymbolAppend(ps, scope, symbol);
}