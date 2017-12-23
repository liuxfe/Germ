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

Symbol* parseFunctionDeclare(ParseState* ps, Dtype* dt, String* name){
	Symbol* symbol = SymbolAllocFunction(name, dt);

	if(!ParseExceptToken(ps, Token_rparen)){
	    repeat:
		_parseFuncParam(ps, &symbol->funcParam);
		if(ParseExceptToken(ps, Token_comma)){
			goto repeat;
		}
		ParseMatchToken(ps, Token_rparen);
	}

	if(!ParseExceptToken(ps, Token_semicon)){	 // no function body
		ParseMatchToken(ps, Token_lbrace);
		while(!ParseExceptToken(ps, Token_rbrace)){ // not empty function
			ParseInternalStmt(ps, symbol);
		}
	}

	return symbol;
}

Symbol* parseVariableDeclare(ParseState* ps, Dtype* dt, String* name){
	ParseMatchToken(ps, Token_semicon);

	return SymbolAllocVariable(name, dt, ST_GlobalVar);
}

Symbol* ParseExternalDeclare(ParseState* ps){
	Dtype* dt;
	String* name;

	dt = ParseDtype(ps);
	if(!dt){
		ParseFatal(ps, "type");
	}

	name = ParseExceptTokenTD(ps);

	if(ParseExceptToken(ps, Token_lparen)){
		return parseFunctionDeclare(ps, dt, name);
	} else{
		return parseVariableDeclare(ps, dt, name);
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